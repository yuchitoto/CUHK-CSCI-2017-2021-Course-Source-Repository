#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key, freq;
    struct node *lftptr, *rhtptr, *stk_down;
}node;

typedef struct BST{
    struct node *root;
}BST;

typedef struct stack{
    struct node *root;
    struct stack *down_stk;
    int freq;
}stack;

typedef struct stkstk{
    struct stack *root;
}stkstk;

node *new_node(int key)
{
    node *n = (node*)malloc(sizeof(node));
    n->freq=1;
    n->key=key;
    n->lftptr=NULL;
    n->rhtptr=NULL;
    n->stk_down=NULL;
    return n;
}

stack *new_stack(int freq)
{
    stack *k = (stack*)malloc(sizeof(stack));
    k->freq=freq;
    k->down_stk=NULL;
    k->root=NULL;
    return k;
}

stack *istk(node *n, stack *stk)
{
    if(stk==NULL)
    {
        stack *tmp = new_stack(n->freq);
        tmp->root = n;
        return tmp;
    }
    else if(n->freq > stk->freq)
    {
        stack *tmp = new_stack(n->freq);
        tmp->root = n;
        tmp->down_stk = stk;
        return tmp;
    }
    else if(n->freq == stk->freq)
    {
        n->stk_down = stk->root;
        stk->root = n;
        return stk;
    }
    else
    {
        stk->down_stk = istk(n,stk->down_stk);
        return stk;
    }
}

void in_stk(node *n, stkstk *stk)
{
    stk->root=istk(n,stk->root);
}

node *update(node *root, stkstk *stk)
{
    stack *pos = stk->root;
    while(pos->freq!=root->freq)
    {
        pos = pos->down_stk;
    }
    node *pos2 = pos->root;
    if(pos2==root)
    {
        pos->root=root->stk_down;
    }
    else
    {
        while(pos2->stk_down!=root)
        {
            pos2=pos2->stk_down;
        }
        pos2->stk_down=root->stk_down;
    }
    root->freq+=1;
    root->stk_down=NULL;
    in_stk(root,stk);
    return root;
}

node *insert(node *root, int key, stkstk *stk)
{
    if(root==NULL)
    {
        node *k = new_node(key);
        in_stk(k,stk);
        return k;
    }
    else if(root->key==key)
    {
        return update(root,stk);
    }
    else if(key < root->key)
    {
        root->lftptr = insert(root->lftptr,key,stk);
    }
    else
        root->rhtptr = insert(root->rhtptr,key,stk);
    return root;
}

int printstack(node *stk, int count, int lim)
{
    if(count>=lim)
    {
        return count;
    }
    if(count>0)
    {
        printf(" ");
    }
    printf("%d", stk->key);
    int c=count+1;
    if(stk->stk_down==NULL)
        return c;
    else
        c=printstack(stk->stk_down,c,lim);
    return c;
}

void printstk(stkstk *stk,int noprt)
{
    int count = 0;
    stack *cur = stk->root;
    while(count<noprt)
    {
        count = printstack(cur->root,count,noprt);
        cur = cur->down_stk;
    }
}

node *frem(node *gc)
{
    gc->lftptr = (gc->lftptr!=NULL)?frem(gc->lftptr):NULL;
    gc->rhtptr = (gc->rhtptr!=NULL)?frem(gc->rhtptr):NULL;
    free(gc);
    return NULL;
}

stack *clr(stack *stk)
{
    if(stk->down_stk!=NULL)
    {
        stk->down_stk=clr(stk->down_stk);
    }
    free(stk);
    return NULL;
}

int main(void)
{
    BST tree;
    stkstk stk;
    int lp;
    scanf("%d", &lp);
    for(int a=0;a<lp;a++)
    {
        tree.root=NULL;
        stk.root=NULL;
        int ca, nf;
        scanf("%d %d",&ca,&nf);
        for(int b=0;b<ca;b++)
        {
            int tmp;
            scanf("%d",&tmp);
            tree.root=insert(tree.root,tmp,&stk);
        }
        printstk(&stk,nf);
        printf("\n");
        tree.root=frem(tree.root);
        stk.root=clr(stk.root);
    }
    return 0;
}
