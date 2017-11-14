/*
 * singlethread.cpp
 *
 *  Created on: 14 nov. 2017
 *      Author: willy
 */

#include <iostream>
#include "stdio.h"
#include "stdlib.h"

#define TIMES			200
#define SIZE			(1024*1024)
#define MIN_VALUE	-1.0
#define MAX_VALUE	1.0


double *w_vector;
double *u_vector;

double* initVector(int minValue, int maxValue, int size) {
	double *result = (double *) malloc(sizeof(double) * SIZE);

	for(int i = 0; i < SIZE; i++) {
		result[i] = (((double) rand() / (double) RAND_MAX) * (maxValue - minValue)) + minValue ;
	}

	return result;
}

double maxValueOf(double *vector) {
	double maxValue = 0;
	for(int i = 0; i < SIZE; i++) {
		if(vector[i] > maxValue) {
			maxValue = vector[i];
		}
	}
	return maxValue;
}

double* dif2(double *vector) {
	double *result = (double *) malloc(sizeof(double) * SIZE);

	for(int i = 0; i < SIZE; i++) {
		if(i == 0) {
			result[i] = (result[i])/2;
		} else {
			result[i] = ((result[i] - result[i-1])/2);
		}
	}

	return result;
}

double* div(double* vector1, double* vector2) {
	double *result = (double *) malloc(sizeof(double) * SIZE);

	for(int i = 0; i < SIZE; i++) {
		result[i] = (vector1[i]/vector2[i]);
	}

	return result;
}

int main() {
	w_vector = initVector(MIN_VALUE, MAX_VALUE, SIZE);
	u_vector = initVector(MIN_VALUE, MAX_VALUE, SIZE);

	printf("hola \n");
}
