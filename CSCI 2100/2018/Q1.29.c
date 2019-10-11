#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int kl;
    scanf("%d\n",&kl);
    char gc;
    for(int l=0;l<kl;l++)
    {
        char an[11]={0};
        scanf("%s",an);
        scanf("%c",&gc);
        bool ans = (an[0]>=65&&an[0]<=77)&&(an[2]>=48&&an[2]<=57)&&(an[3]>=48&&an[3]<=57)&&(an[4]>=48&&an[4]<=57)&&(an[6]>=48&&an[6]<=57)&&(an[7]>=48&&an[7]<=57)&&(an[8]>=48&&an[8]<=57)&&((an[10]>=48&&an[10]<=57)||an[10]==65);
        int k = ((an[0]-64)*8+(an[2]-48)*7+(an[3]-48)*6+(an[4]-48)*5+(an[6]-48)*4+(an[7]-48)*3+(an[8]-48)*2)%11;
        ans = (k==0)?((an[10]==48)?ans:0):((k>1&&k<=10)?((an[10]-48==(11-k)||an[10]-64==(11-k))?ans:0):((an[10]==65)?ans:0));
        printf("%s\n",ans?"True":"False");
    }
    return 0;
}
