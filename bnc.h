#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

// TODO
// - could possibly add some enums for configuration, OS, directories etc

#define BNC_CMD_CAP 4096

typedef struct {
    char cmd[BNC_CMD_CAP];
    size_t cmdLen;
} Executable;

#define bnc_Add(exe, ...) bnc_Join(exe, __VA_ARGS__, NULL)

static inline void bnc_Join(Executable* exe, const char* first, ...) {
    va_list args;
    va_start(args, first);

    const char* s = first;
    while (s) {
        if (exe->cmdLen > 0) {
            memcpy(exe->cmd + exe->cmdLen, " ", 1);
            exe->cmdLen++;

            memcpy(exe->cmd + exe->cmdLen, s, strlen(s));
            exe->cmdLen += strlen(s);
            s = va_arg(args, const char*);
        }
    }

    va_end(args);
}

static inline void bnc_Print(Executable* exe) {
    // we need to add an assert
    exe->cmd[exe->cmdLen] = '\0';
    printf("%s", exe->cmd);
}

static inline void bnc_Build(Executable* exe) {
    // we need to assert here
    exe->cmd[exe->cmdLen] = '\0';
    system(exe->cmd);
}
