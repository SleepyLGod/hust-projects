#include"def.h"
extern const char* TestSTACK(int& s);
int main()
{
    int e = 0;
    const char* s = TestSTACK(e);
    cout << s << endl;
    cout << e << endl;
}
