#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5
void *PrintMulOfFive(void *n)
{
  int i=n+1,k,g=0;
  if(n==0 ){i=1;}
  for (;i<=n+200;i++)
  {
    k=i*5;
    g=g+k;
    printf("Multiple of 5 with %d =%d\n",i,k);
  }
  printf("Sum of multiples:%d\n",g);
}
int main( )
{
 pthread_t threads;
 int rc, t, k=0;
 for(t=0; t <5; t++) {
 printf ("\nCreating thread %d\n", t);
 rc = pthread_create (&threads, NULL, PrintMulOfFive, (void *) k );
 k+=200;
 pthread_join(threads, NULL);
 if (rc) {
 printf("ERROR; return code from pthread_create() is %d\n", rc);
 exit(NULL);
 }
 }
}
