//cnt=as qa counter
#include<stdio.h> 
 int main() 
  { 
 
     int cnt,j,r,remain,flag=0; 
     double time,time_quantum;
     double wait_time=0,turnaround_time=0,arrivaltime[10],Bursttime[10],rt[10]; 
     printf("Enter Total Process:\t "); 
     scanf("%d",&r); 
     remain=r; 
     for(cnt=0;cnt<r;cnt++) 
      { 
        printf("Enter Arrival Time and Burst Time for  Process Number %d :",cnt+1); 
        scanf("%d",&arrivaltime[cnt]); 
        scanf("%d",&Bursttime[cnt]); 
        rt[cnt]=Bursttime[cnt]; 
      } 
        printf("Enter Time Quantum:\t"); 
        scanf("%d",&time_quantum); 
        printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
    for(time=0,cnt=0;remain!=0;) 
     { 
    if(rt[cnt]<=time_quantum && rt[cnt]>0) 
    { 
      time+=rt[cnt]; 
      rt[cnt]=0; 
      flag=1; 
    } 
    else if(rt[cnt]>0) 
    { 
      rt[cnt]-=time_quantum; 
      time+=time_quantum; 
    } 
    if(rt[cnt]==0 && flag==1) 
    { 
      remain--; 
      printf("P[%d]\t|\t%d\t|\t%d\n",cnt+1,time-arrivaltime[cnt],time-arrivaltime[cnt]-Bursttime[cnt]); 
      wait_time+=time-arrivaltime[cnt]-Bursttime[cnt]; 
      turnaround_time+=time-arrivaltime[cnt]; 
      flag=0; 
    } 
    if(cnt==r-1) 
      cnt=0; 
    else if(arrivaltime[cnt+1]<=time) 
      cnt++; 
    else 
      cnt=0; 
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/r); 
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/r); 
  
  return 0; 
}
