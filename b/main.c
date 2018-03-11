#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

static char *tsunagariSources[] = {
    "src/areas/grove-house.cpp",
    "src/areas/secret-room.cpp",
    "src/world/clouds.cpp",
    "src/world/world.cpp",
    "TsunagariC/src/main.cpp",
    "TsunagariC/src/nbcl/nbcl.cpp",
    "TsunagariC/src/av/sdl2/error.cpp",
    "TsunagariC/src/av/sdl2/images.cpp",
    "TsunagariC/src/av/sdl2/music.cpp",
    "TsunagariC/src/av/sdl2/sounds.cpp",
    "TsunagariC/src/av/sdl2/window.cpp",
    "TsunagariC/src/core/animation.cpp",
    "TsunagariC/src/core/area.cpp",
    "TsunagariC/src/core/area-json.cpp",
    "TsunagariC/src/core/character.cpp",
    "TsunagariC/src/core/client-conf.cpp",
    "TsunagariC/src/core/cooldown.cpp",
    "TsunagariC/src/core/display-list.cpp",
    "TsunagariC/src/core/entity.cpp",
    "TsunagariC/src/core/formatter.cpp",
    "TsunagariC/src/core/images.cpp",
    "TsunagariC/src/core/jsons.cpp",
    "TsunagariC/src/core/log.cpp",
    "TsunagariC/src/core/measure.cpp",
    "TsunagariC/src/core/music-impl.cpp",
    "TsunagariC/src/core/music-worker.cpp",
    "TsunagariC/src/core/npc.cpp",
    "TsunagariC/src/core/overlay.cpp",
    "TsunagariC/src/core/player.cpp",
    "TsunagariC/src/core/resources.cpp",
    "TsunagariC/src/core/sounds.cpp",
    "TsunagariC/src/core/tile.cpp",
    "TsunagariC/src/core/viewport.cpp",
    "TsunagariC/src/core/window.cpp",
    "TsunagariC/src/core/world.cpp",
    "TsunagariC/src/data/data-area.cpp",
    "TsunagariC/src/data/data-world.cpp",
    "TsunagariC/src/data/inprogress.cpp",
    "TsunagariC/src/os/unix.cpp",
    "TsunagariC/src/pack/file-type.cpp",
    "TsunagariC/src/pack/pack-file.cpp",
    "TsunagariC/src/resources/pack.cpp",
    "TsunagariC/src/util/assert.cpp",
    "TsunagariC/src/util/bitrecord.cpp",
    "TsunagariC/src/util/dispatch-queue.cpp",
    "TsunagariC/src/util/dispatch-queue-impl.cpp",
    "TsunagariC/src/util/random.cpp",
    "TsunagariC/src/util/string2.cpp",
    "TsunagariC/src/util/transform.cpp",
};

static char *packToolSources[] = {
    "TsunagariC/src/os/unix.cpp",
    "TsunagariC/src/pack/file-type.cpp",
    "TsunagariC/src/pack/main.cpp",
    "TsunagariC/src/pack/pack-file.cpp",
    "TsunagariC/src/pack/pool.cpp",
    "TsunagariC/src/pack/ui-log.cpp",
    "TsunagariC/src/pack/walker.cpp",
    "TsunagariC/src/util/assert.cpp",
};

static char objectPrefixTsunagari[] = "CMakeFiles/tsunagari.dir/";
static char objectPrefixPackTool[] = "CMakeFiles/pack-tool.dir/";
static char objectSuffix[] = ".o";

static char *argv[] = {
        "/usr/bin/c++",
        "-ITsunagariC/deps/rapidjson/include",
        "-ITsunagariC/src",
        "-I/usr/include/SDL2",
        "-ITsunagariC/src/core",
        "-Isrc",
        "-std=c++11",
        "-msse4.2",
        "-Wall",
        "-Wextra",
        "-Wconversion",
        "-Wdeprecated",
        "-DBACKEND_SDL2",
        "-g",
        "-o",
        NULL,
        "-c",
        NULL,
        NULL,
};
static int argvO = 15;
static int argvC = 17;

static void run(char **argv) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        _exit(1);
    }

    if (pid == 0) {
        execve(argv[0], argv, environ);
        perror("execve");
        _exit(1);
    }

    pid = waitpid(pid, &status, 0);
    if (pid == -1) {
        perror("waitpid");
        _exit(1);
    }
    if (!WIFEXITED(status)) {
        _exit(1);
    }
    if (WEXITSTATUS(status)) {
        _exit(1);
    }
}

static void compile(char *prefix, int prefixLen, char *src, int srcLen) {
    char o[128];

    memcpy(o, prefix, prefixLen);
    memcpy(o+prefixLen, src, srcLen);
    memcpy(o+prefixLen+srcLen, objectSuffix, sizeof(objectSuffix)+1);

    argv[argvO] = o;
    argv[argvC] = src;

    run(argv);
}

static void link() {
    /*
    /usr/bin/c++
     -std=c++11
     -msse4.2
     -Wall
     -Wextra
     -Wconversion
     -Wdeprecated
     -DBACKEND_SDL2
     -g
     CMakeFiles/pack-tool.dir/TsunagariC/src/os/unix.cpp.o
     CMakeFiles/pack-tool.dir/TsunagariC/src/pack/file-type.cpp.o
     CMakeFiles/pack-tool.dir/TsunagariC/src/pack/main.cpp.o
     CMakeFiles/pack-tool.dir/TsunagariC/src/pack/pack-file.cpp.o
     CMakeFiles/pack-tool.dir/TsunagariC/src/pack/pool.cpp.o
     CMakeFiles/pack-tool.dir/TsunagariC/src/pack/ui-log.cpp.o
     CMakeFiles/pack-tool.dir/TsunagariC/src/pack/walker.cpp.o
     CMakeFiles/pack-tool.dir/TsunagariC/src/util/assert.cpp.o
     -o
     pack-tool
     -lpthread
    */
}

/*
/usr/bin/c++    -I/home/pdm/Source/TsunagariC-Testing/TsunagariC/deps/rapidjson/include -I/home/pdm/Source/TsunagariC-Testing/TsunagariC/src -I/usr/include/SDL2 -I/home/pdm/Source/TsunagariC-Testing/TsunagariC/src/core -I/home/pdm/Source/TsunagariC-Testing/src  -std=c++11 -msse4.2 -Wall -Wextra -Wconversion -Wdeprecated -DBACKEND_SDL2 -g   -o CMakeFiles/tsunagari.dir/TsunagariC/src/av/sdl2/sounds.cpp.o -c /home/pdm/Source/TsunagariC-Testing/TsunagariC/src/av/sdl2/sounds.cpp

/usr/bin/c++    -std=c++11 -msse4.2 -Wall -Wextra -Wconversion -Wdeprecated -DBACKEND_SDL2 -g   CMakeFiles/tsunagari.dir/src/ai/ai-wander.cpp.o CMakeFiles/tsunagari.dir/src/areas/big-tree.cpp.o CMakeFiles/tsunagari.dir/src/areas/cave01.cpp.o CMakeFiles/tsunagari.dir/src/areas/grove01.cpp.o CMakeFiles/tsunagari.dir/src/areas/grove04.cpp.o CMakeFiles/tsunagari.dir/src/areas/grove06.cpp.o CMakeFiles/tsunagari.dir/src/areas/grove-house.cpp.o CMakeFiles/tsunagari.dir/src/areas/secret-room.cpp.o CMakeFiles/tsunagari.dir/src/world/clouds.cpp.o CMakeFiles/tsunagari.dir/src/world/world.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/main.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/nbcl/nbcl.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/av/sdl2/error.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/av/sdl2/images.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/av/sdl2/music.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/av/sdl2/sounds.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/av/sdl2/window.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/animation.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/area.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/area-json.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/character.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/client-conf.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/cooldown.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/display-list.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/entity.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/formatter.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/images.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/jsons.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/log.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/measure.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/music-impl.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/music-worker.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/npc.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/overlay.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/player.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/resources.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/sounds.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/tile.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/viewport.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/window.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/core/world.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/data/data-area.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/data/data-world.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/data/inprogress.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/os/unix.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/pack/file-type.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/pack/pack-file.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/resources/pack.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/util/assert.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/util/bitrecord.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/util/dispatch-queue.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/util/dispatch-queue-impl.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/util/random.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/util/string2.cpp.o CMakeFiles/tsunagari.dir/TsunagariC/src/util/transform.cpp.o  -o tsunagari -lSDL2 -lSDL2_image -lSDL2 -lSDL2_mixer -lSDL2 -lpthread -lSDL2_image -lSDL2_mixer
/usr/bin/c++    -std=c++11 -msse4.2 -Wall -Wextra -Wconversion -Wdeprecated -DBACKEND_SDL2 -g   CMakeFiles/pack-tool.dir/TsunagariC/src/os/unix.cpp.o CMakeFiles/pack-tool.dir/TsunagariC/src/pack/file-type.cpp.o CMakeFiles/pack-tool.dir/TsunagariC/src/pack/main.cpp.o CMakeFiles/pack-tool.dir/TsunagariC/src/pack/pack-file.cpp.o CMakeFiles/pack-tool.dir/TsunagariC/src/pack/pool.cpp.o CMakeFiles/pack-tool.dir/TsunagariC/src/pack/ui-log.cpp.o CMakeFiles/pack-tool.dir/TsunagariC/src/pack/walker.cpp.o CMakeFiles/pack-tool.dir/TsunagariC/src/util/assert.cpp.o  -o pack-tool -lpthread
*/



int main(int argc, char* argv) {
    int i;
    char *src;

    for (i = 0; i < sizeof(tsunagariSources) / sizeof(tsunagariSources[0]); i++) {
        src = tsunagariSources[i];
        puts(src);
        compile(objectPrefixTsunagari, sizeof(objectPrefixTsunagari)-1, src, strlen(src));
    }

    for (i = 0; i < sizeof(packToolSources) / sizeof(packToolSources[0]); i++) {
        src = packToolSources[i];
        puts(src);
        compile(objectPrefixPackTool, sizeof(objectPrefixPackTool)-1, src, strlen(src));
    }

    return 0;
}
