#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_util/file_util.h"

static bool isvowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

static bool blacklisted(char *s) {
    return s[0] == 'a' && s[1] == 'b' || s[0] == 'c' && s[1] == 'd' ||
           s[0] == 'p' && s[1] == 'q' || s[0] == 'x' && s[1] == 'y';
}

static bool isnice(char *s) {
    size_t amt_vowels = 0;
    for (char *c = s; *c && *c != '\n'; c++) amt_vowels += isvowel(*c);

    bool hasdouble = false;
    bool hasblacklisted = false;
    for (char *c = s; c[1] && c[1] != '\n'; c++) {
        hasdouble |= c[0] == c[1];
        hasblacklisted |= blacklisted(c);
    }

    return amt_vowels >= 3 && hasdouble && !hasblacklisted;
}

void d5p1() {
    char *inp = file_read_full("input/day5/input");

    size_t ans = 0;

    for (char *c = inp; *c;) {
        ans += isnice(c);
        while (*c && *c != '\n') c++;
        if (*c && *c == '\n') c++;
    }

    printf("%zu\n", ans);

    free(inp);
}

static bool isnice2(char *s) {
    char seen[26 * 26] = {[0 ... 26 * 26 - 1] = -1};

    bool haspair = false;

    size_t i = 0;
    for (char *c = s; !haspair && c[1] && c[1] != '\n'; c++, i++) {
        if (seen[c[0] - 'a' + 26 * (c[1] - 'a')] == -1) {
            seen[c[0] - 'a' + 26 * (c[1] - 'a')] = i;
        } else if (i - seen[c[0] - 'a' + 26 * (c[1] - 'a')] >= 2) {
            haspair = true;
        }
    }

    bool has_uwu = false;

    for (char *c = s; !has_uwu && c[2] && c[2] != '\n'; c++) {
        has_uwu |= c[0] == c[2];
    }

    return haspair && has_uwu;
}

void d5p2() {
    char *inp = file_read_full("input/day5/input");

    size_t ans = 0;

    for (char *c = inp; *c;) {
        ans += isnice2(c);
        while (*c && *c != '\n') c++;
        if (*c && *c == '\n') c++;
    }

    printf("%zu\n", ans);

    free(inp);
}
