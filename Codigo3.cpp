#include <stdio.h>

void functionA(int n);

void functionB(int n);

void functionA(int n){
	if(n>0){
		printf("A:%d\n",n);
		functionB(n-1);
	}
}

void functionB(int n){
	if (n>1){
		printf("B:%d\n",n);
		functionA(n/2);
	}
}

int main(){
	int n = 10;
	functionA(n);
	return 0;
}
