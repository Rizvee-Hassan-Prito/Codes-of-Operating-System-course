#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t s1,s2,s3,s5,s6,s7;
void* thread_one()
{
    printf("Are");
    sem_post(&s5);
}
void* thread_two()
{
    sem_wait(&s1);
    printf("Roses");
    sem_post(&s6);
}
void* thread_three()
{
    sem_wait(&s2);
    printf("Red");
    sem_post(&s3);
}
void* thread_four()
{
    sem_wait(&s3);
    printf("?");
}
void* thread_five()
{
    sem_wait(&s5);
    printf(" ");
    sem_post(&s1);
    sem_wait(&s6);
    printf(" ");
    sem_post(&s2);
}
int main()
{
    sem_init(&s1,0,0);
    sem_init(&s2,0,0);
    sem_init(&s3,0,0);
    sem_init(&s5,0,0);
    sem_init(&s6,0,0);
    sem_init(&s7,0,0);
    pthread_t t1,t2,t3,t4,t5;
    pthread_create(&t5,NULL,thread_five,NULL);
    pthread_create(&t1,NULL,thread_one,NULL);
    pthread_create(&t2,NULL,thread_two,NULL);
    pthread_create(&t3,NULL,thread_three,NULL);
    pthread_create(&t4,NULL,thread_four,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
}
