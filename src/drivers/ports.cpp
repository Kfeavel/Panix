/**
 * File: ports.cpp
 * Author: Keeton Feavel and James Osborne
 */

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Learned this in Linux Systems Progamming, but keeping it here as a reminder
 * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
 * '"d" (port)': map the C variable '(port)' into e'd'x register
 * Inputs and outputs are separated by colons
 */
unsigned char port_byte_in (unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in (unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
