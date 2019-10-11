#include <stdio.h>
#include <stdlib.h>

/**
 * Q2.12
 */

typedef struct pile{
	int key;
	struct pile *below, *above;
}pile;

void init(pile *cube, int k)
{
	for(int c=1;c<=k;c++)
	{
		cube[c].key = c;
		cube[c].below = NULL;
		cube[c].above = NULL;
	}
}

void link(pile *cube, int a, int b)
{
	pile *ptr = &cube[a];
	pile *ptrb = &cube[b];
	while(ptr->below!=NULL)
    {
        ptr = ptr->below;
    }
    while(ptrb->above!=NULL)
    {
        ptrb = ptrb->above;
    }
    ptr->below = ptrb;
    ptr->below->above = ptr;
}

int count(pile *cube, int a)
{
	int k=0;
	pile *ptr = &cube[a];
	while(ptr->below!=NULL)
	{
		ptr = ptr->below;
		k++;
	}
	return k;
}

int main(void)
{
	pile cube[300];
	init(cube,300);
	int k;
	scanf("%d\n",&k);
	for(int c=0;c<k;c++)
	{
		char cm;
		char gc[256];
		scanf("%c ",&cm);
		if(cm=='M')
        {
            int a,b;
            scanf("%d %d",&a,&b);
            gets(gc);
            link(cube,a,b);
        }
        else if(cm=='C')
        {
            int a;
            scanf("%d",&a);
            gets(gc);
            printf("%d\n",count(cube,a));
        }
	}
	return 0;
}
