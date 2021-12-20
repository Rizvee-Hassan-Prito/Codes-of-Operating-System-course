#include <stdio.h>

int main()
{
  int i,j,m,n,k,s=0,g=0,h=0,sum1=0;
  printf("Enter the number of process: ");
  scanf("%d",&m);
  printf("Enter the number of resources: ");
  scanf("%d",&n);
  int prcs[m][n];
  int max [m][n];
  int avl [n];
  int mmry[m],mmry2[m];

  printf("Enter allocation values of processes: \n");
  for(i=0;i<m;i++)
  {
      for(j=0;j<n;j++)
      {
          scanf("%d",&prcs[i][j]);
      }
  }

  printf("Enter max values of resources: \n");
  for(i=0;i<m;i++)
  {
      for(j=0;j<n;j++)
      {
          scanf("%d",&max[i][j]);
      }
  }
  printf("Enter the available resources:\n");
  for(i=0;i<n;i++){scanf("%d",&avl[i]);}

  printf("Safe sequence:\n");
  for(i=0;i<m;i++)
  {
    if(prcs[i][0]==-1){continue;}
    k=0;
    for(j=0;j<n;j++)
    {
      sum1=max[i][j]-prcs[i][j];
      if(sum1>avl[j])
        {
            k=1;
            if(g==0){mmry[s]=i;s++;}
            break;
        }
    }
    if(k==0)
    {
    for(j=0;j<n;j++)
    {
      sum1=max[i][j]-prcs[i][j];
      avl[j]+=prcs[i][j];
    }
    prcs[i][0]=-1;
    if(g==1){h=1;}
    printf("P%d ",i);
    }
    if(s>0 && i==m-1 && g==0|| g==1 && i==mmry[s-1] && h==1 ){i=mmry[0]-1;g=1;h=0;}
  }
  for(j=0;j<n;j++){printf("\n%d ",avl[j]);}
}

