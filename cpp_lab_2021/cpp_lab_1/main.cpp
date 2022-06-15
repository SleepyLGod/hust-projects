#include "def.h"

extern const char* TestQueue(int& s);
int main() {
    const char* test;
    int s;
    test = TestQueue(s);
    printf("%s\n%d", test, s);
}