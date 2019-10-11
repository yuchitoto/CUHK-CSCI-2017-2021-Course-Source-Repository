#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node{
    int num;
    struct node *prev, *next;
}node;

typedef struct determined_node{
    struct node *num;
    int stack;  //0:null -1:dp 1:a 2:b
    struct determined_node *prev, *next;
}determined_node;

typedef struct list{
    struct node *init, *end;
}list;

typedef struct group{
    struct determined_node *init, *end;
    bool d[3];  //0:same stack 1:diff stack
    struct group *prev, *next;
}group;

typedef struct group_list{
    struct group *init, *end;
}group_list;

void n_link_next(node a, node b)
{
    a.next = &b;
    b.prev = &a;
}

void dn_link_next(determined_node a, determined_node b)
{
    a.next = &b;
    b.prev = &a;
}

void g_link_next(group a, group b)
{
    a.next=&b;
    b.prev=&a;
}

void connect(group a, group b)
{
}

void new_list(int n, char *line)
{
    char *k=strtok(line," ");
    while(k!=NULL)
    {

    }
}

void new_group(void)
{
}

int main(void)
{
    int lp;
    scanf("%d",&lp);
    for(int c=0;c<lp;c++)
    {
        int k;
        scanf("%d",&k);
        char line[4000];
        gets(line);
        new_list(k,line);
    }
    return 0;
}
