#include <stdio.h>
#include <math.h>

int main(void)
{
    int l;
    unsigned int a,b;
    scanf("%d",&l);
    for(int c=0;c<l;c++)
    {
        scanf("%u %u",&a,&b);
        a = a << (b!=0?(int)(log(b)/log(2))+1:0);
        a += b;
        printf("%u\n",a);
    }
    return 0;
}
