#include <stdio.h>
#include <stdlib.h>

void inhp(int *heap, int key, int hs)
{
    if(heap[0]<hs)
    {
        heap[0]+=1;
        heap[heap[0]]=key;
        printf("%d!\n",heap[heap[0]]);
        int loc=heap[0];
        while(heap[loc]>heap[loc/2]&&loc>0)
        {
            int tmp=heap[loc/2];
            heap[loc/2]=heap[loc];
            heap[loc]=tmp;
        }
    }
    else
    {
        if(key<heap[1])
        {
            heap[1]=heap[hs];
            heap[0]-=1;
            inhp(heap,key,hs);
        }
    }
}

int main(void)
{
    int hs;
    scanf("%d",&hs);
    int heap[hs+1];
    for(int c=0;c<=hs;c++)
        heap[c]=0;
    char in=' ';
    while(in!='S')
    {
        scanf("%c",&in);
        if(in=='I')
        {
            int num;
            scanf("%d",&num);
            inhp(heap,num,hs);
        }
        else if(in=='O')
            printf("%d\n",heap[1],heap[2],heap[3],heap[0]);
    }
    return 0;
}
