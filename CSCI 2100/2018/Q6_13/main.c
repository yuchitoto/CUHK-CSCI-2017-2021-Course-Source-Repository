#include <stdio.h>
#include <stdlib.h>

/*double median(int l, int *arr)
{
    //printf("%d %d\n",l/2,l/2-((l%2==0)?1:0));
    return ((double)(arr[l/2]+arr[l/2-((l%2==0)?1:0)]))/2.0;
}

int *mergesort_merg(int a, int *arrA, int b, int *arrB)
{
    int ca=0;
    int cb=0;
    int c=0;
    int *ans = (int*)malloc((a+b)*sizeof(int));

    while(ca<a && cb<a)
    {
        if(arrB[cb]<arrA[ca])
        {
            ans[c]=arrB[cb];
            cb++;
        }
        else
        {
            ans[c]=arrA[ca];
            ca++;
        }
        c++;
    }

    while(ca<a)
    {
        ans[c]=arrA[ca];
        ca++;
        c++;
    }

    while(cb<b)
    {
        ans[c]=arrB[cb];
        cb++;
        c++;
    }

    return ans;
}*/

double median2(int a, int *arrA, int b, int *arrB)
{
    int loc = (a+b)/2;
    int ansA=0;
    int ansB=0;
    int ca=0;
    int cb=0;
    int c=0;

    while(ca<a && cb<b && c<=loc)
    {
        ansA=ansB;
        if(arrB[cb]<arrA[ca])
        {
            ansB=arrB[cb];
            cb++;
        }
        else
        {
            ansB=arrA[ca];
            ca++;
        }
        c++;
    }

    while(c<=loc && ca<a)
    {
        ansA=ansB;
        ansB=arrA[ca];
        ca++;
        c++;
    }

    while(c<=loc && cb<b)
    {
        ansA=ansB;
        ansB=arrB[cb];
        cb++;
        c++;
    }

    if((a+b)%2==0)
        return ((double)(ansA+ansB))/2.0;
    else
        return (double)ansB;
}

int main()
{
    int lp, a, b/*, *tot*/;
    double ans;
    scanf("%d",&lp);
    for(int c=0;c<lp;c++)
    {
        scanf("%d %d",&a,&b);
        int arrA[a], arrB[b];
        for(int t=0;t<a;t++)
        {
            scanf("%d",&arrA[t]);
        }
        for(int t=0;t<b;t++)
        {
            scanf("%d",&arrB[t]);
        }

        /*tot = mergesort_merg(a,arrA,b,arrB);

        for(int t=0;t<a+b;t++)
            printf("%d ",tot[t]);
        printf("\n");

        ans = median(a+b,tot);

        free(tot);*/

        ans = median2(a,arrA,b,arrB);

        printf("%.1f\n",ans);
    }
    return 0;
}
