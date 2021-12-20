#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
int choce,x,y,r;
sem_t s1,s2;
void *input(void *a)
{

    printf("Enter two numbers:");
    scanf("%d%d",&x,&y);
    sem_post(&s1);
}
void *choice(void *a)
{
    sem_wait(&s1);
    printf("ADD for 1\n");
    printf("Sub for 2\n");
    scanf("%d",&choce);
    sem_post(&s2);
}
void *AddorSub(void *a)
{
   sem_wait(&s2);
   if(choce==1){r=x+y;}
   else{r=x-y;}
}
int main()
{
    sem_init(&s1,0,0);
    sem_init(&s2,0,0);
    pthread_t t,q,m;
    pthread_create(&q,NULL,choice,NULL);
    pthread_create(&m,NULL,AddorSub,NULL);
    pthread_create(&t,NULL,input,NULL);
    pthread_join(t,NULL);
    pthread_join(q,NULL);
    pthread_join(m,NULL);
    printf("Result= %d\n",r);

}
