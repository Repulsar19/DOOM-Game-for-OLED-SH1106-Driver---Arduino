/*!
 * @file Adafruit_SSD1306.h
 *
 * This is part of for Adafruit's SSD1306 library for monochrome
 * OLED displays: http://www.adafruit.com/category/63_98
 *
 * These displays use I2C or SPI to communicate. I2C requires 2 pins
 * (SCL+SDA) and optionally a RESET pin. SPI requires 4 pins (MOSI, SCK,
 * select, data/command) and optionally a reset pin. Hardware SPI or
 * 'bitbang' software SPI are both supported.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries, with
 * contributions from the open source community.
 *
 * BSD license, all text above, and the splash screen header file,
 * must be included in any redistribution.
 *
 */

#ifndef _Adafruit_SH1106_H_
#define _Adafruit_SH1106_H_

#include "TWI_Master.h"
#include "string.h"
#include "constants.h"

/// The following "raw" color names are kept for backwards client compatability
/// They can be disabled by predefining this macro before including the Adafruit header
/// client code will then need to be modified to use the scoped enum values directly
#ifndef NO_ADAFRUIT_SH1106_COLOR_COMPATIBILITY
#define BLACK                     SH1106_BLACK    ///< Draw 'off' pixels
#define WHITE                     SH1106_WHITE    ///< Draw 'on' pixels
#define INVERSE                   SH1106_INVERSE  ///< Invert pixels
#endif
        /// fit into the SH1106_ naming scheme
#define SH1106_BLACK               0    ///< Draw 'off' pixels
#define SH1106_WHITE               1    ///< Draw 'on' pixels
#define SH1106_INVERSE             2    ///< Invert pixels

#define SH1106_MEMORYMODE          0x20 ///< See datasheet
#define SH1106_COLUMNADDR          0x21 ///< See datasheet
#define SH1106_PAGEADDR            0x22 ///< See datasheet
#define SH1106_SETCONTRAST         0x81 ///< See datasheet
#define SH1106_CHARGEPUMP          0x8D ///< See datasheet
#define SH1106_SEGREMAP            0xA0 ///< See datasheet
#define SH1106_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SH1106_DISPLAYALLON        0xA5 ///< Not currently used
#define SH1106_NORMALDISPLAY       0xA6 ///< See datasheet
#define SH1106_INVERTDISPLAY       0xA7 ///< See datasheet
#define SH1106_SETMULTIPLEX        0xA8 ///< See datasheet
#define SH1106_DISPLAYOFF          0xAE ///< See datasheet
#define SH1106_DISPLAYON           0xAF ///< See datasheet
#define SH1106_COMSCANINC          0xC0 ///< Not currently used
#define SH1106_COMSCANDEC          0xC8 ///< See datasheet
#define SH1106_SETDISPLAYOFFSET    0xD3 ///< See datasheet
#define SH1106_SETDISPLAYCLOCKDIV  0xD5 ///< See datasheet
#define SH1106_SETPRECHARGE        0xD9 ///< See datasheet
#define SH1106_SETCOMPINS          0xDA ///< See datasheet
#define SH1106_SETVCOMDETECT       0xDB ///< See datasheet

#define SH1106_SETLOWCOLUMN        0x00 ///< Not currently used
#define SH1106_SETHIGHCOLUMN       0x10 ///< Not currently used
#define SH1106_SETSTARTLINE        0x40 ///< See datasheet

#define SH1106_EXTERNALVCC         0x01 ///< External display voltage source
#define SH1106_SWITCHCAPVCC        0x02 ///< Gen. display voltage from 3.3V

#define SH1106_RIGHT_HORIZONTAL_SCROLL              0x26 ///< Init rt scroll
#define SH1106_LEFT_HORIZONTAL_SCROLL               0x27 ///< Init left scroll
#define SH1106_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29 ///< Init diag scroll
#define SH1106_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A ///< Init diag scroll
#define SH1106_DEACTIVATE_SCROLL                    0x2E ///< Stop scroll
#define SH1106_ACTIVATE_SCROLL                      0x2F ///< Start scroll
#define SH1106_SET_VERTICAL_SCROLL_AREA             0xA3 ///< Set scroll range

/*! 
    @brief  Class that stores state and functions for interacting with
            SH1106 OLED displays.
*/
template <uint8_t WIDTH, uint8_t HEIGHT>
class Adafruit_SH1106 {
 public:
  Adafruit_SH1106() = default;

  ~Adafruit_SH1106(void) = default;

  bool      begin(uint8_t switchvcc=SH1106_SWITCHCAPVCC,
                 uint8_t i2caddr=0);
  void         display(void);
  void         clearDisplay(void);
  void         invertDisplay(bool i);
  void         drawPixel(int16_t x, int16_t y, uint16_t color);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  bool      getPixel(int16_t x, int16_t y);
  uint8_t     *getBuffer(void);
  void clearRect(uint8_t, uint8_t, uint8_t, uint8_t);
  void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);

 private:
  void         drawFastVLineInternal(int16_t x, int16_t y, int16_t h,
                 uint16_t color);
  void         sh1106_command1(uint8_t c);
  void         sh1106_commandList(const uint8_t *c, uint8_t n);

  uint8_t     buffer[WIDTH * ((HEIGHT + 7) / 8)];
  int8_t       i2caddr, vccstate, page_end;
};

template class Adafruit_SH1106<SCREEN_WIDTH, SCREEN_HEIGHT>;

#endif // _Adafruit_SH1106_H_
