#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct num_node{
    int num;
    bool done;
    bool *pred;  //assign size of array
}num_node;

void init(num_node *arr, int siz)
{
    for(int c=0;c<siz;c++)
    {
        arr[c].num=c+1;
        arr[c].done=false;
        arr[c].pred=(bool*)malloc(siz*sizeof(bool));
        for(int d=0;d<siz;d++)
            arr[c].pred[d]=false;
    }
}

int print(num_node *arr,int l,int siz,int count)
{
    if(arr[l].done==true)
        return count;
    for(int c=0;c<siz;c++)
    {
        if(arr[l].pred[c]==true)
            count = print(arr,c,siz,count);
    }
    arr[l].done=true;
    if(count>1)
        printf(" ");
    printf("%d",arr[l].num);
    return count+1;
}

void clean(num_node *arr, int siz)
{
    for(int c=0;c<siz;c++)
        free(arr[c].pred);
}

int main()
{
    int lp,siz,cs,a,b;
    scanf("%d",&lp);
    for(int c=0;c<lp;c++)
    {
        scanf("%d%d",&siz,&cs);
        num_node arr[siz];
        init(arr, siz);

        for(int d=0;d<cs;d++)
        {
            scanf("%d %d",&a,&b);
            arr[b-1].pred[a-1]=true;
        }

        int count=1;
        for(int d=0;d<siz;d++)
        {
            count = print(arr,d,siz,count);
        }

        printf("\n");

        clean(arr,siz);
    }
    return 0;
}
