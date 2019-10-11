#include <stdio.h>
#include <stdlib.h>

typedef struct node_int{
    int data;
    struct node_int *pred, *lftptr, *rhtptr;
    int p, c;
}node_int;

typedef struct bin_tree{
    struct node_int *root;
}bin_tree;

node_int *new_node(int data, node_int *pr)
{
    node_int *k = (node_int*)malloc(sizeof(node_int));
    k->data = data;
    k->pred = pr;
    k->lftptr = NULL;
    k->rhtptr = NULL;
    p = 0;
    c = 0;
    return k;
}

node_int *load(int *data, node_int *node, int l, int s)
{
    if(data[l]==0)
        return NULL;

    node_int *ret = new_node(data[l], node);

    if(2*l+1<s)
    {
        ret->lftptr = load(data, ret, 2*l+1, s);

        if(2*l+2<s)
        {
            ret->rhtptr = load(data, ret, 2*l+2, s);
        }
    }
    return ret;
}

node_int *frem(node_int *gc)
{
    gc->lftptr = (gc->lftptr!=NULL)?frem(gc->lftptr):NULL;
    gc->rhtptr = (gc->rhtptr!=NULL)?frem(gc->rhtptr):NULL;
    free(gc);
    return NULL;
}

void coverage(node_int *root)
{
    /**
    if left not null to left
    left right null to pred p cover
    */
}

int main()
{
    bin_tree tree;
    int lp;
    scanf("%d",&lp);
    for(int c=0;c<lp;c++)
    {
        tree.root=NULL;
        int n;
        scanf("%d", &n);
        int num[n];
        for(int k=0;k<n;k++)
            scanf("%d", &num[k]);
        tree.root = load(num,NULL,0,n);

    }
}
