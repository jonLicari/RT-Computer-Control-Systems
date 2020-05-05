#include "dlab_def.h"
#include <stdio.h>
#include <math.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

struct thread_info {
   float Fs;
   float run_time;
   float kp;
};

typedef struct thread_info thread_info_t;

sem_t data_avail;

#define MAXS 10000		// Max # of samples

float theta[MAXS];		// Stores motor position
float ref[MAXS]; 		// Array for storing reference input
float mtr_pos;			// Motor position in radians
float ti, td, n;		// Integral, Derivative Time constant, 

void *Control(void *arg) {
	int k = 0;
	float uk;	// Control value
    float Fs, kp, run_time;
    float dkt[MAXS]={0}, ek[MAXS]={0}, ikt[MAXS]={0}, pkt[MAXS]={0};

	// Receive info from thread arg
    thread_info_t *info;
	info = (thread_info_t *)arg;
	run_time = info -> run_time;
	Fs = info -> Fs;
	kp = info -> kp;
	
    float t = 1/Fs;	// Sampling Period
	int sample_num = (int)(run_time*Fs); // Number of samples

	while (k<sample_num) {
		sem_wait(&data_avail);			// Wait for semaphore
		mtr_pos = EtoR(ReadEncoder());
		//printf("\n%f", EtoR(ReadEncoder()));
		//printf("\n%f", mtr_pos);
		ek[k] = ref[k] - mtr_pos;			// Calculate tracking error
		//printf("\n%f", ek);		
		if (k<1) {
			ikt[k] = 0;
			dkt[k] = 0;
		}
		else {
			if (ti==0){
				ikt[k]=0;
			}
			else{
				ikt[k] = (ikt[k-1]) + ((kp/ti)*(ek[k-1])*t);
			}
			dkt[k] = ((td/(n*t))*(dkt[k-1])) + (((kp*td*n)/((n*t)+td)*(ek[k]-ek[k-1])));
		}
		
		pkt[k] = kp*ek[k];
		
		uk = pkt[k]  + ikt[k] + dkt[k];				// Control Value
		DtoA(VtoD(uk));
		theta[k] = mtr_pos;
		k++;
	}
	pthread_exit(NULL);
}

void menu_select() {
	printf("\nChoose your player: \n");
	printf("r: Run the control algorithm \n");
	printf("p: Change the value of Kp \n");
	printf("i: Change Integral Time Constant value\n");
	printf("d: Change Differential Time Constant value\n");
	printf("n: Change N value\n");
	//printf("f: Change the sampling frequency Fs \n");
	printf("t: Change the value of total run time Tf \n");
	printf("u: Change the type of inputs (Step or Square)\n");
	printf("	For Step: enter the magnitude of the step\n");
	printf("	For Square: enter the magnitude, frequency, and duty cycle\n");
	printf("g: Plot motor position on screen \n");
	printf("h: Save a hard copy of the plot in Postscript\n");
	printf("q: Exit\n\n");
}

void main() {
	pthread_t control;
	thread_info_t info;
	float mag;					// Reference signal magnitude 
	float freq, dc;				// Frequency of reference signal
	char select, ip_ref;
	int i;
	
	float Kp = 1.0;
	float run_time = 10.0;	// Set initial run time to 10 seconds
	float Fs = 200.0;		// Set initial sampling frequency to 200 Hz
	double mtr_nbr = 2;			// Use 2 for Simulation
	int pts = Fs*run_time;

	// From 2.2
	Kp = 60.3;
	ti = 0.02647;
	td = 0.00662;
	n = 20;

	while(1) {
		menu_select();
		scanf(" %c", &select);

		switch(select) {
			case 'r':
				pts = Fs*run_time;
				sem_init(&data_avail, 0,0);
				Initialize(Fs, mtr_nbr);	// Initialize simulation only
				// Pass variables nicely
				info.Fs = Fs;
				info.run_time = run_time;
				info.kp = Kp;
	
				pthread_create(&control, NULL, &Control, &info);
				pthread_join(control, NULL);
				Terminate();
				sem_destroy(&data_avail);
				break;

			case 'p':
				printf("Enter new Kp value: ");
				scanf("%f", &Kp);
				printf("\nKp = %f", Kp);
				break;

			case 'i':
				printf("\nChange value of Ti: ");
				scanf("%f", &ti);
				printf("\nTi = %f", ti);
				break;				

			case 'd':
				printf("\nChange value of Td: ");
				scanf("%f", &td);
				printf("\nTd = %f", td);
				break;
					
			case 'n':
				printf("\nChange value of N: ");
				scanf("%f", &n);
				printf("\nN = %f", n);
				break;
											
			case 'u':
				printf("\nEnter 's' for Step, 'q' for Square\n");
				scanf(" %c", &ip_ref);

				if (ip_ref == 's') {
					printf("Enter Step Magnitude: ");
					scanf("%f", &mag); 
					mag = (mag*3.14)/180;
					//printf("\nMag = %f", mag);
					for (i = 0; i < pts; i++) {
						ref[i] = mag;
					}
				}
				else {
					printf("\nEnter magnitude, frequency, and duty cycle (%): \n");
					scanf("%f %f %f", &mag, &freq, &dc);
					mag = (mag*3.14)/180;					
					Square(ref, pts, (float) Fs, (float) mag, freq, dc);
				}
				break;

			case 't':
				printf("Enter the total run time: ");
				scanf("%f", &run_time);
				printf("\nTf = %f", run_time);				
				break;
				
			case 'g':
				//plot(ref, theta, Fs, pts, SCREEN,"Ref. & Theta vs. Time", "Time", "Position");
				plot(ref,theta,Fs,(int)(pts),SCREEN,"Step Response","Time","Magnitude");
				break;
				
			case 'h': 
				//Save plot results in Postscript,
				//plot(ref, theta, Fs, pts, PS, "Ref. & Theta vs. Time", "Time", "Position");
				plot(ref,theta,Fs,(int)(pts),PS,"Step Response","Time","Magnitude");	
				break;

			case 'q':
				//Terminate();
				exit(0);

			default:
				printf("INVALID INPUT TRY AGAIN");
				break;
		}
	}	
}
