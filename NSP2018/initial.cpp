#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "head.h"


solution i_solution;
solution temp_for_initial;

int ini_test[T];
void random_nurse_solution(int i);
void shuffle(int ary[], int size);
void get_initial_solution();

void get_initial_solution()
{

	for (int i = 0; i < I; i++) {
		int count = 0;
		solution best;
		while (count < TRY) {
			random_nurse_solution(i);
			if (count == 0) { best = temp_for_initial; }//�ŏ��������珉����
			if (best.nurse_value[i] > temp_for_initial.nurse_value[i]) {
				best = temp_for_initial;
			}
			count++;
		}

		i_solution.input_model_nurse(i, best.X);
	}

	i_solution.evaluate();
}

void random_nurse_solution(int i)
{

	//�S�ċx�݂ɏ�����
	for (int t = 0; t < T; t++) {
		temp_for_initial.X[i][t] = K;
	}
	temp_for_initial.nurse_evaluate(i);

	//���t���V���b�t��
	int RT[T]; shuffle(RT, T);

	//�����_���ȓ��t�ɑ΂��A�Ζ������蓖�ĂĂ���
	for (int tt = 0; tt < T; tt++) {
		int t = RT[tt];
		if (nurse[i].DaysOFF[t]) { continue; }//�x�݊�]�������疳�����Ď��̃��[�v��

		int RK[K + 1]; shuffle(RK, K + 1);//�Ζ��V���b�t��(�x�݂��܂߂�)

										  //best���ŏ��̐�ΐ���ᔽ���Abest_k�����̂Ƃ��̋Ζ�����
		int best_k = temp_for_initial.X[i][t];
		int best = temp_for_initial.nurse_value[i];

		for (int kk = 0; kk < K + 1; kk++) {
			int k = RK[kk];
			int temp_feasible = temp_for_initial.if_assign_value(i, t, k);
			if (best > temp_feasible) {
				best_k = k;
				best = temp_feasible;
			}

		}
		//t���̋Ζ���best_k�Ŋ���
		temp_for_initial.X[i][t] = best_k;
		temp_for_initial.nurse_evaluate(i);

		//��ΐ��񂷂ׂĖ���������I��
		if (temp_for_initial.nurse_Score[i] == 0) {
			break;
		}
	}


}


void shuffle(int ary[], int size)
{
	for (int x = 0; x < size; x++)
	{
		ary[x] = x;
	}

	for (int x = 0; x<size; x++)
	{
		int y = rand() % size;
		int z = ary[x];
		ary[x] = ary[y];
		ary[y] = z;
	}
}


