#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "arr.h"

extern char **environ;

static char exe_tsunagari[] = "tsunagari";
static char *sources_tsunagari[] = {
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

static char exe_pack_tool[] = "pack-tool";
static char *sources_pack_tool[] = {
    "TsunagariC/src/os/unix.cpp",
    "TsunagariC/src/pack/file-type.cpp",
    "TsunagariC/src/pack/main.cpp",
    "TsunagariC/src/pack/pack-file.cpp",
    "TsunagariC/src/pack/pool.cpp",
    "TsunagariC/src/pack/ui-log.cpp",
    "TsunagariC/src/pack/walker.cpp",
    "TsunagariC/src/util/assert.cpp",
};

static char object_prefix_tsunagari[] = "CMakeFiles/tsunagari.dir/";
static char object_prefix_pack_tool[] = "CMakeFiles/pack-tool.dir/";
static char object_suffix[] = ".o";

static char *object_argv[] = {
        "/usr/bin/c++",
        "-std=c++11",
        "-I/usr/include/SDL2",
        "-ITsunagariC/deps/rapidjson/include",
        "-ITsunagariC/src",
        "-Isrc",
        "-msse4.2",
        "-g",
};

static void print_argv(char **argv) {
    for (; *argv; argv++) {
        printf("%s ", *argv);
    }
    printf("\n");
}

static void run(char **argv) {
    pid_t pid;
    int status;

    if (getenv("VERBOSE")) {
        print_argv(argv);
    }

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

static void object(arr *cxxflags, char *prefix, int prefix_len, char *src, int src_len) {
    arr argv;
    char o[128], **ss;
    int i;

    memcpy(o, prefix, prefix_len);
    memcpy(o+prefix_len, src, src_len);
    memcpy(o+prefix_len+src_len, object_suffix, sizeof(object_suffix)+1);

    arr_construct_n(char *, &argv, 16);

    for (i = 0; i < sizeof(object_argv) / sizeof(object_argv)[0]; i++) {
        arr_push(char *, &argv, object_argv[i]);
    }

    for_each_in_arr(ss, cxxflags) {
        arr_push(char *, &argv, *ss);
    }

    arr_push(char *, &argv, "-c");
    arr_push(char *, &argv, src);
    arr_push(char *, &argv, "-o");
    arr_push(char *, &argv, o);
    arr_push(char *, &argv, NULL);

    run(arr_array(char *, &argv));

    arr_destroy(&argv);
}

static void exe(char *out, char **srcs) {
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

static void arr_split(arr *a, char *s) {
    char *space;

    if (!s) {
        return;
    }

    space = strchr(s, ' ');
    while (space) {
        if (space - s != 0) {
            arr_push(char *, a, strndup(s, space - s));
        }
        s = space + 1;
        space = strchr(s, ' ');
    }

    if (*s != '\0') {
        arr_push(char *, a, strdup(s));
    }
}

int main() {
    arr cxxflags;
    int i;
    char *src, **ss;

    arr_construct(&cxxflags);
    arr_split(&cxxflags, getenv("CXXFLAGS"));

    for (i = 0; i < sizeof(sources_tsunagari) / sizeof(sources_tsunagari[0]); i++) {
        src = sources_tsunagari[i];
        puts(src);
        object(&cxxflags, object_prefix_tsunagari, sizeof(object_prefix_tsunagari)-1, src, strlen(src));
    }

    exe(exe_tsunagari, sources_tsunagari);

    for (i = 0; i < sizeof(sources_pack_tool) / sizeof(sources_pack_tool[0]); i++) {
        src = sources_pack_tool[i];
        puts(src);
        object(&cxxflags, object_prefix_pack_tool, sizeof(object_prefix_pack_tool)-1, src, strlen(src));
    }

    exe(exe_pack_tool, sources_pack_tool);

    for_each_in_arr(ss, &cxxflags) {
        free(*ss);
    }

    arr_destroy(&cxxflags);

    return 0;
}
