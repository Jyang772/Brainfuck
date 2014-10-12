#include<stdio.h>
#include<stdlib.h>
int main(){
unsigned char* _=(unsigned char*)malloc(32*1024);/*32kB*/if(_==0){printf("MEMORY ERROR!\n");return 1;}
*_ += 48;_ += 1;*_ += 10;
while(*_) {
*_ += -1;_ += -1;putchar(*_);
*_ += 1;_ += 1;}
free(_);
return 0;
}
