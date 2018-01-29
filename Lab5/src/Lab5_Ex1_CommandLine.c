// Lab4_Ex1_CommandLine.c
#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0, count;
	while(i < argc){
		printf("argv[%d] = %s, ", i, argv[i]);
		
		count = 0;
		while(argv[i][count++] != '\0');
		
		printf("#of characters (not including string termination char.): %d\n", count-1);
		i++;
	}
	return 0;
}

int i = 0;
while(i < argc){
    if(argv[i][0] == '-'){
        switch(argv[i][0]){
            case 'h':{
                menu();
                break;
            }
            case 'n':{
                
            }
        }
        
    }
