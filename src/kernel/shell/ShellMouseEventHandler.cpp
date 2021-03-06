/**
 * @file ShellMouseEventHandler.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <kernel/shell/ShellMouseEventHandler.hpp>

ShellMouseEventHandler::ShellMouseEventHandler() {}

void ShellMouseEventHandler::onMouseDown(uint8_t button) {
    kprint("Mouse down event.\n");
}

void ShellMouseEventHandler::onMouseUp(uint8_t button) {
    kprint("Mouse up event.\n");
}

void ShellMouseEventHandler::onActivate() {
    uint16_t* videoMemory = (uint16_t*) 0xb8000;
    x = 40;
    y = 12;
    videoMemory[80 * y + x] = (videoMemory[80 * y + x] & 0x0F00) << 4
                            | (videoMemory[80 * y + x] & 0xF000) >> 4
                            | (videoMemory[80 * y + x] & 0x00FF);
}

void ShellMouseEventHandler::onMouseMove(int xoffset, int yoffset) {
    static uint16_t* videoMemory = (uint16_t*) 0xb8000;
    videoMemory[80 * y + x] = (videoMemory[80 * y + x] & 0x0F00) << 4
                            | (videoMemory[80 * y + x] & 0xF000) >> 4
                            | (videoMemory[80 * y + x] & 0x00FF);
    x += xoffset;
    if (x >= 80) {
        x = 79;
    }
    if (x < 0) {
        x = 0;
    }
    y += yoffset;
    if (y >= 25) {
        y = 24;
    }
    if (y < 0) {
        y = 0;
    }

    videoMemory[80 * y + x] = (videoMemory[80 * y + x] & 0x0F00) << 4
                            | (videoMemory[80 * y + x] & 0xF000) >> 4
                            | (videoMemory[80 * y + x] & 0x00FF);
}