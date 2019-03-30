#include<stdio.h> 
 
int main() 
{ 
 
  int count,j,r,remain,flag=0; 
  double time,time_quantum;
  double wait_time=0,turnaround_time=0,arrivaltime[10],Bursttime[10],rt[10]; 
  printf("Enter Total Process:\t "); 
  scanf("%d",&r); 
  remain=r; 
  for(count=0;count<r;count++) 
  { 
    printf("Enter Arrival Time and Burst Time for  Process Number %d :",count+1); 
    scanf("%d",&arrivaltime[count]); 
    scanf("%d",&Bursttime[count]); 
    rt[count]=Bursttime[count]; 
  } 
  printf("Enter Time Quantum:\t"); 
  scanf("%d",&time_quantum); 
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(time=0,count=0;remain!=0;) 
  { 
    if(rt[count]<=time_quantum && rt[count]>0) 
    { 
      time+=rt[count]; 
      rt[count]=0; 
      flag=1; 
    } 
    else if(rt[count]>0) 
    { 
      rt[count]-=time_quantum; 
      time+=time_quantum; 
    } 
    if(rt[count]==0 && flag==1) 
    { 
      remain--; 
      printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-arrivaltime[count],time-arrivaltime[count]-Bursttime[count]); 
      wait_time+=time-arrivaltime[count]-Bursttime[count]; 
      turnaround_time+=time-arrivaltime[count]; 
      flag=0; 
    } 
    if(count==r-1) 
      count=0; 
    else if(arrivaltime[count+1]<=time) 
      count++; 
    else 
      count=0; 
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/r); 
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/r); 
  
  return 0; 
}
