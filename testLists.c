#include <stdlib.h>
#include <stdio.h>
#include "list.h"



int main(int n, char *args[n]) {
    if (n == 1) testLists();

    else {
        printf( "Use: ./list\n");
        exit(1);
    }
    return 0;
}
