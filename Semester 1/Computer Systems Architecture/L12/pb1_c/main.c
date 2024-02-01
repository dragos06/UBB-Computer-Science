#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(linker, "/INCLUDE:_printf")

void interlacing(char* s1, char* s2, char* s3, char* s4, int lens);

int main()
{
    char s1[100] = "abcdef", s2[100] = "123456", s3[100]="", s4[100]="";
    int lens;
    lens = strlen(s1);
    interlacing(s1,s2,s3,s4,lens);
    return 0;
}
