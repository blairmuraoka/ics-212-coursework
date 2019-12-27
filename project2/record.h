#include <string>

using namespace std;
struct record
{
    int             accountno;
    string          name;
    string          address;
    int             yearofbirth;
    struct record*  next;
};
