#include <stdio.h>
#include <stdlib.h>

int systime=0;
void input(int n,int m,int arr[n][m]);
void output(int m,int n,int arr[m][n]);
void swap(int*,int*);
void sortbyburst(int a,int b,int arr[a][b]);
void sortbyarrival(int a,int b,int arr[a][b]);
void sortbypriority(int a,int b,int arr[a][b]);




int main()
{
  int num;
  system("clear");
  printf("\n--------------------------------------------------------------------\n");
  printf("\nEnter number of processes : ");
  scanf("%d",&num);
  int table[num][4];
  input(num,4,table);
  printf("\n--------------------------------------------------------------------\n");
  printf("\nEntered input : \n");
  output(num,4,table);
  return 0;

}

void fcfs(int rows, int cols, int thisarray[rows][cols])
{
  printf("\nFIRST COME FIRST SERVE.\n");

  systime=0;
  sortbyarrival(rows,cols,thisarray);
  int startsystime[rows],endsystemtime[rows],responsetime[rows],bt[rows],wt[rows],tat[rows];
  float wtavg,tatavg;
  wt[0] = wtavg = 0;
	tat[0] = tatavg = tble[0][2];
  systime=thisarray[0][1];
  startsystime[0]=thisarray[0][1];
  for(i=1;i<row;i++)
	{
    while(systime<thisarray[i][1])
    {
      systime++;
    }
    startsystime[i]=systime;

		wt[i] = wt[i-1] +tble[i-1][2];
		tat[i] = tat[i-1] +tble[i][2];
		wtavg = wtavg + wt[i];
		tatavg = tatavg + tat[i];
	}



void input(int n,int m,int arr[n][m])   //takes input to table
{
  int i;
  printf("\nEnter details of %d processes : \n(!!!!  1 is the highest priority  !!!!)",n);
  for (i=0;i<n;i++)
  {
    printf("\n\tEnter details of process %d : ",i);
    int inp;
    arr[i][0]=i;
    printf("\n\t\tEnter arrival time of process %d : ",i);
    scanf("%d",&inp);
    arr[i][1]=inp;
    printf("\n\t\tEnter burst  time of process %d : ",i);
    scanf("%d",&inp);
    arr[i][2]=inp;
    printf("\n\t\tEnter priority of process %d : " ,i);
    scanf("%d",&inp);
    arr[i][3]=inp;
  }
}
void output(int m,int n,int arr[m][n])     //Prints input table
{
  int i;
  printf("\tProcess\tArrival time\tBurst time\tPriority");
  for(i=0;i<m;i++)
  {
    printf("\n");

    printf("\tP%d \t%d \t\t%d \t\t%d",arr[i][0],arr[i][1],arr[i][2],arr[i][3]);
  }
  printf("\n");
}
void sortbyarrival(int a,int b,int arr[a][b]) //sorts table by arrival time
{
  int i,j;
  for(i=0;i<a-1;i++)
  {
    for(j=0;j<a-i-1;j++)
    {
      if (arr[j][1] > arr[j+1][1])
      {
            swap(&arr[j][1], &arr[j+1][1]);
            swap(&arr[j][0], &arr[j+1][0]);
            swap(&arr[j][2], &arr[j+1][2]);
            swap(&arr[j][3], &arr[j+1][3]);
      }
    }
  }
  printf("\nEntered input sorted by arrival time : \n");
  output(a,b,arr);
}
void sortbyburst(int a,int b,int arr[a][b])   //sorts table by burst time
{
  printf("\nEntered input sorted by burst time : \n");
  int i,j;
  for(i=0;i<a-1;i++)
  {
    for(j=0;j<a-i-1;j++)
    {
      if (arr[j][2] > arr[j+1][2])
      {
            swap(&arr[j][1], &arr[j+1][1]);
            swap(&arr[j][0], &arr[j+1][0]);
            swap(&arr[j][2], &arr[j+1][2]);
            swap(&arr[j][3], &arr[j+1][3]);
      }
    }
  }
  output(a,b,arr);
}
void sortbypriority(int a,int b,int arr[a][b])     //Sorts table by priority   1 being the highest
{
  printf("\nEntered input sorted by priority : \n");
  int i,j;
  for(i=0;i<a-1;i++)
  {
    for(j=0;j<a-i-1;j++)
    {
      if (arr[j][3] > arr[j+1][3])
      {
            swap(&arr[j][1], &arr[j+1][1]);
            swap(&arr[j][0], &arr[j+1][0]);
            swap(&arr[j][2], &arr[j+1][2]);
            swap(&arr[j][3], &arr[j+1][3]);
      }
    }
  }
  output(a,b,arr);
}
