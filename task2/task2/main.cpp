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

// startWithCount value:
//      -1 - strict equality
//      0 - str2 start with str1
//      >0 - str2 start with startWithCount first chars from str2
int cmp2zcharCount(const char* str1,const char* str2, int startWithCount = -1)
{
    int idx = 0;
    while (*str1!='\0' && *str1==*str2 && (startWithCount<=0 || idx<startWithCount-1))
    {
        ++str1;
        ++str2;
        ++idx;
    }
    if (*str1==*str2) return 0;
    if (startWithCount>=0 && *str1=='\0') return 0;
    if (*str1>*str2) return 1;      //assuming '\0' less than any symbol
    return -1;
}

int substrFind(const char* str,const char* substr,int startWithCount = 0)
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
        if (cmp2zcharCount(substr,str,startWithCount)==0) k++;
        ++str;
    }

    return k;
}

int main()
{

    TEST("test equality",cmp2zcharCount("test2","test2"),0);
    TEST("test lesser",cmp2zcharCount("test1","test2"),-1);
    TEST("test greater",cmp2zcharCount("test","tes"),1);
    TEST("test equality 2 first chars",cmp2zcharCount("tegt2","test2", 2),0);


    TEST("test empty in empty",substrFind("",""),1);
    TEST("test empty in string",substrFind("","test"),0);
    TEST("test string in empty",substrFind("test",""),0);
    TEST("test equal",substrFind("test","test"),1);
    TEST("test 2 times",substrFind("testdstest","test"),2);
    TEST("test 3 times with partial",substrFind("tetestdstesttetest","test"),3);
    TEST("test partial",substrFind("testestest","test"),3);
    TEST("test intersecting occurrences",substrFind("sssss","ss"),4);
    TEST("test first 2 chars",substrFind("Testqwerrtytest","Test",2),1);
    TEST("test first 2 chars harder",substrFind("TebtqwerrTytest","Test",2),1);


    return 0;
}
