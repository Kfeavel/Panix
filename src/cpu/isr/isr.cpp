/**
 * File: isr.cpp
 * Author: Keeton Feavel and James Osborne
 */

#include "isr.h"

isr_t interruptHandlers[256];

const char splashScreen[8][32] = {
    " ___________________________ \n",
    "< Oops! Panix has panicked! >\n",
    " --------------------------- \n",
    "    \\   ^__^\n",
    "     \\  (**)\\_______\n",
    "        (__)\\       )\\/\\\n",
    "         U  ||----w |\n",
    "            ||     ||\n\n"
};

/* To print the message which defines every exception */
const char exceptionMessages[32][32] {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void irqInstall() {
    /* Enable interruptions */
    asm volatile("sti");
    /* IRQ0: timer */
    initTimer(50);
    /* IRQ1: keyboard */
    Keyboard::initialize();
}

/* Can't do this with a loop because we need the address
 * of the function names */
void isrInstall() {
    setIdtGate(0, (uint32_t) isr0);
    setIdtGate(1, (uint32_t) isr1);
    setIdtGate(2, (uint32_t) isr2);
    setIdtGate(3, (uint32_t) isr3);
    setIdtGate(4, (uint32_t) isr4);
    setIdtGate(5, (uint32_t) isr5);
    setIdtGate(6, (uint32_t) isr6);
    setIdtGate(7, (uint32_t) isr7);
    setIdtGate(8, (uint32_t) isr8);
    setIdtGate(9, (uint32_t) isr9);
    setIdtGate(10, (uint32_t) isr10);
    setIdtGate(11, (uint32_t) isr11);
    setIdtGate(12, (uint32_t) isr12);
    setIdtGate(13, (uint32_t) isr13);
    setIdtGate(14, (uint32_t) isr14);
    setIdtGate(15, (uint32_t) isr15);
    setIdtGate(16, (uint32_t) isr16);
    setIdtGate(17, (uint32_t) isr17);
    setIdtGate(18, (uint32_t) isr18);
    setIdtGate(19, (uint32_t) isr19);
    setIdtGate(20, (uint32_t) isr20);
    setIdtGate(21, (uint32_t) isr21);
    setIdtGate(22, (uint32_t) isr22);
    setIdtGate(23, (uint32_t) isr23);
    setIdtGate(24, (uint32_t) isr24);
    setIdtGate(25, (uint32_t) isr25);
    setIdtGate(26, (uint32_t) isr26);
    setIdtGate(27, (uint32_t) isr27);
    setIdtGate(28, (uint32_t) isr28);
    setIdtGate(29, (uint32_t) isr29);
    setIdtGate(30, (uint32_t) isr30);
    setIdtGate(31, (uint32_t) isr31);

    /* Remap the PIC */
    setPortByte(0x20, 0x11);
    setPortByte(0xA0, 0x11);
    setPortByte(0x21, 0x20);
    setPortByte(0xA1, 0x28);
    setPortByte(0x21, 0x04);
    setPortByte(0xA1, 0x02);
    setPortByte(0x21, 0x01);
    setPortByte(0xA1, 0x01);
    setPortByte(0x21, 0x0);
    setPortByte(0xA1, 0x0); 

    /* Install the IRQs */
    setIdtGate(32, (uint32_t)irq0);
    setIdtGate(33, (uint32_t)irq1);
    setIdtGate(34, (uint32_t)irq2);
    setIdtGate(35, (uint32_t)irq3);
    setIdtGate(36, (uint32_t)irq4);
    setIdtGate(37, (uint32_t)irq5);
    setIdtGate(38, (uint32_t)irq6);
    setIdtGate(39, (uint32_t)irq7);
    setIdtGate(40, (uint32_t)irq8);
    setIdtGate(41, (uint32_t)irq9);
    setIdtGate(42, (uint32_t)irq10);
    setIdtGate(43, (uint32_t)irq11);
    setIdtGate(44, (uint32_t)irq12);
    setIdtGate(45, (uint32_t)irq13);
    setIdtGate(46, (uint32_t)irq14);
    setIdtGate(47, (uint32_t)irq15);

    setIdt(); /* Load with ASM */
}

void isrHandler(registers_t r) {
    /* TODO: Write a panic message. Maybe animate it? */
    Screen::clearScreen();
    printKernelPanicSplash();
    Screen::kprint((char*) "\n");
    Screen::kprint((char*) exceptionMessages[r.interruptNumber]);
    Screen::kprint((char*) "\n");
    asm volatile("hlt");
}

void registerInterruptHandler(uint8_t n, isr_t handler) {
    interruptHandlers[n] = handler;
}

void irqHandler(registers_t r) {
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    
    /* slave */
    if (r.interruptNumber >= 40) {
        setPortByte(0xA0, 0x20);
    }
    /* master */
    setPortByte(0x20, 0x20); 

    /* Handle the interrupt in a more modular way */
    if (interruptHandlers[r.interruptNumber] != 0) {
        isr_t handler = interruptHandlers[r.interruptNumber];
        handler(r);
    }
}

void printKernelPanicSplash() {
    Screen::clearScreen();
    for (int i = 0; i < 8; i++) {
        Screen::kprint((char*) splashScreen[i]);
    }
}