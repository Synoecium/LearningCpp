#include <iostream>
#include <string.h>

#include "TEST.h"

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

void delSubstrOccurs(char* str, const char* substr)
{
    bool isStrEmpty = (str==nullptr || str[0]=='\0');
    bool isSubstrEmpty = (substr==nullptr || substr[0]=='\0');
    if (isStrEmpty || isSubstrEmpty)    //nothing to do
        return;

    unsigned substrLength = strlen(substr);
    char* trimmedStrPtr = str;

    while (*str!='\0')
    {
        if (strncmp(substr,str,substrLength)==0)
        {
            str+=substrLength;
            continue;
        };

        *trimmedStrPtr = *str;
        ++trimmedStrPtr;
        ++str;
    }
    *trimmedStrPtr = '\0';

}

void runTestOn_delSubstrOccurs(const char* testName, const char* str, const char* substr, const char* result)
{
    unsigned strLen = strlen(str);
    char *buff = new char[strLen+1];
    strncpy(buff,str,strLen);
    buff[strLen] = '\0';
    delSubstrOccurs(buff,substr);
    TEST(testName,myStrncmp(buff,result,strLen),0);
    delete buff;
}

int main()
{
    std::cout<<"Procedure void delSubstrOccurs(char* str, const char* substr) tests:"<<std::endl;
    runTestOn_delSubstrOccurs("test 2 chars delete", "test", "es", "tt");
    runTestOn_delSubstrOccurs("test 2 chars delete result empty", "es", "es", "");
    runTestOn_delSubstrOccurs("test delete empty from empty", "", "", "");
    runTestOn_delSubstrOccurs("test delete nullptr from string", "test", nullptr, "test");
    runTestOn_delSubstrOccurs("test delete 2 times", "tetesttetetetestttt", "test", "tetetetettt");
    runTestOn_delSubstrOccurs("test delete many chars", "ttetesttetetetestttt", "t", "eeseeees");
    runTestOn_delSubstrOccurs("test delete not found", "ttetesttetetetestttt", "ss", "ttetesttetetetestttt");
    runTestOn_delSubstrOccurs("test delete intersecting", "testestest", "test", "es");

    return 0;
}
