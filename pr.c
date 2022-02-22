#include <stdio.h>
void fifo(int np,int pages[np],int nf,int frames[nf]);
void lfu(int np,int pages[np],int nf,int frames[nf]);
int findLRU(int time[], int n);
void lru(int np,int pages[np],int nf,int frames[nf]);

int main()
{
    int noofpages,noofframes;
    printf("\nEnter number of pages : ");
    scanf("%d",&noofpages);
    printf("\nEnter number of frames : ");
    scanf("%d",&noofframes);
    int array[noofpages],framearry[noofframes];
    printf("\nEnter Reference string : ");
    for(int i=0;i<noofpages;i++)
    {
        scanf("%d",&array[i]);
    }
    fifo(noofpages,array,noofframes,framearry);
    lfu(noofpages,array,noofframes,framearry);
    lru(noofpages,array,noofframes,framearry);

}

void fifo(int np,int pages[np],int nf,int frames[nf])
{
    printf("\nFIFO\n");
    int pageFaults = 0, m, n, s;
    for(m = 0; m < nf; m++)
    {
        frames[m] = -1;
    }
    for(m = 0; m < np; m++)
    {
        s = 0;
        for(n = 0; n < nf; n++)
        {
            if(pages[m] == frames[n])
            {
                s++;
                pageFaults--;

            }
        }
        pageFaults++;
        if((pageFaults <= nf) && (s == 0))
        {
            frames[m] = pages[m];
        }
        else if(s == 0)
        {
            frames[(pageFaults - 1) % nf] = pages[m];
        }
        printf("\n");
        for(n = 0; n < nf; n++)
        {
            printf("%d\t", frames[n]);
        }
    }
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int findLRU(int time[], int n)
{
    int i, minimum = time[0], pos = 0;
    for(i = 1; i < n; ++i)
    {
        if(time[i] < minimum)
        {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}
void lru(int np,int pages[np],int nf,int frames[nf])
{
    printf("\nLRU\n");
    int counter = 0, time[np], flag1, flag2, i, j, pos, pageFaults = 0;

    for(i = 0; i < nf; i++)
    {
         frames[i] = -1;
    }

    for(i = 0; i < np; ++i)
    {
        flag1 = flag2 = 0;

        for(j = 0; j < nf; ++j)
        {
            if(frames[j] == pages[i])
            {
                 counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }
        if(flag1 == 0)
        {
            for(j = 0; j < nf; ++j)
            {
                if(frames[j] == -1)
                {
                    counter++;
                    pageFaults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }
        if(flag2 == 0)
        {
            pos = findLRU(time, nf);
            counter++;
            pageFaults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }
        printf("\n");
        for(j = 0; j < nf; ++j)
        {
            printf("%d\t", frames[j]);
        }
    }
    printf("\nTotal Page Faults = %d\n", pageFaults);
}


void lfu(int np,int pages[np],int nf,int frames[nf])
{
    printf("\nLFU\n");
    int temp[np], flag1, flag2, flag3, i, j, k, pos, max, pageFaults = 0;
    for(i = 0; i < nf; ++i)
    {
        frames[i] = -1;
    }

    for(i = 0; i < np; ++i)
    {
        flag1 = flag2 = 0;

        for(j = 0; j < nf; ++j)
        {
            if(frames[j] == pages[i])
            {
                flag1 = flag2 = 1;
                break;
            }
        }

        if(flag1 == 0)
        {
            for(j = 0; j < nf; ++j)
            {
                if(frames[j] == -1)
                {
                    pageFaults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }
        }

        if(flag2 == 0)
        {
            flag3 =0;

            for(j = 0; j < nf; ++j)
            {
                temp[j] = -1;

                for(k = i + 1; k < np; ++k)
                {
                    if(frames[j] == pages[k])
                    {
                        temp[j] = k;
                        break;
                    }
                }
            }

            for(j = 0; j < nf; ++j)
            {
                if(temp[j] == -1)
                {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }

            if(flag3 ==0)
            {
                max = temp[0];
                pos = 0;

                for(j = 1; j < nf; ++j)
                {
                    if(temp[j] > max)
                    {
                        max = temp[j];
                        pos = j;
                    }
                }
            }
            frames[pos] = pages[i];
            pageFaults++;
        }
        printf("\n");
        for(j = 0; j < nf; ++j)
        {
            printf("%d\t", frames[j]);
        }
    }
    printf("\nTotal Page Faults = %d\n", pageFaults);
}
