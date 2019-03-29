

// Write a program to coordinate the barber and the customers.
//In this problem i am using three semaphores variables.Semaphore customers counts waiting customers; semaphore
//barbers is the number of idle barbers (0 or 1); and mutex is used for mutual exclusion. A
//shared data variable customers1 also counts waiting customers. It is a copy of customers.
//But we need it here because we can’t access the value of semaphores directly. We also
//need a semaphore cutting which ensures that the barber won’t cut another customer’s
//hair before the previous customer leaves.
// shared data
semaphore customers = 0;
semaphore barbers = 0;
semaphore cutting = 0;
semaphore mutex = 1;
int customer1 = 0;
void barber() 
     {
       while(true) 
       {
       wait(customers); //sleep when there are no waiting customers
       wait(mutex); //mutex for accessing customers1 this for
       customers1 = customers1 - 1;
       signal(barbers);
       signal(mutex);
       cut_hair();
       }
     }
void customer() 
  {
       wait(mutex); //mutex for accessing customers1
       if (customers1 < n) 
          {
            customers1 = customers1 + 1;
            signal(customers);
            signal(mutex);
            wait(barbers); //wait for available barbers
            get_haircut();
          }
       else 
          { 
           //do nothing (leave) when all chairs are used.
          signal(mutex);
         }
  }
  cut_hair()
  {
      waiting(cutting);
  }
get_haircut()
   {
     get hair cut for some time;
     signal(cutting);
}
