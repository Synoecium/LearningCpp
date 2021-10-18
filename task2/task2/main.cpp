#include <iostream>
#include <string.h>

#include "TEST.h"


/*reworked from scratch
// startWithCount value:
//      -1 - strict equality
//      0 - str2 start with str1
//      >0 - str2 start with startWithCount first chars from str2
int cmp2zcharCount(const char* str1,const char* str2, int startWithCount = -1)
{
    int idx = 0;
    while (str1[idx]!='\0' && str1[idx]==str2[idx] && (startWithCount<=0 || idx<startWithCount-1))
    {
        ++idx;
    }
    if (str1[idx]==str2[idx])
        return 0;
    if (startWithCount>=0 && str1[idx]=='\0')
        return 0;
    if (str1[idx]>str2[idx])
        return 1;      //assuming '\0' less than any symbol
    return -1;
}

int substrFind(const char* str,const char* substr,int startWithCount = 0)
{
    bool isStrEmpty = (str==nullptr || str[0]=='\0');
    bool isSubstrEmpty = (substr==nullptr || substr[0]=='\0');
    if (isStrEmpty && isSubstrEmpty)
        return 1;
    if (isStrEmpty || isSubstrEmpty)
        return 0;

    unsigned k = 0;

    while (*str!='\0')
    {
        if (cmp2zcharCount(substr,str,startWithCount)==0)
            k++;
        ++str;
    }

    return k;
}
*/

int myStrncmp(const char* str1, const char* str2, unsigned int maxcount=0)
{
    int idx = 0;
    while (str1[idx]!='\0' && str1[idx]==str2[idx] && idx<maxcount-1)
    {
        ++idx;
    }
    if (str1[idx]==str2[idx])
        return 0;
    if (str1[idx]>str2[idx])
        return 1;      //assuming '\0' less than any symbol
    return -1;
}

int substrFind(const char* str,const char* substr)
{
    bool isStrEmpty = (str==nullptr || str[0]=='\0');
    bool isSubstrEmpty = (substr==nullptr || substr[0]=='\0');
    if (isStrEmpty && isSubstrEmpty)
        return 1;
    if (isStrEmpty || isSubstrEmpty)
        return 0;

    unsigned k = 0;
    unsigned substrLength = strlen(substr);

    while (*str!='\0')
    {
        if (strncmp(substr,str,substrLength)==0)
            k++;
        ++str;
    }

    return k;
}

int main()
{

    std::cout<<"Function int myStrncmp(const char* str1, const char* str2, int maxcount) tests:"<<std::endl;
    TEST("test inequality",myStrncmp("test","foobar",10),1);
    TEST("test equality",myStrncmp("test2","test2",10),0);
    TEST("test lesser",myStrncmp("test1","test2",10),-1);
    TEST("test greater",myStrncmp("test","tes",10),1);
    TEST("test equality 2 first chars",myStrncmp("tegt2","test2", 2),0);
    TEST("test equality 2 first chars",myStrncmp("te","te", 2),0);
    TEST("test inequality 2 first chars",myStrncmp("te","tr", 2),-1);
    TEST("test equality 1 first chars",myStrncmp("t","t", 1),0);
    TEST("test equal empty strings",myStrncmp("","",1),0);
    //TEST("test equal nullptrs",myStrncmp(nullptr,nullptr,1),0);   //original strncmp() fails with nullptr parameters
    std::cout<<std::endl;

    std::cout<<"Function int substrFind(const char* str,const char* substr) tests:"<<std::endl;
    TEST("test nullptr in nullptr",substrFind(nullptr,nullptr),1);
    TEST("test nullptr in string",substrFind(nullptr,"test"),0);
    TEST("test string in nullptr",substrFind("test",nullptr),0);
    TEST("test empty in empty",substrFind("",""),1);
    TEST("test empty in string",substrFind("","test"),0);
    TEST("test string in empty",substrFind("test",""),0);
    TEST("test equal",substrFind("test","test"),1);
    TEST("test 2 times",substrFind("testdstest","test"),2);
    TEST("test 3 times with partial",substrFind("tetestdstesttetest","test"),3);
    TEST("test partial",substrFind("testestest","test"),3);
    TEST("test intersecting occurrences",substrFind("sssss","ss"),4);
    std::cout<<std::endl;

    return 0;
}
