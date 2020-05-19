/**
 * @file kprint.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_KPRINT_HPP
#define PANIX_KPRINT_HPP

#include <types.hpp>

enum TTYColor {
    Black           = 0x0,
    Blue            = 0x1,
    Green           = 0x2,
    Cyan            = 0x3,
    Red             = 0x4,
    Magenta         = 0x5,
    Brown           = 0x6,
    LightGrey       = 0x7,
    DarkGrey        = 0x8,
    LightBlue       = 0x9,
    LightGreen      = 0xA,
    LightCyan       = 0xB,
    LightRed        = 0xC,
    LightMagenta    = 0xD,
    Yellow          = 0xE,
    White           = 0xF
};

inline uint16_t* videoMemory = (uint16_t*) 0xb8000;
/**
 * @brief Prints a given string to the kernel display.
 * 
 * @param str Input string to be printed.
 */
void kprint(const char* str);
/**
 * @brief Prints a given string to a particular coordinate in the kernel display.
 * 
 * @param str Input string to be printed.
 * @param x X-coordinate of the kernel display.
 * @param y Y-coordinate of the kernel display.
 * @param resetCursor Determines whether or not the cursor should be reset to the starting position.
 */
void kprintAtPosition(const char* str, uint8_t x, uint8_t y, bool resetCursor = false);
/**
 * @brief Prints a hexidecimal address to the kernel console.
 * 
 * @param key Hexidecimal value to print.
 */
void kprintHex(uint8_t key);

/**
 * @brief Set the color of the text when the next kprint is called.
 * 
 * @param fore Foreground color
 * @param back Background color
 */
void kprintSetColor(TTYColor fore, TTYColor back);

#endif /* PANIX_KPRINT_HPP */