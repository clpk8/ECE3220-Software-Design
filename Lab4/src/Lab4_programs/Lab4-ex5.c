#include<stdio.h>
#include<malloc.h>
void main()
{
    char *a = "hey";
  //  free( a ); you dont need to free because malloc is not used
    a = "hello";
    printf("%s",a);
}

