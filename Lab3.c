#include<stdio.h>
#include<stdlib.h>

typedef struct process
{
    int at;
    int bt;
    int n;
    int st;
} prcs;

prcs p[50],pr[50],p2[50],t;

int main()
{
    prcs s,s2,s3;
    int i,j=0,n,k=0,k2,k3,m,l,f,time=0,time2;
    printf("Enter the number of process:\n");
    scanf("%d",&n);
    printf("Enter the arrival time and the burst time of processes respectively:\n");
    for(i=0;i<n;i++)
    {
        scanf("%d%d",&p[i].at, &p[i].bt);
        p[i].n=i+1;
    }

 for(j=0;j<n;j++){
 for(i=0;i<n-1;i++)
    {
       if(p[i].at>p[i+1].at)
       {
           s=p[i+1];
           p[i+1]=p[i];
           p[i]=s;
       }
    }
}

for(i=0;i<n;i++)
{
        if(p[i].at==p[i+1].at)
        {
           s=p[i];
           for(j=i+1;j<n;j++)
           {
             if(s.at==p[j].at && s.bt>p[j].bt)
             {
                 s=p[j];
                 k2=j;
             }
           }
           if(p[i].n!=s.n)
           {
             p[k2]=p[i];
           }
           if(i==0){s.st=s.at;time=time+s.bt+s.at;}
           else{s.st=time;time=time+s.bt;}
           p[i]=s;
        }
        else if(time>p[i].at && i!=n-1){
            s=p[i];
            for(j=i;j<n;j++)
            {
             if(time>p[j].at)
             {
               k2=j;
             }
            }
            f=1;
            for(j=i;j<=k2;j++)
            {
               if(s.bt>p[j].bt)
               {
                   f=0;
                   s=p[j];
                   k3=j;
               }
            }
            if(f==0){
            s2=p[k3];
            p[k3]=p[i];
            p[i]=s2;}
            for(j=i;j<n;j++){
             if(p[j].n==s.n)
             {
                p[j].st=time;
             }}
            time=time+s.bt;
        }
        else
        {
             if(i==0){p[i].st=p[i].at;time=time+p[i].bt+p[i].at;}
             else{p[i].st=time;time=time+p[i].bt;}
        }
    }

 for(i=0;i<n;i++)
  {
      printf("Process: %d\tWaiting time: %d \tTurnaround Time: %d \n",p[i].n,(p[i].st-p[i].at),((p[i].st-p[i].at)+p[i].bt));
  }
}

