g++ -std=c++11 -O3 test_classifier.cc -o test_classifier -lm && \
tail -n 10000 $2 | ./test_classifier $1 >test_classifier.log 
