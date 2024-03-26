#include "stdio.h"
int main(int argc,char* argv[])
{
    char str[256];
    sprintf(str,"part1: %d",3);
    sprintf(str,"repeat part1: %s;",str);
    printf("%s\n",str);
}
/**
 * repeat part1: repeat p;
*/