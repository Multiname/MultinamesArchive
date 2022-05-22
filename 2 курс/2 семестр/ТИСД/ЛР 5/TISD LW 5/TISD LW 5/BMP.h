#ifndef BMP_H
#define BMP_H

#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <string>

class BMP {
public:
    /// Конструктор с параметрами. Загружает растровое изображение с диска
    /// @param file_path путь к файлу изображения с расширением bmp
    explicit BMP(const std::string & file_path);

    /// Загрузка растрового изображения с диска
    /// @param file_path - путь для загрузки
    void load(const std::string & file_path);

    /// Получение ширины растрового изображения
    /// @return - текущая ширина изображения
    int32_t getWidth() const;

    /// Получение высоты растрового изображения
    /// @return - текущая высота изображения
    int32_t getHeight() const;

    uint32_t getSizeImage() const;

protected:
#pragma pack(push, 1)
    struct FileHeader {
        /// Отметка для отличия формата от других (сигнатура формата). Может содержать единственное значение 0x4D42
        uint16_t    file_type      { 0x4D42 };

        /// Размер файла в байтах
        uint32_t    file_size      { 0 };

        /// Зарезервированное поле. Всегда должно содержать ноль
        uint16_t    reserved1      { 0 };

        /// Зарезервированное поле. Всегда должно содержать ноль
        uint16_t    reserved2      { 0 };

        /// Положение пиксельных данных относительно начала данной структуры
        uint32_t    offset_data    { 0 };
    };
#pragma pack(pop)

    struct InfoHeader {
        /// Размер данной структуры в байтах, указывающий также на версию структуры
        uint32_t    size                { 0 };

        /// Ширина растрового изображения в пикселях
        int32_t     width               { 0 };

        /// Высота растрового изображения в пикселях
        int32_t     height              { 0 };

        /// Количество цветовых плоскостей. Всегда должно быть равно единице
        uint16_t    planes              { 1 };

        /// Количество бит на пиксель
        uint16_t    bit_count           { 0 };

        /// Способ хранения пикселей
        uint32_t    compression         { 0 };

        /// Размер пиксельных данных в байтах
        uint32_t    size_image          { 0 };

        /// Количество пикселей на метр по горизонтали
        int32_t     x_pixels_per_meter  { 0 };

        /// Количество пикселей на метр по вертикали
        int32_t     y_pixels_per_meter  { 0 };

        /// Количество цветов в цветовой палитр
        uint32_t    colors_used         { 0 };

        /// Цвета, используемые растровым изображением
        uint32_t    colors_important    { 0 };
    };

    struct ColorHeader {
        /// Битовая маска для канала красного
        uint32_t    red_mask            { 0x00ff0000 };

        /// Битовая маска для канала зеленого
        uint32_t    green_mask          { 0x0000ff00 };

        /// Битовая маска для канала синего
        uint32_t    blue_mask           { 0x000000ff };

        /// Битовая маска для альфа-канала
        uint32_t    alpha_mask          { 0xff000000 };

        /// Тип цветового пространства. По-умолчанию sRGB (0x73524742)
        uint32_t    color_space_type    { 0x73524742 };

        /// Неиспользуемые данные для цветового пространства sRGB
        uint32_t    unused[16]          { 0 };
    };

    /// Заголовочная структура текущего растрового изображения
    FileHeader              m_file_header;

    /// Информационная структура текущего растрового изображения
    InfoHeader              m_info_header;

    /// Цветовая структура текущего растрового изображения
    ColorHeader             m_color_header;

    /// Хранилище для информации о пикселях
    std::vector<uint8_t>    m_data;

    /// Количество значимых байт
    uint32_t                m_row_stride;

    /// Проверка формата цвета на соответствие форматам цветов
    /// @param color_header - ColorHeader с заданными битовыми масками и типом цветового пространства
    void        _checkColorHeader(ColorHeader & color_header);

    /// Выравнивание длины строки
    /// @param align_stride - коэффициент выравнивания
    /// @return - длина выравненной строки
    uint32_t    _makeStrideAligned(uint32_t align_stride) const;
};

#endif //BMP_H