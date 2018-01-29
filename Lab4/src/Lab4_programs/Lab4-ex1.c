#include <stdio.h>
 
int main()
{
    char* fileName;
    printf("Specify file name you would like to print to: \n");
    scanf("%s",fileName);//and you scan a string you dont need &
 

    FILE* file1 = fopen(fileName, "a+");
 
    char c;
    while ((c=getchar()) != EOF)
    {
        fprintf(file1, "%c", c);//found fprint if is wrong
    }
 
    fclose(file1);
    
    printf("CTRL+d is a correct ending");
    
    return 0;
}
