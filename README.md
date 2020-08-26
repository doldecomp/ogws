# Wii Sports

This repo contains a WIP decompilation of Wii Sports (US, revision 1).

## Required tools

* gcc
* devkitPro

## Build instructions

1. Obtain a clean DOL of Wii Sports (US Rev 1), place it in `include` and name it `baserom.dol`.

2. Obtain version 3.0 of `mwcceppc.exe` and `mwldeppc.exe` and place them in `tools`.

3. Obtain version 2.7 of `mwcceppc.exe` and `mwldeppc.exe` and place them in `tools/old`.

4. Obtain `powerpc-eabi-as.exe` from devkitPPC and place it in `tools`.

5. Run `make`.

## Contributions

Contributions and PRs are welcome.
