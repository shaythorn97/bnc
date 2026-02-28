#define BNC_IMPLEMENTATION
#include "bnc.h"

int main() {
    Executable exe = {0};

    add_source_files(&exe, "src/main.c", "src/array.c");
    add_include_dirs(&exe, "external/include", "external/maths/include");
    add_library_files(&exe, "user32.lib", "external/lib/mylib.lib");

    print_target(&exe);

    //build_target(&exe);

    // bnc_AddCommand(&exe, "cl");
    // bnc_AddCommand(&exe, 
    //         "src/main.c",
    //         "src/renderer.c",
    //         "src/camera.c",
    //         "src/bnkgl.c",
    //         "src/eventmanager.c",
    //         "src/shader.c",

    //         "external/glad/src/glad.c");
    // bnc_AddCommand(&exe, 
    //         "/I external/glfw/include",
    //         "/I external/glad/include");
    // bnc_AddCommand(&exe, 
    //         "/Fe: build/main.exe",
    //         "/Fo: build/",
    //         "/Fd: build/");
    // bnc_AddCommand(&exe, 
    //         "/Zi",
    //         "/MD",
    //         "/W1",
    //         "/fsanitize=address");
    // bnc_AddCommand(&exe, 
    //         "external/glfw/lib/glfw3.lib",

    //         "opengl32.lib",
    //         "user32.lib",
    //         "gdi32.lib",
    //         "shell32.lib",
    //         "vcruntime.lib",
    //         "msvcrt.lib");

    // bnc_CmdPrint(&exe);
}
