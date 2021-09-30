.include "macros.inc"

.section .ctors, "a"

.4byte 0x800a17b4 # eggFrustum
.4byte 0x800a1c2c # eggGXUtility
.4byte __sinit_$$3eggDrawHelper_cpp
