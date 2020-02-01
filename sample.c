#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_info {
   int x, y, one, two; // Aval, Bval, index i, j
};

typedef struct thread_info thread_info_t;


int a[4][2], b[2][4];
volatile int c[4][4] = {0};

void create() {
	int i, j;

	/* POPULATE MATRIX A */
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 2; j++) {
			a[i][j] = (i+1) + (j+1);
			printf("%4d   ", a[i][j]);
		}
		printf("\n");		
	}

	printf("\n\n");

	/* POPULATE MATRIX B */
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			b[i][j] = (i+1) + 2*(j+1);
			printf("%4d   ", b[i][j]);
		}
		printf("\n");
	}		
	printf("\n\n");
}

void outprint() {
	int i, j;
	double sum;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			printf("%4d   ", c[i][j]);
			sum += c[i][j];
		}

		printf("\n");
	}

	printf("\n\nSum is = %f", sum);
}

void *func(void *arg) //Addition
{
   thread_info_t *info;
   int aval, bval, i, j;
   
   info = (thread_info_t *)arg;
   aval = info->x;
   bval = info->y;
   i = info->one;
   j = info->two;

   c[i][j] += aval*bval;
   
   pthread_exit(NULL);   
}

int main(void)
{
	struct timespec time_1, time_2;
	int i, j, k;
	double ex_time = 0.0;
	
	pthread_t thread;
	thread_info_t info;

	// Populates the matrices A and B 
	create(); 

	// Get START time
	clock_gettime(CLOCK_REALTIME, &time_1);
	
	// CALCULATION OF MATRIX MULTIPLICATION
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			for (k = 0; k < 2; k++) {

				//c[i][j] += a[i][k]*b[k][j];
				info.x = a[i][k];
				info.y = b[k][j];
				info.one = i;
				info.two = j;

				pthread_create(&thread, NULL, &func, &info);
				pthread_join(thread, NULL);
			}
		}	
	}

	// Get END time
	clock_gettime(CLOCK_REALTIME, &time_2);

	// COMPUTE CALCULATION TIME
	ex_time = (time_2.tv_nsec - time_1.tv_nsec)/1e09;
	printf("The calculation was performed in %lf [sec]\n\n", ex_time);

   outprint();	

   pthread_exit(NULL);
}
