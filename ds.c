#include<stdio.h>
void fcfs(int n,int data[][2],int cp)
{
    printf("FCFS\n");
    printf("\n");
    int i,j,seek_time=0;
	for(i=0;i<n;++i)
	{
		printf("executing request at position %d\n",data[i][0]);
		j=cp-data[i][0];
		if(j<0)
		{
			j=j*-1;
		}
		cp=data[i][0];
		seek_time=seek_time+j;
	}
	printf("total seek time  is : %d\n",seek_time);
}
void scan(int n,int data[][2],int cp,int limit)
{
    printf("SCAN\n");
    printf("\n");
    int i,k=0,seek_time=0;
	while(k<n && cp<=limit)
	{
		for(i=0;i<n;++i)
		{
			if(cp==data[i][0]&&data[i][1]==0)
			{
				printf("executing request at position %d\n",data[i][0]);
				k++;
				data[i][1]=1;
			}
		}
		cp++;
		seek_time++;
	}
	if(cp>limit && k<n)
	{
		seek_time--;
		cp--;
		while(k<n)
		{
			for(i=0;i<n;++i)
			{
				if(cp==data[i][0]&&data[i][1]==0)
				{
					printf("executing request at position %d\n",data[i][0]);
					k++;
					data[i][1]=1;
				}
			}
			cp--;
			seek_time++;
		}
	}
	printf("total seek time  is : %d\n",(seek_time-1));
}
void cscan(int n,int data[][2],int cp,int limit)
{
    printf("CSCAN\n");
    printf("\n");
    int i,k=0,seek_time=0;
	while(k<n && cp<=limit)
	{
		for(i=0;i<n;++i)
		{
			if(cp==data[i][0]&&data[i][1]==0)
			{
				printf("executing request at position %d\n",data[i][0]);
				k++;
				data[i][1]=1;
			}
		}
		cp++;
		seek_time++;
	}
	if(cp>limit && k<n)
	{
		seek_time--;
		cp=0;
		while(k<n)
		{
			for(i=0;i<n;++i)
			{
				if(cp==data[i][0]&&data[i][1]==0)
				{
					printf("executing request at position %d\n",data[i][0]);
					k++;
					data[i][1]=1;
				}
			}
			cp++;
			seek_time++;
		}
	}
	printf("total seek time  is : %d\n",(seek_time-1));
}

void main()
{
  int n,i,cp,limit;
	printf("Enter the number of requests\n");
	scanf("%d",&n);
	int data[n][2],data1[n][2];
	for(i=0;i<n;++i)
	{
		printf("Enter the location of data %d\n",i);
		scanf("%d",&data[i][0]);
    data1[i][0]=data[i][0];
		data[i][1]=0;
    data1[i][1]=0;
	}
	printf("enter the curent head position\n");
	scanf("%d",&cp);
	printf("enter the limit of disk \n");
	scanf("%d",&limit);
  printf("\n");
  fcfs(n,data,cp);
  printf("\n");
  scan(n,data,cp,limit);
  printf("\n");
  cscan(n,data1,cp,limit);
}
