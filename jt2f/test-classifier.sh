g++ -std=c++11 -O3 test_classifier.cc -o test_classifier -lm && \
tail -n 1000 $2 | ./test_classifier $1
