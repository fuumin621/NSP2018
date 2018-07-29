#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "head.h"


void solution::evaluate()
{
	//������
	value = 0;
	for (int j = 0; j < 12; j++)
	{
		Score[j] = 0;
	}

	//�e�Ō�t(or���ɂ�)�̕]���l�v�Z
	for (int i = 0; i < I; i++) { nurse_evaluate(i); }
	for (int t = 0; t < T; t++) { Cover_error(t); }

	//���񂲂Ƃɍ��v
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < 11; j++) {
			Score[j] += nurse_Score[i][j];
		}
	}
	for (int t = 0; t < T; t++) { Score[11] += save_Cover_error[t]; }

	//���v
	for (int j = 0; j<9; j++) { value += Score[j] * weight_H; }
	for (int j = 9; j < 12; j++) { value += Score[j] * weight_S; }

}


void solution::nurse_ON(int i)
{
	int count = 0;
	for (int t = 0; t < T; t++) {
		if (nurse[i].ReqON_type[t] != -1 && (X[i][t] != nurse[i].ReqON_type[t]))
			count += nurse[i].ReqON_weight[t];
	}
	save_nurse_ON[i] = count;
}

void solution::nurse_OFF(int i)
{
	int count = 0;
	for (int t = 0; t < T; t++) {
		if (nurse[i].ReqOFF_type[t] != -1 && (X[i][t] == nurse[i].ReqOFF_type[t]))
			count += nurse[i].ReqOFF_weight[t];
	}
	save_nurse_OFF[i] = count;
}

void solution::Day_ninzu(int t, int k)
{
	int count = 0;
	for (int i = 0; i < I; i++) {
		if (X[i][t] == k)
			count++;
	}
	save_Day_ninzu[t][k] = count;
}

void solution::Cover_error(int t)
{
	int count = 0;
	for (int k = 0; k < K; k++) {
		int need = Cover[t][k];
		//int real = Day_ninzu(t, k);
		Day_ninzu(t, k);
		int real = save_Day_ninzu[t][k];
		if (real<need) {
			count += (need - real)*Cover_Weight[t][k][0];
		}
		else if (real > need) {
			count += (real - need)*Cover_Weight[t][k][1];
		}
	}
	save_Cover_error[t] = count;
}

void solution::modify(int i, int t, int k)//X[i][t]��k�ɕύX���A�]���l���X�V(�������)
{
	int k_before = X[i][t];//�ύX�O�̋Ζ�
	X[i][t] = k;//�Ζ��ύX

	for (int j = 0; j < 12; j++) {
		nurse_Score[i][j] = 0;
	}

	//���̊Ō�t�ɂ�������т��l�����鐧��̕]���l�X�V(�֎~�Ζ��p�^�[���Ȃ�)
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

	nurse_BWP(i);
	nurse_Score[i][8] = save_nurse_BWP[i];



	//���̊Ō�t�ɂ�������т��l�����Ȃ�����̕]���l�X�V(�Ζ���]�Ȃ�)


	//�x�Ɋ�]
	bool before_flag = (k_before != K&&nurse[i].DaysOFF[t]);
	bool after_flag = (k != K&&nurse[i].DaysOFF[t]);
	if (before_flag == after_flag) {}
	else if (before_flag > after_flag) { save_nurse_DayOFF[i]--; }
	else { save_nurse_DayOFF[i]++; }
	nurse_Score[i][4] = save_nurse_DayOFF[i];


	//�Ζ���
	save_nurse_kinmusu[i][k_before]= save_nurse_kinmusu[i][k_before]-1;
	save_nurse_kinmusu[i][k]= save_nurse_kinmusu[i][k]+1;
	nurse_Score[i][5] = 0;
	for (int k = 0; k < K; k++) {
		if (save_nurse_kinmusu[i][k]>nurse[i].max_kinmusu[k]) {
			nurse_Score[i][5] += save_nurse_kinmusu[i][k] - nurse[i].max_kinmusu[k];
		}
	}

	//�Ζ�����
	save_nurse_Time[i] -= Shift_Time[k_before];
	save_nurse_Time[i] += Shift_Time[k];
	if (save_nurse_Time[i] > nurse[i].maxTime) {
		nurse_Score[i][6] = save_nurse_Time[i] - nurse[i].maxTime;
	}
	if (save_nurse_Time[i] < nurse[i].minTime) {
		nurse_Score[i][7] = nurse[i].minTime - save_nurse_Time[i];
	}

	//ON���N�G�X�g
	before_flag = (nurse[i].ReqON_type[t] != -1 && (k_before != nurse[i].ReqON_type[t]));
	after_flag = (nurse[i].ReqON_type[t] != -1 && (k != nurse[i].ReqON_type[t]));
	if (before_flag == after_flag) {}
	else if (before_flag > after_flag) { save_nurse_ON[i]--; }
	else { save_nurse_ON[i]++; }
	nurse_Score[i][9] = save_nurse_ON[i];

	//OFF���N�G�X�g
	before_flag = (nurse[i].ReqOFF_type[t] != -1 && (k_before == nurse[i].ReqOFF_type[t]));
	after_flag = (nurse[i].ReqOFF_type[t] != -1 && (k == nurse[i].ReqOFF_type[t]));
	if (before_flag == after_flag) {}
	else if (before_flag > after_flag) { save_nurse_OFF[i]--; }
	else { save_nurse_OFF[i]++; }
	nurse_Score[i][10] = save_nurse_OFF[i];

	//���̓��̐���̕]���l�X�V
	Cover_error(t);

	//�i�[�X���v
	nurse_value[i] = 0;
	for (int j = 0; j<9; j++) {
		nurse_value[i] += nurse_Score[i][j] * weight_H;
	}
	for (int j = 9; j <= 10; j++) {
		nurse_value[i] += nurse_Score[i][j] * weight_S;
	}
	
	//�S�̍��v(�v����)
	value = 0;
	for (int j = 0; j < 12; j++) { Score[j] = 0; }

	for (int i = 0; i < I; i++) {
		for (int j = 0; j < 11; j++) {
			Score[j] += nurse_Score[i][j];
		}
	}
	for (int t = 0; t < T; t++) { Score[11] += save_Cover_error[t]; }

	

	for (int j = 0; j<9; j++) { value += Score[j] * weight_H; }
	for (int j = 9; j < 12; j++) { value += Score[j] * weight_S; }

}

void solution::modify_i_2t(int i, int tt[2], int kk[2])
{
	int k_before[2];
	k_before[0] = X[i][tt[0]];//�ύX�O�̋Ζ�
	k_before[1] = X[i][tt[1]];

	X[i][tt[0]] = kk[0];//�Ζ��ύX
	X[i][tt[1]] = kk[1];

	for (int j = 0; j < 12; j++) {
		nurse_Score[i][j] = 0;
	}

	//���̊Ō�t�ɂ�������т��l�����鐧��̕]���l�X�V(�֎~�Ζ��p�^�[���Ȃ�)
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

	nurse_BWP(i);
	nurse_Score[i][8] = save_nurse_BWP[i];


	//���̊Ō�t�ɂ�������т��l�����Ȃ�����̕]���l�X�V(�Ζ���]�Ȃ�)


	int c = 0;
	bool before_flag, after_flag;
	while (c <= 1) {

		//�x�Ɋ�]
		before_flag = (k_before[c] != K&&nurse[i].DaysOFF[tt[c]]);
		after_flag = (kk[c] != K&&nurse[i].DaysOFF[tt[c]]);
		if (before_flag == after_flag) {}
		else if (before_flag > after_flag) { save_nurse_DayOFF[i]--; }
		else { save_nurse_DayOFF[i]++; }

		//�Ζ���
		save_nurse_kinmusu[i][k_before[c]]--;
		save_nurse_kinmusu[i][kk[c]]++;


		//�Ζ�����
		save_nurse_Time[i] -= Shift_Time[k_before[c]];
		save_nurse_Time[i] += Shift_Time[kk[c]];


		//ON���N�G�X�g

		before_flag = (nurse[i].ReqON_type[tt[c]] != -1 && (k_before[c] != nurse[i].ReqON_type[tt[c]]));
		after_flag = (nurse[i].ReqON_type[tt[c]] != -1 && (kk[c] != nurse[i].ReqON_type[tt[c]]));
		if (before_flag == after_flag) {}
		else if (before_flag > after_flag) { save_nurse_ON[i]--; }
		else { save_nurse_ON[i]++; }



		//OFF���N�G�X�g
		before_flag = (nurse[i].ReqOFF_type[tt[c]] != -1 && (k_before[c] == nurse[i].ReqOFF_type[tt[c]]));
		after_flag = (nurse[i].ReqOFF_type[tt[c]] != -1 && (kk[c] == nurse[i].ReqOFF_type[tt[c]]));
		if (before_flag == after_flag) {}
		else if (before_flag > after_flag) { save_nurse_OFF[i]--; }
		else { save_nurse_OFF[i]++; }


		c++;
	}

	nurse_Score[i][4] = save_nurse_DayOFF[i];

	for (int k = 0; k < K; k++) {
		if (save_nurse_kinmusu[i][k] > nurse[i].max_kinmusu[k]) {
			nurse_Score[i][5] += save_nurse_kinmusu[i][k] - nurse[i].max_kinmusu[k];
		}
	}

	if (save_nurse_Time[i] > nurse[i].maxTime) {
		nurse_Score[i][6] = save_nurse_Time[i] - nurse[i].maxTime;
	}
	if (save_nurse_Time[i] < nurse[i].minTime) {
		nurse_Score[i][7] = nurse[i].minTime - save_nurse_Time[i];
	}

	nurse_Score[i][9] = save_nurse_ON[i];
	nurse_Score[i][10] = save_nurse_OFF[i];

	//���̓��̐���̕]���l�X�V
	Cover_error(tt[0]);
	Cover_error(tt[1]);


	//������
	value = 0;
	for (int j = 0; j < 12; j++) { Score[j] = 0; }

	//���񂲂Ƃɍ��v
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < 11; j++) {
			Score[j] += nurse_Score[i][j];
		}
	}
	for (int t = 0; t < T; t++) { Score[11] += save_Cover_error[t]; }

	//���v
	nurse_value[i] = 0;
	for (int j = 0; j<9; j++) {
		nurse_value[i] += nurse_Score[i][j] * weight_H;
	}

	for (int j = 9; j <= 10; j++) {
		nurse_value[i] += nurse_Score[i][j] * weight_S;
	}

	for (int j = 0; j<9; j++) { value += Score[j] * weight_H; }
	for (int j = 9; j < 12; j++) { value += Score[j] * weight_S; }

}

void solution::modify_temp(int i, int t)
{
	
	//������
	value = 0;
	for (int j = 0; j < 12; j++)
	{ Score[j] = 0; }

	//�e�Ō�t(or���ɂ�)�̕]���l�v�Z
	
	nurse_evaluate(i); 
	


	Cover_error(t); 
	
	

	//���񂲂Ƃɍ��v
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < 11; j++) {
			Score[j] += nurse_Score[i][j];
		}
	}
	for (int t = 0; t < T; t++) { Score[11] += save_Cover_error[t]; }

	//���v
	for (int j = 0; j<9; j++) { value += Score[j] * weight_H; }
	for (int j = 9; j < 12; j++) { value += Score[j] * weight_S; }
}

