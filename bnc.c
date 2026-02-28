#define BNC_IMPLEMENTATION
#include "bnc.h"

int main() {
    Executable exe = {0};

    add_source_files(&exe, "src/main.c", "src/array.c");
    add_include_dirs(&exe, "external/include", "external/maths/include");
    add_library_files(&exe, "user32.lib", "external/lib/mylib.lib");

    print_target(&exe);
}
