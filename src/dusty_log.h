/*
 * dusty_log.h — C-side logging bridge for Dusty Bytes platform
 *
 * Include in Emscripten game engine forks. Routes log calls through EM_ASM
 * to the JS logging framework (dusty.log) in the Web Worker.
 *
 * Under Emscripten: calls dusty.log() via EM_ASM.
 * On host (e.g. wartool): prints to stderr via fprintf.
 * Without -DDUSTY_LOG_ENABLED: all calls compile to nothing.
 *
 * Usage:
 *   DUSTY_LOG("wartool", "warn", "[wartool] entry=%d path=%s reason=missing", idx, path);
 */

#ifndef DUSTY_LOG_H
#define DUSTY_LOG_H

#ifdef DUSTY_LOG_ENABLED

#include <stdio.h>

#ifdef __EMSCRIPTEN__

#include <emscripten.h>

#define DUSTY_LOG(channel, level, fmt, ...) \
    do { \
        char _dusty_buf[512]; \
        snprintf(_dusty_buf, sizeof(_dusty_buf), fmt, ##__VA_ARGS__); \
        EM_ASM({ \
            if (typeof dusty !== 'undefined' && dusty.log) { \
                dusty.log(UTF8ToString($0), UTF8ToString($1), UTF8ToString($2)); \
            } \
        }, channel, level, _dusty_buf); \
    } while (0)

#else /* !__EMSCRIPTEN__ — host binary (wartool, etc.) */

#include <stdarg.h>

#define DUSTY_LOG(channel, level, fmt, ...) \
    do { \
        char _dusty_buf[1024]; \
        snprintf(_dusty_buf, sizeof(_dusty_buf), fmt, ##__VA_ARGS__); \
        fprintf(stderr, "[%s/%s] %s\n", channel, level, _dusty_buf); \
    } while (0)

#endif /* __EMSCRIPTEN__ */

#else /* !DUSTY_LOG_ENABLED */

#define DUSTY_LOG(channel, level, fmt, ...) ((void)0)

#endif /* DUSTY_LOG_ENABLED */

#endif /* DUSTY_LOG_H */
