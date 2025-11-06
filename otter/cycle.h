#ifndef CYCLE_H
#define CYCLE_H

static inline unsigned long rdcycle(void) {
    unsigned long x;
    asm volatile ("rdcycle %0" : "=r"(x));
    return x;
}

#endif
