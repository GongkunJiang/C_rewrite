#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>

int bin2dec(char *str);
int main(){
   char *a = "1111";
   printf("%s\n",a);
   int b = bin2dec(a);
   printf("%d\n",b);
}

int bin2dec(char *str){
	int i ,num=0,len;
	len = strlen(str);
	for(i = len - 1;i>=0;i-- ){
		num = num*2 + (str[i] - 48);	//'0'µÄasciiÎª48 
	}
	
	return num;
}
