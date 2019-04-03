#include <stdio.h>
#include<unistd>
#include<pthread.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<semaphore.h>


int main()
{   
    pthread_t barber[NUM_BARB],customer[MAX_CUST]; 
    int i,status=0;
   
    sem_init(&customers,0,0);
    sem_init(&barbers,0,0);
    sem_init(&mutex,0,1);   
   
    printf("Barber Shop Opens\n");
    for(i=0;i<NUM_BARB;i++)                    
    {   
       status=pthread_create(&barber[i],NULL,(void *)barberThread,(void*)&i);
       sleep(1);
       if(status!=0)
          printf("No Barber Present... Sorry\n");
    }
    
    for(i=0;i<MAX_CUST;i++)                     
    {   
       status=pthread_create(&customer[i],NULL,(void *)customerThread,(void*)&i);
       wait();                   
       if(status!=0)
           printf("No Customers Yet\n");
    }   
    for(i=0;i<MAX_CUST;i++)       
        pthread_join(customer[i],NULL);
    printf("Barber Shop Closes\n");
    exit(EXIT_SUCCESS); 
}

void customerThread(void *tmp)  
{   
    int mySeat, B;
    sem_wait(&mutex);  
    count++;           
    printf("Customer-%d[Id:%d] Entered Shop. ",count,pthread_self());
    if(numberOfFreeSeats > 0) 
    {
        --numberOfFreeSeats;           
        printf("Customer-%d Sits In Waiting Room.\n",count);
        sitHereNext = (++sitHereNext) % MAX_CHAIRS;  
        mySeat = sitHereNext;
        seatPocket[mySeat] = count;
        sem_post(&mutex);                  
        sem_post(&barbers);               
        sem_wait(&customers);             
        sem_wait(&mutex);                
          B = seatPocket[mySeat];    
          numberOfFreeSeats++;            
        sem_post(&mutex);                       
               
    } 
    else 
    {
       sem_post(&mutex);  
       printf("Customer-%d Finds No Seat & Leaves.\n",count);
    }
    pthread_exit(0);
}

void barberThread(void *tmp)      
{   
    int index = *(int *)(tmp);      
    int myNext, C;
    printf("Barber-%d[Id:%d] Joins Shop. ",index,pthread_self());
    while(1)            
    {   
        printf("Barber-%d Gone To Sleep.\n",index);
        sem_wait(&barbers);         
        sem_wait(&mutex);           
          serveMeNext = (++serveMeNext) % MAX_CHAIRS; 
          myNext = serveMeNext;
          C = seatPocket[myNext];                 
          seatPocket[myNext] = pthread_self();     
        sem_post(&mutex);
        sem_post(&customers);         
              
        printf("Barber-%d Wakes Up & Is Cutting Hair Of Customer-%d.\n",index,C);
        sleep(CUT_TIME);
        printf("Barber-%d Finishes. ",index);
    }
}

void wait()     
{
     int x = rand() % (250000 - 50000 + 1) + 50000; 
     srand(time(NULL));
     usleep(x);     
}
