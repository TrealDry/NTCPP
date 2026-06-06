# NTCPP - Nuclear Throne C++ Reconstruction

A reconstruction of **Nuclear Throne (version 98)** written in **C++17** with **SDL3**.

## About

NTCPP aims to recreate Nuclear Throne as close to 1:1 as possible - replicating the original game's behavior, feel, and mechanics. Performance optimization and modding support are secondary goals.

> **Note:** This project requires the original game's assets to run. See [ASSETS.md](ASSETS.md) for instructions on how to obtain them.

## Building

**Prerequisites:** CMake ≥ 4.2, a C++17-capable compiler, Git.

```bash
git clone --recurse-submodules https://github.com/TrealDry/NTCPP.git
cd NTCPP
cmake -B build -DBUILD_SHARED_LIBS=OFF
cmake --build build
```

## License

This project is licensed under the [MIT License](LICENSE.md).

Nuclear Throne is a game by [Vlambeer](https://www.vlambeer.com/). This project is an unofficial fan reconstruction and is not affiliated with or endorsed by Vlambeer.

## Contacts

[My Discord Server](https://discord.gg/qFMn5VvwCB)
