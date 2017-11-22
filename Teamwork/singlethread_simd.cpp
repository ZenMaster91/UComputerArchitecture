/*
 * singlethread.cpp
 *
 *  Created on: 14 nov. 2017
 *      Author: willy
 */

#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include <intrin.h>
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

double maxValueOf_SSE(double *vector) {
    double res;
    __m128d *m128vector = (__m128d*) vector;
    __m128d maxval = _mm_setzero_ps();

    for (int i = 0; i < SIZE / 4; i++) {
        maxval = _mm_max_ps(maxval, m128vector[i]);
    }

    for (int i = 0; i < 3; i++) {
        maxval = _mm_max_ps(maxval, _mm_shuffle_ps(maxval, maxval, 0x93));
    }

    _mm_store_ss(&res, maxval);

    return res;
}

double* dif2_SSE(double *vector) {
	//To implement...
}

double* div_SSE(double* vector1, double* vector2) {
	//To implement...
}

double* mul_SSE(double factor, double* vector) {
	//To implement...
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

		double *result = div_SSE(mul_SSE(maxValueOf_SSE(w_vector),dif2_SSE(u_vector)),t_vector);

		clock_t end = clock();

		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		//printf("%f \n", elapsed_secs);
		executionTimes[executedTimes] = elapsed_secs;
		executedTimes++;
		//printf("%f \n", ((double)((double)executedTimes/ (double)TIMES)*100));
	}

	printf("Mean of time elapsed: %f \n", mean(executionTimes));
	printf("Variance: %f \n", variance(executionTimes, mean(executionTimes)));
	printf("Std. Deviation: %f \n", sqrt(variance(executionTimes, mean(executionTimes))));

	free(w_vector);
	free(u_vector);
}
