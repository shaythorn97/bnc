#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define BNC_CMD_CAP 4096

typedef struct {
    char cmd[BNC_CMD_CAP];
    size_t cmdLen;
} Executable;

#define bnc_AddCommand(exe, ...) bnc_CmdJoin(exe, __VA_ARGS__, NULL)

static inline void bnc_CmdAppend(Executable* exe, const char* file) {
    if (exe->cmdLen > 0) {
        memcpy(exe->cmd + exe->cmdLen, " ", 1);
        exe->cmdLen++;
    }

    memcpy(exe->cmd + exe->cmdLen, file, strlen(file));
    exe->cmdLen += strlen(file);
}

static inline void bnc_CmdJoin(Executable* exe, const char* first, ...) {
    va_list args;
    va_start(args, first);

    const char* s = first;
    while (s) {
        bnc_CmdAppend(exe, s);
        s = va_arg(args, const char*);
    }

    va_end(args);
}

static inline void bnc_CmdPrint(Executable* exe) {
    // we need to add an assert
    exe->cmd[exe->cmdLen] = '\0';
    printf("%s", exe->cmd);
}

static inline void bnc_CmdBuild(Executable* exe) {
    // we need to assert here
    exe->cmd[exe->cmdLen] = '\0';
    system(exe->cmd);
}
