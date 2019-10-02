/**
 * @file kprint.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#include <lib/kprint.hpp>

uint8_t ttyCoordsX = 0;
uint8_t ttyCoordsY = 0;
uint8_t backColor = Black;
uint8_t foreColor = White;

void kprint(const char* str) {
    volatile uint16_t* where;
    uint16_t attrib = (backColor << 4) | (foreColor & 0x0F);
    // For each character in the string
    for(int i = 0; str[i] != '\0'; ++i) {
        switch(str[i]) {
            // Backspace
            case 0x08:
                if (ttyCoordsX > 0) {
                    ttyCoordsX--;
                }
                where = videoMemory + (ttyCoordsY * 80 + ttyCoordsX);
                *where = ' ' | (attrib << 8);
                break;
            // Newline
            case '\n':
                ttyCoordsX = 0;
                ttyCoordsY++;
                break;
            // Anything else
            default:
                where = videoMemory + (ttyCoordsY * 80 + ttyCoordsX);
                *where = str[i] | (attrib << 8);
                ttyCoordsX++;
                break;
        }
        // Move to the next line
        if(ttyCoordsX >= 80) {
            ttyCoordsX = 0;
            ttyCoordsY++;
        }
        // Clear the screen
        if(ttyCoordsY >= 25) {
            for(ttyCoordsY = 0; ttyCoordsY < 25; ttyCoordsY++) {
                for(ttyCoordsX = 0; ttyCoordsX < 80; ttyCoordsX++) {
                    where = videoMemory + (ttyCoordsY * 80 + ttyCoordsX);
                    *where = ' ' | (attrib << 8);
                }
            }
            ttyCoordsX = 0;
            ttyCoordsY = 0;
        }
    }
}

void kprintAtPosition(const char* str, uint8_t positionX, uint8_t positionY, bool resetCursor) {
    volatile uint16_t* where;
    uint16_t attrib = (backColor << 4) | (foreColor & 0x0F);
    for(int i = 0; str[i] != '\0'; ++i) {
        switch(str[i]) {
            // Backspace
            case 0x08:
                if (positionX > 0) {
                    positionX--;
                }
                where = videoMemory + (positionY * 80 + positionX);
                *where = ' ' | (attrib << 8);
                break;
            // Newline
            case '\n':
                positionX = 0;
                positionY++;
                break;
            // Anything else
            default:
                where = videoMemory + (positionY * 80 + positionX);
                *where = str[i] | (attrib << 8);
                positionX++;
                break;
        }
        // Move to the next line
        if(positionX >= 80) {
            positionX = 0;
            positionY++;
        }
        // Clear the screen
        if(positionY >= 25) {
            for(positionY = 0; positionY < 25; positionY++) {
                for(positionX = 0; positionX < 80; positionX++) {
                    where = videoMemory + (positionY * 80 + positionX);
                    *where = ' ' | (attrib << 8);
                }
            }
            positionX = 0;
            positionY = 0;
        }
    }
    // If we are told to reset the cursor
    if (resetCursor) {
        ttyCoordsX = 0;
        ttyCoordsY = 0;
    }
}

void kprintHex(uint8_t key) {
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    kprint(foo);
}

void kprintSetColor(TTYColor fore, TTYColor back) {
    foreColor = fore;
    backColor = back;
}