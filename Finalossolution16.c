7
#include<stdio.h> 
 int main() 
  { 
 
     int cnt,j,u,re,flag=0; 
     double time,TQ;
     double WT=0,TAT=0,AT[10],BT[10],rt[10]; 
     printf("Enter Total Process:\t "); 
     scanf("%d",&u); 
     re=u; 
     for(cnt=0;cnt<u;cnt++) 
      { 
        printf("Enter Arrival Time" ,cnt+1); 
        scanf("%d",&AT[cnt]); 
        printf("EnterBurst Time for  Process Number %d :",cnt+1); 
        scanf("%d",&BT[cnt]); 
        rt[cnt]=BT[cnt]; 
      } 
        printf("Enter Time Quantum:\t"); 
        scanf("%d",&TQ); 
        printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
    for(time=0,cnt=0;re!=0;) 
     { 
    if(rt[cnt]<=TQ && rt[cnt]>0) 
    { 
      time+=rt[cnt]; 
      rt[cnt]=0; 
      flag=1; 
    } 
    else if(rt[cnt]>0) 
    { 
      rt[cnt]-=TQ; 
      time+=TQ; 
    } 
    if(rt[cnt]==0 && flag==1) 
    { 
      re--; 
      printf("P[%d]\t|\t%d\t|\t%d\n",cnt+1,time-AT[cnt],time-AT[cnt]-BT[cnt]); 
      
      WT+=time-AT[cnt]-BT[cnt]; 
      TAT+=time-AT[cnt]; 
      flag=0; 
    } 
    if(cnt==u-1) 
      cnt=0; 
    else if(AT[cnt+1]<=time) 
      cnt++; 
    else 
      cnt=0; 
  } 
  printf("\nAverage Waiting Time= %f\n",WT*1.0/u); 
  printf("Avg Turnaround Time = %f",TAT*1.0/u); 
  
  return 0; 
}

