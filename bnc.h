#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

// TODO
// - for now lets strip the namespace
// - we could add shadowing data to the backend, like stb headers

#define BNC_BUF_SIZE 1024 * 8

typedef enum {
    BNC_COMPILER_MSVC,
} CompilerType;

typedef enum {
    BNC_CONFIG_DEBUG,
    BNC_CONFIG_RELEASE
} ConfigType;

typedef struct {
    char cmd[BNC_BUF_SIZE];
    size_t cmdLen;
    CompilerType compiler;
    ConfigType config;
    const char* name;
    const char* outDir;
} Executable;

#define add_source_files(exe, ...) bnc_join_default(exe, __VA_ARGS__, (char*)NULL)
#define add_include_dirs(exe, ...) bnc_join_include(exe, __VA_ARGS__, (char*)NULL)
#define add_library_files(exe, ...) bnc_join_default(exe, __VA_ARGS__, (char*)NULL)
#define add_options(exe, ...) bnc_join_default(exe, __VA_ARGS__, (char*)NULL)

void print_target(Executable* exe);
void build_target(Executable* exe);

void bnc_join_default(Executable* exe, const char* first, ...);
void bnc_join_include(Executable* exe, const char* first, ...);

#ifdef BNC_IMPLEMENTATION

void build_command(Executable* exe) {
    char temp[BNC_BUF_SIZE]; 
    int tempLen = exe->cmdLen;
    memcpy(temp, exe->cmd, exe->cmdLen);
    exe->cmdLen = 0;

    const char* compiler = "";
    const char* config = "";
    
    if (!exe->name) {
        exe->name = "a";
    }

    switch (exe->compiler) {
    case BNC_COMPILER_MSVC: 
        compiler = "cl ";
        break;
    }

    switch (exe->config) {
    case BNC_CONFIG_DEBUG:
        config = "/Zi ";
        break;
    }
    
    sprintf(exe->cmd, "%s%s", compiler, config);
    exe->cmdLen += strlen(compiler) + strlen(config);

    const char* fo = "/Fo:";
    const char* fe = "/Fe:";
    const char* fd = "/Fd:";

    const char* sep = "/";
    if (!exe->outDir) {
        sep = "";
        exe->outDir = "";
    } else {
        const char* suffix = "/ ";
        sprintf(exe->cmd + exe->cmdLen, "%s%s%s", fo, exe->outDir, suffix);
        exe->cmdLen += strlen(fo) + strlen(exe->outDir) + strlen(suffix);
    }

    sprintf(exe->cmd + exe->cmdLen, "%s%s%s%s ", fe, exe->outDir, sep, exe->name);
    exe->cmdLen += strlen(fe) + strlen(exe->outDir) + strlen(sep) + strlen(exe->name) + 1;

    sprintf(exe->cmd + exe->cmdLen, "%s%s%s%s ", fd, exe->outDir, sep, exe->name);
    exe->cmdLen += strlen(fd) + strlen(exe->outDir) + strlen(sep) + strlen(exe->name) + 1;

    memcpy(exe->cmd + exe->cmdLen, temp, tempLen);
    exe->cmdLen += tempLen;
}

void print_target(Executable* exe) {
    build_command(exe);
    exe->cmd[exe->cmdLen] = '\0';
    printf("%s", exe->cmd);
}

void build_target(Executable* exe) {
    build_command(exe);
    exe->cmd[exe->cmdLen] = '\0';
    system(exe->cmd);
}

void bnc_join_default(Executable* exe, const char* first, ...) {
    va_list args;
    va_start(args, first);

    const char* s = first;
    while (s) {
        if (exe->cmdLen > 0) {
            exe->cmd[exe->cmdLen++] = ' ';
        }

        memcpy(exe->cmd + exe->cmdLen, s, strlen(s));
        exe->cmdLen += strlen(s);
        s = va_arg(args, const char*);
    }

    va_end(args);
}

void bnc_join_include(Executable* exe, const char* first, ...) {
    va_list args;
    va_start(args, first);

    const char* prefix = " /I ";

    const char* s = first;
    while (s) {
        if (exe->cmdLen > 0) {
            memcpy(exe->cmd + exe->cmdLen, prefix, strlen(prefix));
            exe->cmdLen += strlen(prefix);
        }

        memcpy(exe->cmd + exe->cmdLen, s, strlen(s));
        exe->cmdLen += strlen(s);
        s = va_arg(args, const char*);
    }

    va_end(args);
}

#endif
