#include <iostream>

#include "TEST.h"


using namespace std;

int cmp2zchar(const char* str1,const char* str2, bool isStartWith=false)
{
    while (*str1!='\0' && *str1==*str2)
    {
        ++str1;
        ++str2;
    }
    if (*str1==*str2) return 0;
    if (isStartWith && *str1=='\0') return 0;
    if (*str1>*str2) return 1;      //assuming '\0' less than any symbol
    return -1;
}

int substrFind(const char* str,const char* substr)
{
    if (str[0]=='\0')
    {
        if (substr[0]=='\0') return 1;
        return 0;
    }
    if (substr[0]=='\0') return 0;

    unsigned k = 0;

    while (*str!='\0')
    {
        if (cmp2zchar(substr,str,true)==0) k++;
        ++str;
    }

    return k;
}

int main()
{
    /*
    TEST("test equality",cmp2zchar("test2","test2"),0);
    TEST("test lesser",cmp2zchar("test1","test2"),-1);
    TEST("test greater",cmp2zchar("test","tes"),1);
    */

    TEST("test empty in empty",substrFind("",""),1);
    TEST("test empty in string",substrFind("","test"),0);
    TEST("test string in empty",substrFind("test",""),0);
    TEST("test equal",substrFind("test","test"),1);
    TEST("test 2 times",substrFind("testdstest","test"),2);
    TEST("test 3 times with partial",substrFind("tetestdstesttetest","test"),3);
    TEST("test partial",substrFind("testestest","test"),3);
    TEST("test intersecting occurrences",substrFind("sssss","ss"),4);


    return 0;
}
