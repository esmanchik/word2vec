#include <stdio.h>
#include <math.h>

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>

typedef float * Matrix;

class word_vectors {
    size_t size;
    size_t words;
    std::vector<std::string> vocab;
    Matrix matrix;
public:
    word_vectors() {
        size = words = 0;
        matrix = NULL;
    }
    
    ~word_vectors() {
        if (matrix != NULL) delete[] matrix;
    }
    
    size_t vector_size() { return size; }
    size_t word_count() { return words; }
    
    void load(const char *path) {
        const size_t max_w = 255;
        char word[max_w];
        float len;
        size_t a, b;
        FILE *f = fopen(path, "rb");
        if (f == NULL) {
          throw std::runtime_error("Input file not found");
        }
        fscanf(f, "%lu", &words);
        fscanf(f, "%lu", &size);
        Matrix M = matrix = new float[(long long)words * (long long)size];
        if (M == NULL) {
            //printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
            fclose(f);
            throw  std::runtime_error("Cannot allocate memory");
        }
        vocab.resize(words);
        for (b = 0; b < words; b++) {
          a = 0;
          while (1) {
            word[a] = fgetc(f);
            if (feof(f) || (word[a] == ' ')) break;
            if ((a < max_w) && (word[a] != '\n')) a++;
          }
          word[a] = 0;
          std::string test = word;
          vocab[b] = test;
          for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
          len = 0;
          for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
          len = sqrt(len);
          for (a = 0; a < size; a++) M[a + b * size] /= len;
        }
        fclose(f);
    }
    
    const float * find_vector(const char *word) {
        size_t i;
        for (i = 0; i < vocab.size(); i++) {
            if (vocab[i] == word) {
                break;
            }
        }
        return i == vocab.size() ? NULL : &matrix[i * size];
    }
    
    void norm_vector(std::vector<float> & vec) {
        // normalize vector
        size_t a;
        float len = 0;
        for (a = 0; a < size; a++) len += vec[a] * vec[a];
        len = sqrt(len);
        // DEBUG printf("\nvector / %f = ", len);
        for (a = 0; a < size; a++) {
            vec[a] = vec[a] / len;
            // DEBUG printf("%f ", vec[a]);
        }
        // DEBUG printf("\n\n");
    }

    void closest(std::vector<float> & vec, std::string & bestw) {
        const size_t N = 10;
        size_t a, b, c;
        float dist, len, bestd;        
        Matrix M = matrix;
        for (a = 0; a < N; a++) bestd = -1;
        for (a = 0; a < N; a++) bestw = "";
        for (c = 0; c < words; c++) {
            std::string str = vocab[c];
            if ('0' > str[0] || str[0] > '9' || str.length() != 8) continue;
            dist = 0;
            for (a = 0; a < size; a++) dist += vec[a] * M[a + c * size];
            if (dist > bestd) {
                bestd = dist;
                bestw = vocab[c];
            }
        }
    }
};
