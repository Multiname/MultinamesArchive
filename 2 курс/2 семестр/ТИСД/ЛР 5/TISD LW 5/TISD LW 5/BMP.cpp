#include "BMP.h"

BMP::BMP(const std::string & file_path) : m_row_stride{0} {
    load(file_path);
}

void BMP::load(const std::string & file_path) {
    // открываем файловый поток в бинарном режиме
    std::ifstream input{file_path, std::ios::binary};

    // проверяем, открылся ли файл
    if (!input) throw std::runtime_error("Unable to open the input image file!");

    // считываем заголовочную структуру изображения
    input.read((char*)&m_file_header, sizeof(m_file_header));

    // проверяем формат изображения
    if (m_file_header.file_type != 0x4D42) throw std::runtime_error("Unrecognized file format!");

    // считываем информационный хэдер
    input.read((char*)&m_info_header, sizeof(m_info_header));

    // если изображение 32-битное, нужно проверить и считать ColorHeader
    if (m_info_header.bit_count == 32) {
        // проверям содержит ли файл ColorHeader (записывается только в 32-битные изображения)
        if (m_info_header.size >= (sizeof(InfoHeader) + sizeof(ColorHeader))) {
            // считываем ColorHeader
            input.read((char*)&m_color_header, sizeof(m_color_header));

            // проверяем, записаны ли пиксели в формате BGRA и является ли цветовое пространство sRGB
            _checkColorHeader(m_color_header);
        }
        // если не содержит - выбрасываем исключение
        else {
            std::cerr << "Warning! The file \"" << file_path << "\" does not seem to contain bit mask information\n";
            throw std::runtime_error("Error! Unrecognized file format!");
        }
    }

    // перемещаемся к началу пикселей
    input.seekg(m_file_header.offset_data, std::ifstream::beg);

    // в силу того, что некоторые фоторедакторы помещают в файл служебную информацию, которую можно спокойно игнорировать,
    // чтобы ничего не сбилось, нужно настроить размер информационного хэдера, размер файла и указать, откуда начинаются пиксели

    // если изображение 32-битное
    if (m_info_header.bit_count == 32) {
        // записываем размер информационного хэдера, учитывая ColorHeader
        m_info_header.size = sizeof(InfoHeader) + sizeof(ColorHeader);

        // записываем, через сколько байт от начала файла начинаются пиксели, учитывая ColorHeader
        m_file_header.offset_data = sizeof(FileHeader) + sizeof(InfoHeader) + sizeof(ColorHeader);
    }
    // если изображение 24-битное
    else {
        // записываем размер информационного хэдера
        m_info_header.size = sizeof(InfoHeader);

        // записываем, через сколько байт от начала файла начинаются пиксели
        m_file_header.offset_data = sizeof(FileHeader) + sizeof(InfoHeader);
    }
    // записываем размер файла (это не весь размер файла, а лишь то,
    // сколько занимают заголовочные структуры и служебная информация)
    m_file_header.file_size = m_file_header.offset_data;

    // если высота изображения задается отрицательным числом,
    // то отсчет пикселей ведется сверху-вниз, начиная в верхнем левом углу

    // если высота изображения задается положительным числом,
    // то отсчет пикселей ведется снизу-вверх, начиная в нижнем левом углу

    // данная программа берет за начало отсчета нижний левый угол

    // проверям высоту
    if (m_info_header.height < 0)
        throw std::runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");

    // выделям память для хранения информации о пикселях (ширина * высота * количество каналов)
    m_data.resize(m_info_header.width * m_info_header.height * m_info_header.bit_count / 8);

    // Формат изображения BMP предполагает, что каждая строка данных будет выровнена по границе четырех байтов или
    // дополнена нулями, если это не так. Для изображения с разрешением 32 бита на пиксель условие выравнивания всегда выполняется.
    // В случае изображений с разрешением 24 бита на пиксель условие выравнивания выполняется только в том случае,
    // если ширина изображения делится на 4, в противном случае нам нужно будет заполнить строки нулями.

    // если ширина изображения делится на 4
    if (m_info_header.width % 4 == 0) {
        // считываем информацию о пикселях
        input.read((char*)m_data.data(), m_data.size());

        // обновляем размер файла (добавляем к нему то, сколько занимает информация о пикселях)
        m_file_header.file_size += m_data.size();
    }
    // если ширина изображения не делится на 4
    else {
        // вычисляем width
        // (количество пикселей в строке * количество каналов = количество байт в строке (width))
        m_row_stride = m_info_header.width * m_info_header.bit_count / 8;

        // вычисляем line_stride
        uint32_t new_stride{_makeStrideAligned(4)};

        // выделяем память для отступа (line_padding)
        std::vector<uint8_t> padding_row(new_stride - m_row_stride);

        // проходимся по каждой строке пикселей
        for (int y = 0; y < m_info_header.height; ++y) {
            // считываем информацию об отступе в информацию о пикселях
            // m_data.data() - начало отсчета
            // m_row_stride - сколько нужно отсупить, чтобы попасть на начало отступа
            // y - поскольку в памяти компьютера информация хранится в виде последовательности байт (как одномерный массив),
            //     смена строки пикселей производится через умножение

            // изначально имеем пустой вектор m_data
            // сперва считываем в него информацию о имеющихся пикселях
            input.read((char*)(m_data.data() + m_row_stride * y), m_row_stride);

            // есть два варианта, как поступить с отступом:
            // 1) считать незначащие нули
            // 2) программно переместить указатель на следующую строку

            // потом считываем отступ
            input.read((char*)padding_row.data(), padding_row.size());
        }

        // обновляем размер файла (размер пикселей + высота изображения * размер отступа)
        m_file_header.file_size += m_data.size() + m_info_header.height * padding_row.size();

        m_info_header.size_image = m_info_header.width * m_info_header.height * m_info_header.bit_count / 8;
    }
}

void BMP::_checkColorHeader(ColorHeader &color_header) {
    ColorHeader expected_color_header{};

    // проверяем формат цвета, чтобы он соответствовал BGRA формату
    if (expected_color_header.red_mask   != color_header.red_mask   ||
        expected_color_header.blue_mask  != color_header.blue_mask  ||
        expected_color_header.green_mask != color_header.green_mask ||
        expected_color_header.alpha_mask != color_header.alpha_mask) {

        throw std::runtime_error("Unexpected color mask format! "
                                 "The program expects the pixel data to be in the BGRA format!");
    }

    // проверяем цветовое пространство, чтобы оно соответствовало sRGB
    if (expected_color_header.color_space_type != color_header.color_space_type) {
        throw std::runtime_error("Unexpected color space type! The program expects sRGB values");
    }
}

uint32_t BMP::_makeStrideAligned(uint32_t align_stride) const {
    // берем текущее количество байт в строке
    uint32_t new_stride{m_row_stride};

    // увеличиваем до тех пор, пока не будет делиться на 4
    while (new_stride % align_stride != 0) ++new_stride;

    return new_stride;
}

int32_t BMP::getWidth() const {
    return m_info_header.width;
}

int32_t BMP::getHeight() const {
    return m_info_header.height;
}

uint32_t BMP::getSizeImage() const {
    return m_info_header.size_image;
}