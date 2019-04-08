#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX_CUSTOMERS 25
void *customer(void *n);
void *barber(void *);
void randwait(int secs);
sem_t waitingRoom;
sem_t barberChair;
sem_t barberPillow;
sem_t seatBelt;
int Done = 0;
int main(int argc, char *argv[]) 
{
pthread_t btid;
pthread_t tid[MAX_CUSTOMERS];
long RandSeed;
int i, toCust, Tochair;
int Number[MAX_CUSTOMERS];

printf( "Enter Total Custmors :");
scanf("%d",&toCust) ;
printf("Enter the number of Chairs :"); 
scanf("%d",&Tochair);
if (toCust > MAX_CUSTOMERS) 
{
printf("The maximum number of Customers is %d.\n", MAX_CUSTOMERS);
exit(-1);
}
for (i=0; i<MAX_CUSTOMERS; i++) 
{
Number[i] = i;
}
sem_init(&waitingRoom, 0, Tochair);
sem_init(&barberChair, 0, 1);
sem_init(&barberPillow, 0, 0);
sem_init(&seatBelt, 0, 0);

pthread_create(&btid, NULL, barber, NULL);

for (i=0; i<toCust; i++) 
{
pthread_create(&tid[i], NULL, customer, (void *)&Number[i]);
sleep(1);
}


for (i=0; i<toCust; i++) 
{
pthread_join(tid[i],NULL);
sleep(5);
}
Done = 1;
sem_post(&barberPillow); 
pthread_join(btid,NULL);
}

void *customer(void *number)
 {
int n = *(int *)number;


printf("Customer %d leaving for barber shop.\n", n);
randwait(5);
printf("Customer %d arrived at barber shop.\n", n);
sem_wait(&waitingRoom);
printf("Customer %d entering waiting room.\n", n);
sem_wait(&barberChair);
sem_post(&waitingRoom);
printf("Customer %d waking the barber.\n", n);
sem_post(&barberPillow);
sem_wait(&seatBelt);
sem_post(&barberChair);
printf("Customer %d leaving barber shop.\n", n);
}

void *barber(void *junk) 
{
while (!Done) 
{
sem_wait(&barberPillow);
if (!Done) 
{
printf("The barber is cutting hair\n");
randwait(2);
printf("The barber has finished cutting hair.\n");
sem_post(&seatBelt);
}
else
 {
printf("The barber is going home for the day.\n");
}
}
}
void randwait(int secs) 
{
int len;
len = (int) ((1 * secs) + 1);
sleep(len);
}

