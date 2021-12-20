#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include<semaphore.h>

typedef struct students
{
   int id;
   int num_studentVisit;
   char status[20];
   int help_number;
} std;

int student_number,chrs,ttr,free_tutor=0,checking_student=0,all_help_number=0;
int flag=0,flag2=0,f=0,g=0,checking_number_start=0,p=0,count=1;
std arr[500];
pthread_t student[100],cordntr,tutor[100];


pthread_mutex_t lock;
sem_t smph1,smph2,smph3;

void *Student(void *k){
        int i=k;
        printf("Enter the number of %d student visit the club: \n",arr[i].id);
        scanf("%d",&arr[i].num_studentVisit);
        printf("Enter the total number of help this student needs: \n");
        scanf("%d",&arr[i].help_number);
        flag=flag+arr[i].help_number;
        printf("\n");
}

void *Coordinator(void *n)
{
    sem_wait(&smph1);

    std s;
    int i,j;
    for(i=0;i<n;i++)
    {
    for(j=0;j<n-1;j++)
    {
        if(arr[j].num_studentVisit>arr[j+1].num_studentVisit)
        {
            s=arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=s;
        }
    }
    }
    sem_wait(&smph2);

    while(1)
    {
        if(flag==0){break;}
        if(flag2==ttr){
            sem_post(&smph3);
        }
    }
}

void *Tutor(void* arg)
{
    int k=(int*)arg;
    while(1)
    {
    sem_wait(&smph3);
    pthread_mutex_lock(&lock);
    int i;

    if(arr[checking_student].help_number==0)
    {
        printf("\n");
      strcpy(arr[checking_student].status,"Checked");
    }
    else{
            printf("\n");
        printf("\nTeacher %d is helping...\nStudent %d is taking help ...\n",k,checking_student+1);
        arr[checking_student].help_number--;flag--;
    }

    if(checking_student==chrs-1 && flag!=0||checking_student==student_number-1 && flag!=0)
    {
      checking_student=checking_number_start;
      flag2++;
      pthread_mutex_unlock(&lock);
    }
    else if(checking_student==chrs-1 && flag==0||checking_student==student_number-1 && flag==0)
    {
        if(checking_student==chrs-1 && flag==0)
        {
            if(flag==0){
                    for(i=0;i<chrs;i++)
                    strcpy(arr[i].status,"Checked");
            }
        }
        else
        {
           if(flag==0){
                    for(i=0;i<student_number;i++)
                    strcpy(arr[i].status,"Checked");
            }
        }

       for(i=0;i<student_number;i++){
        if(f!=1){
        printf("\nThe student %d is %s\nThe number of help of this student is %d\n",arr[i].id,arr[i].status,arr[i].help_number);
        }
       }
       f=1;
       pthread_mutex_unlock(&lock);
       break;
    }
    else
    {
       checking_student++;
       flag2++;
       pthread_mutex_unlock(&lock);
    }
    }
}
void tutoring_area()
{
    int i,j;
    printf("\n           Working status and student's status:         \n");
    for(j=0;j<ttr;j++)
    {
        pthread_create(&tutor[j],NULL,Tutor,(void*)j);
    }
    for(j=0;j<ttr;j++)
    sem_post(&smph3);
    sem_post(&smph2);
}
void waiting_area()
{
   int i,j;
   {
    for(i=0;i<student_number;i++)
    {
        arr[i].id=i+1;
        strcpy(arr[i].status,"Unchecked");
        pthread_create(&student[i],NULL,Student,(void*)i);
        pthread_join(student[i],NULL);
    }
    checking_number_start=0;

    pthread_create(&cordntr,NULL,Coordinator,(void*)student_number);
    sem_post(&smph1);

    tutoring_area();


    for(j=0;j<ttr;j++)
    pthread_join(tutor[j],NULL);
    pthread_join(cordntr,NULL);
   }
}


int main()
{
    printf("\n       Enter input numbers:  \n\n");
    int i=0,j,c2;
    printf("Enter the total number of students: \n");
    scanf("%d",&student_number);
    printf("Enter the total number of empty chairs: \n");
    scanf("%d",&chrs);
    c2=chrs;
    printf("Enter the total number of tutors: \n");
    scanf("%d",&ttr);
    p=student_number;

    count=i;
    while(i!=p)
    {
    while(i<c2)
    {
        if(i==p){break;}
        i++;
    }
    student_number=i-count;
    sem_init(&smph1,0,0);
    sem_init(&smph2,0,0);
    sem_init(&smph3,0,0);
    if(student_number<ttr){ttr=student_number;}
    pthread_mutex_init(&lock, NULL);
    printf("\n         Enter input numbers:  \n\n");
    waiting_area();
    c2=c2+chrs;
    count=i;
    checking_student=0,all_help_number=0;
    flag=0,flag2=0,f=0,g=0,checking_number_start=0;
    printf("\n");
    }
}
