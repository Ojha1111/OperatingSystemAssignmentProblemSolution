



semaphore customers = 0;
semaphore barbers = 0;
semaphore cutting = 0;
semaphore mutex = 1;
int customer1 = 0;
void barber() {
while(true) {
wait(customers); //sleep when there are no waiting customers
wait(mutex); //mutex for accessing customers1
customers1 = customers1 - 1;
signal(barbers);
signal(mutex);
cut_hair();
}
}
void customer() {
wait(mutex); //mutex for accessing customers1
if (customers1 < n) {
customers1 = customers1 + 1;
signal(customers);
signal(mutex);
wait(barbers); //wait for available barbers
get_haircut();
}
else { //do nothing (leave) when all chairs are used.
signal(mutex);
}
}
cut_hair(){
waiting(cutting);
}
get_haircut(){
get hair cut for some time;
signal(cutting);
}
