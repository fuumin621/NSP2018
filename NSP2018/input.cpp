#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "head.h"


FILE *fp;
int i, j, t, k, w, w2, count;
void input_data();//問題データ入力
void get_solution();
clock_t start_clock, end_clock;

int exp_count;
int p_count;
bool debug_flag=true;

int weight_H;
int weight_S;
struct basic_data nurse[I];
char FileName[128];
int Cover[T][K];
int Cover_Weight[T][K][2];//0はunder,1はoverのペナルティ重み
int Shift_Time[K];
bool BWP_data[K + 1][K + 1];//1つ目のシフト→2つ目のシフトが禁止勤務パターンならtrue、そうでないならfalse
int X[I][T];
char nurse_name[I][5];
char shift_name[K + 1][5];

int feasible_in_kinbou;
int total_in_kinbou;


void input_data()
{
	for (i = 0; i < I; i++) {
		for (t = 0; t < T; t++) {
			nurse[i].DaysOFF[t] = false;
			nurse[i].ReqON_type[t] = -1;
			nurse[i].ReqON_weight[t] = -1;
			nurse[i].ReqOFF_type[t] = -1;
			nurse[i].ReqOFF_weight[t] = -1;
		}
	}

	for (k = 0; k <= K; k++) {
		for (i = 0; i <= K; i++)
		{
			BWP_data[k][i] = false;
		}
	}

	sprintf(FileName, "input/ins%d/nurse_data.txt",P);
	if ((fp = fopen(FileName, "r")) != NULL) {
		for (i = 0; i < I; i++) {
			for (k = 0; k < K; k++)
			{
				fscanf(fp, "%d", &nurse[i].max_kinmusu[k]);
			}
			fscanf(fp, "%d", &nurse[i].maxTime);
			fscanf(fp, "%d", &nurse[i].minTime);
			fscanf(fp, "%d", &nurse[i].maxRenkin);
			fscanf(fp, "%d", &nurse[i].minRenkin);
			fscanf(fp, "%d", &nurse[i].minRenkyu);
			fscanf(fp, "%d", &nurse[i].maxWeekend);
		}
	}
	fclose(fp);

	sprintf(FileName, "input/ins%d/DaysOFF.txt",P);
	if ((fp = fopen(FileName, "r")) != NULL) {
		for (i = 0; i < I; i++) {
			for (t = 0; t < O; t++) {//1はDaysOFFの日数
				int temp;
				fscanf(fp, "%d", &temp);
				nurse[i].DaysOFF[temp] = true;
			}
		}
	}
	fclose(fp);

	sprintf(FileName, "input/ins%d/RequestON.txt",P);
	if ((fp = fopen(FileName, "r")) != NULL) {
		while (fscanf(fp, "%d %d %d %d", &i, &t, &k, &w) != EOF)
		{
			nurse[i].ReqON_type[t] = k;
			nurse[i].ReqON_weight[t] = w;
		}
	}
	fclose(fp);

	sprintf(FileName, "input/ins%d/RequestOFF.txt",P);
	if ((fp = fopen(FileName, "r")) != NULL) {
		while (fscanf(fp, "%d %d %d %d", &i, &t, &k, &w) != EOF)
		{
			nurse[i].ReqOFF_type[t] = k;
			nurse[i].ReqOFF_weight[t] = w;
		}
	}
	fclose(fp);

	sprintf(FileName, "input/ins%d/Cover.txt",P);
	if ((fp = fopen(FileName, "r")) != NULL) {
		while (fscanf(fp, "%d %d %d %d %d", &t, &k, &i, &w, &w2) != EOF)
		{
			Cover[t][k] = i;
			Cover_Weight[t][k][0] = w;
			Cover_Weight[t][k][1] = w2;
		}
	}
	fclose(fp);

	int temp;
	sprintf(FileName, "input/ins%d/Shifts.txt",P);//Shiftsは禁止勤務パターンの組み合わせ以外-1、禁止勤務パターンはシフト番号が入っている。列は勤務時間とK-1個の要素で構成(自分自身は除くから)
	if ((fp = fopen(FileName, "r")) != NULL) {
		for (k = 0; k < K; k++) {
			fscanf(fp, "%d", &Shift_Time[k]);

			for (i = 0; i < B; i++) {
				fscanf(fp, "%d", &temp);
				if (temp != -1)
				{
					BWP_data[k][temp] = true;
				}
			}
		}
	}
	fclose(fp);

	sprintf(FileName, "input/ins%d/shift_name.txt",P);
	if ((fp = fopen(FileName, "r")) != NULL) {
		for (k = 0; k < K; k++) {
			fscanf(fp, "%s", shift_name[k]);
		}
		sprintf(shift_name[K], "─");
	}
	fclose(fp);

	sprintf(FileName, "input/ins%d/nurse_name.txt",P);
	if ((fp = fopen(FileName, "r")) != NULL) {
		for (i = 0; i < I; i++) {
			fscanf(fp, "%s", nurse_name[i]);
		}
	}
	fclose(fp);
}

