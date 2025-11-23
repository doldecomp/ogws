# Wii Sports  

[![Build Status]][actions] [![Code Progress]][progress] [![Data Progress]][progress] [![Discord Badge]][discord]

[Build Status]: https://github.com/doldecomp/ogws/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/doldecomp/ogws/actions/workflows/build.yml
[Code Progress]: https://decomp.dev/doldecomp/ogws.svg?mode=shield&measure=code&label=Code
[Data Progress]: https://decomp.dev/doldecomp/ogws.svg?mode=shield&measure=data&label=Data
[progress]: https://decomp.dev/doldecomp/ogws
[Discord Badge]: https://img.shields.io/discord/727908905392275526?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.gg/hKx3FJJgrV

<!-- markdownlint-disable MD033 -->
[<img src="https://decomp.dev/doldecomp/ogws.svg?w=512&h=256" width="512" height="256" alt="A visual">][Progress]
<!-- markdownlint-enable MD033 -->

A work-in-progress decompilation of Wii Sports.

> [!IMPORTANT]
> This repository does **not** contain any game assets or assembly whatsoever.
An existing copy of the game is required.

Supported versions:

| Version         | SHA-1 hash                                 |
| --------------- | ------------------------------------------ |
| US (Revision 1) | `8bb422971b88b5551a37de98db69557df7b46637` |

## Getting Started

Once you have confirmed that your copy of the game is a supported version,
please dump your copy and follow the build instructions in [this document](docs/getting_started.md).

> [!TIP]
> Not sure which version you have?
>
> Enter the following button combination on the title screen using any remote:
>
> ```text
> A, D-Up, 2, D-Down, B, 1, 1, B, D-Left, A, D-Right
> ```

You should see information on the game's build date in either the bottom-left
or bottom-right corner of the screen.

Reference the following table to determine exactly which version you have:

| Build date  | Version         |
| ----------- | --------------- |
| 2006/10/07  | US (Revision 0) |
| 2007/07/05  | US (Revision 1) |

## Contributing

Thank you for your interest in the project! We ask that you please follow our
contribution guidelines outlined in [this document](docs/contributing.md) to
ensure consistency across the codebase and its documentation.

<!-- markdownlint-disable MD028 -->
> [!CAUTION]
> Please avoid utilizing leaked material! We want to stay as clean-room as
> possible, and have this repository be freely usable by other projects without
> the worry of being associated with leaks.
>
> "Leaked material" includes, but is not limited to:
>
> - Source code leaked online, pertaining to any software libraries linked
> within this game
> - Source code acquired through means only intended for licensed developers, such as a software development kit (SDK) distribution
>

> [!IMPORTANT]
> "Leaked material" does **NOT** include debugging information **left behind in
> retail games**, such as:
>
> - A linker or symbol map file
> - Debug builds of the executable
> - Binary object files (`*.o`), and static libraries (`*.a`) that may contain them
<!-- markdownlint-enable MD028 -->
