#include "disjoint_set.h"
using namespace std;


void basic_LS_test()
{
    vector<int> vec = {0,1,2,3,4,5,6,7};
    List_Sets<int> LSC;
    for (int i : vec)
        LSC.make_set(i);
    LSC.print_LS();

    int i = 0;
    while (i < vec.size())
    {
        LSC.LS_union(i,i+1);
        i += 2;
    }
    LSC.print_LS();
    cout << SEPERATION;
}

void exer_21_2_2()
{
    List_Sets<int> LSC;
    for (int i = 1; i <= 16; i++)
        LSC.make_set(i);

    for (int i = 1; i <= 15; i+=2)
        LSC.LS_union(i,i+1);

    for (int i = 1; i <= 13; i+=4)
        LSC.LS_union(i,i+2);

    LSC.LS_union(1,5);
    LSC.LS_union(11,13);
    LSC.LS_union(1,10);
    cout << "Current collection of set is:" << endl;
    LSC.print_LS();

    cout << "Find-Set x2:"  << endl;
    LSC.print_LS(LSC.find_set(2));
    cout << "Find-Set x9:" << endl;
    LSC.print_LS(LSC.find_set(9));
    cout << SEPERATION;
}

void basic_TS_test()
{
    vector<int> vec = {0,1,2,3,4,5,6,7};
    Tree_Sets<int> LSC;
    for (int i : vec)
        LSC.make_set(i);
    int i = 0;
    while (i < vec.size())
    {
        LSC.ts_union(i,i+1);
        i += 2;
    }
    cout << SEPERATION;
}


int main()
{
    basic_LS_test();
    exer_21_2_2();
    basic_TS_test();
    return 0;
}