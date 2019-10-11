#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node_int{
    int data;
    int height;
    struct node_int *lftptr, *rhtptr;
}node_int;

typedef struct AVL_tree{
    struct node_int *root;
}AVL_tree;

int counter;

node_int *new_node(int data)
{
    node_int *node = (node_int*)malloc(sizeof(node_int));
    node->data = data;
    node->lftptr = NULL;
    node->rhtptr = NULL;
    node->height = 1;
    return node;
}

int get_height(node_int *node)
{
    return (node!=NULL)?node->height:0;
}

int max(int a, int b)
{
    return (a>b)?a:b;
}

node_int *R_rotate(node_int *imba)
{
    counter++;
    node_int *ptr = imba->lftptr;
    imba->lftptr = ptr->rhtptr;
    ptr->rhtptr = imba;
    imba->height = max(get_height(imba->lftptr), get_height(imba->rhtptr)) + 1;
    ptr->height = max(get_height(ptr->lftptr), imba->height) + 1;
    return ptr;
}

node_int *L_rotate(node_int *imba)
{
    counter++;
    node_int *ptr = imba->rhtptr;
    imba->rhtptr = ptr->lftptr;
    ptr->lftptr = imba;
    imba->height = max(get_height(imba->lftptr), get_height(imba->rhtptr)) + 1;
    ptr->height = max(get_height(ptr->rhtptr), imba->height) + 1;
    return ptr;
}

node_int *LR_rotate(node_int *imba)
{
    imba->lftptr = L_rotate(imba->lftptr);
    return R_rotate(imba);
}

node_int *RL_rotate(node_int *imba)
{
    imba->rhtptr = R_rotate(imba->rhtptr);
    return L_rotate(imba);
}

node_int *balance(node_int *node)
{
    if(get_height(node->lftptr)-get_height(node->rhtptr) > 1)
        node = (get_height(node->lftptr->lftptr) > get_height(node->lftptr->rhtptr))?R_rotate(node):LR_rotate(node);
    else if(get_height(node->rhtptr)-get_height(node->lftptr) > 1)
        node = (get_height(node->rhtptr->rhtptr) > get_height(node->rhtptr->lftptr))?L_rotate(node):RL_rotate(node);
    return node;
}

node_int *insert(node_int *root, int data)
{
    if(root==NULL)
        return root = new_node(data);
    else if(data < root->data)
        root->lftptr = insert(root->lftptr, data);
    else
        root->rhtptr = insert(root->rhtptr, data);
    root->height = max(get_height(root->lftptr), get_height(root->rhtptr)) + 1;
    root = balance(root);
    return root;
}

node_int *frem(node_int *gc)
{
    gc->lftptr = (gc->lftptr!=NULL)?frem(gc->lftptr):NULL;
    gc->rhtptr = (gc->rhtptr!=NULL)?frem(gc->rhtptr):NULL;
    free(gc);
    return NULL;
}

int main(void)
{
    AVL_tree tree;
    tree.root=NULL;
    int lp;
    scanf("%d", &lp);
    for(int c=0;c<lp;c++)
    {
        counter = 0;
        int k;
        scanf("%d", &k);
        for(int b=0;b<k;b++)
        {
            int i;
            scanf("%d",&i);
            tree.root = insert(tree.root,i);
          }
        printf("%d\n", counter);
        tree.root = frem(tree.root);
  }
    return 0;
}
