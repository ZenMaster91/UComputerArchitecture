/*
 * singlethread.cpp
 *
 *  Created on: 14 nov. 2017
 *      Author: willy
 */

#include <iostream>
#include "stdio.h"
#include "stdlib.h"
//#include <intrin.h>
#include <math.h>
#include <ctime>

#define TIMES		200
#define SIZE		(1024*1024)
#define MIN_VALUE	-1.0
#define MAX_VALUE	1.0


double *w_vector;
double *u_vector;
double *t_vector;

double* initVector() {
	return (double *) malloc(sizeof(double) * SIZE);
}

double* initVector(int minValue, int maxValue) {
	double *result = initVector();

	for(int i = 0; i < SIZE; i++) {
		result[i] = (((double) rand() / (double) RAND_MAX) * (maxValue - minValue)) + minValue ;
	}

	return result;
}

double maxValueOf(double *vector) {
	double maxValue = -1;
	for(int i = 0; i < SIZE; i++) {
		if(vector[i] > maxValue) {
			maxValue = vector[i];
		}
	}
	return maxValue;
}

double* dif2(double *vector) {
	double *result = initVector();

	for(int i = 0; i < SIZE; i++) {
		if(i == 0) {
			result[i] = (vector[i])/2;
		} else {
			result[i] = ((vector[i] - vector[i-1])/2);
		}
	}

	return result;
}

double* div(double* vector1, double* vector2) {
	double *result = initVector();

	for(int i = 0; i < SIZE; i++) {
		result[i] = (vector1[i]/vector2[i]);
	}

	return result;
}

double* mul(double factor, double* vector) {
	double *result = initVector();

	for(int i = 0; i < SIZE; i++) {
		result[i] = (vector[i]*factor);
	}
	return vector;
}

double mean(double* vector) {
	double result = 0.0;
	for(int i = 0; i < TIMES; i++) {
		result = result + vector[i];
	}
	return (result / TIMES);

}

double variance(double* vector, double mean) {
	double var = 0;
	for( int i = 0; i < TIMES; i++ ) {
  	var += (vector[i] - mean) * (vector[i] - mean);
	}
	return var;
}

int main() {
	w_vector = initVector(MIN_VALUE, MAX_VALUE);
	u_vector = initVector(MIN_VALUE, MAX_VALUE);
	t_vector = initVector(MIN_VALUE, MAX_VALUE);
	double elapsed_secs;
	int executedTimes = 0;
	double* executionTimes = (double *) malloc(sizeof(double) * TIMES);

	while(executedTimes < TIMES) {
		clock_t begin = clock();

		double *result = div(mul(maxValueOf(w_vector),dif2(u_vector)),t_vector);

		clock_t end = clock();

		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		//printf("%f \n", elapsed_secs);
		executionTimes[executedTimes] = elapsed_secs;
		executedTimes++;
		//printf("%f \n", ((double)((double)executedTimes/ (double)TIMES)*100));
	}

	printf("Mean of time elapsed: \t%f \n", mean(executionTimes));
	printf("Variance: \t\t%f \n", variance(executionTimes, mean(executionTimes)));
	printf("Std. Deviation: \t%f \n", sqrt(variance(executionTimes, mean(executionTimes))));

	free(w_vector);
	free(u_vector);
}
