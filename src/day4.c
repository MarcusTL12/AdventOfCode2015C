#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "aoc_util/int_util.h"
#include "aoc_util/md5_util.h"

const char *INPUT = "ckczppom";

void d4p1() {
    size_t inplen = strlen(INPUT);

    char strbuffer[32], hashbuf[16];
    char *numbuffer = strbuffer + inplen;
    memcpy(strbuffer, INPUT, inplen);

    size_t i = 1;
    while (true) {
        size_t digits = sprintf(numbuffer, "%zu", i);
        md5(hashbuf, strbuffer, inplen + digits);
        if (!hashbuf[0] && !hashbuf[1] && !(hashbuf[2] & 0xf0)) break;
        i++;
    }

    printf("%zu\n", i);
}

typedef struct {
    size_t start, off, ans;
    bool *done;
} thread_args_t;

static void *threaded_loop(void *args_) {
    thread_args_t *args = args_;

    size_t inplen = strlen(INPUT);

    char strbuffer[32], hashbuf[16];
    char *numbuffer = strbuffer + inplen;
    memcpy(strbuffer, INPUT, inplen);

    size_t i = args->start;
    bool found = false;
    while (!*args->done) {
        size_t digits = sprintf(numbuffer, "%zu", i);
        md5(hashbuf, strbuffer, inplen + digits);
        if (!hashbuf[0] && !hashbuf[1] && !hashbuf[2]) {
            found = true;
            *(args->done) = true;
            args->ans = i;
            break;
        }
        i += args->off;
    }

    return NULL;
}

void d4p2() {
    size_t num_cpus = sysconf(_SC_NPROCESSORS_ONLN);

    thread_args_t *args = malloc(sizeof(thread_args_t) * num_cpus);
    pthread_t *ids = malloc(sizeof(pthread_t) * num_cpus);

    bool done = false;

    for (size_t i = 0; i < num_cpus; i++) {
        args[i] = (thread_args_t){
            .start = i, .off = num_cpus, .done = &done, .ans = SIZE_MAX};
        pthread_create(ids + i, NULL, threaded_loop, args + i);
    }

    size_t ans = SIZE_MAX;

    for (size_t i = 0; i < num_cpus; i++) {
        pthread_join(ids[i], NULL);
        ans = min(ans, args[i].ans);
    }

    printf("%zu\n", ans);

    free(ids);
    free(args);
}
