#ifndef BMP_H
#define BMP_H

#include <iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <string>

class BMP {
public:
    explicit BMP(const std::string & file_path);

    void load(const std::string & file_path);
    void save(const std::string& file_path);

    void fillRegion(uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, uint8_t R, uint8_t G, uint8_t B, uint8_t A);

    int32_t getWidth() const;
    int32_t getHeight() const;
    uint32_t getSizeImage() const;

protected:
#pragma pack(push, 1)
    struct FileHeader {
        uint16_t    file_type      { 0x4D42 };
        uint32_t    file_size      { 0 };
        uint16_t    reserved1      { 0 };
        uint16_t    reserved2      { 0 };
        uint32_t    offset_data    { 0 };
    };
#pragma pack(pop)

    struct InfoHeader {
        uint32_t    size                { 0 };
        int32_t     width               { 0 };
        int32_t     height              { 0 };
        uint16_t    planes              { 1 };
        uint16_t    bit_count           { 0 };
        uint32_t    compression         { 0 };
        uint32_t    size_image          { 0 };
        int32_t     x_pixels_per_meter  { 0 };
        int32_t     y_pixels_per_meter  { 0 };
        uint32_t    colors_used         { 0 };
        uint32_t    colors_important    { 0 };
    };

    struct ColorHeader {
        uint32_t    red_mask            { 0x00ff0000 };
        uint32_t    green_mask          { 0x0000ff00 };
        uint32_t    blue_mask           { 0x000000ff };
        uint32_t    alpha_mask          { 0xff000000 };
        uint32_t    color_space_type    { 0x73524742 };
        uint32_t    unused[16]          { 0 };
    };

    FileHeader              m_file_header;
    InfoHeader              m_info_header;
    ColorHeader             m_color_header;
    std::vector<uint8_t>    m_data;
    uint32_t                m_row_stride;

    void        _checkColorHeader(ColorHeader & color_header);
    uint32_t    _makeStrideAligned(uint32_t align_stride) const;
    void        _writeHeaders(std::ofstream& stream);
    void        _writeHeadersAndData(std::ofstream& stream);
};

#endif //BMP_H