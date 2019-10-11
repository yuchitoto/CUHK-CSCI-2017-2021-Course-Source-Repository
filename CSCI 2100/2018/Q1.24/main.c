#include <stdio.h>
#include <string.h>

int main(void)
{
    int l;
    scanf("%d\n",&l);
    for(int c=0;c<l;c++)
    {
        char st[256]={'\0'};
        char sto[256]={0};
        gets(st); //not include \n
        int t=strlen(st);
        for(int d=0;d<t;d++)
            sto[d]=st[t-1-d];
        printf("%s\n",sto);
    }
    return 0;
}
