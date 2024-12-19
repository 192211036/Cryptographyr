#include<stdio.h>
#include<string.h>
#include<ctype.h>
void ceasercipher(char text[],int key){
	for(int i=0;text[i]!='\0';i++){
		char ch=text[i];
		if (isalpha(ch)){
		char offset=islower(ch)? 'a':'A';
		text[i]=(ch-offset+key)%26+offset;
	}
}
}
int main(){
	char text[200];
	int key;
	printf("enter the plaintext:");
	fgets(text,sizeof(text),stdin);
	printf("enter the shift value from(1-25):");
	scanf("%d",&key);
	if(key<1||key>25){
		printf("invalid shift operation pls enter between(1-25)!");
		return 1;
	}
	ceasercipher(text,key);
	printf("the encrypted text is:%s",text);
	return 0;
	
}
