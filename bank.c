#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>


int Numofprocess;
int Numofresources;

int Allocation[10][10];
int Max[10][10];
int Need[10][10];

int Available[10];


int checksafe()
{
	int i,j,k;
//////Declaration of duplicates
	int Allocation1[10][10];
	int Need1[10][10];
	int Available1[10];

/////Initialiging the duplicates
//Allocation
	for( i=0;i<Numofprocess;i++)
	{
	     for(j=0;j<Numofresources;j++)
	     {
	    	Allocation1[i][j] = Allocation[i][j];
	     }

	}

//Available
	for( j=0;j<Numofresources;j++)
	{
	     Available1[j] = Available[j];
	}

//Need
	for( i=0;i<Numofprocess;i++)
	{
	     for( j=0;j<Numofresources;j++)
	     {
	    	Need1[i][j] = Max[i][j] - Allocation1[i][j];
	     }

	}


//Checking the safe state
	int flagforunsafe = 0;
	int arrayflag[Numofprocess];/* Array flag declaration and initialization*/
	for( i=0;i<Numofprocess;i++)
	{
	    arrayflag[i] = 0;//If process is not finished yet... it will kept as Zero
	}
	
/* K loop because it will take exactly checks equal to number of processes to be found in safe state */
	for( k=0;k<Numofprocess;k++)
	{
	     //for each time we will check each process to fill it's requirement */
	     for( i=0;i<Numofprocess;i++)
	     {
		if(arrayflag[i] == 0)//Only if it's not compleated yet
		{
		    int flagforneed = 0;//Used to check if need of process i is less than availability of resource instances
		    for( j=0;j<Numofresources;j++)
		    {
			if(Available1[j] < Need1[i][j])
			{
			    flagforneed = 1;
			    break;//If any of resource instanse is less then this process can not be satisfied yet
			}
		    }
		    if(flagforneed == 0)//If process can be satisfied
		    {
			arrayflag[i] = 1;//process compleated
			for(j=0;j<Numofresources;j++)//Updating the Available Array
			{
			   Available1[j] = Available1[j] + Allocation1[i][j];
			}
			break;//go for next k value
		    }
		if(i+1 == Numofprocess)
		{
		    flagforunsafe = 1;
		}

		}
		
	    }

	}

	return flagforunsafe;

}

int main()
{
	int i,j;
	printf("Enter number of processes:\n");
	scanf("%d",&Numofprocess);
	fflush(stdin);
	printf("Enter number of Resources:\n");
	scanf("%d",&Numofresources);
	fflush(stdin);
	printf("Enter the allocation matrix:\n");
	for(i=0;i<Numofprocess;i++)
	{
	     for( j=0;j<Numofresources;j++)
	     {
	    	printf("Enter the number of instances of resource %d process %d have:\n",j,i);
		scanf("%d",&Allocation[i][j]);	
	     }

	}
	printf("Enter the Maximum need matrix:\n");
	for( i=0;i<Numofprocess;i++)
	{
	     for(j=0;j<Numofresources;j++)
	     {
	    	printf("Enter the number of instances of resource %d process %d Need at max:\n",j,i);
		scanf("%d",&Max[i][j]);
	     }

	}


	for( j=0;j<Numofresources;j++)
	{
	     printf("Enter the number of instances of resource %d have\n",j);
	     scanf("%d",&Available[j]);
	}


	int f = checksafe();
	
	if(f==1){printf("already not in safe state\n");
		return 0;}


	pthread_t proc[Numofprocess];
	for( i=0;i<Numofprocess;i++)
	{
	   // pthread_create(&proc[i],NULL,function,NULL);
	}

	for( i=0;i<Numofprocess;i++)
	{
	  //  pthread_join(proc[i],NULL);
	}
	return 0;


}

