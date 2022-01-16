# Wii Sports [![Discord Badge]][Discord]

*A* ***WIP*** *decompilation of the* ***1st*** *revision of the* ***US*** *version.*

<br>

---

<br>

## Building

### Requirements

- **[DevKitPro]**

- **[GCC]**

    ```sh
    pacman -S gcc
    ```

<br>

### Instructions

1. Obtain a clean **DOL** of `Wii Sports US rev1`.

2. Place it in the `include` folder with `baserom.dol` as it's name.

3. Obtain `mwcceppc.exe` & `mwldeppc.exe`.

    *Version : `3.0`*

4. Place them in `tools`.

5. Obtain  `mwcceppc.exe` & `mwldeppc.exe`.

    *Version : `2.7`*

6. Place them in `tools/old`.

7. Obtain `powerpc-eabi-as.exe` from **[DevKitPPC]**.

8. Place it in `tools`.

9. Run the **Make** command :

    ```sh
    make
    ```

<br>

---

<br>

## Contributions

*`Contributions` / `Pull Requests` are welcome !*


<!----------------------------------------------------------------------------->

[DevKitPro]: https://devkitpro.org/wiki/Getting_Started
[DevKitPPC]: https://wiibrew.org/wiki/DevkitPPC
[GCC]: https://gcc.gnu.org/

[Discord Badge]: https://img.shields.io/badge/Discord-7289DA?style=for-the-badge&logo=discord&logoColor=white
[Discord]: https://discord.gg/hKx3FJJgrV
