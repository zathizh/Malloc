//
//  main.c
//  malloc
//
//  Created by Sathish Bowatta on 10/27/15.
//  Copyright © 2015 Sathish Bowatta. All rights reserved.
//

#include <stdio.h>
#include "mymalloc.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    int *p = (int *)MyMalloc(1000*sizeof(int));
    printf("%p\n", p);
    char *q = (char *)MyMalloc(1000);
    printf("%p\n", q);
    int *r = (int *)MyMalloc(1000);
    printf("%p\n", r);
    int *t = (int *)MyMalloc(1000);
    printf("%p\n", t);
    MyFree(t);
    int  *l = (int *)MyMalloc(1000);
    printf("%p\n", l);
    MyFree(q);
    MyFree(r);
    char *x = (char *)MyMalloc(1000);
    printf("%p\n", x);
    
    
    return 0;
}
