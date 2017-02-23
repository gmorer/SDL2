# SDL2 [![Build Status](https://travis-ci.org/gmorer/SDL2.svg?branch=master)](https://travis-ci.org/gmorer/SDL2)

## Dependencies

- SDL2
- SDL2\_ttf
- SDL2\_image

### Ubuntu

```sh
sudo apt update
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
```

if you get an error like:

```sh
# ...
E: Unable to locate package libssl2-dev
E: Unable to locate package libsdl2-ttf-dev
E: Unable to locate package libsdl2-image-dev
```

run the following commands:

```sh
sudo apt-add-repository -y ppa:zoogie/sdl2-snapshots
sudo apt update
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
```

### ArchLinux

```sh
sudo pacman -S sdl2 sdl2_ttf sdl2_image
```

## Installation

```sh
git clone https://github.com/gmorer/SDL2.git && cd SDL2 && make
```

## Usage

```sh
./line
```

## License

Released under the terms of the permissive [MIT license](LICENSE).
