                 
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t lock;
int Numofprocess;
int Numofresources;

int Allocation[10][10];
int Max[10][10];
int Need[10][10];

int Available[10];


int checksafe(int required[],int pro)
{
//////Declaration of duplicates
	int Allocation1[10][10];
	int Need1[10][10];
	int Available1[10];

/////Initialiging the duplicates
//Allocation
	for(int i=0;i<Numofprocess;i++)
	{
	     for(int j=0;j<Numofresources;j++)
	     {
	    	Allocation1[i][j] = Allocation[i][j];
	     }

	}

//Available
	for(int j=0;j<Numofresources;j++)
	{
	     Available1[j] = Available[j];
	}

/////////After Asigning the reqired resources state of the machine

if(pro != -1){
	for(int j=0;j<Numofresources;j++)
	{
	    Allocation1[pro][j] = Allocation1[pro][j] + required[j];
	    Available1[j] = Available1[j] - required[j];
	}

}
//Need
	for(int i=0;i<Numofprocess;i++)
	{
	     for(int j=0;j<Numofresources;j++)
	     {
	    	Need1[i][j] = Max[i][j] - Allocation1[i][j];
	     }

	}





/////printing all the values

printf("Available resources:\n");

	for(int j=0;j<Numofresources;j++)
	     {
	    	printf("Resources %d\t%d\n",j,Available1[j]);
	     }
printf("Max matrix:\n");

	for(int i=0;i<Numofprocess;i++)
	{
	     for(int j=0;j<Numofresources;j++)
	     {
	    	printf("%d\t",Max[i][j]);
	     }
	     printf("\n");
	}
printf("Alocation matrix:\n");
	for(int i=0;i<Numofprocess;i++)
	{
	     for(int j=0;j<Numofresources;j++)
	     {
	    	printf("%d\t",Allocation1[i][j]);
	     }
	     printf("\n");
	}
printf("Need matrix:\n");
	for(int i=0;i<Numofprocess;i++)
	{
	     for(int j=0;j<Numofresources;j++)
	     {
	    	printf("%d\t",Need1[i][j]);
	     }
	     printf("\n");
	}

//Checking the safe state
	int flagforunsafe = 0;
	int arrayflag[Numofprocess];/* Array flag declaration and initialization*/
	for(int i=0;i<Numofprocess;i++)
	{
	    arrayflag[i] = 0;//If process is not finished yet... it will kept as Zero
	}
	printf("Everything copied and array flag has been initialized\n");
/* K loop because it will take exactly checks equal to number of processes to be found in safe state */
	for(int k=0;k<Numofprocess;k++)
	{
	   printf("running for k=%d\n",k);
	     //for each time we will check each process to fill it's requirement */
	     for(int i=0;i<Numofprocess;i++)
	     {
		printf("running for k=%d and process =%d\n",k,i);
		if(arrayflag[i] == 0)//Only if it's not compleated yet
		{
		    printf("process %d was not compleated till %dth value of k\n",i,k);
		    int flagforneed = 0;//Used to check if need of process i is less than availability of resource instances
		    for(int j=0;j<Numofresources;j++)
		    {
			if(Available1[j] < Need1[i][j])
			{
			   printf("Available is less than the need in repetition %d for process %d at resource %d\n",k,i,j);
			    flagforneed = 1;
			    break;//If any of resource instanse is less then this process can not be satisfied yet
			}else{printf("Available is more or equal than the need in repetition %d for process %d at resource %d\n",k,i,j);
				}
		    }
		    if(flagforneed == 0)//If process can be satisfied
		    {
			printf("Process %d can be provided all the resources that it needs in the repetition %d\n",i,k);
			arrayflag[i] = 1;//process compleated
			for(int j=0;j<Numofresources;j++)//Updating the Available Array
			{
			   printf("Updated available instances of resource %d from the repetition %d is %d from %d\n",j,k,Available1[j] + 				Allocation1[i][j],Available1[j]);
			   Available1[j] = Available1[j] + Allocation1[i][j];
			}
			printf("Job done for repetition %d\n it has compleated process %d\n",k,i);
			goto next_k;//go for next k value
		    }
		    if(i+1 == Numofprocess)
		    {
		      	flagforunsafe = 1;
		    }
		
		}
		
	     }
//Come here for next k value
next_k: printf("going for next k value till the time it was %d\n",k);
	}

	return flagforunsafe;

}


/*A function to be shared by all the n threads created by user in main function
here each thread will work like a process every time a new thread will start excecution it will ask for the 
extra resources needed by the thread, if it leads the system in safe state then the changes will be made permanent to the allocation matrix and availability list of instances of each resources*/

void function(int pro)
{
	pthread_mutex_lock(&lock);
    int Allocation1[Numofresources];
    printf("Enter request array for process %d\n\n",pro);
    for(int j=0;j<Numofresources;j++)
	{
	    printf("Enter the number of instaces required of resource %d\n",j);
	    scanf("%d",&Allocation1[j]);
	    if(Allocation1[j]>Available[j])
		{
		  printf("Request can not be granted\n");
		  pthread_mutex_unlock(&lock);
		  pthread_exit(NULL);
		}
	}
    if (checksafe(Allocation1,pro) == 1)
	{
	   printf("Request can not be granted\n");
	}else
	{
	printf("Request granted :\n");
	//Update the allocation, Need, Maximum required matrix
	}

	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}









int main()
{

pthread_mutex_init(&lock,NULL);

	printf("Enter number of processes:\n");
	scanf("%d",&Numofprocess);
	fflush(stdin);
	printf("Enter number of Resources:\n");
	scanf("%d",&Numofresources);
	fflush(stdin);
	printf("Enter the allocation matrix:\n");
	for(int i=0;i<Numofprocess;i++)
	{
	     for(int j=0;j<Numofresources;j++)
	     {
	    	printf("Enter the number of instances of resource %d process %d have:\n",j,i);
		scanf("%d",&Allocation[i][j]);	
	     }

	}
	printf("Enter the Maximum need matrix:\n");
	for(int i=0;i<Numofprocess;i++)
	{
	     for(int j=0;j<Numofresources;j++)
	     {
	    	printf("Enter the number of instances of resource %d process %d Need at max:\n",j,i);
		scanf("%d",&Max[i][j]);
	     }

	}

	int Allocation1[Numofresources];
	for(int j=0;j<Numofresources;j++)
	{
	     printf("Enter the number of instances of resource %d have\n",j);
	     scanf("%d",&Available[j]);
	     Allocation1[j] = 0;
	}


	int f = checksafe(Allocation1,-1);
	
	if(f==1){printf("already not in safe state\n");
		return 0;}

	pthread_t proc[Numofprocess];
	for(int i=0;i<Numofprocess;i++)
	{
	    pthread_create(&proc[i],NULL,function,i);
	}
	printf("All threads created\n");
	for(int i=0;i<Numofprocess;i++)
	{
	    pthread_join(proc[i],NULL);
	}
	return 0;
  }

