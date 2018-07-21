#ifndef __FUNC_H_dgsauohgdaoj_INCLUDE__
#define __FUNC_H_dgsauohgdaoj_INCLUDE__

#pragma warning( disable : 4996 ) //警告非表示

//instance 3
/*#define P 3
#define I 20
#define T 14
#define K 3//シフト番号（0～k-1)Kは休暇
#define O 1//1ナースあたりのDayOFFの日数
#define B 2
#define TRY 1000//実行可能解生成のトライ回数上限
*/

//instance 15
/*#define P 15//問題番号
#define I 45
#define T 42
#define K 6//シフト番号（0～k-1)Kは休暇
#define O 4//1ナースあたりのDayOFFの日数
#define B 5
#define TRY 1000//実行可能解生成のトライ回数上限
*/

//instance24
#define P 24
#define I 150
#define T 364
#define K 32//シフト番号（0～k-1)Kは休暇
#define O 36//1ナースあたりのDayOFFの日数
#define B 28
#define TRY 10//実行可能解生成のトライ回数上限


void input_data();
void get_initial_solution();
void get_initial_solution2();
void get_solution();
void reset_nurse_solution(int i);


void shuffle(int ary[], int size);

//近傍
bool one_change_N();//1つのセル交換
void one_change_Y();//1つのセル交換
bool i_two_changeN();//一人の看護師の2日の勤務を交換
void two_change_Y2_one_nurse(int i);
void ex_rand_i();
void ex_rand_t();
void rand_cell();
void two_change_Y();
void two_change_Y2();
void half_change_Y();
void two_change_Y2_select(int select_i);
void select_i_t(int select_i, int select_t);
void one_ex_rand_i(int i);
void one_select_i_t(int i, int select_t);

extern int weight_H;
extern int weight_S;
extern FILE *fp;
extern char FileName[128];
extern clock_t start_clock, end_clock;
extern int exp_count;


extern char nurse_name[I][5];
extern char shift_name[K + 1][5];
extern char FileName[128];
extern int Cover[T][K];
extern int Cover_Weight[T][K][2];//0はunder,1はoverのペナルティ重み
extern int Shift_Time[K];
extern bool BWP_data[K + 1][K + 1];//1つ目のシフト→2つ目のシフトが禁止勤務パターンならtrue、そうでないならfalse
extern int X[I][T];


struct basic_data
{
	int max_kinmusu[K];
	int maxTime;
	int minTime;
	int maxRenkin;
	int minRenkin;
	int minRenkyu;
	int maxWeekend;
	bool DaysOFF[T];
	int ReqON_type[T];
	int ReqON_weight[T];
	int ReqOFF_type[T];
	int ReqOFF_weight[T];
};

extern struct basic_data nurse[I];

class solution
{
public:
	//勤務表
	int X[I][T];
	void input_model(int x[I][T]);
	void input_model_nurse(int i, int x[I][T]);
	void output_roster(int mode);
	void output_value();

	void mutation(int num);

	//目的関数
	long long value;//目的関数
	long long value_real;//目的関数(重み本来)
	long long nurse_value[I];//看護師ごとの目的関数
	void nurse_evaluate(int i);
	void evaluate();

	//制約条件
	int Score[12];//0:最大連勤違反,1:最小連勤違反,2:最小連休違反,3:週末最大違反,4:休み希望違反,5:最大勤務数違反,6:最大勤務時間違反,7:最小勤務時間違反,8:禁止勤務パターン数,9:シフトON希望,10:シフトOFF希望,11:人数制約違反
	int nurse_Score[I][11];//0:最大連勤違反,1:最小連勤違反,2:最小連休違反,3:週末最大違反,4:休み希望違反,5:最大勤務数違反,6:最大勤務時間違反,7:最小勤務時間違反,8:禁止勤務パターン数,9:シフトON希望,10:シフトOFF希望
	bool feasibility;
	int if_assign_value(int i, int t, int k);

	//絶対制約
	void nurse_kinmusu(int i, int k);
	void nurse_Time(int i);
	void nurse_maxRenkin(int i);
	void nurse_minRenkin(int i);
	void nurse_minRenkyu(int i);
	void nurse_Weekend(int i);
	void nurse_DayOFF(int i);
	void nurse_BWP(int i);


	//絶対制約違反格納する変数
	int save_nurse_kinmusu[I][K];
	int save_nurse_Time[I];
	int save_nurse_maxRenkin[I];
	int save_nurse_minRenkin[I];
	int save_nurse_minRenkyu[I];
	int save_nurse_Weekend[I];
	int save_nurse_DayOFF[I];
	int save_nurse_BWP[I];


	//目標制約条件

	void nurse_ON(int i);
	void nurse_OFF(int i);
	void Day_ninzu(int t, int k);
	void Cover_error(int t);

	//目標制約違反格納する変数
	int save_nurse_ON[I];
	int save_nurse_OFF[I];
	int save_Day_ninzu[T][K];
	int save_Cover_error[T];


	//近傍操作における評価関数更新
	void modify(int i, int t, int k);//X[i][t]をkに変更し、評価値も更新
	void modify_temp(int i, int t);//X[i][t]を変更したとき評価値更新（とりあえず作成,今後↑作る)
	void modify_i_2t(int i, int tt[2], int kk[2]);


	//不要
	/*bool nurse_HC_A_feasible[I];
	bool nurse_HC_B_feasible[I];
	int nurse_HC_A[I][5];//シフト関係なし。0:最大連勤違反,1:最小連勤違反,2:最小連休違反,3:週末最大違反,4:休み希望違反
	int nurse_HC_B[I][4];//シフト関係あり。0:最大勤務数違反,1:最大勤務時間違反,2:最小勤務時間違反,3:禁止勤務パターン数
	void nurse_HC_A_CHECK(int i);//シフト関係なし。
	void nurse_HC_B_CHECK(int i);//シフト関係あり。
	void nurse_HC(int i);*/
};

extern solution i_solution;





#endif