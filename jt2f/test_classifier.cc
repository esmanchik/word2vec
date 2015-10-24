#include <stdio.h>
#include "parser.cc"
#include "word_vectors.cc"

int line2vec(char *line, word_vectors & vectors, std::vector<float> & vec) {
    int cl, wc = 0;
    float len = 0;
    size_t size = vectors.vector_size();
    vec.resize(size);
    tokenize(line, [&vectors, line, size, &vec, &len, &wc, &cl](const char *word) {
        if (wc) {
            printf("%s ", word);
            // search through the known words and create vector
            const float * v = vectors.find_vector(word);
            if (v == NULL) return;
            size_t a;
            // DEBUG printf("vector[%d] = ", wc);
            for (a = 0; a < size; a++) {
                vec[a] += v[a];
                // DEBUG printf("%f ", v[a]);
            }
            // DEBUG printf("\n");            
        } else {
            // find class
            cl = str2class(word);
        }
        wc++;
    });
    printf("\n");
    // normalize vector
    //vectors.norm_vector(vec);
    size_t a;
    for (a = 0; a < size; a++) len += vec[a] * vec[a];
    len = sqrt(len);
    //vectors.norm_vector(vec);
    //printf("\nvector / %f = ", len);
    for (a = 0; a < size; a++) {
        vec[a] /= len;
        //printf("%f ", vec[a]);
    }
    //printf("\n\n");
    return cl;
}

int main(int argc, char **argv) {
    int n, j, expected, actual, errors, errors1, unknown;
    float accuracy, error;
    char buf[512], *line;

    if (argc < 2) {
        printf("Usage: %s <FILE>\nwhere FILE contains word projections in the BINARY FORMAT\n", *argv);
        return -1;
    }

    std::string word;
    std::vector<float> vector;
    word_vectors vectors;
    vectors.load(argv[1]);

    errors1 = errors = n = unknown = 0;
    while(1) {
        // per line
        line = fgets(buf, sizeof(buf), stdin);
        if (line == NULL) break;
	n++;
        printf("%s", line);
        // create vector from line
        expected = line2vec(line, vectors, vector);
        // recognize
        vectors.closest(vector, word);
        actual = str2class(word.c_str());
        printf("closest=%s, expected=%d, actual=%d\n", word.c_str(), expected, actual);
        if (expected != actual) {
            errors++;
        }
        // DEBUG printf("%s\n", line);
        // DEBUG printf("actual=%d, expected=%d\n", actual, expected);
        // DEBUG printf("function %d instead of %d\n\n",
        // DEBUG        class2fun(actual), class2fun(expected));
    }
    accuracy = (float) (n - errors - unknown) / n;
    error = (float) errors / n;

    printf("total=%d\n", n);
    printf("accuracy=%.6f\n", accuracy);
    printf("error=%.6f\n", error);
    printf("unknown=%d\n", unknown);

    return 0;
}
