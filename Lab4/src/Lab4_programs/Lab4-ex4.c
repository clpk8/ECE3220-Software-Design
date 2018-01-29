
#include<stdio.h>
#include<string.h>
void main()
{
    int i=0;
    char arr1[ 20 ] = "Trumantiger"; //make two array same length
    char arr2[ 20 ];
    while(i<20){
        arr2[ i ] = 'A';
	++i;
    }
    strcpy( arr1 , arr2 );
    for ( i = 0; i < 20; i++){
    	printf("%c",arr1[i]);
    } // i print the string character by character so it does not output grabage
    return 0;
}

