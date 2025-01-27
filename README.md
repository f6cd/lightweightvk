LightweightVK [![Build Status](https://github.com/corporateshark/lightweightvk/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/corporateshark/lightweightvk/actions)
========================

LightweightVK is a deeply refactored fork of [IGL](https://github.com/facebook/igl) which is designed to run on top of Vulkan 1.3.

The main goals of LightweightVK:

1. **Lean.** Minimalistic API without bloat (no `std::vector`, `std::unordered_map` etc in the API).
2. **Bindless.** Utilize Vulkan 1.3+ dynamic rendering, descriptor indexing, and buffer device address features for modern API design.
3. **Agile.** A playground for experiments to enable quick exploration of ideas and adoption of Vulkan API changes.
Designed for rapid prototyping of Vulkan-based renderers.

There are no plans to keep this fork in sync with the upstream.

## Supported rendering backends

 * Vulkan 1.3

## Supported platforms

 * Linux
 * Windows

## API Support

|                          | Windows                    | Linux                      |
| ------------------------ | -------------------------- | -------------------------- |
| Vulkan 1.3               | :heavy_check_mark:         | :heavy_check_mark:         |

## Build

Before building, run the deployment scripts:

```
python3 deploy_content.py
python3 deploy_deps.py

```

These scripts download external third-party dependencies. Please check [Dependencies] for the full list.

* Windows

```
cd build
cmake .. -G "Visual Studio 17 2022"
```

* Linux

```
sudo apt-get install clang xorg-dev libxinerama-dev libxcursor-dev libgles2-mesa-dev libegl1-mesa-dev libglfw3-dev libglew-dev libstdc++-12-dev
cd build
cmake .. -G "Unix Makefiles"
```

## Screenshots

![image](.github/screenshot01.jpg)

## License

LightweightVK is released under the MIT license, see [LICENSE.md](./LICENSE.md) for the full text as well as third-party library
acknowledgements.
