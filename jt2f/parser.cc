#include <vector>
#include <functional>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef std::function<void (const char *)> word_handler_type;

int tokenize(const char *line, word_handler_type word_handler) {
    int i, j, k, n;
    char prefix[512], word[512];
    // DEBUG const char *start = line;
    // tokenize to words
    k = 0;
    while(1) {
        n = sscanf(line, "%512[^A-Za-z0-9']%n", prefix, &i);
        // DEBUG printf("n=%d\n", n);
        if (n > 0) {
            // DEBUG printf("at %d is prefix %s\n", line - start, prefix);
            line += i;
        }
        n = sscanf(line, "%512[A-Za-z0-9']%n", word, &i);
        // DEBUG printf("n=%d\n", n);
        if (n < 1) break;
        // lowercase word
        for (j = 0; word[j] != '\0'; j++) {
            word[j] = tolower(word[j]);
        }
        // DEBUG printf("at %d is %s\n", line - start, word);
        word_handler(word);
        // DEBUG printf("line=%s\n", line);
        line += i;
        k++;
    }
    return k;
}

int str2class(const char *s) {
    int cl, fn = atoi(s);
    cl = fn / 1000000;
    // DEBUG printf("function=%d, class=%d\n", fn, cl);
    return cl;
}
