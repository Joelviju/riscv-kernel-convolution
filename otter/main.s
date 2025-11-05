# LEDS: 0x11080000
# SWITCHES: 0x11000000

.globl _start
.type _start, @function
_start:
    addi sp, sp, -4
    sw a0, 4(sp)
    # move image pointer and dimension into argument registers
    mv a0, s0
    # see 'draw.c'
    call run_img_proc
    lw a0, 4(sp)
    addi sp, sp, 4
    ret
