#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node_int{
    int data;
    int height;
    struct node_int *pred, *lftptr, *rhtptr;
}node_int;

typedef struct AVL_tree{
    struct node_int *root;
}AVL_tree;

int counter;

node_int *new_node(int data)
{
    node_int *k = (node_int*)malloc(sizeof(node_int));
    k->data = data;
    k->lftptr = NULL;
    k->rhtptr = NULL;
    k->pred = NULL;
    k->height = 0;
    return k;
}

int get_height(node_int *node)
{
    if(node==NULL)
        return -1;
    if(node->lftptr==NULL && node->rhtptr==NULL)
        return node->height;
    int l, r;
    l = (node->lftptr==NULL)?0:get_height(node->lftptr);
    r = (node->rhtptr==NULL)?0:get_height(node->rhtptr);
    return (l>=r)?l:r;
}

void re_height(node_int *node)
{
    if(node->pred==NULL)
    {
        node->height = 1;
        if(node->lftptr!=NULL)
        re_height(node->lftptr);
        if(node->rhtptr!=NULL)
        re_height(node->rhtptr);
    }
    else
    {
        node->height = node->pred->height + 1;
        if(node->lftptr!=NULL)
        re_height(node->lftptr);
        if(node->rhtptr!=NULL)
        re_height(node->rhtptr);
    }
}

void L_rotate(node_int *imba, node_int *ptr, node_int **root)
{
    *root = ptr;
    imba->rhtptr = ptr->lftptr;
    if(imba->rhtptr!=NULL)
    imba->rhtptr->pred = imba;
    ptr->pred = imba->pred;
    ptr->lftptr = imba;
    imba->pred = ptr;
    counter++;
    re_height(ptr);
}

void R_rotate(node_int *imba, node_int *ptr, node_int **root)
{
    *root = ptr;
    imba->lftptr = ptr->rhtptr;
    if(imba->lftptr!=NULL)
    imba->lftptr->pred = imba;
    ptr->pred = imba->pred;
    ptr->rhtptr = imba;
    imba->pred = ptr;
    counter++;
    re_height(ptr);
}

void LR_rotate(node_int *imba, node_int *ptr, node_int **root)
{
    L_rotate(ptr, ptr->rhtptr, &imba->lftptr);
    ptr = imba->lftptr;
    R_rotate(imba, ptr, root);
}

void RL_rotate(node_int *imba, node_int *ptr, node_int **root)
{
    R_rotate(ptr, ptr->lftptr, &imba->rhtptr);
    ptr = imba->rhtptr;
    L_rotate(imba, ptr, root);
}

void R_rotation(node_int *node, node_int **root)
{
    if(node->lftptr->rhtptr!=NULL)
    {
        LR_rotate(node, node->lftptr, root);
    }
    else
    {
        R_rotate(node, node->lftptr, root);
    }

}

void L_rotation(node_int *node,node_int **root)
{
    if(node->rhtptr->lftptr!=NULL)
    RL_rotate(node, node->rhtptr, root);
    else
    L_rotate(node, node->rhtptr, root);
}

void balance(node_int *node, AVL_tree *tree)
{
    node_int *ptr;
    ptr = node;
    while(ptr->pred!=NULL)
    {

        int l, r;
        l = (ptr->lftptr==NULL)?0:(get_height(ptr->lftptr)-ptr->height);
        r = (ptr->rhtptr==NULL)?0:(get_height(ptr->rhtptr)-ptr->height);
        if(l-r>1){
            R_rotation(ptr,((ptr->data<ptr->pred->data)?&ptr->pred->lftptr:&ptr->pred->rhtptr));
        }
        else if(r-l>1){
            L_rotation(ptr,((ptr->data<ptr->pred->data)?&ptr->pred->lftptr:&ptr->pred->rhtptr));
        }
        ptr = ptr->pred;
    }
    if(ptr->pred==NULL)
    {
        int l, r;
        l = (ptr->lftptr==NULL)?0:(get_height(ptr->lftptr)-ptr->height);
        r = (ptr->rhtptr==NULL)?0:(get_height(ptr->rhtptr)-ptr->height);
        if(l-r>1)
        R_rotation(ptr,&tree->root);
        else if(r-l>1)
        L_rotation(ptr,&tree->root);
    }
}

void insert(AVL_tree *tree, int data)
{
    node_int *ptr;
    ptr = tree->root;
    if(tree->root==NULL)
    {
        tree->root = new_node(data);
        tree->root->height = 1;
        return;
    }
    while(TRUE)
    {
        if(data < ptr->data)
        {
            if(ptr->lftptr != NULL)
            {
                ptr = ptr->lftptr;
            }
            else
            {
                ptr->lftptr = new_node(data);
                ptr->lftptr->pred = ptr;
                ptr->lftptr->height = ptr->height + 1;
                break;
            }
        }
        else
        {
            if(ptr->rhtptr != NULL)
            {
                ptr = ptr->rhtptr;
            }
            else
            {
                ptr->rhtptr = new_node(data);
                ptr->rhtptr->pred = ptr;
                ptr->rhtptr->height = ptr->height + 1;
                break;
            }
        }
    }
    balance(ptr, tree);
}

void in_traverse(node_int *node)
{
	if(node->lftptr!=NULL)
        in_traverse(node->lftptr);
    printf("%d ",node->data);
    if(node->rhtptr!=NULL)
        in_traverse(node->rhtptr);
}

void frem(node_int *gc)
{
    printf("clear left\n");
    if(gc->lftptr!=NULL)
        frem(gc->lftptr);
    printf("left cleared, clear right\n");
    if(gc->rhtptr!=NULL)
        frem(gc->rhtptr);
    printf("right cleared\n");
    free(gc);
    printf("clean\n");
}

void destroy(AVL_tree *gc)
{
    frem(gc->root);
    gc->root = NULL;
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
            //printf("%d\n",i);
            insert(&tree,i);
        }
        printf("%d\n", counter);
        destroy(&tree);
    }
    return 0;
}
