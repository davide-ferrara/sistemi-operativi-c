#include <stdio.h>

void test1(int *age){
    (*age)++; 
    printf("Age is: %d \n", *age);
}

int main(void){

    int age = 10;
    int *pAge = &age;

    test1(pAge);

    return 0;
}