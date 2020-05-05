#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_info {
   int maxitr;
   double exec_time;
};

typedef struct thread_info thread_info_t;

void *func1(void *arg) //Multiplication
{
   struct timespec time_1, time_2;
   double exec_time;
   thread_info_t *info;
   int i, maxitr;
   volatile double a, b, c;

   info = (thread_info_t *)arg;
   maxitr = info->maxitr;

   b = 2.3; c = 4.5;

   exec_time = 0.0;

   clock_gettime(CLOCK_REALTIME, &time_1);

   for (i = 0; i < maxitr ; i++) {
         a = b*c;
   }
         
   clock_gettime(CLOCK_REALTIME, &time_2);

   exec_time = (time_2.tv_sec - time_1.tv_sec)*1.0e9;
   exec_time = exec_time + (time_2.tv_nsec - time_1.tv_nsec);

   exec_time = exec_time/maxitr;

   info->exec_time = exec_time;

   pthread_exit(NULL);
   
}

void *func2(void *arg) // Division
{
   struct timespec time_1, time_2;
   double exec_time;
   thread_info_t *info;
   int i, maxitr;
   volatile double a, b, c;

   info = (thread_info_t *)arg;
   maxitr = info->maxitr;

   b = 2.3; c = 4.5;

   exec_time = 0.0;

   clock_gettime(CLOCK_REALTIME, &time_1);

   for (i = 0; i < maxitr ; i++) {
         a = b/c;
   }
         
   clock_gettime(CLOCK_REALTIME, &time_2);

   exec_time = (time_2.tv_sec - time_1.tv_sec)*1.0e9;
   exec_time = exec_time + (time_2.tv_nsec - time_1.tv_nsec);

   exec_time = exec_time/maxitr;

   info->exec_time = exec_time;

   pthread_exit(NULL);
   
}

void *func3(void *arg) //Addition
{
   struct timespec time_1, time_2;
   double exec_time;
   thread_info_t *info;
   int i, maxitr;
   volatile double a, b, c;

   info = (thread_info_t *)arg;
   maxitr = info->maxitr;

   b = 2.3; c = 4.5;

   exec_time = 0.0;

   clock_gettime(CLOCK_REALTIME, &time_1);

   for (i = 0; i < maxitr ; i++) {
         a = b+c;
   }
         
   clock_gettime(CLOCK_REALTIME, &time_2);

   exec_time = (time_2.tv_sec - time_1.tv_sec)*1.0e9;
   exec_time = exec_time + (time_2.tv_nsec - time_1.tv_nsec);

   exec_time = exec_time/maxitr;
   
   info->exec_time = exec_time;

   pthread_exit(NULL);
   
}

void *func4(void *arg) //Subtraction
{
   struct timespec time_1, time_2;
   double exec_time;
   thread_info_t *info;
   int i, maxitr;
   volatile double a, b, c;

   info = (thread_info_t *)arg;
   maxitr = info->maxitr;

   b = 2.3; c = 4.5;

   exec_time = 0.0;

   clock_gettime(CLOCK_REALTIME, &time_1);

   for (i = 0; i < maxitr ; i++) {
         a = b-c;
   }
         
   clock_gettime(CLOCK_REALTIME, &time_2);

   exec_time = (time_2.tv_sec - time_1.tv_sec)*1.0e9;
   exec_time = exec_time + (time_2.tv_nsec - time_1.tv_nsec);

   exec_time = exec_time/maxitr;
   
   info->exec_time = exec_time;

   pthread_exit(NULL);
   
}

int main(void)
{
   pthread_t thread1;
   pthread_t thread2;
   pthread_t thread3;
   pthread_t thread4;
   thread_info_t info1;
   thread_info_t info2;
   thread_info_t info3;
   thread_info_t info4;
   double maxitr;

   maxitr = 5.0e8;

   info1.maxitr = (int)maxitr;
   info2.maxitr = (int)maxitr;
   info3.maxitr = (int)maxitr;
   info4.maxitr = (int)maxitr;

   if (pthread_create(&thread1, NULL, &func1, &info1) != 0) {
           printf("Error in creating thread 1\n");
           exit(1);
   }
   
   if (pthread_create(&thread2, NULL, &func2, &info2) != 0) {
           printf("Error in creating thread 1\n");
           exit(1);
   }

   if (pthread_create(&thread3, NULL, &func3, &info3) != 0) {
           printf("Error in creating thread 1\n");
           exit(1);
   }

   if (pthread_create(&thread4, NULL, &func4, &info4) != 0) {
           printf("Error in creating thread 1\n");
           exit(1);
   }


   pthread_join(thread1, NULL);
   printf("Exec time for thread1(x) = %lf sec\n", info1.exec_time);
   
   pthread_join(thread2, NULL);
   printf("Exec time for thread2(/) = %lf sec\n", info2.exec_time);

   pthread_join(thread3, NULL);
   printf("Exec time for thread3(+) = %lf sec\n", info3.exec_time);

   pthread_join(thread4, NULL);
   printf("Exec time for thread4(-) = %lf sec\n", info4.exec_time);

   pthread_exit(NULL);
}
