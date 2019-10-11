#include <stdio.h>
#include <stdlib.h>

typedef struct heap{
    int *heap;
    int cap, cur;
}heap;

void del(heap *hp)
{
    int pred, cur;
    int temp=hp->heap[hp->cur];
    pred=1;
    cur=2;
    while(cur<=hp->cur-1)
    {
        if ((cur<hp->cur-1)&&(hp->heap[cur]<hp->heap[cur+1]))
            cur++;
        if (temp>=hp->heap[cur])
            break;
        hp->heap[pred]=hp->heap[cur];
        pred=cur;
        cur*=2;
    }
    hp->heap[pred]=temp;
}

void inhp(heap *hp, int key)
{
    if (hp->cur==hp->cap)
    {
        if(key < hp->heap[1])
        {
            del(hp);
            hp->cur-=1;
            inhp(hp,key);
        }
    }
    else
    {
        hp->cur+=1;
        int t = hp->cur;
        while ( (t!=1) && (key>hp->heap[t/2]) )
        {
            hp->heap[t] = hp->heap[t/2];
            t/=2;
        }
        hp->heap[t]=key;
    }
}

int main(void)
{
    heap hp;
    scanf("%d",&hp.cap);
    hp.cap;
    hp.cur=0;
    hp.heap = (int*)malloc((hp.cap+1)*sizeof(int));
    for(int c=0;c<=hp.cap;c++)
        hp.heap[c]=0;
    char in=' ';
    while(in!='S')
    {
        scanf("%c",&in);
        if(in=='I')
        {
            int num;
            scanf("%d",&num);
            inhp(&hp,num);
        }
        else if(in=='O')
            printf("%d\n",hp.heap[1]);
    }
    return 0;
}
