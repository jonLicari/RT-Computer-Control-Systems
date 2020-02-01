#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_info {
   int x, y, one, two; // Aval, Bval, index i, index j
};

typedef struct thread_info thread_info_t;


int a[4][2], b[2][4];
int c[4][4] = {0};

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

int main(void)
{
	int i, j, k;
	
	pthread_t thread;
	thread_info_t info;

	create(); // Populates the matrices A and B 

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			for (k = 0; k < 2; k++) {

				c[i][j] += a[i][k]*b[k][j];
				/*info.x = (int)a[i][j];
				info.y = b[j][i];
				info.one = i;
				info.two = j;

				pthread_create(&thread, NULL, &func, &info);*/
			}
		}	
	}

   //pthread_join(thread, NULL);

   outprint();	

   pthread_exit(NULL);
}
