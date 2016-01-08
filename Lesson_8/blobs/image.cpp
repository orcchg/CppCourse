/**
 * Copyright (c) 2015, Alov Maxim <alovmax@yandex.ru>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions
 * and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided with
 * the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to
 * endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include "image.h"
#include "logger.h"

Image::Image(const char* filepath)
  : m_filename(new char[128])
  , m_buffer(nullptr)
  , m_width(0)
  , m_height(0)
  , m_size(0)
  , m_error_code(0) {
  strcpy(m_filename, filepath);
}

Image::~Image() {
  delete [] m_filename;  m_filename = nullptr;
  delete [] m_buffer;  m_buffer = nullptr;
}

void Image::rawImage(const char* outpath) {
  rawImageWrite(outpath, m_buffer, m_size);
}

// ----------------------------------------------------------------------------
PNGImage::PNGImage(const char* filepath)
  : Image(filepath) {
  loadImage();
}

PNGImage::PNGImage()
  : Image("") {
  // used in global friend function 'saveImage()' only
}

PNGImage::~PNGImage() {
}

void PNGImage::loadImage() {
  FILE* file_descriptor = nullptr;
  png_byte header[8];
  png_structp png_ptr = nullptr;
  png_infop info_ptr = nullptr;
  png_byte* image_buffer = nullptr;
  png_bytep* row_ptrs = nullptr;
  png_int_32 row_size = 0;
  bool transparency = false;
  int error_code = 0;

  size_t header_size = sizeof(header);
  file_descriptor = std::fopen(m_filename, "rb");
  if (file_descriptor == nullptr) { error_code = 10; goto ERROR_PNG; }
  if (header_size != std::fread(header, 1, header_size, file_descriptor)) { error_code = 11; goto ERROR_PNG; }
  if (png_sig_cmp(header, 0, 8) != 0) { error_code = 3; goto ERROR_PNG; }

  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (png_ptr == nullptr) { error_code = 4; goto ERROR_PNG; }
  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == nullptr) { error_code = 5; goto ERROR_PNG; }

  png_set_read_fn(png_ptr, file_descriptor, callback_read_file);
  {
    int jump_code = 0;
    if ( (jump_code = setjmp(png_jmpbuf(png_ptr))) != 0) {
      ERR("PNGImage: setjump() returned code %i", jump_code);
      error_code = 6; goto ERROR_PNG;
    }
  }

  png_set_sig_bytes(png_ptr, 8);
  png_read_info(png_ptr, info_ptr);

  png_int_32 depth, color_type;
  png_uint_32 width, height;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &depth, &color_type, nullptr, nullptr, nullptr);
  m_width = width;  m_height = height;

  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
    png_set_tRNS_to_alpha(png_ptr);
    transparency = true;
  }

  if (depth < 8) {
    png_set_packing(png_ptr);
  } else {
    png_set_strip_16(png_ptr);
  }

  switch (color_type) {
    case PNG_COLOR_TYPE_PALETTE:
      png_set_palette_to_rgb(png_ptr);
      break;
    case PNG_COLOR_TYPE_GRAY:
      png_set_expand_gray_1_2_4_to_8(png_ptr);
      break;
    case PNG_COLOR_TYPE_GA:
      png_set_expand_gray_1_2_4_to_8(png_ptr);
      break;
    case PNG_COLOR_TYPE_RGB:
    case PNG_COLOR_TYPE_RGBA:
    default:
      break;
  }
  png_read_update_info(png_ptr, info_ptr);

  row_size = png_get_rowbytes(png_ptr, info_ptr);
  m_size = row_size * height;
  if (row_size <= 0) { error_code = 7; goto ERROR_PNG; }
  image_buffer = new (std::nothrow) png_byte[m_size];
  if (image_buffer == nullptr) { error_code = 8; goto ERROR_PNG; }

  row_ptrs = new (std::nothrow) png_bytep[height];
  if (row_ptrs == nullptr) { error_code = 9; goto ERROR_PNG; }
  for (int32_t i = 0; i < height; ++i) {
    row_ptrs[height - (i + 1)] = image_buffer + i * row_size;
  }
  png_read_image(png_ptr, row_ptrs);

  std::fclose(file_descriptor);
  png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
  delete [] row_ptrs;

  m_buffer = image_buffer;
  return;

  ERROR_PNG:
    m_error_code = error_code;
    ERR("Error while reading PNG file: %s, code %i", m_filename, m_error_code);
    std::fclose(file_descriptor);
    delete [] image_buffer;  image_buffer = nullptr;
    delete [] row_ptrs;  row_ptrs = nullptr;
    if (png_ptr != nullptr) {
      png_infop* info_ptr_p = info_ptr != nullptr ? &info_ptr : nullptr;
      png_destroy_read_struct(&png_ptr, info_ptr_p, nullptr);
    }
}

void PNGImage::callback_read_file(png_structp io, png_bytep data, png_size_t size) {
  FILE* file = (FILE*) png_get_io_ptr(io);
  if (size != std::fread(data, 1, size, file)) {
    std::fclose(file);
    png_error(io, "Error while reading PNG file (from callback_read_file()) !");
  }
}

// ----------------------------------------------------------------------------
inline void setRGB(png_byte *ptr, float val) {
  int v = (int)(val * 767);
  if (v < 0) v = 0;
  if (v > 767) v = 767;
  int offset = v % 256;

  if (v < 256) {
    ptr[0] = 0; ptr[1] = 0; ptr[2] = offset;
  } else if (v < 512) {
    ptr[0] = 0; ptr[1] = offset; ptr[2] = 255 - offset;
  } else {
    ptr[0] = offset; ptr[1] = 255 - offset; ptr[2] = 0;
  }
}

void PNGImage::saveImage(const char* outpath) {
  int error_code = 0;
  FILE* file_descriptor = nullptr;
  png_structp png_ptr = nullptr;
  png_infop info_ptr = nullptr;
  png_bytep row = nullptr;

  file_descriptor = fopen(outpath, "wb");
  if (file_descriptor == nullptr) { error_code = 101; goto ERROR_PNG_write; }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (png_ptr == nullptr) { error_code = 10; goto ERROR_PNG_write; }
  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == nullptr) { error_code = 5; goto ERROR_PNG_write; }

  if (setjmp(png_jmpbuf(png_ptr))) { error_code = 6; goto ERROR_PNG_write; }

  png_init_io(png_ptr, file_descriptor);

  // Write header (8 bit colour depth)
  png_set_IHDR(png_ptr, info_ptr, m_width, m_height,
        8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  // Allocate memory for one row (3 bytes per pixel - RGB)
  row = (png_bytep) malloc(3 * m_width * sizeof(png_byte));

  for (int y = 0; y < m_height; ++y) {
    for (int x = 0; x < m_width; ++x) {
      setRGB(&(row[x * 3]), m_buffer[y * m_width + x]);
    }
    png_write_row(png_ptr, row);
  }

  png_write_end(png_ptr, nullptr);

  ERROR_PNG_write:
    if (error_code != 0) {
      m_error_code = error_code;
      ERR("Error while writing PNG file: %s, code %i", outpath, m_error_code);
    }
    if (file_descriptor != nullptr) fclose(file_descriptor);
    if (info_ptr != nullptr) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    if (png_ptr != nullptr) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
    if (row != nullptr) free(row);
}

// ----------------------------------------------------------------------------
void rawImageWrite(const char* outpath, uint8_t* raw, int size) {
  FILE* file_descriptor = fopen(outpath, "wb");
  if (file_descriptor != nullptr) {
    fputs((const char*) raw, file_descriptor);
    fclose(file_descriptor);
  }
}

void savePNGImage(const char* outpath, uint8_t* raw, int w, int h, int size) {
  PNGImage image;
  image.m_buffer = new uint8_t[size];  // deep copy
  for (int i = 0; i < size; ++i) {
    image.m_buffer[i] = raw[i];
  }
  image.m_width = w;
  image.m_height = h;
  image.m_size = size;
  image.save(outpath);
}

