#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "head.h"

void solution::input_model(int x[I][T])
{
	for (int i = 0; i < I; i++) {
		for (int t = 0; t < T; t++)
			X[i][t] = x[i][t];
	}
}

void solution::input_model_nurse(int i, int x[I][T])
{
	for (int t = 0; t < T; t++) {
		X[i][t] = x[i][t];
	}
}

void solution::output_roster(int mode)
{
	char FileName[128];
	FILE *fp;
	sprintf(FileName, "output/ins%d/roster%d.csv", P,mode);

	if ((fp = fopen(FileName, "w")) == NULL) {
		printf("file open error!!\n");
		exit(1);
	}
	fprintf(fp, ",");
	for (int t = 0; t < T; t++) { fprintf(fp, "%d,", t); }

	fprintf(fp, "i[X]Ώl,ΕεAΞα½,Ε¬AΞα½,Ε¬Axα½,TΕεα½,xΙσ]α½,ΕεΞ±α½,ΕεΞ±Τα½, Ε¬Ξ±Τα½,Φ~Ξ±p^[,");
	fprintf(fp, "ONNGXg,OFFNGXg");
	fprintf(fp, "\n");
	for (int i = 0; i < I; i++) {
		fprintf(fp, "%s,", nurse_name[i]);
		//fprintf(fp, "%d,",i);
		for (int t = 0; t < T; t++) {
			//fprintf(fp, "%s,", shift_name[X[i][t]]);
			fprintf(fp, "%d,", X[i][t]);
		}
		fprintf(fp, "%lld,", nurse_value[i]);

		for (int x = 0; x < 11; x++) {
			fprintf(fp, "%d,", nurse_Score[i][x]);
		}

		//fprintf(fp, "%d,", save_nurse_Time[i]);
		for (int k = 0; k < K; k++) {
			fprintf(fp, "%d,", save_nurse_kinmusu[i][k]);
		}
		fprintf(fp, "%d,", save_nurse_Time[i]);
		
		fprintf(fp, "\n");
	}
	fprintf(fp, "lα½,");
	for (int t = 0; t < T; t++) {
		fprintf(fp, "%d,", save_Cover_error[t]);
	}
	fprintf(fp, "\n");
	for (int k = 0; k < K; k++) {
		fprintf(fp, "%sΜΞ±l,", shift_name[k]);
		for (int t = 0; t < T; t++) {
			fprintf(fp, "%d,", save_Day_ninzu[t][k]);
		}
		fprintf(fp, "\n");
	}
	for (int k = 0; k < K; k++) {
		fprintf(fp, "%sΜKvl,", shift_name[k]);
		for (int t = 0; t < T; t++) {
			fprintf(fp, "%d,", Cover[t][k]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
}


void solution::output_value()
{
	FILE *fp;
	char FileName[128];
	double now_time = (double)(clock() - start_clock) / CLOCKS_PER_SEC;

	sprintf(FileName, "output/ins%d/evaluation.csv",P);
	if ((fp = fopen(FileName, "a")) == NULL) {
		printf("file open error!!\n");
		exit(1);
	}


	fprintf(fp, "%d,%lf,%lld,", exp_count, now_time, value);
	for (int i = 0; i < 12; i++) {
		fprintf(fp, "%d,", Score[i]);
	}
	
	fprintf(fp, "%d,",total_in_kinbou);
	fprintf(fp, "%d,", feasible_in_kinbou);
	fprintf(fp, "%d,", infeasibility);
	fprintf(fp, "\n");
	fclose(fp);
}


