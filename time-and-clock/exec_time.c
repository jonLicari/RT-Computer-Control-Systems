#include <stdio.h>
#include <time.h>

int main()
{
	int i, maxitr = 500000000;
	struct timespec TIME1, TIME2, res;
	double a, b, c, tpi, tmp, ELAPSED_TIME;

	printf("Enter Value of a: ");
	scanf("%lf", &a);

	printf("Enter Value of b: ");
	scanf("%lf", &b);

	clock_gettime(CLOCK_REALTIME, &TIME1);
	
	for(i = 0; i < maxitr; i++)
	{
		c = a/b;
	}

		clock_gettime(CLOCK_REALTIME, &TIME2);


		tmp = (TIME2.tv_sec - TIME1.tv_sec)*1e9;
		tmp += (TIME2.tv_nsec - TIME1.tv_nsec);
		ELAPSED_TIME = tmp;
	
	tpi = ELAPSED_TIME/maxitr;

	printf("Value of c: %lf\n", c);
	printf("Time per iteration: %lf nsec\n", tpi);

	return 0;
}
