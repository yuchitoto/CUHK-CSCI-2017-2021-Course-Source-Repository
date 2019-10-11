#include <stdio.h>
#include <stdlib.h>

#define HASHLOAD 0.75
#define HASHFUNC(key,tbsize) (key%tbsize)

typedef struct node{
	int data;
	int freq;
	struct node *nextstk;
}node;

typedef struct hashtable{
	int tbsize;
	struct node **hsh;
}hashtable;

typedef struct stack{
	int root;
	int freq;
	struct stack *nextstk;
}stack;

typedef struct stkstack{
	struct stack *root;
}stkstack;

hashtable *initht(int num_input)
{
	hashtable *t = malloc(sizeof(hashtable));
	t->tbsize = (int)((double)num_input/HASHLOAD);
	t->hsh = (node**)malloc(sizeof(node)*t->tbsize);
	for(int i=0;i<t->tbsize;i++)
	{
		node *item = (node*)malloc(sizeof(node));
		item->data=-1;
		item->freq=0;
		item->nextstk=NULL;
		t->hsh[i]=item;
	}
	return t;
}

hashtable *deshtb(hashtable *gc)
{
	for(int i=0;i<gc->tbsize;i++)
	{
		free(gc->hsh[i]);
	}
	free(gc->hsh);
	free(gc);
	return NULL;
}

//stack func
stack *new_stack(stack *stk, int freq)
{
	stack *tmp = (stack*)malloc(sizeof(stack));
	tmp->freq = freq;
	tmp->nextstk = stk;
	tmp->root = -1;	//uninit
	return tmp;
}

void in_stk(int loc, node *ht, stkstack *hp)
{
	int freq = ht[loc].freq;
	stack *tmp = hp->root;
	if(tmp->root<0 || freq>tmp->freq){
		hp->root = new_stack(hp->root, freq);
		hp->root->root = loc;
	}
	else
	{
		while(freq<tmp)
		{
			tmp=tmp->nextstk;
		}
		ht[loc].nextstk = tmp->root;
		tmp->root = loc;
	}
}

int printstack(int ptr, int count, int lim, hashtable *hs)
{
	if(count>=lim)
	{
		return count;
	}
	if(count>0)
	{
		printf(" ");
	}
	printf("%d", hs[ptr].key);
	int c=count+1;
	if(ptr<0)
	return c;
	else
	c=printstack(hs[ptr]->nextstk,c,lim,hs);
	return c;
}

void printstk(stkstack *stk,int lim,hash *hs)
{
	int count=0;
	stack *ptr = stk->root;
	while(count<lim)
	{
		count = printstack(ptr->root,count,lim,hs);
		ptr = ptr->nextstk;
	}
}

int find(int key, hashtable *htb)
{
	int hashIndex = HASHFUNC(key,htb->tbsize);
	while(htb->hsh[hashIndex].freq>0)
	{
		if(htb->hsh[hashIndex].data==key)
		return hashIndex;
		hashIndex++;
	}
	return -1;
}

void insert(int key, hashtable *htb, stkstack *stk)
{
	int hashkey = HASHFUNC(key,htb->tbsize);
	int loc;
	if((loc=find(key,htb))!=-1)
	{
		htb->hsh[loc]->freq+=1;
		//update()
	}
	else
	{
        htb->hsh[loc].data = key;
        htb->hsh[loc].freq = 1;
        in_stk(loc,*htb->hsh[loc],stk);
	}
}

int main(void)
{
	int lp;
	stkstack cap;
	scanf("%d",&lp);
	for(int a=0;a<lp;a++)
	{
		cap.root = new_stack(NULL,1);
		int ca, nf;
		scanf("&d %d", &ca, &nf);
		int h = (int)((double)c / HASHLOAD);
		hash ht[h];
		for(int b=0;b<h;b++)
		ht[b].occ = 0;
		for(int b=0;b<ca;b++)
		{
			int tmp;
			scanf("%d", &tmp);
			hashing(tmp, h, &ht, &cap);
		}
		printstk(&cap,nf,&ht);
	}
}
