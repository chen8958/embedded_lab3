#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[]){
	FILE *fp;
	char *buffer=(char *)malloc(sizeof(char));
	int count = 0;
	fp=fopen("concert.txt","r");
	if(fp==0){
		printf("open file fail!!");
		return 0;
	}
	/*read header*/
	fread(buffer,sizeof(char),1,fp);
	while(*buffer!='\n'){
//		printf("buffer= %c %d count = %d ",*buffer,*buffer,count);
		count=count*10+*buffer-'0';
		fread(buffer,sizeof(char),1,fp);
	}
//	printf("count = %d \n",count);
	char **content = (char **)malloc(count*sizeof(char));
	for(int i=0;i<count;i++){
		content[i]=(char *)malloc(100*sizeof(char));
	}
	int j=0,i=0;
	while(!feof(fp)){
		fread(buffer,sizeof(char),1,fp);
		while(*buffer!='\n'){
			content[i][j++]=*buffer;
			fread(buffer,sizeof(char),1,fp);
		}
		i++;
		j=0;
	}
	for(i=0;i<count;i++){
		printf("%s\n",content[i]);
	}
	/*
	char *buffer=(char*)malloc(5*sizeof(char));
	int i=0;
	while(!feof(fp)){
		fread(buffer,3*sizeof(char),1,fp);
		printf("time=%d%s",i,buffer);
		i++;
	}
	*/
}
