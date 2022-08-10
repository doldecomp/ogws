
# Building

*How to setup & build this project.*

<br>

## Requirements

- **[DevKitPro]**

- **[GCC]**

    ```sh
    pacman -S gcc
    ```

<br>
<br>

## Instructions

<br>

1.  Obtain a clean **DOL** of  `Wii Sports US rev1` 

    <br>

2.  Place it in the  `include`  folder <br>
    with  `baserom.dol`  as it's name

    <br>

3.  Obtain  `mwcceppc.exe`  &  `mwldeppc.exe`

    *Version :  `3.0`*

    ⤷  Place them in  `tools`

    <br>

4.  Obtain  `mwcceppc.exe`  &  `mwldeppc.exe` 

    *Version :  `2.7`*
    
    ⤷  Place them in  `tools/old`

    <br>

5.  Obtain  `powerpc-eabi-as.exe`  from **[DevKitPPC]** 

    <br>

6.  Place it in  `tools` 

    <br>

7.  Run the **Make** command :

    ```sh
    make
    ```

<br>


<!----------------------------------------------------------------------------->

[DevKitPro]: https://devkitpro.org/wiki/Getting_Started
[DevKitPPC]: https://wiibrew.org/wiki/DevkitPPC
[GCC]: https://gcc.gnu.org/
