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

#ifndef IMAGE__H__
#define IMAGE__H__

#include <libgen.h>
#include "png/png.h"

void rawImageWrite(const char* outpath, uint8_t* raw, int size);

class Image {
public:
  Image(const char* filepath);
  virtual ~Image();

  inline void save(const char* outpath) {
    saveImage(outpath);
  }

  void rawImage(const char* outpath);
  inline uint8_t* getImage() const { return m_buffer; }
  inline uint32_t getWidth() const { return m_width; }
  inline uint32_t getHeight() const { return m_height; }
  inline int getSize() const { return m_size; }

protected:
  char* m_filename;
  uint8_t* m_buffer;
  uint32_t m_width;
  uint32_t m_height;
  uint32_t m_size;  // in bytes
  int m_error_code;

  virtual void loadImage() = 0;
  virtual void saveImage(const char* filename) = 0;
};

// ----------------------------------------------------------------------------
/**
 * PNG image writing: @see http://www.labbookpages.co.uk/software/imgProc/libPNG.html
 */
void savePNGImage(const char* outpath, uint8_t* raw, int w, int h, int size);

class PNGImage : public Image {
  friend void savePNGImage(const char* outpath, uint8_t* raw, int w, int h, int size);
public:
  PNGImage(const char* filepath);
  PNGImage(uint8_t* raw);
  virtual ~PNGImage();

private:
  static void callback_read_file(png_structp png, png_bytep data, png_size_t size);

  PNGImage();  // for save purposes only
  void loadImage() override final;
  void saveImage(const char* filename) override final;
};

/**
 * Error codes (PNG):
 *
 * 1 - assets->open() failed
 * 2 - assets->read() header failed
 * 3 - png_sig_cmp() failed, wrong header of PNG file
 * 4 - png_create_read_struct() failed
 * 5 - png_create_info_struct() failed
 * 6 - setjmp(png_jmpbuf()) failed
 * 7 - png_get_rowbytes() failed
 * 8 - image_buffer allocation failed
 * 9 - row_ptrs allocation failed
 * 10 - fopen() failed
 * 11 - fread() for header of PNG file failed
 */

#endif /* IMAGE__H__ */

