#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int stk[100];
    int ed; //ed labels end null can 101
}simp_int_stack;

void push(int *stk, int *ed, int value)
{
    stk[*ed]=value;
    *ed+=1;
}

int pop(int *stk, int *ed)
{
    int ans=stk[*ed-1];
    stk[*ed-1]=0;
    *ed-=1;
    return ans;
}

int top(int *stk, int *ed)
{
    return stk[*ed-1];
}

//end of stack func

int fac(int n)
{
    int ans=1;
    for(int c=2;c<=n;c++)
        ans*=c;
    return ans;
}

int main(void)
{
    int lp=0,a,b,k=0;
    scanf("%d\n",&lp);
    simp_int_stack num;

    for(int c=0;c<lp;c++)
    {
	    k=0;
        num.ed=0;
        int *ed=&num.ed;
        char st[256];
        gets(st);
        char *str=strtok(st," ");
        while(str!=NULL)
        {
            switch(str[0])
            {
                case '+' :
                    a=pop(num.stk,ed);
                    b=pop(num.stk,ed);
                    push(num.stk,ed,b+a);
                    break;
                case '-':
                    if(strlen(str)>1)
                    {
                        push(num.stk,ed,atoi(str));
                    }
                    else
                    {
                        int a=pop(num.stk,ed);
                        int b=pop(num.stk,ed);
                        push(num.stk,ed,b-a);
                    }
                    break;
                case '*':
                    a=pop(num.stk,ed);
                    b=pop(num.stk,ed);
                    push(num.stk,ed,b*a);
                    break;
                case '/':
                    a=pop(num.stk,ed);
                    b=pop(num.stk,ed);
                    if(a==0)
                    {
                        printf("division by zero\n");
                        k=1;
                        break;
                    }
                    push(num.stk,ed,b/a);
                    break;
                case '!':
                    a=pop(num.stk,ed);
                    if(a<0)
                    {
                        printf("factorial of an negative number\n");
                        k=1;
                        break;
                    }
                    push(num.stk,ed,fac(a));

                    break;
                default:
                    push(num.stk,ed,atoi(str));
                    break;
            }
	    if(k==1)
		    break;
            str=strtok(NULL," ");
        }
        if(k==1)
            continue;
        printf("%d\n",num.stk[0]);
    }
    return 0;
}
