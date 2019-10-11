#include <stdio.h>
#include <stdlib.h>

int main()
{
    // define the variables
    int n, i, digit;
    char c;
    // read the line number
    scanf("%d", &n);
    for(i=0; i<n; i++){
        // read and omit the '\n' char at the end of each line
        scanf("%c", &c);
        // read each line
        scanf("%c %d", &c, &digit);
        // print out each line
        printf("%c %d\n", c, digit);
    }
    return 0;
}
