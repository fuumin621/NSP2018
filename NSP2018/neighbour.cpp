#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "head.h"

void swap_i(int X[I][T], int i, int t1, int t2);

bool one_change_N()
{
	solution s = i_solution;
	long long zantei = i_solution.value;

	int best_i = -1;
	int best_t, best_k;

	for (int i = 0; i < I; i++) {
		for (int t = 0; t < T; t++) {
			for (int k = 0; k <= K; k++) {
				s.modify(i, t, k);
				//s.X[i][t] = k;
				//s.evaluate();
				if (s.value < zantei) {
					best_i = i;
					best_t = t;
					best_k = k;
				}
				s = i_solution;
			}
		}
	}
	if (best_i != -1) {
		//i_solution.X[best_i][best_t] = best_k;
		//i_solution.evaluate();
		i_solution.modify(best_i, best_t, best_k);
		return true;
	}

	else {
		return false;
	}
}

void one_change_Y()
{
	solution s = i_solution;
	long long zantei = NULL;

	int best_i, best_t, best_k;

	int t = rand() % T;
	for (int i = 0; i < I; i++) {
		for (int k = 0; k <= K; k++) {
			if (s.X[i][t] != k) {
				//s.X[i][t] = k;
				//s.evaluate();
				//s.modify_temp(i, t);
				s.modify(i, t, k);
				if (zantei == NULL)//交換可能はじめてのときそれを暫定評価値の初期値に設定
				{
					zantei = s.value;
					best_t = t;
					best_i = i;
					best_k = k;
				}

				if (s.value < zantei)
				{
					zantei = s.value;
					best_t = t;
					best_i = i;
					best_k = k;
				}

				/*if (s.value == zantei)
				{
					if (rand() % 2 == 0) {
						zantei = s.value;
						best_t = t;
						best_i = i;
						best_k = k;
					}
				}
				*/
				s = i_solution;
			}
		}
	}
	//printf("i=%d,t=%d,k=%d\n", best_i, best_t, best_k);
	//i_solution.X[best_i][best_t] = best_k;
	
	
	//i_solution.modify_temp(best_i,best_t);
	//i_solution.evaluate();
	i_solution.modify(best_i, best_t, best_k);
	
	
}

bool i_two_changeN()
{
	long long zantei = i_solution.value;
	solution s;
	s = i_solution;
	int best_i = -1;
	int best_t1, best_t2;

	for (int i = 0; i < I; i++) {
		for (int t1 = 0; t1 < T - 1; t1++) {
			for (int t2 = t1 + 1; t2 < T; t2++) {
				if (i_solution.X[i][t1] != i_solution.X[i][t2]) {
					swap_i(s.X, i, t1, t2);
					s.evaluate();
					if (s.value < zantei)
					{
						zantei = s.value;
						best_i = i;
						best_t1 = t1;
						best_t2 = t2;
					}
				}
				s = i_solution;
			}
		}
	}

	if (best_i != -1) {
		swap_i(i_solution.X, best_i, best_t1, best_t2);
		i_solution.evaluate();
		return true;
	}

	else {
		return false;
	}
}


void ex_rand_i()
{
	long long zantei = NULL;
	solution s;
	s = i_solution;
	int best_i = 0, best_t1 = 0, best_t2 = 0;
	//int save1, save2;
	int tt[2];
	int kk[2];

	int i = rand() % I;
	for (int t1 = 0; t1 < T - 1; t1++) {
		for (int t2 = t1 + 1; t2 < T; t2++) {
			if (i_solution.X[i][t1] != i_solution.X[i][t2]) {
				//swap_i(s.X, i, t1, t2);
				//s.evaluate();

				//save1 = s.X[i][t1];
				//save2 = s.X[i][t2];
				tt[0] = t1;
				tt[1] = t2;
				kk[0] = s.X[i][t2];
				kk[1] = s.X[i][t1];
				s.modify_i_2t(i, tt, kk);
				//s.modify(i, t1, save2);
				//s.modify(i, t2, save1);

				if (zantei == NULL)//&&s.value!=i_solution.value)//交換可能はじめてのときそれを暫定評価値の初期値に設定
				{
					zantei = s.value;
					best_i = i;
					best_t1 = t1;
					best_t2 = t2;
				}

				if (s.value < zantei)//&&s.value != i_solution.value)
				{
					/*printf("YES\n");
					printf("S=%d\n", s.value);
					printf("i_solution=%d\n", i_solution.value);*/

					zantei = s.value;
					best_i = i;
					best_t1 = t1;
					best_t2 = t2;
				}

				if (s.value == zantei)
				{
					if (rand() % 2 == 0) {
						zantei = s.value;
						best_i = i;
						best_t1 = t1;
						best_t2 = t2;
					}
				}

				s = i_solution;
			}
		}
	}


	tt[0] = best_t1;
	tt[1] = best_t2;
	kk[0] = i_solution.X[i][best_t2];
	kk[1] = i_solution.X[i][best_t1];
	i_solution.modify_i_2t(i, tt, kk);

	//save1 = i_solution.X[best_i][best_t1];
	//save2 = i_solution.X[best_i][best_t2];


	//i_solution.modify(best_i, best_t1, save2);
	//i_solution.modify(best_i, best_t2, save1);

	//i_solution.evaluate();
	//swap_i(i_solution.X, best_i, best_t1, best_t2);
	//printf("i=%d,t1=%d,t2=%d\n", best_i, best_t1, best_t2);
}



void one_ex_rand_i(int i)
{
	long long zantei = NULL;
	solution s;
	s = i_solution;
	int best_i = 0, best_t1 = 0, best_t2 = 0;
	//int save1, save2;
	int tt[2];
	int kk[2];

	for (int t1 = 0; t1 < T - 1; t1++) {
		for (int t2 = t1 + 1; t2 < T; t2++) {
			if (i_solution.X[i][t1] != i_solution.X[i][t2]) {
				//swap_i(s.X, i, t1, t2);
				//s.evaluate();

				//save1 = s.X[i][t1];
				//save2 = s.X[i][t2];
				tt[0] = t1;
				tt[1] = t2;
				kk[0] = s.X[i][t2];
				kk[1] = s.X[i][t1];
				s.modify_i_2t(i, tt, kk);
				//s.modify(i, t1, save2);
				//s.modify(i, t2, save1);

				if (zantei == NULL)//&&s.value!=i_solution.value)//交換可能はじめてのときそれを暫定評価値の初期値に設定
				{
					zantei = s.value;
					best_i = i;
					best_t1 = t1;
					best_t2 = t2;
				}

				if (s.value < zantei)//&&s.value != i_solution.value)
				{
					/*printf("YES\n");
					printf("S=%d\n", s.value);
					printf("i_solution=%d\n", i_solution.value);*/

					zantei = s.value;
					best_i = i;
					best_t1 = t1;
					best_t2 = t2;
				}

				if (s.value == zantei)
				{
					if (rand() % 2 == 0) {
						zantei = s.value;
						best_i = i;
						best_t1 = t1;
						best_t2 = t2;
					}
				}

				s = i_solution;
			}
		}
	}


	tt[0] = best_t1;
	tt[1] = best_t2;
	kk[0] = i_solution.X[i][best_t2];
	kk[1] = i_solution.X[i][best_t1];
	i_solution.modify_i_2t(i, tt, kk);

	//save1 = i_solution.X[best_i][best_t1];
	//save2 = i_solution.X[best_i][best_t2];


	//i_solution.modify(best_i, best_t1, save2);
	//i_solution.modify(best_i, best_t2, save1);

	//i_solution.evaluate();
	//swap_i(i_solution.X, best_i, best_t1, best_t2);
	//printf("i=%d,t1=%d,t2=%d\n", best_i, best_t1, best_t2);
}

void rand_cell()
{
	long long zantei = NULL;
	solution s;
	s = i_solution;

	int best[3];

	int SN[3];//選んだナース
	int SD[3];//選んだ日


	for (int c = 0; c < 3; c++) {
		SN[c] = rand() % I;
		SD[c] = rand() % T;
	}


	for (int i = 0; i < 3; i++) {
		printf("SN[%d]=%d,SD[%d]=%d\n", i, SN[i], i, SD[i]);
	}

	for (int k0 = 0; k0 <= K; k0++) {
		for (int k1 = 0; k1 <= K; k1++) {
			for (int k2 = 0; k2 <= K; k2++) {
				if (k0 != s.X[SN[0]][SD[0]] && k1 != s.X[SN[1]][SD[1]] && k2 != s.X[SN[2]][SD[2]])
				{
					s.X[SN[0]][SD[0]] = k0;
					s.X[SN[1]][SD[1]] = k1;
					s.X[SN[2]][SD[2]] = k2;
					s.evaluate();
					printf("(k0,k1,k2)=(%d,%d,%d)→  ", k0, k1, k2);
					printf("evaluation=%d\n", s.value);


					if (zantei == NULL)//&&s.value!=i_solution.value)//交換可能はじめてのときそれを暫定評価値の初期値に設定
					{
						zantei = s.value;
						best[0] = k0;
						best[1] = k1;
						best[2] = k2;
					}


					if (s.value < zantei)//&&s.value != i_solution.value)
					{
						zantei = s.value;
						best[0] = k0;
						best[1] = k1;
						best[2] = k2;
					}

					if (s.value == zantei)
					{
						if (rand() % 2 == 0) {
							zantei = s.value;
							best[0] = k0;
							best[1] = k1;
							best[2] = k2;
						}
					}

					s = i_solution;
				}
			}
		}
	}

	i_solution.X[SN[0]][SD[0]] = best[0];
	i_solution.X[SN[1]][SD[1]] = best[1];
	i_solution.X[SN[2]][SD[2]] = best[2];
	i_solution.evaluate();

	for (int i = 0; i < 3; i++) {
		printf("best[%d]=%d\n", i, best[i]);
	}
	printf("evaluation=%d\n", i_solution.value);


}




void two_change_Y()
{
	solution s = i_solution;
	long long zantei = NULL;

	int best_i0, best_i1, best_k0, best_k1;

	int t0, t1;
	do {
		t0 = rand() % T;
		t1 = rand() % T;
	} while (t0 == t1);

	//printf("t0=%d,t1=%d\n", t0, t1);



	for (int i0 = 0; i0 < I; i0++) {
		for (int i1 = 0; i1 < I; i1++) {
			for (int k0 = 0; k0 <= K; k0++) {
				for (int k1 = 0; k1 <= K; k1++) {
					if (s.X[i0][t0] != k0 || s.X[i1][t1] != k1) {

						s.X[i0][t0] = k0;
						s.X[i1][t1] = k1;
						s.evaluate();

						if (zantei == NULL&&s.value != i_solution.value)//交換可能はじめてのときそれを暫定評価値の初期値に設定
						{
							zantei = s.value;
							best_i0 = i0;
							best_i1 = i1;
							best_k0 = k0;
							best_k1 = k1;

						}

						if (s.value < zantei&&s.value != i_solution.value)
						{
							zantei = s.value;
							best_i0 = i0;
							best_i1 = i1;
							best_k0 = k0;
							best_k1 = k1;
						}
						s = i_solution;
					}
				}
			}
		}
	}
	//printf("before: X[best_i0][t0]=%d , X[besti1][t1]=%d , value=%d\n", i_solution.X[best_i0][t0], i_solution.X[best_i1][t1],i_solution.value);


	i_solution.X[best_i0][t0] = best_k0;
	i_solution.X[best_i1][t1] = best_k1;
	i_solution.evaluate();
	//printf("after: X[best_i0][t0]=%d , X[besti1][t1]=%d , value=%d\n", i_solution.X[best_i0][t0], i_solution.X[best_i1][t1], i_solution.value);

}

void two_change_Y2()
{
	solution s = i_solution;
	long long zantei = NULL;

	int best_i, best_k0, best_k1;

	int t0, t1;
	do {
		t0 = rand() % T;
		t1 = rand() % T;
	} while (t0 == t1);

	//printf("t0=%d,t1=%d\n", t0, t1);

	int tt[2] = { t0, t1 };
	int kk[2];

	for (int i = 0; i < I; i++) {
		for (int k0 = 0; k0 <= K; k0++) {
			for (int k1 = 0; k1 <= K; k1++) {
				if (s.X[i][t0] != k0 || s.X[i][t1] != k1) {

					//s.X[i][t0] = k0;
					//s.X[i][t1] = k1;
					//s.modify_temp(i, t0);
					//s.modify_temp(i, t1);

					//s.modify(i, t0, k0);
					//s.modify(i, t1, k1);

					kk[0] = k0;
					kk[1] = k1;

					s.modify_i_2t(i, tt, kk);

					if (zantei == NULL&&s.value != i_solution.value)//交換可能はじめてのときそれを暫定評価値の初期値に設定
					{
						zantei = s.value;
						best_i = i;
						best_k0 = k0;
						best_k1 = k1;

					}

					if (s.value < zantei&&s.value != i_solution.value)
					{
						zantei = s.value;
						best_i = i;
						best_k0 = k0;
						best_k1 = k1;
					}

					if (s.value == zantei)
					{
						if (rand() % 2 == 0) {
							zantei = s.value;
							best_i = i;
							best_k0 = k0;
							best_k1 = k1;
						}
					}

					s = i_solution;
				}
			}
		}
	}

	//printf("before: X[best_i0][t0]=%d , X[besti1][t1]=%d , value=%d\n", i_solution.X[best_i0][t0], i_solution.X[best_i1][t1],i_solution.value);


	/*i_solution.X[best_i][t0] = best_k0;
	i_solution.X[best_i][t1] = best_k1;
	i_solution.evaluate();
	*/
	//i_solution.modify(best_i, t0, best_k0);
	//i_solution.modify(best_i, t1, best_k1);

	tt[0] = t0; tt[1] = t1;
	kk[0] = best_k0; kk[1] = best_k1;
	i_solution.modify_i_2t(best_i, tt, kk);

	//
	//printf("after: X[best_i0][t0]=%d , X[besti1][t1]=%d , value=%d\n", i_solution.X[best_i0][t0], i_solution.X[best_i1][t1], i_solution.value);

}



void two_change_Y2_one_nurse(int i)
{
	solution s = i_solution;
	long long zantei = NULL;

	int best_i, best_k0, best_k1;

	int t0, t1;
	do {
		t0 = rand() % T;
		t1 = rand() % T;
	} while (t0 == t1);

	//printf("t0=%d,t1=%d\n", t0, t1);

	int tt[2] = { t0, t1 };
	int kk[2];


	for (int k0 = 0; k0 <= K; k0++) {
		for (int k1 = 0; k1 <= K; k1++) {
			if (s.X[i][t0] != k0 || s.X[i][t1] != k1) {

				//s.X[i][t0] = k0;
				//s.X[i][t1] = k1;
				//s.modify_temp(i, t0);
				//s.modify_temp(i, t1);

				//s.modify(i, t0, k0);
				//s.modify(i, t1, k1);

				kk[0] = k0;
				kk[1] = k1;

				s.modify_i_2t(i, tt, kk);

				if (zantei == NULL&&s.value != i_solution.value)//交換可能はじめてのときそれを暫定評価値の初期値に設定
				{
					zantei = s.value;
					best_i = i;
					best_k0 = k0;
					best_k1 = k1;

				}

				if (s.value < zantei&&s.value != i_solution.value)
				{
					zantei = s.value;
					best_i = i;
					best_k0 = k0;
					best_k1 = k1;
				}

				if (s.value == zantei)
				{
					if (rand() % 2 == 0) {
						zantei = s.value;
						best_i = i;
						best_k0 = k0;
						best_k1 = k1;
					}
				}

				s = i_solution;
			}
		}
	}


	//printf("before: X[best_i0][t0]=%d , X[besti1][t1]=%d , value=%d\n", i_solution.X[best_i0][t0], i_solution.X[best_i1][t1],i_solution.value);


	/*i_solution.X[best_i][t0] = best_k0;
	i_solution.X[best_i][t1] = best_k1;
	i_solution.evaluate();
	*/
	//i_solution.modify(best_i, t0, best_k0);
	//i_solution.modify(best_i, t1, best_k1);

	tt[0] = t0; tt[1] = t1;
	kk[0] = best_k0; kk[1] = best_k1;
	i_solution.modify_i_2t(best_i, tt, kk);

	//
	//printf("after: X[best_i0][t0]=%d , X[besti1][t1]=%d , value=%d\n", i_solution.X[best_i0][t0], i_solution.X[best_i1][t1], i_solution.value);

}




void two_change_Y2_select(int select_i)
{
	solution s = i_solution;
	long long zantei = NULL;

	int best_i, best_k0, best_k1;

	int t0, t1;
	do {
		t0 = rand() % T;
		t1 = rand() % T;
	} while (t0 == t1);

	//printf("t0=%d,t1=%d\n", t0, t1);

	int tt[2] = { t0, t1 };
	int kk[2];

	int RI[I]; shuffle(RI, I);

	for (int ii = 0; ii < select_i; ii++) {
		int i = RI[ii];
		for (int k0 = 0; k0 <= K; k0++) {
			for (int k1 = 0; k1 <= K; k1++) {
				if (s.X[i][t0] != k0 || s.X[i][t1] != k1) {

					//s.X[i][t0] = k0;
					//s.X[i][t1] = k1;
					//s.modify_temp(i, t0);
					//s.modify_temp(i, t1);

					//s.modify(i, t0, k0);
					//s.modify(i, t1, k1);

					kk[0] = k0;
					kk[1] = k1;

					s.modify_i_2t(i, tt, kk);

					if (zantei == NULL&&s.value != i_solution.value)//交換可能はじめてのときそれを暫定評価値の初期値に設定
					{
						zantei = s.value;
						best_i = i;
						best_k0 = k0;
						best_k1 = k1;

					}

					if (s.value < zantei&&s.value != i_solution.value)
					{
						zantei = s.value;
						best_i = i;
						best_k0 = k0;
						best_k1 = k1;
					}

					if (s.value == zantei)
					{
						if (rand() % 2 == 0) {
							zantei = s.value;
							best_i = i;
							best_k0 = k0;
							best_k1 = k1;
						}
					}

					s = i_solution;
				}
			}
		}
	}

	//printf("before: X[best_i0][t0]=%d , X[besti1][t1]=%d , value=%d\n", i_solution.X[best_i0][t0], i_solution.X[best_i1][t1],i_solution.value);


	/*i_solution.X[best_i][t0] = best_k0;
	i_solution.X[best_i][t1] = best_k1;
	i_solution.evaluate();
	*/
	//i_solution.modify(best_i, t0, best_k0);
	//i_solution.modify(best_i, t1, best_k1);

	tt[0] = t0; tt[1] = t1;
	kk[0] = best_k0; kk[1] = best_k1;
	i_solution.modify_i_2t(best_i, tt, kk);

	//
	//printf("after: X[best_i0][t0]=%d , X[besti1][t1]=%d , value=%d\n", i_solution.X[best_i0][t0], i_solution.X[best_i1][t1], i_solution.value);

}



void select_i_t(int select_i, int select_t)
{
	solution s = i_solution;
	long long zantei = NULL;

	int best_i, best_t, best_k;

	int RI[I]; shuffle(RI, I);
	int RT[T]; shuffle(RT, T);

	feasible_in_kinbou=0;
	total_in_kinbou=0;

	int i, t;
	for (int ii = 0; ii < select_i; ii++) {
		i = RI[ii];
		for (int tt = 0; tt < select_t; tt++) {
			t = RT[tt];
			for (int k = 0; k <= K; k++) {
				if (s.X[i][t] != k) {
					//s.X[i][t] = k;
					//s.modify_temp(i, t);
					//s.evaluate();
					total_in_kinbou++;
					s.modify(i, t, k);
					if (zantei == NULL)//交換可能はじめてのときそれを暫定評価値の初期値に設定
					{
						zantei = s.value;
						best_t = t;
						best_i = i;
						best_k = k;
					}
					if (s.infeasibility==0) { feasible_in_kinbou++; }

					if (s.value < zantei)
					{
						zantei = s.value;
						best_t = t;
						best_i = i;
						best_k = k;
					}

					s = i_solution;
				}
			}
		}
	}
	//i_solution.X[best_i][best_t] = best_k;
	//i_solution.modify_temp(best_i, best_t);
	//i_solution.evaluate();

	i_solution.modify(best_i, best_t, best_k);


}

void select_i_t_k(int select_i, int select_t,int select_k)
{
	solution s = i_solution;
	long long zantei = NULL;

	int best_i, best_t, best_k;

	int RI[I]; shuffle(RI, I);
	int RT[T]; shuffle(RT, T);
	int RK[K + 1]; shuffle(RK, K + 1);

	int i, t,k;
	for (int ii = 0; ii < select_i; ii++) {
		i = RI[ii];
		for (int tt = 0; tt < select_t; tt++) {
			t = RT[tt];
			for (int kk = 0; kk <select_k; kk++) {
				k = RK[kk];
				if (s.X[i][t] != k) {
					//s.X[i][t] = k;
					//s.evaluate();
					s.modify(i, t, k);
					if (zantei == NULL)//交換可能はじめてのときそれを暫定評価値の初期値に設定
					{
						zantei = s.value;
						best_t = t;
						best_i = i;
						best_k = k;
					}

					if (s.value < zantei)
					{
						zantei = s.value;
						best_t = t;
						best_i = i;
						best_k = k;
					}

					if (s.value == zantei)
					{
						if (rand() % 2 == 0) {
							zantei = s.value;
							best_t = t;
							best_i = i;
							best_k = k;
						}
					}

					s = i_solution;
				}
			}
		}
	}
	//i_solution.X[best_i][best_t] = best_k;
	//i_solution.evaluate();
	i_solution.modify(best_i, best_t, best_k);


}

void one_select_i_t(int i, int select_t)
{
	solution s = i_solution;
	long long zantei = NULL;

	int best_i, best_t, best_k;

	int RI[I]; shuffle(RI, I);
	int RT[T]; shuffle(RT, T);

	int t;
	for (int tt = 0; tt < select_t; tt++) {
		t = RT[tt];
		for (int k = 0; k <= K; k++) {
			if (s.X[i][t] != k) {
				//s.X[i][t] = k;
				//s.evaluate();
				s.modify(i, t, k);
				if (zantei == NULL)//交換可能はじめてのときそれを暫定評価値の初期値に設定
				{
					zantei = s.value;
					best_t = t;
					best_i = i;
					best_k = k;
				}

				if (s.value < zantei)
				{
					zantei = s.value;
					best_t = t;
					best_i = i;
					best_k = k;
				}

				if (s.value == zantei)
				{
					if (rand() % 2 == 0) {
						zantei = s.value;
						best_t = t;
						best_i = i;
						best_k = k;
					}
				}

				s = i_solution;
			}
		}
	}
	
	//i_solution.X[best_i][best_t] = best_k;
	//i_solution.evaluate();
	i_solution.modify(best_i, best_t, best_k);


}


void half_change_Y()
{
	solution s = i_solution;
	long long zantei = NULL;

	int best_i, best_t, best_k;

	int t = rand() % T;

	int ir[I / 2]; shuffle(ir, I / 2);
	/*for (int i = 0; i<(I / 2); i++) {
	printf("RI[%d]=%d", i, ir[i]);
	}*/


	for (int i = 0; i <(I / 2); i++) {
		for (int k = 0; k <= K; k++) {
			if (s.X[ir[i]][t] != k) {
				//s.X[ir[i]][t] = k;
				//s.evaluate();
				s.modify(ir[i], t, k);
				if (zantei == NULL)//交換可能はじめてのときそれを暫定評価値の初期値に設定
				{
					zantei = s.value;
					best_t = t;
					best_i = ir[i];
					best_k = k;
				}

				if (s.value < zantei)
				{
					zantei = s.value;
					best_t = t;
					best_i = ir[i];
					best_k = k;
				}
				s = i_solution;
			}
		}
	}
	//i_solution.X[best_i][best_t] = best_k;
	//i_solution.evaluate();
	i_solution.modify(best_i, best_t, best_k);
	//printf("i=%d,t=%d,k=%d\n", best_i, best_t, best_k);
}


void imp_worst_day(int select_i) {
	solution s = i_solution;
	long long zantei = NULL;
	int t_worst=0;
	int worst=0;
	for (int t = 0; t < T; t++) {
		if (worst < i_solution.save_Cover_error[t]) {
			t_worst = t;
			worst = i_solution.save_Cover_error[t];
		}
	}

	int RI[I]; shuffle(RI, I);
	int best_i, best_t, best_k;
	for (int ii = 0; ii < select_i; ii++) {
		int i = RI[ii];
		for (int k = 0; k <= K; k++) {
			if (s.X[i][t_worst] != k) {
				//s.X[i][t] = k;
				//s.evaluate();
				//s.modify_temp(i, t);
				s.modify(i, t_worst, k);
				if (zantei == NULL)//交換可能はじめてのときそれを暫定評価値の初期値に設定
				{
					zantei = s.value;
					best_t = t_worst;
					best_i = i;
					best_k = k;
				}

				if (s.value < zantei)
				{
					zantei = s.value;
					best_t = t_worst;
					best_i = i;
					best_k = k;
				}

				/*if (s.value == zantei)
				{
				if (rand() % 2 == 0) {
				zantei = s.value;
				best_t = t;
				best_i = i;
				best_k = k;
				}
				}
				*/
				s = i_solution;
			}
		}
	}
	//printf("i=%d,t=%d,k=%d\n", best_i, best_t, best_k);
	//i_solution.X[best_i][best_t] = best_k;


	//i_solution.modify_temp(best_i,best_t);
	//i_solution.evaluate();
	i_solution.modify(best_i, best_t, best_k);

}

void reset_day() {
	int t_worst = 0;
	int worst = 0;
	for (int t = 0; t < T; t++) {
		if (worst < i_solution.save_Cover_error[t]) {
			t_worst = t;
			worst = i_solution.save_Cover_error[t];
		}
	}
	int t = t_worst;
	solution s = i_solution;
	//対象の日すべてランダムに初期化
	for (int i = 0; i < I; i++) {
		s.X[i][t] = rand()%(K+1);
	}
	s.evaluate();

	//看護師をシャッフル
	
	printf("worst_day=%d\n", t);
	int RI[I]; shuffle(RI, I);
	int i;
	for (int ii = 0; ii < I; ii++) {
		i = RI[ii];
		if (nurse[i].DaysOFF[t]) 
		{
			s.X[i][t] = K;
			continue;
		}
		solution temp_sol = s;
		int best_k = temp_sol.X[i][t];
		long long best_value = temp_sol.value;
		
		int RK[K + 1]; shuffle(RK, K + 1);
		for (int kk = 0; kk < K+1; kk++) {
			int k = RK[kk];
			temp_sol.X[i][t] = k;
			temp_sol.evaluate();
			if (temp_sol.value < best_value) {
				best_k = k;
				best_value = temp_sol.value;
			}
			temp_sol = s;
		}
		printf("best_i=%d,best_k=%d\n", i, best_k);
		s.X[i][t] = best_k;
		s.evaluate();
	}
	i_solution = s;
	
}

void reset_day2() {
	int t_worst = 0;
	int worst = 0;
	for (int t = 0; t < T; t++) {
		if (worst < i_solution.save_Cover_error[t]) {
			t_worst = t;
			worst = i_solution.save_Cover_error[t];
		}
	}
	int t = t_worst;
	printf("対象日:%d\n", t);
	int count = 0;
	//対象の日すべてランダムに初期化
	for (int i = 0; i < I; i++) {
		solution s = i_solution;
		while (true) {
			int k = rand() % (K + 1);
			s.X[i][t] = k;
			s.nurse_evaluate(i);
			if (s.nurse_value[i] < 1000) {
				if (i_solution.X[i][t] != k) { count++; }
				i_solution.X[i][t] = k;
				printf("看護師 %dは勤務%dを選択\n", i, k);
				
				break;
			}
		}
	}
	i_solution.evaluate();
	printf("count=%d\n", count);
}


void solution::mutation(int num)
{
	int count = 0;
	int i, t, k;
	while (count < num) {
		i = rand() % I;
		t = rand() % T;
		k = rand() % (K + 1);
		if (X[i][t] != k) {
			X[i][t] = k;
			count++;
		}
		//printf("i=%d,t=%d,k=%d\n", i, t, k);
	}
	evaluate();
}


void swap_i(int X[I][T], int i, int t1, int t2)
{
	int dummy = X[i][t1];
	X[i][t1] = X[i][t2];
	X[i][t2] = dummy;
}
