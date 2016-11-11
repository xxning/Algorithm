#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void LCS_LENGTH(char *X,char *Y);
void PRINT_LCS(int **b,char *A1,int i,int j);

char In_file[2][23]={"./ex2/input/inputA.txt",
					"./ex2/input/inputB.txt"
					};
					
char Out_LCS[2][31]={"./ex2/output/size1/output2.txt",
					"./ex2/output/size2/output2.txt"
					};
					
char Out_Time[2][30]={"./ex2/output/size1/time2.txt",
					"./ex2/output/size2/time2.txt"
					};

char *A1,*A2,*A3,*A4,*A5,*A6;
char *B1,*B2,*B3,*B4,*B5,*B6;
char *Lcs=(char*)malloc(25*sizeof(char));
int chose;
FILE *OutL,*OutT;
int **b,**c;
int len;
struct timespec time_start={0,0},time_end={0,0};
double Time;

int main(int argc,char *argv[]){
	
	FILE *input;
	char file[23];
	char OutLcs[31];
	char OutTime[30];
	chose=atoi(argv[1]);
	strcpy(file,In_file[chose-1]);
	strcpy(OutLcs,Out_LCS[chose-1]);
	strcpy(OutTime,Out_Time[chose-1]);	
	input=fopen(file,"r");
	OutL=fopen(OutLcs,"w");
	OutT=fopen(OutTime,"w");
	if(!input||!OutL||!OutT){
		printf("error:can't open objcct file.\n");
		exit(1);
	}
	if(chose==1){
		A1=(char*)malloc(15*sizeof(char));
		A2=(char*)malloc(15*sizeof(char));
		A3=(char*)malloc(15*sizeof(char));
		A4=(char*)malloc(15*sizeof(char));
		A5=(char*)malloc(15*sizeof(char));
		A6=(char*)malloc(15*sizeof(char));
		B1=(char*)malloc(10*sizeof(char));
		B2=(char*)malloc(20*sizeof(char));
		B3=(char*)malloc(30*sizeof(char));
		B4=(char*)malloc(40*sizeof(char));
		B5=(char*)malloc(50*sizeof(char));
		B6=(char*)malloc(60*sizeof(char));
		fscanf(input,"%s",A1);
		fscanf(input,"%s",B1);
		fscanf(input,"%s",A2);
		fscanf(input,"%s",B2);
		fscanf(input,"%s",A3);
		fscanf(input,"%s",B3);
		fscanf(input,"%s",A4);
		fscanf(input,"%s",B4);
		fscanf(input,"%s",A5);
		fscanf(input,"%s",B5);
		fscanf(input,"%s",A6);
		fscanf(input,"%s",B6);
		int i,length;
		int l1,l2;
//*************************************************
//*************************************************	
//A1,B1	
		l1=strlen(A1);
		l2=strlen(B1);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}
		
		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A1,B1);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (15,10):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A1,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		l1=strlen(A2);
		l2=strlen(B2);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}

		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A2,B2);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (15,20):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A2,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		l1=strlen(A3);
		l2=strlen(B3);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}
		
		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A3,B3);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (15,30):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A3,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		l1=strlen(A4);
		l2=strlen(B4);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}
		
		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A4,B4);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (15,40):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A4,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		l1=strlen(A5);
		l2=strlen(B5);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}
		
		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A5,B5);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (15,50):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A5,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		l1=strlen(A6);
		l2=strlen(B6);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}
		
		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A6,B6);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (15,60):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A6,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		printf("Complete ex2:Group1\n");
	} 
	else{
		A1=(char*)malloc(15*sizeof(char));
		A2=(char*)malloc(30*sizeof(char));
		A3=(char*)malloc(45*sizeof(char));
		A4=(char*)malloc(60*sizeof(char));
		A5=(char*)malloc(75*sizeof(char));
		A6=(char*)malloc(90*sizeof(char));
		B1=(char*)malloc(25*sizeof(char));
		B2=(char*)malloc(25*sizeof(char));
		B3=(char*)malloc(25*sizeof(char));
		B4=(char*)malloc(25*sizeof(char));
		B5=(char*)malloc(25*sizeof(char));
		B6=(char*)malloc(25*sizeof(char));
		fscanf(input,"%s",A1);
		fscanf(input,"%s",B1);
		fscanf(input,"%s",A2);
		fscanf(input,"%s",B2);
		fscanf(input,"%s",A3);
		fscanf(input,"%s",B3);
		fscanf(input,"%s",A4);
		fscanf(input,"%s",B4);
		fscanf(input,"%s",A5);
		fscanf(input,"%s",B5);
		fscanf(input,"%s",A6);
		fscanf(input,"%s",B6);
		int i,j,length;
		int l1,l2;
//*************************************************
//*************************************************	
//A1,B1	
		l1=strlen(A1);
		l2=strlen(B1);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}

		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A1,B1);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (15,25):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A1,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		l1=strlen(A2);
		l2=strlen(B2);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}
		
		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A2,B2);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (30,25):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A2,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		l1=strlen(A3);
		l2=strlen(B3);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}
		
		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A3,B3);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (45,25):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A3,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		l1=strlen(A4);
		l2=strlen(B4);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}
		
		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A4,B4);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (60,25):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A4,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		l1=strlen(A5);
		l2=strlen(B5);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}

		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A5,B5);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (75,25):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A5,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		l1=strlen(A6);
		l2=strlen(B6);
		b=(int**)malloc((l1+1)*sizeof(int*));
		c=(int**)malloc((l1+1)*sizeof(int*));
		for(i=0;i<l1+1;i++){
			b[i]=(int*)malloc((l2+1)*sizeof(int));
			c[i]=(int*)malloc((l2+1)*sizeof(int));
		}
		
		clock_gettime(CLOCK_REALTIME,&time_start);		
		LCS_LENGTH(A6,B6);
		clock_gettime(CLOCK_REALTIME,&time_end);
		Time=(double)(time_end.tv_nsec-time_start.tv_nsec); 
		fprintf(OutT,"Time of (90,25):%lf\n",Time);

		len=c[l1][l2];
		length=len;
		PRINT_LCS(b,A6,l1,l2);
		Lcs[length]='\0';
		fprintf(OutL,"Length:%d\nLCS:%s\n",length,Lcs);
		for(i=0;i<l1+1;i++){
			free(b[i]);
			free(c[i]);
		}
		free(b);
		free(c);
//*************************************************
//*************************************************	
		printf("Complete ex2:Group2\n");
	}
	fclose(input);
	fclose(OutL);
	fclose(OutT);
	
	return 0;
}

void LCS_LENGTH(char *X,char *Y){
	
	int m,n;
	m=strlen(X);
	n=strlen(Y);
	int i,j;
	for(i=1;i<=m;i++)
		c[i][0]=0;
	for(j=0;j<=n;j++)
		c[0][j]=0;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){
			if(X[i-1]==Y[j-1]){
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]=2;
			}
			else if(c[i-1][j]>=c[i][j-1]){
				c[i][j]=c[i-1][j];
				b[i][j]=1;
			}
			else{
				c[i][j]=c[i][j-1];
				b[i][j]=3;
			}
		}
	}	
}

void PRINT_LCS(int **b,char *X,int i,int j){
	
	if(i==0||j==0)
		return;
	if(b[i][j]==2){
		Lcs[--len]=X[i-1];
		PRINT_LCS(b,X,i-1,j-1);
	}
	else if(b[i][j]==1)
		PRINT_LCS(b,X,i-1,j);
	else
		PRINT_LCS(b,X,i,j-1);
}


