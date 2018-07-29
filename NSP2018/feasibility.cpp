#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "head.h"


void solution::nurse_evaluate(int i)
{

	/*for (int j = 0; j < 12; j++) {
		nurse_Score[i][j] = 0;
	}


	//絶対制約
	nurse_maxRenkin(i);
	if (save_nurse_maxRenkin[i]>nurse[i].maxRenkin) {
		nurse_Score[i][0] = save_nurse_maxRenkin[i] - nurse[i].maxRenkin;
	}

	nurse_minRenkin(i);
	if (save_nurse_minRenkin[i]<nurse[i].minRenkin) {
		nurse_Score[i][1] = nurse[i].minRenkin - save_nurse_minRenkin[i];
	}

	nurse_minRenkyu(i);
	if (save_nurse_minRenkyu[i]<nurse[i].minRenkyu) {
		nurse_Score[i][2] = nurse[i].minRenkyu - save_nurse_minRenkyu[i];
	}

	nurse_Weekend(i);
	if (save_nurse_Weekend[i] > nurse[i].maxWeekend) {
		nurse_Score[i][3] = save_nurse_Weekend[i] - nurse[i].maxWeekend;
	}

	nurse_DayOFF(i);
	if (save_nurse_DayOFF[i] != 0) {
		nurse_Score[i][4] = save_nurse_DayOFF[i];
	}

	nurse_Score[i][5] = 0;
	for (int k = 0; k < K; k++) {
		nurse_kinmusu(i, k);
		if (save_nurse_kinmusu[i][k]>nurse[i].max_kinmusu[k]) {
			nurse_Score[i][5] += save_nurse_kinmusu[i][k] - nurse[i].max_kinmusu[k];
		}
	}

	nurse_Time(i);
	if (save_nurse_Time[i] > nurse[i].maxTime) {
		nurse_Score[i][6] = save_nurse_Time[i] - nurse[i].maxTime;
	}

	if (save_nurse_Time[i] < nurse[i].minTime) {
		nurse_Score[i][7] = nurse[i].minTime - save_nurse_Time[i];
	}

	nurse_BWP(i);
	nurse_Score[i][8] = save_nurse_BWP[i];


	//目標制約
	nurse_ON(i);
	nurse_Score[i][9] = save_nurse_ON[i];

	nurse_OFF(i);
	nurse_Score[i][10] = save_nurse_OFF[i];


	//合計計算
	nurse_value[i] = 0;
	for (int j = 0; j<9; j++) {
		nurse_value[i] += nurse_Score[i][j] * weight_H;
	}

	for (int j = 9; j <= 10; j++) {
		nurse_value[i] += nurse_Score[i][j] * weight_S;
	}
	
	*/
	
	if (debug_flag == true && p_count == 4 )
	{
		printf("1かいめi=%d\n",i);
		printf("1かいめi_solution.nurse_Score[27][0] =%d\n", i_solution.nurse_Score[27][0]);
	}




	for (int j = 0; j < 12; j++) {
		nurse_Score[i][j] = 0;
		if (debug_flag == true && p_count == 4){
			printf("i=%d,j=%d,nurse_score[27][0]=%d\n", i, j, nurse_Score[27][0]);
		}
	}




	if (debug_flag == true && p_count == 4)
	{
		printf("2かいめi=%d\n", i);
		printf("2かいめi_solution.nurse_Score[27][0] =%d\n", i_solution.nurse_Score[27][0]);
	}
	if (debug_flag == true && p_count == 4 && i_solution.nurse_Score[27][0] == 0)
	{
		printf("zeroになった！！\n");
		debug_flag = false;
	}
	
	//絶対制約
	nurse_maxRenkin(i);
	nurse_Score[i][0] = save_nurse_maxRenkin[i];

	
	nurse_minRenkin(i);
	nurse_Score[i][1] = save_nurse_minRenkin[i];


	nurse_minRenkyu(i);
	nurse_Score[i][2] = save_nurse_minRenkyu[i];

	nurse_Weekend(i);
	if (save_nurse_Weekend[i] > nurse[i].maxWeekend) {
		nurse_Score[i][3] = save_nurse_Weekend[i] - nurse[i].maxWeekend;
	}

	nurse_DayOFF(i);
	if (save_nurse_DayOFF[i] != 0) {
		nurse_Score[i][4] = save_nurse_DayOFF[i];
	}

	nurse_Score[i][5] = 0;
	for (int k = 0; k < K; k++) {
		nurse_kinmusu(i, k);
		if (save_nurse_kinmusu[i][k]>nurse[i].max_kinmusu[k]) {
			nurse_Score[i][5] += save_nurse_kinmusu[i][k] - nurse[i].max_kinmusu[k];
		}
	}

	nurse_Time(i);
	if (save_nurse_Time[i] > nurse[i].maxTime) {
		nurse_Score[i][6] = save_nurse_Time[i] - nurse[i].maxTime;
	}

	if (save_nurse_Time[i] < nurse[i].minTime) {
		nurse_Score[i][7] = nurse[i].minTime - save_nurse_Time[i];
	}

	nurse_BWP(i);
	nurse_Score[i][8] = save_nurse_BWP[i];


	//目標制約
	nurse_ON(i);
	nurse_Score[i][9] = save_nurse_ON[i];

	nurse_OFF(i);
	nurse_Score[i][10] = save_nurse_OFF[i];


	//合計計算
	nurse_value[i] = 0;
	for (int j = 0; j<9; j++) {
		nurse_value[i] += nurse_Score[i][j] * weight_H;
	}

	for (int j = 9; j <= 10; j++) {
		nurse_value[i] += nurse_Score[i][j] * weight_S;
	}
	
}






int solution::if_assign_value(int i, int t, int k)
{
	int save = X[i][t];
	X[i][t] = k;
	nurse_evaluate(i);
	int result = nurse_value[i];

	//もとに戻す
	X[i][t] = save;
	nurse_evaluate(i);
	return result;
}

void solution::nurse_kinmusu(int i, int k)
{
	int count = 0;
	for (int t = 0; t < T; t++) {
		if (X[i][t] == k) {
			count++;
		}
	}
	save_nurse_kinmusu[i][k] = count;
}

void solution::nurse_Time(int i)
{
	int count = 0;
	for (int t = 0; t < T; t++) {
		if (0 <= X[i][t] && X[i][t]<K)
			count += Shift_Time[X[i][t]];
	}
	save_nurse_Time[i] = count;
}

void solution::nurse_maxRenkin(int i)
{
	int value = 0;
	int count = 0;

	for (int t = 0; t < T; t++)
	{
		if (X[i][t] != K)
		{
			count++;
		}
		else
		{
			if (count > nurse[i].maxRenkin)
			{
				value += count - nurse[i].maxRenkin;
			}
			count = 0;
		}

	}
	if (count > nurse[i].maxRenkin)
	{
		value += count - nurse[i].maxRenkin;
	}
	save_nurse_maxRenkin[i] = value;

}


void solution::nurse_minRenkin(int i)
{
	int value = 0;
	int count = T;//初めの最小はムシ

	for (int t = 0; t < T; t++)
	{
		if (X[i][t] != K)
		{
			count++;
		}
		else
		{
			if (count != 0 && count < nurse[i].minRenkin)
			{
				value += nurse[i].minRenkin - count;
			}
			count = 0;
		}

	}
	/*if (count != 0 && count < min_renkin)//最後の最小もムシ
	{
	min_renkin = count;
	}*/
	save_nurse_minRenkin[i] = value;
}


void solution::nurse_minRenkyu(int i)
{
	int value = 0;
	int count = T;//はじめの最小はムシ

	for (int t = 0; t < T; t++)
	{
		if (X[i][t] == K)
		{
			count++;
		}
		else
		{
			if (count != 0 && count < nurse[i].minRenkyu)
			{
				value += nurse[i].minRenkyu - count;
			}
			count = 0;
		}

	}
	/*if (count != 0 && count <min_renkyu)//最後の最小もムシ
	{
	min_renkyu = count;
	}*/
	save_nurse_minRenkyu[i] = value;
}


void solution::nurse_Weekend(int i)//ある週に働いたら1、そうでないなら0(働くのが1日でも2日でも同じ)
{
	int count = 0;
	for (int t = 0; t < T; t++) {
		if (t % 7 == 5) {
			if (X[i][t] != K || X[i][t + 1] != K) {
				count++;
			}
		}
	}
	save_nurse_Weekend[i] = count;
}

void solution::nurse_DayOFF(int i)
{
	int count = 0;
	for (int t = 0; t < T; t++) {
		if (X[i][t] != K&&nurse[i].DaysOFF[t]) {
			count++;
		}
	}
	save_nurse_DayOFF[i] = count;
}

void solution::nurse_BWP(int i)
{
	int count = 0;
	for (int t = 0; t < T - 1; t++)
	{
		if (BWP_data[X[i][t]][X[i][t + 1]])count++;
	}
	save_nurse_BWP[i] = count;
}





//以下不要
/*void solution::nurse_HC_A_CHECK(int i)
{
for (int j = 0; j<5; j++){
nurse_HC_A[i][j] = 0;
}
int temp;

temp = nurse_maxRenkin(i);
if (temp>nurse[i].maxRenkin){
nurse_HC_A[i][0] = temp - nurse[i].maxRenkin;
}

temp = nurse_minRenkin(i);
if (temp<nurse[i].minRenkin){
nurse_HC_A[i][1] = nurse[i].minRenkin - temp;
}

temp = nurse_minRenkyu(i);
if (temp<nurse[i].minRenkyu){
nurse_HC_A[i][2] = nurse[i].minRenkyu - temp;
}

temp = nurse_Weekend(i);
if (temp > nurse[i].maxWeekend){
nurse_HC_A[i][3] = temp - nurse[i].maxWeekend;
}

temp = nurse_DayOFF(i);
if (temp != 0){
nurse_HC_A[i][4] = temp;
}

nurse_HC_A_feasible[i] = true;
for (int j = 0; j<5; j++){
if (nurse_HC_A[i][j] != 0){
nurse_HC_A_feasible[i] = false;
}
}

}

void solution::nurse_HC_B_CHECK(int i)
{
for (int j = 0; j<4; j++){
nurse_HC_B[i][j] = 0;
}

int temp;

nurse_HC_B[i][0] = 0;
for (int k = 0; k < K; k++){
temp = nurse_kinmusu(i, k);
if (temp>nurse[i].max_kinmusu[k]){
nurse_HC_B[i][0] += temp - nurse[i].max_kinmusu[k];
}
}

temp = nurse_Time(i);
if (temp > nurse[i].maxTime){
nurse_HC_B[i][1] = temp - nurse[i].maxTime;
}

if (temp < nurse[i].minTime){
nurse_HC_B[i][2] = nurse[i].minTime - temp;
}

nurse_HC_B[i][3] = nurse_BWP(i);


nurse_HC_B_feasible[i] = true;
for (int j = 0; j<4; j++){
if (nurse_HC_A[i][j] != 0){
nurse_HC_A_feasible[i] = false;
}
}

}

void solution::nurse_HC(int i)
{
nurse_HC_A_CHECK(i);//シフト関係なし。
nurse_HC_B_CHECK(i);//シフト関係あり。
nurse_HC_total[i] = 0;

for (int j = 0; j < 5; j++){
nurse_HC_total[i] += nurse_HC_A[i][j];
}

for (int j = 0; j < 4; j++){
nurse_HC_total[i] += nurse_HC_B[i][j];
}

}*/