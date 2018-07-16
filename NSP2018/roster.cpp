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

	fprintf(fp, "ナース評価値,最大連勤違反,最小連勤違反,最小連休違反,週末最大違反,休暇希望違反,最大勤務数違反,最大勤務時間違反, 最小勤務時間違反,禁止勤務パターン数,");
	fprintf(fp, "ONリクエスト,OFFリクエスト");
	fprintf(fp, "\n");
	for (int i = 0; i < I; i++) {
		fprintf(fp, "%s,", nurse_name[i]);
		for (int t = 0; t < T; t++) {
			fprintf(fp, "%s,", shift_name[X[i][t]]);
		}
		fprintf(fp, "%lld,", nurse_value[i]);

		for (int x = 0; x < 11; x++) {
			fprintf(fp, "%d,", nurse_Score[i][x]);
		}
		
		fprintf(fp, "\n");
	}
	fprintf(fp, "人数違反,");
	for (int t = 0; t < T; t++) {
		fprintf(fp, "%d,", save_Cover_error[t]);
	}
	fprintf(fp, "\n");
	for (int k = 0; k < K; k++) {
		fprintf(fp, "%sの勤務人数,", shift_name[k]);
		for (int t = 0; t < T; t++) {
			fprintf(fp, "%d,", save_Day_ninzu[t][k]);
		}
		fprintf(fp, "\n");
	}
	for (int k = 0; k < K; k++) {
		fprintf(fp, "%sの必要人数,", shift_name[k]);
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

	fprintf(fp, "\n");
	fclose(fp);
}


