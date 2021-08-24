#include <math.h>
#include <malloc.h>
#include <stdio.h>

typedef unsigned long int u32;
typedef long int int32;
typedef unsigned int u16;
typedef unsigned char u8;
typedef float f32;

#define SPEED_LIMIT 1 // 三段中第二段的速度限制，Speed limit

//各轴运行距离限制
#define MAXLEN_X 80000
#define MAXLEN_Y 80000
#define MAXLEN_Z 80000

#define MAX_NUM_OF_POINT 35   // 点个数上限
#define CURVATURE_POINT_NUM 8 // 各段求曲率的点个数
#define CON_POINT_RATIO 0.4   // 控制点距中间点位置 与 两目标点位置的比值，Control point ratio

f32 l1, l2, l3, l4;
int stop_f = 0;

typedef struct
{
    f32 Tar_Points[MAX_NUM_OF_POINT][3];                           // Target point list ，目标点与中间点序列，指向MtoC里的 目标点序列
    int Tar_P_Num;                                                 // target points number ，目标点数量
    f32 Con_points[MAX_NUM_OF_POINT - 1][3];                       // Control point list ，控制点序列
    f32 Bez_a[MAX_NUM_OF_POINT][3];                                // 参数 a ，分x、y、z方向
    f32 Bez_b[MAX_NUM_OF_POINT][3];                                // 参数 b ，分x、y、z方向
    f32 Bez_c[MAX_NUM_OF_POINT][3];                                // 参数 c ，分x、y、z方向
    f32 Bez_A[MAX_NUM_OF_POINT];                                   // 参数 A
    f32 Bez_B[MAX_NUM_OF_POINT];                                   // 参数 B
    f32 Bez_C[MAX_NUM_OF_POINT];                                   // 参数 C
    f32 Curve_Len[MAX_NUM_OF_POINT];                               // 各段曲线长度
    f32 To_Point_Curve_Len[MAX_NUM_OF_POINT][CURVATURE_POINT_NUM]; // 从曲线开始到曲率点的 曲线长度 To_Point_Curve_Len
    f32 Curvature[MAX_NUM_OF_POINT][CURVATURE_POINT_NUM];          // 各段多点曲率存储，对应上面的曲线长度
    int order;                                                     // 立即位置所在的 曲线序号
    f32 t;                                                         // 立即位置对应的贝塞尔方程的 参数t

} Bezier_Curve;

void Control_Point_Calculation(void);
void Cross_Product(f32 A[3], f32 B[3], f32 C[3]);
f32 Vector_Length(f32 A[3]);
void Tnit_Bez(void);
void Midpoint_Calculation(void);
void Bezier_Parameter_Calculation(void);
void Curves_Length_Calculation(void);
f32 Distance_Integral(f32 t, f32 A, f32 B, f32 C);
f32 Point_Curvature(f32 t, f32 a[3], f32 b[3], f32 c[3]);
void Curvature_and_Length_Calculation(void);

Bezier_Curve Bez;

// 以下为 Distance_Piece.speed_mode 的选项
#define UNIFORO_MOTION 0 // 匀速运动，uniform motion
#define VARIBLE_ACC 1    // 变变速运动，Variable acceleration
#define SIGLE_ACC 2      // 单次变速运动

#define CURVATURE_LIMIT 2.3 // 曲率限制，高于则限速

#define LOW_SPEED_LIMIT 1 // 低速限制（m/s），Low speed limit
#define ACC_LIMIT 40      // 加速度限制，acceleration limit

#define PREDICT_INTERVALS 0.002

typedef struct
{
    f32 Piece_Dis;     // 本片的路程 , piece distance
    f32 Cur_Total_Dis; // 前面的片的路程之和 , current total distance
    u32 Speed_Mode;    // 速度模式，有宏定义选项
    f32 v1;
    f32 v2;
    f32 v3;
    f32 t1;
    f32 t2;
    f32 t3;
    f32 Acc_Limit; // 加速度限制，变速运动可用
    f32 Uni_Speed; // 匀速速度，匀速运动可用，uniform speed
    f32 duration;  // 持续时间

} Distance_Piece; // 路程片结构体

typedef struct
{
    int p_start; // [start,end)
    int p_end;
    int b_start; // [start,end)
    int b_end;
    f32 time;
    f32 dis;
} Big_Piece;

typedef struct
{
    f32 Speed_Limit[MAX_NUM_OF_POINT];              // 具体点的速度限制
    f32 Acc_Limit[MAX_NUM_OF_POINT];                // 具体点对应的段的加速度限制
    f32 Time_Limit[MAX_NUM_OF_POINT];               // 具体点的时间限制
    Distance_Piece Dis_Piece[MAX_NUM_OF_POINT - 1]; // 路程片结构体
    Big_Piece B_Piece[6];                           // 大片 结构体
    int piece_num;                                  // 路程片个数
    int Bpiece_num;                                 // 大片的个数
    int32 cur_piece;                                // 当前路程片序号
    f32 time_in_piece;                              // 当前片内的时间
} V_T_Diagram;                                      // v_t图 的结构体

V_T_Diagram VT;

#define LENGTH_ACCURACY 0.0001 // 估计曲线长度的误差（单位m），Length accuracy

typedef struct
{
    f32 imm_pos[3];       // 立即到达的位置
    f32 real_pos[3];      // 真正到达的位置
    f32 imm_dir[3];       // 立即位置对应的方向
    f32 imm_speed;        // 立即位置对应的速度
    f32 imm_speed_vec[3]; // 立即位置对应的速度向量
    f32 cor_speed_vec[3]; // 矫正后的速度向量
    f32 imm_total_len;    // 到立即位置为止，运动总长度
    f32 imm_curve_len;    // 到立即位置为止，在曲线内的运动长度
    f32 next_pos[3];      // 下一个点位置，理论位置
    f32 next_move_len;    // 下一段的运动长度
    f32 stop_f;           // 停止标志，默认0

} Real_Time_Data;

Real_Time_Data R_data;

void Real_Time_Data_Init(void);
void Immediate_Point_Direction_Calculation(void);
void Immediate_Point_Speed_Calculation(void);
void Speed_Vector_Calculation(void);
void Next_Pos_Calculation(void);
void Predict_Speed_and_Position(void);

/* 函数：Control_Point_Calculation
 * 功能：计算出控制点位置
 * 参数：void
 * 返回值：void
 * */
void Control_Point_Calculation(void)
{
    /* 计算起点和终点的控制点 */
    int i = 0, j = 0;
    for (i = 0; i < 3; i++)
    { // 第一个控制点
        Bez.Con_points[0][i] = Bez.Tar_Points[0][i] * (1 - CON_POINT_RATIO) + Bez.Tar_Points[2][i] * CON_POINT_RATIO;
        // 最后一个控制点
        Bez.Con_points[Bez.Tar_P_Num - 2][i] =
            Bez.Tar_Points[Bez.Tar_P_Num - 1][i] * (1 - CON_POINT_RATIO) +
            Bez.Tar_Points[Bez.Tar_P_Num - 3][i] * CON_POINT_RATIO;
    }

    /* 计算其余的控制点 */
    f32 BA_vec[3], BC_vec[3]; // 向量BA与BC
    f32 BA_len, BC_len;       // 向量模长
    f32 N_vec[3];             // N = BA X BC
    f32 M_vec[3];             // M = (BA + BC)/2
    f32 K_vec[3];             // K = N X M
    f32 t1;                   // 求下一个点之间的控制点 所用的的参数，为正数
    f32 t2;                   // 求上一个点之间的控制点 所用的的参数，为负数
    for (i = 2; i < Bez.Tar_P_Num - 1; i += 2)
    {
        // 计算BA、BC，并且单位化
        for (j = 0; j < 3; j++)
        {
            BA_vec[j] = Bez.Tar_Points[i - 2][j] - Bez.Tar_Points[i][j];
            BC_vec[j] = Bez.Tar_Points[i + 2][j] - Bez.Tar_Points[i][j];
        }
        BA_len = Vector_Length(BA_vec);
        BC_len = Vector_Length(BC_vec);
        for (j = 0; j < 3; j++) // 单位化
        {
            BA_vec[j] = BA_vec[j] / BA_len;
            BC_vec[j] = BC_vec[j] / BC_len;
        }

        // 计算N、M、K
        Cross_Product(BA_vec, BC_vec, N_vec); // 计算N

        // 直线情况
        if (Vector_Length(N_vec) < 0.001)
        {
            for (j = 0; j < 3; j++)
            {
                K_vec[j] = BC_vec[j];
            }
        }
        // 一般曲线情况
        else
        {
            for (j = 0; j < 3; j++) // 计算M
            {
                M_vec[j] = (BA_vec[j] + BC_vec[j]) / 2;
            }
            Cross_Product(N_vec, M_vec, K_vec); // 计算K
        }

        // 计算参数t1,t2
        t1 = CON_POINT_RATIO * BC_len / Vector_Length(K_vec);
        t2 = -CON_POINT_RATIO * BA_len / Vector_Length(K_vec);

        // 计算前后控制点
        for (j = 0; j < 3; j++)
        {
            Bez.Con_points[i - 1][j] = Bez.Tar_Points[i][j] + K_vec[j] * t2;
            Bez.Con_points[i][j] = Bez.Tar_Points[i][j] + K_vec[j] * t1;
        }
    }
}

/* 函数：Cross_Product
 * 功能：叉乘  C = A X B
 * 参数：f32 A[3] , f32 B[3] ,f32 C[3]
 * 返回值：void
 * */
void Cross_Product(f32 A[3], f32 B[3], f32 C[3])
{
    C[0] = A[1] * B[2] - A[2] * B[1];
    C[1] = -(A[0] * B[2] - A[2] * B[0]);
    C[2] = A[0] * B[1] - A[1] * B[0];
}

/* 函数：Vector_Length
 * 功能：求向量长度
 * 参数：f32 A[3]
 * 返回值：f32
 * */
f32 Vector_Length(f32 A[3])
{
    f32 total = 0;
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        total += A[i] * A[i];
    }
    return sqrt(total);
}

/* 函数：Midpoint_Calculation
 * 功能：中间点计算,为控制点的中心点
 * 参数：void
 * 返回值：void
 * */
void Midpoint_Calculation(void)
{
    int i = 0, j = 0;
    for (i = 1; i < Bez.Tar_P_Num - 1; i += 2)
    {
        for (j = 0; j < 3; j++)
        {
            Bez.Tar_Points[i][j] = (Bez.Con_points[i - 1][j] + Bez.Con_points[i][j]) / 2;
        }
    }
}

/* 函数：Bezier_Parameter_Calculation
 * 功能：贝塞尔参数计算，abcABC
 * 参数：void
 * 返回值：void
 * */
void Bezier_Parameter_Calculation(void)
{
    int i = 0, j = 0;
    for (i = 0; i < Bez.Tar_P_Num - 1; i++)
    {
        for (j = 0; j < 3; j++)
        {
            Bez.Bez_a[i][j] = Bez.Tar_Points[i][j] + Bez.Tar_Points[i + 1][j] - 2 * Bez.Con_points[i][j];
            Bez.Bez_b[i][j] = 2 * (Bez.Con_points[i][j] - Bez.Tar_Points[i][j]);
            Bez.Bez_c[i][j] = Bez.Tar_Points[i][j];
        }
        Bez.Bez_A[i] = 4 * (Bez.Bez_a[i][0] * Bez.Bez_a[i][0] + Bez.Bez_a[i][1] * Bez.Bez_a[i][1] + Bez.Bez_a[i][2] * Bez.Bez_a[i][2]);
        Bez.Bez_B[i] = 4 * (Bez.Bez_a[i][0] * Bez.Bez_b[i][0] + Bez.Bez_a[i][1] * Bez.Bez_b[i][1] + Bez.Bez_a[i][2] * Bez.Bez_b[i][2]);
        Bez.Bez_C[i] = Bez.Bez_b[i][0] * Bez.Bez_b[i][0] + Bez.Bez_b[i][1] * Bez.Bez_b[i][1] + Bez.Bez_b[i][2] * Bez.Bez_b[i][2];
    }
}

/* 函数：Curves_Length_Calculation
 * 功能：求各贝塞尔曲线长度
 * 参数：void
 * 返回值：void
 * */
void Curves_Length_Calculation(void)
{
    int i = 0;
    f32 a1, a2;
    for (i = 0; i < Bez.Tar_P_Num - 1; i++)
    {
        a1 = Distance_Integral(1, Bez.Bez_A[i], Bez.Bez_B[i], Bez.Bez_C[i]);
        a2 = Distance_Integral(0, Bez.Bez_A[i], Bez.Bez_B[i], Bez.Bez_C[i]);
        Bez.Curve_Len[i] = Distance_Integral(1, Bez.Bez_A[i], Bez.Bez_B[i], Bez.Bez_C[i]) -
                           Distance_Integral(0, Bez.Bez_A[i], Bez.Bez_B[i], Bez.Bez_C[i]);
    }
}

/* 函数：Distance_Integral
 * 功能：速度（假）的积分，只能用于相减
 * 参数：f32 t,f32 A,f32 B,f32 C
 * 返回值：f32
 * */
f32 Distance_Integral(f32 t, f32 A, f32 B, f32 C)
{
    float sa = sqrt(A);
    float satb = 2 * A * t + B;
    float satbtc = 2 * sa * sqrt(A * t * t + B * t + C);
    float sa23 = 8 * A * sa;

    float result = (satbtc * satb - (B * B - 4 * A * C) * log(satbtc + satb)) / sa23;
    return result;
}

/* 函数：Point_Curvature
 * 功能：计算某点曲率
 * 参数：f32 t,f32 a, f32 b, f32 c
 * 返回值：f32
 * */
f32 Point_Curvature(f32 t, f32 a[3], f32 b[3], f32 c[3])
{
    f32 B_1[3]; // 一阶导数
    f32 B_2[3]; // 二阶导数
    int i = 0, j = 0;
    for (j = 0; j < 3; j++)
    {
        B_1[j] = 2 * a[j] * t + b[j];
        B_2[j] = 2 * a[j];
    }
    f32 quly = sqrt(pow(B_2[2] * B_1[1] - B_2[1] * B_1[2], 2) + pow(B_2[0] * B_1[2] - B_2[2] * B_1[0], 2) + pow(B_2[1] * B_1[0] - B_2[0] * B_1[1], 2)) / pow(pow(B_1[0], 2) + pow(B_1[1], 2) + pow(B_1[2], 2), 3 / 2);
    return quly;
}

/* 函数：Curvature_and_Length_Calculation
 * 功能：曲率与对应长度计算
 * 参数：void
 * 返回值：void
 * */
void Curvature_and_Length_Calculation(void)
{
    int i = 0, j = 0;
    f32 t;
    for (i = 0; i < Bez.Tar_P_Num - 1; i++)
    {
        f32 len_0 = Distance_Integral(0, Bez.Bez_A[i], Bez.Bez_B[i], Bez.Bez_C[i]);
        for (j = 0; j < 8; j++)
        {
            t = j * 0.125;
            Bez.Curvature[i][j] = Point_Curvature(t, Bez.Bez_a[i], Bez.Bez_b[i], Bez.Bez_c[i]);
            Bez.To_Point_Curve_Len[i][j] = Distance_Integral(t, Bez.Bez_A[i], Bez.Bez_B[i], Bez.Bez_C[i]) - len_0;
        }
    }
}

/* 函数：Tnit_Bez_test
 * 功能：初始化贝塞尔结构体 的测试版本，给定目标点数据
 * 参数：void
 * 返回值：void
 * */
void Tnit_Bez_test(void)
{
    Bez.Tar_P_Num = 29;

    Bez.Tar_Points[0][0] = 0;
    Bez.Tar_Points[0][1] = 0;
    Bez.Tar_Points[0][2] = 0;

    Bez.Tar_Points[2][0] = 0.25356;
    Bez.Tar_Points[2][1] = 0.05;
    Bez.Tar_Points[2][2] = 0.16034;

    Bez.Tar_Points[4][0] = 0.53519;
    Bez.Tar_Points[4][1] = 0.10138;
    Bez.Tar_Points[4][2] = 0.33843;

    Bez.Tar_Points[6][0] = 0.50712;
    Bez.Tar_Points[6][1] = 0.50000;
    Bez.Tar_Points[6][2] = 0.32068;

    Bez.Tar_Points[8][0] = 0.50010;
    Bez.Tar_Points[8][1] = 0.59965;
    Bez.Tar_Points[8][2] = 0.31624;

    // 新增
    Bez.Tar_Points[10][0] = 0.29582;
    Bez.Tar_Points[10][1] = 0.63000;
    Bez.Tar_Points[10][2] = 0.18706;

    Bez.Tar_Points[12][0] = 0.21130;
    Bez.Tar_Points[12][1] = 0.45000;
    Bez.Tar_Points[12][2] = 0.13362;

    Bez.Tar_Points[14][0] = 0.29582;
    Bez.Tar_Points[14][1] = 0.45000;
    Bez.Tar_Points[14][2] = 0.18706;

    Bez.Tar_Points[16][0] = 0.42260;
    Bez.Tar_Points[16][1] = 0.55000;
    Bez.Tar_Points[16][2] = 0.26723;
    // 新增
    Bez.Tar_Points[18][0] = 0.29582;
    Bez.Tar_Points[18][1] = 0.63000;
    Bez.Tar_Points[18][2] = 0.18706;

    Bez.Tar_Points[20][0] = 0.12691;
    Bez.Tar_Points[20][1] = 0.59617;
    Bez.Tar_Points[20][2] = 0.08025;

    Bez.Tar_Points[22][0] = 0.08452;
    Bez.Tar_Points[22][1] = 0.50000;
    Bez.Tar_Points[22][2] = 0.05345;

    Bez.Tar_Points[24][0] = 0.06346;
    Bez.Tar_Points[24][1] = 0.20104;
    Bez.Tar_Points[24][2] = 0.04013;

    Bez.Tar_Points[26][0] = 0.25356;
    Bez.Tar_Points[26][1] = 0.05000;
    Bez.Tar_Points[26][2] = 0.16034;

    Bez.Tar_Points[28][0] = 0.33808;
    Bez.Tar_Points[28][1] = 0.10000;
    Bez.Tar_Points[28][2] = 0.21378;

    Bez.order = 0;
    Bez.t = 0;
}

void len_compare()
{
    printf("---------------------\n");
    for (int i = 0; i < Bez.Tar_P_Num - 1; i++)
    {
        f32 len = 0;
        for (int j = 0; j < 3; j++)
        {
            len += pow(Bez.Tar_Points[i][j] - Bez.Tar_Points[i + 1][j], 2);
            //printf("           %f  %f\n", Bez.Tar_Points[i][j], Bez.Tar_Points[i + 1][j]);
        }
        len = sqrt(len);
        printf("%f  %f\n", len, Bez.Curve_Len[i]);
        l1 += Bez.Curve_Len[i];
    }
}

/* 函数：VT_Init
 * 功能：速度结构体初始化
 * 参数：void
 * 返回值：void
 * */
void VT_Init(void)
{
    int i = 0;
    VT.Dis_Piece[0].v1 = 0; //初始速度为0
    // 将速度限制初始化为-1,>0表示有效
    for (i = 0; i < MAX_NUM_OF_POINT; i++)
    {
        VT.Speed_Limit[i] = -1;
        VT.Acc_Limit[i] = -1;
    }
    // 路程片速度初始化为0
    for (i = 0; i < Bez.Tar_P_Num - 1; i++)
    {
        VT.Dis_Piece[i].Piece_Dis = 0;
    }

    VT.B_Piece[0].p_start = 0;
    VT.B_Piece[0].b_start = 0;

    VT.Speed_Limit[6] = 5.4962108;
    VT.Time_Limit[6] = 3;

    VT.Speed_Limit[22] = 5.4962108;
    VT.Acc_Limit[22] = 20;
    VT.Time_Limit[22] = 4.0954;

    VT.Speed_Limit[28] = 0;
    VT.Time_Limit[28] = 9;

    VT.time_in_piece = 0;
    VT.cur_piece = 0;
}

/* 函数：Curve_Segment
 * 功能：曲线分段
 * 参数：void
 * 返回值：void
 * */
void Curve_Segment(void)
{
    int i = 0;             // 贝塞尔结构体序号
    int j = 0;             //曲率点序号
    int bk = 0;            // 大片路程片序号.big
    int sk = -1;           // 小路程片序号
    int p_f = 0;           //0为低速段，1为变速段
    f32 big_total_dis = 0; // 大片路程片的距离
    // 遍历所有曲线
    for (i = 0; i < Bez.Tar_P_Num - 1; i++)
    {
        if (VT.Speed_Limit[i] > 0) //有速度限制（接抛球）
        {
            // 表示下一个路程段是新的
            p_f = 0;
            // 上一个大片路程片的end序号
            VT.B_Piece[bk].p_end = sk + 1;
            VT.B_Piece[bk].b_end = i;
            // 上一个大片路程片的时间
            if (bk == 0)
            {
                VT.B_Piece[bk].time = VT.Time_Limit[i];
            }
            else
            {
                VT.B_Piece[bk].time = VT.Time_Limit[i] - VT.Time_Limit[VT.B_Piece[bk - 1].b_end];
            }

            bk++;

            // 大片路程片的start序号
            //VT.B_Piece[bk].p_start = sk + 1;
            //VT.B_Piece[bk].b_start = i;

            // 读 速度限制
            VT.Dis_Piece[sk + 1].v1 = VT.Speed_Limit[i];

            if (VT.Acc_Limit[i] > 0) // 限制起点及其中的加速度,接球
            {
                sk++;
                // 路程片所需的变量都已得到
                VT.Dis_Piece[sk].Speed_Mode = SIGLE_ACC;
                VT.Dis_Piece[sk].Piece_Dis = Bez.Curve_Len[i] + Bez.Curve_Len[i + 1];
                VT.Dis_Piece[sk].Acc_Limit = VT.Acc_Limit[i];
                VT.Dis_Piece[sk].v3 = sqrt(
                    pow(VT.Dis_Piece[sk].v1, 2) - 4 * VT.Dis_Piece[sk].Acc_Limit * VT.Dis_Piece[sk].Piece_Dis / 3);
                VT.Dis_Piece[sk].duration = 3 * (VT.Dis_Piece[sk].v1 - VT.Dis_Piece[sk].v3) / (2 * VT.Dis_Piece[sk].Acc_Limit);

                // 被限制的路程是两个贝塞尔曲线

                l3 += VT.Dis_Piece[sk].Piece_Dis;

                VT.B_Piece[bk]
                    .p_start = sk + 1;
                VT.B_Piece[bk].b_start = i + 2;

                i++;
                continue;
            }
            else // 只限制速度，抛球
            {
                VT.Dis_Piece[sk].v3 = VT.Dis_Piece[sk + 1].v1;

                VT.B_Piece[bk].p_start = sk + 1;
                VT.B_Piece[bk].b_start = i;
            }
        }

        //遍历所有曲率点
        for (j = 0; j < CURVATURE_POINT_NUM; j++)
        {
            if (Bez.Curvature[i][j] < CURVATURE_LIMIT) // 不限速
            {
                if (p_f == 0) //第一个小曲率段
                {
                    p_f = 1;
                    sk++;
                    VT.Dis_Piece[sk].Speed_Mode = VARIBLE_ACC;
                }
            }
            else // 限速
            {
                if (p_f == 1) //第一个小曲率段
                {
                    p_f = 0;
                    sk++;
                    VT.Dis_Piece[sk].Speed_Mode = UNIFORO_MOTION;
                }
            }
            // 曲率代表的一小段路程
            f32 curvature_dis =
                (j == CURVATURE_POINT_NUM - 1) ? Bez.Curve_Len[i] - Bez.To_Point_Curve_Len[i][j]
                                               : Bez.To_Point_Curve_Len[i][j + 1] - Bez.To_Point_Curve_Len[i][j];
            VT.Dis_Piece[sk].Piece_Dis += curvature_dis;
            l3 += curvature_dis;
        }
    }

    /* 对最后一个大片做处理 ，最终位置的时间必须给定*/
    // 上一个大片路程片的end序号
    VT.B_Piece[bk].p_end = sk + 1;
    // 上一个大片路程片的时间
    if (bk == 0)
    {
        VT.B_Piece[bk].time = VT.Time_Limit[i];
    }
    else
    {
        VT.B_Piece[bk].time = VT.Time_Limit[i] - VT.Time_Limit[VT.B_Piece[bk - 1].b_end];
    }
    VT.piece_num = sk + 1;
    VT.Bpiece_num = bk + 1;
}

/* 函数：Endpoint_Speed_Calculation
 * 功能：端点速度计算
 * 参数：void
 * 返回值：void
 * */
void Endpoint_Speed_Calculation(void)
{
    int i = 0;
    for (i = 0; i < VT.piece_num; i++)
    {
        if (VT.Dis_Piece[i].Speed_Mode != SIGLE_ACC)
        {
            if (VT.Dis_Piece[i].v1 != 0) // 只限制了一个点的速度的情况
            {
                VT.Dis_Piece[i - 1].v3 = VT.Dis_Piece[i].v1;
                VT.Dis_Piece[i].v3 = LOW_SPEED_LIMIT;
                VT.Dis_Piece[i].Acc_Limit = ACC_LIMIT;
            }
            else // 普通情况，始末都是一样的速度
            {
                VT.Dis_Piece[i].v1 = LOW_SPEED_LIMIT;
                VT.Dis_Piece[i].v3 = LOW_SPEED_LIMIT;
                VT.Dis_Piece[i].Acc_Limit = ACC_LIMIT;
            }
        }
    }
    for (i = 0; i < VT.piece_num; i++)
    {
        if (VT.Dis_Piece[i].Speed_Mode == SIGLE_ACC)
        {
            VT.Dis_Piece[i - 1].v3 = VT.Dis_Piece[i].v1;
            VT.Dis_Piece[i + 1].v1 = VT.Dis_Piece[i].v3;
        }
    }
    VT.Dis_Piece[0].v1 = 0;
    VT.Dis_Piece[VT.piece_num - 1].v3 = 0;
}

/* 函数名：Pre_Piece_Cal
 * 功能：对除最后一段以外的所有段进行速度规划
 * 参数： f32 Piece_Dis  路程片的长度
 *       f32 Start_Speed   路程片的起始速度
 *       f32 End_Speed   路程片的结束速度
 *       f32* Acc   路程片的加速度
 *       f32* Uni_Spd  路程片的匀速度
 *       f32* Duration   路程片的持续时间
 * 返回值：int 运动模式  （1：三段速，2：单段速）
 */
int Pre_Piece_Cal(f32 Piece_Dis, f32 Start_Speed, f32 End_Speed, f32 *Acc,
                  f32 *Uni_Spd, f32 *Duration)
{
    f32 spd = sqrtf(
        (4 * (*Acc) * Piece_Dis + 3 * (powf(Start_Speed, 2) + powf(End_Speed, 2))) / 6);
    if (spd > Start_Speed && spd > End_Speed)
    {
        // 只用两段的速度过大
        if (spd > SPEED_LIMIT)
        {
            *Uni_Spd = SPEED_LIMIT;
            *Duration = (Piece_Dis - 3 * (2 * SPEED_LIMIT * (Start_Speed + End_Speed) - 2 * powf(SPEED_LIMIT, 2) - powf(Start_Speed, 2) - powf(End_Speed, 2)) / (4 * *Acc)) / SPEED_LIMIT;
        }
        // 极限速度不是很大
        else
        {
            *Uni_Spd = spd;
            *Duration = 3 * (2 * (*Uni_Spd) - Start_Speed - End_Speed) / (2 * (*Acc));
        }
        return 1;
    }

    spd = sqrtf(
        -(4 * (*Acc) * Piece_Dis - 3 * (powf(Start_Speed, 2) + powf(End_Speed, 2))) / 6);
    if (spd < Start_Speed && spd < End_Speed)
    {
        *Uni_Spd = spd;
        *Duration = -3 * (2 * (*Uni_Spd) - Start_Speed - End_Speed) / (2 * (*Acc));
        return 1;
    }
    else
    {
        *Acc = 3 * fabsf(powf(End_Speed, 2) - powf(Start_Speed, 2)) / (4 * Piece_Dis);
        *Duration = 3 * fabsf(Start_Speed - End_Speed) / (2 * (*Acc));
        return 2;
    }
}

/* 函数名：Last_Piece_Cal
 * 功能：对最后一个路程片进行速度规划
 * 参数： f32 Piece_Dis  路程片的长度
 *       f32 Start_Speed   路程片的起始速度
 *       f32 End_Speed   路程片的结束速度
 *       f32* Acc   路程片的加速度
 *       f32* Uni_Spd  路程片的匀速度
 *       f32* Duration   路程片的持续时间
 * 返回值：void
 */

void Last_Piece_Cal(f32 Piece_Dis, f32 Start_Speed, f32 End_Speed, f32 *Acc,
                    f32 *Uni_Spd, f32 *Duration)
{
    f32 Uni1;
    f32 Uni2;
    Uni1 = (Piece_Dis - 3 * (powf(End_Speed, 2) - powf(Start_Speed, 2)) / (4 * (*Acc))) / (*Duration - (3 * (End_Speed - Start_Speed)) / (2 * (*Acc)));
    if (Uni1 > Start_Speed && Uni1 < End_Speed)
    {
        *Uni_Spd = Uni1;
        return;
    }
    Uni1 = (Piece_Dis - 3 * (powf(Start_Speed, 2) - powf(End_Speed, 2)) / (4 * (*Acc))) / (*Duration - (3 * (Start_Speed - End_Speed)) / (2 * (*Acc)));
    if (Uni1 < Start_Speed && Uni1 > End_Speed)
    {
        *Uni_Spd = Uni1;
        return;
    }
    f32 a = 3.0 / (-2 * (*Acc));
    f32 b = *Duration + (3 * (Start_Speed + End_Speed) / (2 * (*Acc)));
    f32 c = -(Piece_Dis + (3 * (powf(Start_Speed, 2) + powf(End_Speed, 2))) / (4 * (*Acc)));
    Uni1 = (-b + sqrtf(powf(b, 2) - 4 * a * c)) / (2 * a);
    Uni2 = (-b - sqrtf(powf(b, 2) - 4 * a * c)) / (2 * a);
    if ((Uni1 > Start_Speed && Uni1 > End_Speed &&
         *Duration - 3 * fabs(Start_Speed - Uni1) / (2 * *Acc) - 3 * fabs(End_Speed - Uni1) / (2 * *Acc) > 0) ||
        (Uni2 > Start_Speed && Uni2 > End_Speed &&
         *Duration - 3 * fabs(Start_Speed - Uni2) / (2 * *Acc) - 3 * fabs(End_Speed - Uni2) / (2 * *Acc) > 0))
    {
        *Uni_Spd = Uni1 > Start_Speed && Uni1 > End_Speed ? Uni1 : Uni2;
        return;
    }
    a = 3.0 / (2 * (*Acc));
    b = *Duration + (3 * (-Start_Speed - End_Speed) / (2 * (*Acc)));
    c =
        -(Piece_Dis + (3 * (-powf(Start_Speed, 2) - powf(End_Speed, 2))) / (4 * (*Acc)));
    Uni1 = (-b + sqrtf(powf(b, 2) - 4 * a * c)) / (2 * a);
    Uni2 = (-b - sqrtf(powf(b, 2) - 4 * a * c)) / (2 * a);
    if ((Uni1 > 0 && Uni1 < Start_Speed && Uni1<End_Speed && * Duration - 3 * fabs(Start_Speed - Uni1) / (2 * *Acc) - 3 * fabs(End_Speed - Uni1) / (2 * *Acc)> 0) ||
        (Uni2 > 0 && Uni2 < Start_Speed && Uni2<End_Speed && * Duration - 3 * fabs(Start_Speed - Uni2) / (2 * *Acc) - 3 * fabs(End_Speed - Uni2) / (2 * *Acc)> 0))
    {
        *Uni_Spd = Uni1 < Start_Speed && Uni1 < End_Speed ? Uni1 : Uni2;
        return;
    }
    printf("--计算错误-- %f \n", Piece_Dis);
}

/* 函数：Speed_Planning_in_Piece
 * 功能：段内速度规划
 * 参数：void
 * 返回值：void
 * */
void Speed_Planning_in_Piece(void)
{
    int i = 0;          // 大片的序号
    int j = 0;          // 路程片的序号
    f32 time_total = 0; // 记录大片中已用的时间

    for (i = 0; i < VT.Bpiece_num; i++)
    {
        time_total = 0;
        /* 处理大片里的前几个路程片 */
        for (j = VT.B_Piece[i].p_start; j < VT.B_Piece[i].p_end - 1; j++)
        {
            // 被限制速度的 匀速段
            if (VT.Dis_Piece[j].Speed_Mode == UNIFORO_MOTION)
            {
                VT.Dis_Piece[j].duration = VT.Dis_Piece[j].Piece_Dis / VT.Dis_Piece[j].v1;
            }
            // 普通段
            else
            {
                int changed_f = Pre_Piece_Cal(VT.Dis_Piece[j].Piece_Dis,
                                              VT.Dis_Piece[j].v1,
                                              VT.Dis_Piece[j].v3,
                                              &VT.Dis_Piece[j].Acc_Limit,
                                              &VT.Dis_Piece[j].v2,
                                              &VT.Dis_Piece[j].duration);
                // 还是 三段速 , (可能两段，可能三段)
                if (changed_f == VARIBLE_ACC)
                {
                    // 计算两段各自的时间
                    VT.Dis_Piece[j].t1 = 3 * fabs(VT.Dis_Piece[j].v1 - VT.Dis_Piece[j].v2) / (2 * VT.Dis_Piece[j].Acc_Limit);
                    VT.Dis_Piece[j].t3 = 3 * fabs(VT.Dis_Piece[j].v2 - VT.Dis_Piece[j].v3) / (2 * VT.Dis_Piece[j].Acc_Limit);
                    // 是否有匀速部分
                    if (fabs(VT.Dis_Piece[j].t1 + VT.Dis_Piece[j].t3 - VT.Dis_Piece[j].duration) > 0.0001)
                    {
                        VT.Dis_Piece[j].t2 = VT.Dis_Piece[j].duration - VT.Dis_Piece[j].t1 - VT.Dis_Piece[j].t3;
                    }
                }
                // 变成 单段速
                else
                {
                    VT.Dis_Piece[j].Speed_Mode = SIGLE_ACC;
                }
            }
            time_total += VT.Dis_Piece[j].duration;
        }

        /* 处理大片中的最后一个路程片 */
        // 算出剩余时间
        VT.Dis_Piece[j].duration = VT.B_Piece[i].time - time_total;
        // 求匀速的速度
        Last_Piece_Cal(VT.Dis_Piece[j].Piece_Dis, VT.Dis_Piece[j].v1,
                       VT.Dis_Piece[j].v3, &VT.Dis_Piece[j].Acc_Limit,
                       &VT.Dis_Piece[j].v2, &VT.Dis_Piece[j].duration);
        // 计算三段各自的时间
        VT.Dis_Piece[j].t1 = 3 * fabs(VT.Dis_Piece[j].v1 - VT.Dis_Piece[j].v2) / (2 * VT.Dis_Piece[j].Acc_Limit);
        VT.Dis_Piece[j].t3 = 3 * fabs(VT.Dis_Piece[j].v2 - VT.Dis_Piece[j].v3) / (2 * VT.Dis_Piece[j].Acc_Limit);
        VT.Dis_Piece[j].t2 = VT.Dis_Piece[j].duration - VT.Dis_Piece[j].t1 - VT.Dis_Piece[j].t3;
    }
}

/* 函数：Function_V
 * 功能：函数f = v（t）
 * 参数：f32 t                         参数 时间
 *     f32 v_s,f32 v_e,f32 t_m
 * 返回值：f32                      对应速度
 * */
f32 Function_V(f32 t, f32 v_s, f32 v_e, f32 t_m)
{
    f32 a1 = (v_s - v_e) * t * t / (t_m * t_m);
    return v_s - 3 * a1 + 2 * a1 * t / t_m;
}

/* 函数：Function_S
 * 功能：函数f = s（t）
 * 参数：f32 t                         参数 时间
 *     f32 v_s,f32 v_e,f32 t_m
 * 返回值：f32                      对应路程（相对t=0）
 * */
f32 Function_S(f32 t, f32 v_s, f32 v_e, f32 t_m)
{
    f32 a1 = (v_s - v_e) * pow(t, 3) / (t_m * t_m);
    return v_s * t - a1 + a1 * t / (2 * t_m);
}

/* 函数：Designated_Distance
 * 功能：求被指定的一段路程，给定的时间必须是同一个运动情况内的
 * 参数：int piece_oeder    路程片序号
 *     f32 t_s ,f32 t_e   始末时间
 * 返回值：f32              路程长度
 * */
f32 Designated_Distance(int piece_oeder, f32 t_s, f32 t_e)
{
    // 被限速的匀速情况
    if (VT.Dis_Piece[piece_oeder].Speed_Mode == UNIFORO_MOTION)
    {
        return (t_e - t_s) * VT.Dis_Piece[piece_oeder].v1;
    }
    // 三段变速情况
    else if (VT.Dis_Piece[piece_oeder].Speed_Mode == VARIBLE_ACC)
    {
        // 三段中的 第一段
        if (t_s < VT.Dis_Piece[piece_oeder].t1)
        {
            return Function_S(t_e, VT.Dis_Piece[piece_oeder].v1,
                              VT.Dis_Piece[piece_oeder].v2,
                              VT.Dis_Piece[piece_oeder].t1) -
                   Function_S(t_s, VT.Dis_Piece[piece_oeder].v1,
                              VT.Dis_Piece[piece_oeder].v2,
                              VT.Dis_Piece[piece_oeder].t1);
        }
        // 三段中的 第三段
        else if (t_s > VT.Dis_Piece[piece_oeder].t1 + VT.Dis_Piece[piece_oeder].t2)
        {
            return Function_S(
                       t_e - VT.Dis_Piece[piece_oeder].t1 - VT.Dis_Piece[piece_oeder].t2,
                       VT.Dis_Piece[piece_oeder].v2, VT.Dis_Piece[piece_oeder].v3,
                       VT.Dis_Piece[piece_oeder].t3) -
                   Function_S(
                       t_s - VT.Dis_Piece[piece_oeder].t1 - VT.Dis_Piece[piece_oeder].t2,
                       VT.Dis_Piece[piece_oeder].v2,
                       VT.Dis_Piece[piece_oeder].v3,
                       VT.Dis_Piece[piece_oeder].t3);
        }
        // 三段中的 第二段（匀速）
        else
        {
            return (t_e - t_s) * VT.Dis_Piece[piece_oeder].v2;
        }
    }
    // 单段变速情况
    else
    {
        return Function_S(t_e, VT.Dis_Piece[piece_oeder].v1,
                          VT.Dis_Piece[piece_oeder].v3,
                          VT.Dis_Piece[piece_oeder].duration) -
               Function_S(t_s, VT.Dis_Piece[piece_oeder].v1,
                          VT.Dis_Piece[piece_oeder].v3,
                          VT.Dis_Piece[piece_oeder].duration);
    }
}

/* 函数：Speed_Planning_in_Piece
 * 功能：段内速度规划
 * 参数：f32* speed    output
 *     f32* len      output
 * 返回值：void
 * */
void Get_Speed_and_Len(f32 *speed, f32 *len)
{
    // 下一个时间点(可能溢出)
    f32 next_time = VT.time_in_piece + PREDICT_INTERVALS;
    // 被限速的匀速情况
    if (VT.Dis_Piece[VT.cur_piece].Speed_Mode == UNIFORO_MOTION)
    {
        *speed = VT.Dis_Piece[VT.cur_piece].v1;
        // 有跨段
        if (next_time > VT.Dis_Piece[VT.cur_piece].duration)
        {
            *len = Designated_Distance(VT.cur_piece, VT.time_in_piece,
                                       VT.Dis_Piece[VT.cur_piece].duration) +
                   Designated_Distance(
                       VT.cur_piece + 1, 0,
                       next_time - VT.Dis_Piece[VT.cur_piece].duration);
        }
        // 不跨段
        else
        {
            *len = Designated_Distance(VT.cur_piece, VT.time_in_piece,
                                       next_time);
        }
    }
    // 三段变速情况
    else if (VT.Dis_Piece[VT.cur_piece].Speed_Mode == VARIBLE_ACC)
    {
        // 三段中的 第一段
        if (VT.time_in_piece < VT.Dis_Piece[VT.cur_piece].t1)
        {
            *speed = Function_V(VT.time_in_piece, VT.Dis_Piece[VT.cur_piece].v1,
                                VT.Dis_Piece[VT.cur_piece].v2,
                                VT.Dis_Piece[VT.cur_piece].t1);
            // 有跨段
            if (next_time > VT.Dis_Piece[VT.cur_piece].t1)
            {
                *len = Designated_Distance(VT.cur_piece, VT.time_in_piece,
                                           VT.Dis_Piece[VT.cur_piece].t1) +
                       Designated_Distance(VT.cur_piece,
                                           VT.Dis_Piece[VT.cur_piece].t1,
                                           next_time);
            }
            // 不跨段
            else
            {
                *len = Designated_Distance(VT.cur_piece, VT.time_in_piece,
                                           next_time);
            }
        }
        // 三段中的 第三段
        else if (VT.time_in_piece > VT.Dis_Piece[VT.cur_piece].t1 + VT.Dis_Piece[VT.cur_piece].t2)
        {
            *speed = Function_V(
                VT.time_in_piece - VT.Dis_Piece[VT.cur_piece].t1 - VT.Dis_Piece[VT.cur_piece].t2,
                VT.Dis_Piece[VT.cur_piece].v2,
                VT.Dis_Piece[VT.cur_piece].v3,
                VT.Dis_Piece[VT.cur_piece].t3);
            // 有跨段
            if (next_time > VT.Dis_Piece[VT.cur_piece].duration)
            {
                *len = Designated_Distance(VT.cur_piece, VT.time_in_piece,
                                           VT.Dis_Piece[VT.cur_piece].duration) +
                       Designated_Distance(
                           VT.cur_piece + 1,
                           0,
                           next_time - VT.Dis_Piece[VT.cur_piece].duration);
            }
            // 不跨段
            else
            {
                *len = Designated_Distance(VT.cur_piece, VT.time_in_piece,
                                           next_time);
            }
        }
        // 三段中的 第二段（匀速）
        else
        {
            *speed = VT.Dis_Piece[VT.cur_piece].v2;
            // 有跨段
            if (next_time > VT.Dis_Piece[VT.cur_piece].t1 + VT.Dis_Piece[VT.cur_piece].t2)
            {
                *len = Designated_Distance(
                           VT.cur_piece,
                           VT.time_in_piece,
                           VT.Dis_Piece[VT.cur_piece].t1 + VT.Dis_Piece[VT.cur_piece].t2) +
                       Designated_Distance(
                           VT.cur_piece,
                           VT.Dis_Piece[VT.cur_piece].t1 + VT.Dis_Piece[VT.cur_piece].t2,
                           next_time);
                ;
            }
            // 不跨段
            else
            {
                *len = Designated_Distance(VT.cur_piece, VT.time_in_piece,
                                           next_time);
            }
        }
    }
    // 单段变速情况
    else
    {
        *speed = Function_V(VT.time_in_piece, VT.Dis_Piece[VT.cur_piece].v1,
                            VT.Dis_Piece[VT.cur_piece].v3,
                            VT.Dis_Piece[VT.cur_piece].duration);
        // 有跨段
        if (next_time > VT.Dis_Piece[VT.cur_piece].duration)
        {
            *len = Designated_Distance(VT.cur_piece, VT.time_in_piece,
                                       VT.Dis_Piece[VT.cur_piece].duration) +
                   Designated_Distance(
                       VT.cur_piece + 1, 0,
                       next_time - VT.Dis_Piece[VT.cur_piece].duration);
        }
        // 不跨段
        else
        {
            *len = Designated_Distance(VT.cur_piece, VT.time_in_piece,
                                       next_time);
        }
    }

    // 时间满，则切换下一个时间片
    VT.time_in_piece = next_time;
    l4 += *len;
    if (VT.time_in_piece > VT.Dis_Piece[VT.cur_piece].duration)
    {
        VT.time_in_piece = VT.time_in_piece - VT.Dis_Piece[VT.cur_piece].duration;
        VT.cur_piece++;
        l4 = 0;
        // 终止条件
        if (VT.cur_piece == VT.piece_num)
        {
            R_data.stop_f = 1;
        }
    }
}

/* 函数：VT_Calculation
 * 功能：初始化计算VT结构体
 * 参数：void
 * 返回值：void
 * */
void VT_Calculation(void)
{
    VT_Init();
    Curve_Segment();
    Endpoint_Speed_Calculation();
    Speed_Planning_in_Piece();
}

/* 函数名：Real_Time_Data_Init
 * 功能：初始化 实时运算结构体
 * 参数： void
 * 返回值：void
 */
void Real_Time_Data_Init(void)
{
    R_data.next_pos[0] = Bez.Tar_Points[0][0];
    R_data.next_pos[1] = Bez.Tar_Points[0][1];
    R_data.next_pos[2] = Bez.Tar_Points[0][2];

    R_data.imm_total_len = 0;
    R_data.imm_curve_len = 0;

    R_data.stop_f = 0;
}

/* 函数名：Immediate_Point_Direction_Calculation
 * 功能：计算立即点的方向，并单位化（imm_dir[3]）
 * 参数： void
 * 返回值：void
 */
void Immediate_Point_Direction_Calculation(void)
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        R_data.imm_dir[i] = 2 * Bez.Bez_a[Bez.order][i] * Bez.t + Bez.Bez_b[Bez.order][i];
    }
    f32 dir_len = Vector_Length(R_data.imm_dir);
    for (i = 0; i < 3; i++)
    {
        R_data.imm_dir[i] = R_data.imm_dir[i] / dir_len;
    }
}

/* 函数名：Immediate_Point_Speed_Calculation
 * 功能：计算立即点速度和运动距离（imm_speed，next_move_len）
 * 参数： void
 * 返回值：void
 */
void Immediate_Point_Speed_Calculation(void)
{
    Get_Speed_and_Len(&R_data.imm_speed, &R_data.next_move_len);
    //printf("                      %f   %f\n", R_data.imm_speed, R_data.next_move_len);
}

/* 函数名：Speed_Vector_Calculation
 * 功能：速度向量计算,将速度进行分解（imm_speed_vec[3]）
 * 参数： void
 * 返回值：void
 */
void Speed_Vector_Calculation(void)
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        R_data.imm_speed_vec[i] = R_data.imm_speed * R_data.imm_dir[i];
    }
    printf("%f   %f    %f    ", R_data.imm_speed_vec[0], R_data.imm_speed_vec[1], R_data.imm_speed_vec[2]);
}

/* 函数名：Next_Pos_Calculation
 * 功能：计算下一个位置（next_pos[3]）
 * 参数： void
 * 返回值：void
 */
void Next_Pos_Calculation(void)
{
    R_data.imm_curve_len += R_data.next_move_len;        //更新曲线内运动长度
    if (R_data.imm_curve_len > Bez.Curve_Len[Bez.order]) //如果超出当前曲线
    {
        R_data.imm_curve_len = R_data.imm_curve_len - Bez.Curve_Len[Bez.order];
        Bez.order++; // 曲线序号增加
        Bez.t = 0;   // t重置
    }
    // t=0 的积分
    f32 curve_len_t0 = Distance_Integral(0, Bez.Bez_A[Bez.order],
                                         Bez.Bez_B[Bez.order],
                                         Bez.Bez_C[Bez.order]);
    // 用于 与t时刻的积分 进行比较
    f32 com_len = curve_len_t0 + R_data.imm_curve_len;
    // 存放t时刻的积分
    f32 len_t;
    // t的上下限
    f32 ts = Bez.t, te = 1, tm;
    do // 向中间逼近
    {
        tm = (ts + te) / 2;
        len_t = Distance_Integral(tm, Bez.Bez_A[Bez.order],
                                  Bez.Bez_B[Bez.order], Bez.Bez_C[Bez.order]);
        if (len_t > com_len)
        {
            te = tm;
        }
        else
        {
            ts = tm;
        }
    } while (fabs(len_t - com_len) > LENGTH_ACCURACY);
    Bez.t = tm;
    l2 += R_data.next_move_len;
    //printf("%f   %f   %f   %f  %d  %f  %f  %f  %f\n", R_data.imm_speed, R_data.imm_curve_len, Bez.Curve_Len[Bez.order], l2, VT.cur_piece, l4, VT.Dis_Piece[VT.cur_piece].Piece_Dis, VT.time_in_piece, VT.Dis_Piece[VT.cur_piece].duration);
    printf("%d   %f   %f   %f  %f\n", Bez.order, Bez.t, R_data.imm_dir[0], R_data.imm_dir[1], R_data.imm_dir[2]);
    // 计算下一点位置
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        R_data.next_pos[i] = Bez.Bez_a[Bez.order][i] * Bez.t * Bez.t + Bez.Bez_b[Bez.order][i] * Bez.t + Bez.Bez_c[Bez.order][i];
    }
    // 检验下一点位置是否合法
    /*
    if (R_data.next_pos[0] < 0 || R_data.next_pos[0] > MAXLEN_X || R_data.next_pos[1] < 0 || R_data.next_pos[1] > MAXLEN_Y || R_data.next_pos[2] < 0 || R_data.next_pos[2] > MAXLEN_Z)
    {
        R_data.stop_f = 1;
    }
    */
}

/* 函数名：Predict_Speed_and_Position
 * 功能：预测速度和位置
 * 参数： void
 * 返回值：void
 */
void Predict_Speed_and_Position(void)
{
    int i = 0;
    for (i = 0; i < 3; i++) // 更新立即到达位置（imm_pos[3]），用于矫正
    {
        R_data.imm_pos[i] = R_data.next_pos[i];
    }
    Immediate_Point_Direction_Calculation();
    Immediate_Point_Speed_Calculation();
    Speed_Vector_Calculation();
    Next_Pos_Calculation();
}

int main()
{
    Tnit_Bez_test();
    Control_Point_Calculation();
    Midpoint_Calculation();
    Bezier_Parameter_Calculation();
    Curves_Length_Calculation();
    len_compare();
    Curvature_and_Length_Calculation();

    VT_Calculation();
    printf("VT计算完成\n");
    /*
    f32 spd, len, len_total = 0;
    while (R_data.stop_f == 0)
    {
        Get_Speed_and_Len(&spd, &len);
        len_total += len;
        printf("%f  %f  %f\n", spd, len, len_total);
    }
    */
    while (R_data.stop_f == 0)
    {
        Predict_Speed_and_Position();
    }
    printf("%f %f\n", l1, l3);
    printf("结束\n");
    return 0;
}