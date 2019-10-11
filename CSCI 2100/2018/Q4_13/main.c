#include <stdio.h>
#include <stdlib.h>

void percolate_up(int *heap, int adr)
{
    while(adr>1)
    {
        if(heap[adr/2]<heap[adr])
        {
            int tmp=heap[adr/2];
            heap[adr/2]=heap[adr];
            heap[adr]=tmp;
            adr/=2;
        }
        else
            adr=1;
    }
}

void percolate_down(int *heap, int adr,int s)
{
    int key;
    if(adr*2+1>s)
    {
        if(adr*2>s)
            return;
        key = adr*2;
    }
    else
    {
        key = (heap[adr*2]>heap[adr*2+1])?adr*2:adr*2+1;
    }
    if(heap[adr]<heap[key])
    {
        int tmp = heap[adr];
        heap[adr] = heap[key];
        heap[key] = tmp;
        percolate_down(heap,key,s);
    }
}

void insert(int *heap, int key)
{
    heap[0]+=1;
    heap[heap[0]]=key;
    percolate_up(heap,heap[0]);
}

void instm(int *heap, int key, int s)
{
    if(heap[0]<s)
        insert(heap, key);
    else
    {
        if(key<heap[1])
        {
            heap[1]=key;
            percolate_down(heap,1,s);
        }
    }
}

int main(void)
{
    int k;
    scanf("%d", &k);
    char gb[256];
    char r=0;
    int heap[k+1];
    heap[0]=0;
    while(r!='S'&&r!='s')
    {
        scanf("%c", &r);
        if(r=='I'||r=='i')
        {
            int tmp;
            scanf("%d",&tmp);
            gets(gb);
            instm(heap,tmp,k);
        }
        else if(r=='O'||r=='o')
        {
            printf("%d\n", heap[1]);;
        }
    }
    return 0;
}
