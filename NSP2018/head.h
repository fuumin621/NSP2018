#ifndef __FUNC_H_dgsauohgdaoj_INCLUDE__
#define __FUNC_H_dgsauohgdaoj_INCLUDE__

#pragma warning( disable : 4996 ) //�x����\��

//instance 3
/*#define P 3
#define I 20
#define T 14
#define K 3//�V�t�g�ԍ��i0�`k-1)K�͋x��
#define O 1//1�i�[�X�������DayOFF�̓���
#define B 2
#define TRY 1000//���s�\�𐶐��̃g���C�񐔏��
*/

//instance 15
/*#define P 15//���ԍ�
#define I 45
#define T 42
#define K 6//�V�t�g�ԍ��i0�`k-1)K�͋x��
#define O 4//1�i�[�X�������DayOFF�̓���
#define B 5
#define TRY 1000//���s�\�𐶐��̃g���C�񐔏��
*/

//instance24
#define P 24
#define I 150
#define T 364
#define K 32//�V�t�g�ԍ��i0�`k-1)K�͋x��
#define O 36//1�i�[�X�������DayOFF�̓���
#define B 28
#define TRY 10//���s�\�𐶐��̃g���C�񐔏��


void input_data();
void get_initial_solution();
void get_initial_solution2();
void get_solution();
void reset_nurse_solution(int i);


void shuffle(int ary[], int size);

//�ߖT
bool one_change_N();//1�̃Z������
void one_change_Y();//1�̃Z������
bool i_two_changeN();//��l�̊Ō�t��2���̋Ζ�������
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
extern int Cover_Weight[T][K][2];//0��under,1��over�̃y�i���e�B�d��
extern int Shift_Time[K];
extern bool BWP_data[K + 1][K + 1];//1�ڂ̃V�t�g��2�ڂ̃V�t�g���֎~�Ζ��p�^�[���Ȃ�true�A�����łȂ��Ȃ�false
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
	//�Ζ��\
	int X[I][T];
	void input_model(int x[I][T]);
	void input_model_nurse(int i, int x[I][T]);
	void output_roster(int mode);
	void output_value();

	void mutation(int num);

	//�ړI�֐�
	long long value;//�ړI�֐�
	long long value_real;//�ړI�֐�(�d�ݖ{��)
	long long nurse_value[I];//�Ō�t���Ƃ̖ړI�֐�
	void nurse_evaluate(int i);
	void evaluate();

	//�������
	int Score[12];//0:�ő�A�Έᔽ,1:�ŏ��A�Έᔽ,2:�ŏ��A�x�ᔽ,3:�T���ő�ᔽ,4:�x�݊�]�ᔽ,5:�ő�Ζ����ᔽ,6:�ő�Ζ����Ԉᔽ,7:�ŏ��Ζ����Ԉᔽ,8:�֎~�Ζ��p�^�[����,9:�V�t�gON��],10:�V�t�gOFF��],11:�l������ᔽ
	int nurse_Score[I][11];//0:�ő�A�Έᔽ,1:�ŏ��A�Έᔽ,2:�ŏ��A�x�ᔽ,3:�T���ő�ᔽ,4:�x�݊�]�ᔽ,5:�ő�Ζ����ᔽ,6:�ő�Ζ����Ԉᔽ,7:�ŏ��Ζ����Ԉᔽ,8:�֎~�Ζ��p�^�[����,9:�V�t�gON��],10:�V�t�gOFF��]
	bool feasibility;
	int if_assign_value(int i, int t, int k);

	//��ΐ���
	void nurse_kinmusu(int i, int k);
	void nurse_Time(int i);
	void nurse_maxRenkin(int i);
	void nurse_minRenkin(int i);
	void nurse_minRenkyu(int i);
	void nurse_Weekend(int i);
	void nurse_DayOFF(int i);
	void nurse_BWP(int i);


	//��ΐ���ᔽ�i�[����ϐ�
	int save_nurse_kinmusu[I][K];
	int save_nurse_Time[I];
	int save_nurse_maxRenkin[I];
	int save_nurse_minRenkin[I];
	int save_nurse_minRenkyu[I];
	int save_nurse_Weekend[I];
	int save_nurse_DayOFF[I];
	int save_nurse_BWP[I];


	//�ڕW�������

	void nurse_ON(int i);
	void nurse_OFF(int i);
	void Day_ninzu(int t, int k);
	void Cover_error(int t);

	//�ڕW����ᔽ�i�[����ϐ�
	int save_nurse_ON[I];
	int save_nurse_OFF[I];
	int save_Day_ninzu[T][K];
	int save_Cover_error[T];


	//�ߖT����ɂ�����]���֐��X�V
	void modify(int i, int t, int k);//X[i][t]��k�ɕύX���A�]���l���X�V
	void modify_temp(int i, int t);//X[i][t]��ύX�����Ƃ��]���l�X�V�i�Ƃ肠�����쐬,���な���)
	void modify_i_2t(int i, int tt[2], int kk[2]);


	//�s�v
	/*bool nurse_HC_A_feasible[I];
	bool nurse_HC_B_feasible[I];
	int nurse_HC_A[I][5];//�V�t�g�֌W�Ȃ��B0:�ő�A�Έᔽ,1:�ŏ��A�Έᔽ,2:�ŏ��A�x�ᔽ,3:�T���ő�ᔽ,4:�x�݊�]�ᔽ
	int nurse_HC_B[I][4];//�V�t�g�֌W����B0:�ő�Ζ����ᔽ,1:�ő�Ζ����Ԉᔽ,2:�ŏ��Ζ����Ԉᔽ,3:�֎~�Ζ��p�^�[����
	void nurse_HC_A_CHECK(int i);//�V�t�g�֌W�Ȃ��B
	void nurse_HC_B_CHECK(int i);//�V�t�g�֌W����B
	void nurse_HC(int i);*/
};

extern solution i_solution;





#endif