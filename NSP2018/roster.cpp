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

	fprintf(fp, "�i�[�X�]���l,�ő�A�Έᔽ,�ŏ��A�Έᔽ,�ŏ��A�x�ᔽ,�T���ő�ᔽ,�x�Ɋ�]�ᔽ,�ő�Ζ����ᔽ,�ő�Ζ����Ԉᔽ, �ŏ��Ζ����Ԉᔽ,�֎~�Ζ��p�^�[����,");
	fprintf(fp, "ON���N�G�X�g,OFF���N�G�X�g");
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
	fprintf(fp, "�l���ᔽ,");
	for (int t = 0; t < T; t++) {
		fprintf(fp, "%d,", save_Cover_error[t]);
	}
	fprintf(fp, "\n");
	for (int k = 0; k < K; k++) {
		fprintf(fp, "%s�̋Ζ��l��,", shift_name[k]);
		for (int t = 0; t < T; t++) {
			fprintf(fp, "%d,", save_Day_ninzu[t][k]);
		}
		fprintf(fp, "\n");
	}
	for (int k = 0; k < K; k++) {
		fprintf(fp, "%s�̕K�v�l��,", shift_name[k]);
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


