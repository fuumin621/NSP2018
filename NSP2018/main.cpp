#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "head.h"

void output_initial();
void get_initial_example();


int kinbou_select(int arr[4]) {
	int ruikei[4];
	ruikei[0] = arr[0];
	for (int i = 1; i < 4; i++)ruikei[i] = ruikei[i - 1] + arr[i];
	int p = rand() % ruikei[3];
	int n = 0;
	while (p >= ruikei[n])n++;
	return n;
}

int main(void)
{
	//srand(time(NULL));
	srand(10);

	FILE *fp;
	char FileName[128];
	sprintf(FileName, "output/ins%d/evaluation.csv",P);
	if ((fp = fopen(FileName, "w")) == NULL) {
		printf("file open error!!\n");
		exit(1);
	}
	fprintf(fp, "回数,計算時間,評価値,");
	fprintf(fp, "最大連勤違反,最小連勤違反,最小連休違反,週末最大違反,休暇希望違反,最大勤務数違反,最大勤務時間違反, 最小勤務時間違反,禁止勤務パターン数,");
	fprintf(fp, "ONリクエスト,OFFリクエスト,人数違反");
	fprintf(fp, "\n");
	fclose(fp);

	

	for (exp_count = 0; exp_count < 1; exp_count++) {

		//srand(time(NULL));

		start_clock = clock();

		weight_H = 1000;
		weight_S = 1;

		input_data();//問題データ入力
		//最適解入力
		get_solution();
		i_solution.input_model(X);
		i_solution.evaluate();
		i_solution.output_value();
		i_solution.output_roster(1);
		printf("saiteki_value = %lld\n", i_solution.value);


		//get_initial_solution();//初期解生成
		//初期解入力
		//get_initial_solution();//初期解生成
		get_initial_example();
		i_solution.input_model(X);
		i_solution.evaluate();
		i_solution.output_value();
		i_solution.output_roster(1);
		printf("initial_value = %lld\n", i_solution.value);

		
		
		



		bool terminal;
		do
		{
			terminal = one_change_N();

			if (terminal)
			{
				printf("成功ですの\n");
			}

		} while (terminal);

		printf("zantei=%d\n", i_solution.value);
		i_solution.output_value();
		
		output_initial();
		//output_initial();

		/*int kinbou_kaizen[4];
		int kinbou_count[4];
		for (int i = 0; i < 4; i++) {
			kinbou_count[i] = 0;
			kinbou_kaizen[i] = 1;
		}
		int zantei_limit = 1;

		/*for (int count = 0; count <= 100000; count++) {
		//int num = rand() % 4;
		//int num = 2;
		//if (count < 1000)num = rand() % 4;
		//else num= kinbou_select(kinbou_kaizen);
		int num = 3;
		switch (num) {
		case 0:
		//printf("近傍①適用\n");
		one_change_Y();

		break;
		case 1:
		//printf("近傍②適用\n");
		ex_rand_i();
		break;
		case 2:
		//printf("近傍③適用\n");
		half_change_Y();
		break;
		case 3:
		//printf("近傍④適用\n");
		two_change_Y2();
		break;
		}
		kinbou_count[num]++;
		//if (count % 10000 == 0) { i_solution.output_value(); }
		if (zantei.value > i_solution.value) {
		zantei = i_solution;
		kinbou_kaizen[num]++;
		zantei_limit = 0;
		}
		zantei_limit++;

		}
		*/

		solution zantei = i_solution;
		int select_nurse = 0;
		for (select_nurse = 0; select_nurse < I; select_nurse++) {
			i_solution.output_roster(0);
			printf("before_value=%lld\n", i_solution.nurse_value[select_nurse]);
			for (int count = 0; count <= 100000; count++) {


				//two_change_Y2_one_nurse(select_nurse);
				one_select_i_t(select_nurse, 5);
				//select_i_t(10, 5);
				//if (count % 1000 == 0) { i_solution.output_value(); }
				if (zantei.value > i_solution.value) {
					zantei = i_solution;

				}
				if (zantei.nurse_value[select_nurse] < 1000) {
					i_solution = zantei;
					break; 
				}
			}
			i_solution = zantei;
			printf("after_value=%lld\n", i_solution.nurse_value[select_nurse]);
		}
		i_solution.output_value();
		printf("zantei=%d\n", zantei.value);
		//printf("i_solution.nurse_value[0]=%lld\n", i_solution.nurse_value[select_nurse]);
		i_solution.output_roster(1);



		/*for (int count = 0; count <= 1000; count++) {


			one_ex_rand_i(select_nurse);

			//select_i_t(10, 5);
			//if (count % 1000 == 0) { i_solution.output_value(); }
			if (zantei.value > i_solution.value) {
			zantei = i_solution;

			}


			}*/
		//printf("i_solution.nurse_value[0]=%lld\n", i_solution.nurse_value[select_nurse]);
		i_solution.output_roster(2);

		/*for (int count = 0; count <= 100000; count++) {


			//two_change_Y2_one_nurse(0);
			ex_rand_i();
			//if (count % 1000 == 0) { i_solution.output_value(); }
			if (zantei.value > i_solution.value) {
			zantei = i_solution;

			}


			}
			*/

		/*printf("zantei=%d\n", zantei.value);
		printf("終了\n");
		/*for (int i = 0; i < 4; i++) {
			printf("kinbou %d: count=%d,kaizen=%d\n", i, kinbou_count[i], kinbou_kaizen[i]);
			}*/

		/*i_solution.output_value();
		i_solution = zantei;

		printf("zantei=%d\n", zantei.value);






		for (int count = 0; count <= 100000; count++) {

			two_change_Y2();
			//if (count % 1000 == 0) { i_solution.output_value(); }
			if (zantei.value > i_solution.value) {
				zantei = i_solution;

			}

		}

		i_solution = zantei;
		i_solution.output_value();
		printf("zantei=%d\n", zantei.value);

		*/

		for (int count = 0; count <= 100000; count++) {

			two_change_Y2();
			//if (count % 1000 == 0) { i_solution.output_value(); }
			if (zantei.value > i_solution.value) {
				zantei = i_solution;

			}

		}

		i_solution = zantei;
		i_solution.output_value();
		printf("zantei=%d\n", zantei.value);


		for (int count = 0; count <= 100000; count++) {

			ex_rand_i();
			//if (count % 1000 == 0) { i_solution.output_value(); }
			if (zantei.value > i_solution.value) {
				zantei = i_solution;

			}

		}

		i_solution = zantei;
		i_solution.output_value();
		printf("zantei=%d\n", zantei.value);
		

		do
		{
			terminal = one_change_N();

			if (terminal)
			{
				printf("成功だぜ\n");
				//i_solution.output_value();
				if (zantei.value > i_solution.value) {
					zantei = i_solution;
				}
			}

		} while (terminal);


		i_solution = zantei;
		i_solution.output_value();
		printf("zantei=%d\n", zantei.value);
		i_solution.output_roster(1);


		printf("zantei=%d\n", zantei.value);

		end_clock = clock();
		printf("Caluculation Time :%lf\n", (double)(end_clock - start_clock) / CLOCKS_PER_SEC);
	}
	
}

void get_solution()
{
	for (int i = 0; i < I; i++)
	{
		for (int t = 0; t < T; t++)
		{
			X[i][t] = K;
		}
	}
	FILE *fp;
	int i, t, k;
	sprintf(FileName, "input/ins%d/Solution.txt",P);
	if ((fp = fopen(FileName, "r")) != NULL) {
		while (fscanf(fp, "%d %d %d", &i, &t, &k) != EOF)
		{
			X[i][t] = k;
		}
	}
	fclose(fp);
}

void output_initial()
{
	FILE *fp;
	char FileName[128];

	sprintf(FileName, "output/ins%d/initial.txt", P);
	if ((fp = fopen(FileName, "w")) == NULL) {
		printf("file open error!!\n");
		exit(1);
	}

	for (int i = 0; i < I; i++) {
		for (int t=0; t < T; t++) {
			fprintf(fp, "%d %d %d", i,t,i_solution.X[i][t]);
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}

void get_initial_example()
{
	for (int i = 0; i < I; i++)
	{
		for (int t = 0; t < T; t++)
		{
			X[i][t] = K;
		}
	}
	FILE *fp;
	int i, t, k;
	sprintf(FileName, "input/ins%d/initial.txt", P);
	if ((fp = fopen(FileName, "r")) != NULL) {
		while (fscanf(fp, "%d %d %d", &i, &t, &k) != EOF)
		{
			X[i][t] = k;
		}
	}
	fclose(fp);
}
