asm float fabsf(float x) {
    nofralloc

    frsp f0, f1
    fabs f0, f0
    frsp f1, f0
    blr
}
