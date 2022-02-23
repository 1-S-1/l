#include<stdio.h>
int readyQueue[10],front=-1,rear=-1;
float turnSum=0,waitingSum=0,completionSum=0,responseSum=0;
void input(int n,int arr[n][4]);
void output(int m,int arr[m][4]);
void swap(int*,int*);
void sortbyburst(int a,int arr[a][4]);
void sortbyarrival(int a,int arr[a][4]);
void sortbypriority(int a,int arr[a][4]);
void sortbyPID(int a,int arr[a][4]);
int completion(int,int);
int turnAround(int,int);
void waiting(int,int);
void response(int,int);
void printAvg(int);



void nonPreEmptive(int n,int arr[n][4])
{
  int key=0,sysTime=0,flag[n];
  for(int i=0;i<n;++i)
  flag[i]=0;
  printf("\nPID \t COMPLETION TIME \t TURNAROUND TIME \t WAITING TIME \t\t RESPONSE TIME\n");
  while(key<n)
  {
    int temp = sysTime;
    repeat:
    for(int i=0;i<n;++i)
    {
      if(arr[i][1]<=sysTime && flag[i]!=1)
      {
        printf("%d\t\t",arr[i][0]); //printing pid
        int comp = completion(sysTime,arr[i][2]);
        int turn = turnAround(comp,arr[i][1]);
        waiting(turn,arr[i][2]);
        response(arr[i][1],sysTime);
        sysTime += arr[i][2];
        ++key;
        flag[i]=1;
        goto repeat;
      }
    }
    if(temp==sysTime) //to increment system time if no process is executed
    ++sysTime;
  }
  printAvg(n);
}

void preEmptive(int n,int q,int arr[n][4])
{
  int remTime[n],remain=n,time=0,flag=0;
  for(int i=0;i<n;++i) //storing burst time in remTime
    remTime[i] = arr[i][2];
  printf("\nPID \t COMPLETION TIME \t TURNAROUND TIME \t WAITING TIME \t\t RESPONSE TIME\n");
  for(int i=0;remain!=0;)
  {
    if(remTime[i]<=q && remTime[i]>0)
    {
      time += remTime[i];
      remTime[i]=0;
      flag=1;
    }
    else if(remTime[i]>0)
    {
      time += q;
      remTime[i] -= q;
    }
    if(remTime[i]==0 && flag==1)
    {
      remain--;
      printf("%d\t\t%d\t\t\t",arr[i][0],time); //printing pid and completion
      int turn = turnAround(time,arr[i][1]);
      waiting(turn,arr[i][2]);
      response(arr[i][1],time);
      flag=0;
    }
    if(i==n-1)
      i=0;
    else if(arr[i+1][1] <= time)
      i++;
    else
      i=0;
  }
  printAvg(n);
}

void fcfs(int n,int arr[n][4])
{
  printf("\nFIRST COME FIRST SERVE\n");
  sortbyarrival(n,arr);
  nonPreEmptive(n,arr);
}

void sjf(int n,int arr[n][4])
{
  printf("\nSHORTEST JOB FIRST\n");
  sortbyburst(n,arr);
  nonPreEmptive(n,arr);
}
void priority(int n,int arr[n][4])
{
  printf("\nPRIORITY\n");
  sortbypriority(n,arr);
  nonPreEmptive(n,arr);
}
void roundRobin(int n,int q,int arr[n][4])
{
  printf("\nROUND ROBIN\n");
  sortbyPID(n,arr);
  preEmptive(n,q,arr);
}


int main()
{
  int numofpro,q;
  printf("Enter the number of processes : ");
  scanf("%d",&numofpro);
  int procarr[numofpro][4];
  input(numofpro,procarr);
  output(numofpro,procarr);
  fcfs(numofpro,procarr);
  sjf(numofpro,procarr);
  priority(numofpro,procarr);
  printf("\n\nEnter the time Slice : ");
  scanf("%d",&q);
  roundRobin(numofpro,q,procarr);
}
void input(int n,int arr[n][4])   //takes input to table
{
  int i;
  printf("\nEnter details of %d processes : \n(!!!!  1 is the highest priority  !!!!)",n);
  for (i=0;i<n;i++)
  {
    printf("\n\tEnter details of process %d : ",i+1);
    int inp;
    arr[i][0]=(i+1);
    printf("\n\t\tEnter arrival time of process %d : ",i+1);
    scanf("%d",&inp);
    arr[i][1]=inp;
    printf("\n\t\tEnter burst  time of process %d : ",i+1);
    scanf("%d",&inp);
    arr[i][2]=inp;
    printf("\n\t\tEnter priority of process %d : " ,i+1);
    scanf("%d",&inp);
    arr[i][3]=inp;
  }
}
void output(int m,int arr[m][4])     //Prints input table
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
void swap(int *val1, int *val2) //Swap func for sort
{
  int temp = *val1;
  *val1 = *val2;
  *val2 = temp;
}
void sortbyarrival(int a,int arr[a][4]) //sorts table by arrival time
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
  //printf("\nEntered input sorted by arrival time : \n");
  //output(a,arr);
}
void sortbyburst(int a,int arr[a][4])   //sorts table by burst time
{
  //printf("\nEntered input sorted by burst time : \n");
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
  //output(a,arr);
}
void sortbypriority(int a,int arr[a][4])     //Sorts table by priority   1 being the highest
{
  //printf("\nEntered input sorted by priority : \n");
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
  //output(a,arr);
}

void sortbyPID(int a,int arr[a][4])     //Sorts table by PID
{
  //printf("\nEntered input sorted by PID : \n");
  int i,j;
  for(i=0;i<a-1;i++)
  {
    for(j=0;j<a-i-1;j++)
    {
      if (arr[j][0] > arr[j+1][0])
      {
            swap(&arr[j][0], &arr[j+1][0]);
            swap(&arr[j][1], &arr[j+1][1]);
            swap(&arr[j][2], &arr[j+1][2]);
            swap(&arr[j][3], &arr[j+1][3]);
      }
    }
  }
  //output(a,arr);
}

int completion(int sysTime,int burst)
{
  int completion = sysTime + burst;
  printf("%d\t\t\t",completion);
  completionSum += completion;
  return completion;
}

int turnAround(int completion,int arrival)
{
  int turnAround = completion - arrival;
  printf("%d\t\t\t",turnAround);
  turnSum += turnAround;
  return turnAround;
}

void waiting(int turnAround,int burst)
{
  int waiting = turnAround - burst;
  printf("%d\t\t\t",waiting);
  waitingSum += waiting;
}

void response(int arrival,int sysTime)
{
  int response = sysTime - arrival;
  printf("%d\n",response);
  responseSum += response;
}

void printAvg(int n)
{
  printf("\nAverage response time is : %f\n",responseSum/n);
  printf("Average completion time is : %f\n",completionSum/n);
  printf("Average turn around Time is : %f\n",turnSum/n);
  printf("Average waiting time is : %f\n",waitingSum/n);
  responseSum = completionSum = turnSum = waitingSum = 0 ;
}
