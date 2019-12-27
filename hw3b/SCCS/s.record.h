h20139
s 00008/00000/00000
d D 1.1 16/10/15 17:05:33 bmura 1 0
c date and time created 16/10/15 17:05:33 by bmura
e
u
U
f e 0
t
T
I 1
struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    int                yearofbirth;
    struct record*     next;
};
E 1
