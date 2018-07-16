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
			if (count == 0) { best = temp_for_initial; }//最初だったら初期化
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

	//全て休みに初期化
	for (int t = 0; t < T; t++) {
		temp_for_initial.X[i][t] = K;
	}
	temp_for_initial.nurse_evaluate(i);

	//日付をシャッフル
	int RT[T]; shuffle(RT, T);

	//ランダムな日付に対し、勤務を割り当てていく
	for (int tt = 0; tt < T; tt++) {
		int t = RT[tt];
		if (nurse[i].DaysOFF[t]) { continue; }//休み希望だったら無視して次のループへ

		int RK[K + 1]; shuffle(RK, K + 1);//勤務シャッフル(休みも含める)

										  //best→最小の絶対制約違反数、best_k→そのときの勤務割当
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
		//t日の勤務をbest_kで割当
		temp_for_initial.X[i][t] = best_k;
		temp_for_initial.nurse_evaluate(i);

		//絶対制約すべて満たしたら終了
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


