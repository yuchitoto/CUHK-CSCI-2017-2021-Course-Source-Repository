#include <stdio.h>
#include <stdlib.h>

typedef struct node_int{
    int data;
    struct node_int *pred, *lftptr, *rhtptr;
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

void in_traverse(node_int *node)
{
	  if(node->lftptr!=NULL)
    {
        in_traverse(node->lftptr);
        printf(" ");
    }
    printf("%d",node->data);
    if(node->rhtptr!=NULL)
    {
        printf(" ");
        in_traverse(node->rhtptr);
    }
}

int main(void)
{
    bin_tree tree;
    tree.root=NULL;

    int r;
    scanf("%d",&r);
    for(int c=0;c<r;c++)
    {
        int num;
        scanf("%d",&num);
        int arr[num];
        for(int d=0;d<num;d++)
            scanf("%d",&arr[d]);
        tree.root = load(arr, NULL, 0, sizeof(arr)/sizeof(int));
        in_traverse(tree.root);
        printf("\n");
        tree.root = frem(tree.root);
    }
    return 0;
}
