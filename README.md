# TsunagariC-Testing

A tech demo world for [TsunagariC](https://github.com/pmer/TsunagariC).

## Setup

### Cloning

```bash
git clone --recursive https://github.com/pmer/TsunagariC-Testing.git
cd TsunagariC-Testing
```

### Acquiring `Autumn_Forest.oga`

From the root directory:

#### Method 1: Use `youtube-dl` and `ffmpeg`

```bash
# macOS
brew install youtube-dl
brew install --with-libvorbis ffmpeg
```

```bash
cd data/music
youtube-dl -x -f 22 -o Autumn_Forest.mp4 'https://www.youtube.com/watch?v=v2qOllkxwiw'
ffmpeg -i Autumn_Forest.m4a -c:a libvorbis Autumn_Forest.oga
cd ../..
```

#### Method 2: Download from `pdm.me`

```bash
# macOS
cd data/music
curl -O https://pdm.me/Autumn_Forest.oga
cd ../..
```

```bash
# Ubuntu
cd data/music
wget https://pdm.me/Autumn_Forest.oga
cd ../..
```

### Installing build and runtime dependencies

```bash
# macOS
brew install libgosu
```

### Building

From the root directory:

Compile:

```bash
# macOS
mkdir build-debug
cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j $(sysctl -n hw.ncpu)
cd ..
```

```bash
# Ubuntu
mkdir build-debug
cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j $(nproc)
cd ..
```

Build the resources:

```bash
TsunagariC/scripts/build-config.sh
TsunagariC/scripts/build-world.sh
```

Build the application bundle/install to bin:

```bash
# macOS
TsunagariC/scripts/build-bundle-debug.sh
```

```bash
# Ubuntu
cp build-debug/tsunagari bin/
```

### Running

#### Using a GUI file manager

On macOS, open `Tsunagari.app` in Finder.

On Ubuntu, open `bin/tsunagari` in Files.

#### Using a terminal

```bash
# macOS
Tsunagari.app/Contents/MacOS/Tsunagari
```

```bash
# Ubuntu
cd bin
./tsunagari
```

### Debugging

From the root directory:

```bash
# macOS
lldb Tsunagari.app/Contents/MacOS/Tsunagari
```

```bash
# Ubuntu
cd bin
gdb ./tsunagari
```

## TODO

- Windows instructions
