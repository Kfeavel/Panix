/**
 * File: ports.cpp
 * Author: Keeton Feavel and James Osborne
 */

#include "ports.h"

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Learned this in Linux Systems Progamming, but keeping it here as a reminder
 * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
 * '"d" (port)': map the C variable '(port)' into e'd'x register
 * Inputs and outputs are separated by colons
 */
uint8_t getPortByte (uint16_t port) {
    uint8_t result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void setPortByte (uint16_t port, uint8_t data) {
    asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint16_t getPortWord (uint16_t port) {
    uint16_t result;
    asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void setPortWord (uint16_t port, uint16_t data) {
    asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}