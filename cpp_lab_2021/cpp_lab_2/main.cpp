#include "def.h"
extern const char* TestQUEUE(int& s);
int main()
{
    int s;
    const char* e = TestQUEUE(s);
    cout << s << endl << e << endl;
    return 0;
}