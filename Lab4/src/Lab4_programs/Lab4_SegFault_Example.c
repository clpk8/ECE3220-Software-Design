#include <stdio.h>
#include <string.h>

void tester(int* c, int k) {
	printf("x[%d] = %d\n", k, c[k]);
	c[9999]=1309;//change all the index to a same number
}

int main(int argc, char* argv[]) {
	int i = 0, j, k;
	int x[9999];
	
	while(i < 9999){
		x[i] = i;
		i++;
	}

	printf("Enter an integer between 0 to 9999: ");
	fflush(stdout);
	scanf("%d",&k);

	tester(x, k);
}
