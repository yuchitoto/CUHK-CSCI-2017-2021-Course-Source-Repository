#include <stdio.h>

int main(void)
{
    int five, ten, count;
    five=0;
    ten=0;
    count=0;
    int lp=0;
    scanf("%d",&lp);
    for(int c=0;c<lp;c++)
    {
        int in=0;
        scanf("%d",&in);
        switch(in)
        {
        case 5:
            five++;
            count++;
            break;
        case 10:
            if(five>0)
            {
                five--;
                ten++;
                count++;
            }
            break;
        default:
            printf("Error Input\n");
        }
    }
    printf("%d\n",count);
    return 0;
}
