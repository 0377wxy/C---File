#include <math.h>
#include <malloc.h>
#include <stdio.h>

typedef unsigned long int u32;
typedef long int int32;
typedef unsigned int u16;
typedef unsigned char u8;
typedef float f32;

#define MAX_NUM_OF_POINT 30   // 点个数上限
#define CURVATURE_POINT_NUM 8 // 各段求曲率的点个数
#define CON_POINT_RATIO 0.4   // 控制点距中间点位置 与 两目标点位置的比值，Control point ratio

f32 l1, l2, l3;

typedef struct
{
    f32 Tar_Points[MAX_NUM_OF_POINT][3];                           // Target point list ，目标点与中间点序列，指向MtoC里的 目标点序列
    u32 Tar_P_Num;                                                 // target points number ，目标点数量
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

} Bezier_Curve; // 贝塞尔曲线结构体

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

#define CURVATURE_LIMIT 2 // 曲率限制，高于则限速

#define LOW_SPEED_LIMIT 1 // 低速限制（m/s），Low speed limit
#define ACC_LIMIT 3       // 加速度限制，acceleration limit

typedef struct
{
    f32 Piece_Dis;     // 本片的路程 , piece distance
    f32 Cur_Total_Dis; // 前面的片的路程之和 , current total distance
    u32 Speed_Mode;    // 速度模式，有宏定义选项
    f32 v1;
    f32 v2;
    f32 v3;
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
    f32 Speed_Limit[30];                            // 具体点的速度限制
    f32 Acc_Limit[30];                              // 具体点对应的段的加速度限制
    f32 Time_Limit[30];                             // 具体点的时间限制
    Distance_Piece Dis_Piece[MAX_NUM_OF_POINT - 1]; // 路程片结构体
    Big_Piece B_Piece[6];                           // 大片 结构体
    int piece_num;                                  // 路程片个数
    int Bpiece_num;                                 // 大片的个数
    int32 cur_piece;                                // 当前路程片序号
    u32 time_in_piece;                              // 当前片内的时间
} V_T_Diagram;                                      // v_t图 的结构体

V_T_Diagram VT;

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
        for (j = 0; j < 3; j++)               // 计算M
        {
            M_vec[j] = (BA_vec[j] + BC_vec[j]) / 2;
        }
        Cross_Product(N_vec, M_vec, K_vec); // 计算K

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
    for (i = 0; i < Bez.Tar_P_Num - 1; i++)
    {
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
    Bez.Tar_P_Num = 11;

    Bez.Tar_Points[0][0] = 0;
    Bez.Tar_Points[0][1] = 0;
    Bez.Tar_Points[0][2] = 0;

    Bez.Tar_Points[2][0] = 5;
    Bez.Tar_Points[2][1] = 25;
    Bez.Tar_Points[2][2] = 0;

    Bez.Tar_Points[4][0] = 10;
    Bez.Tar_Points[4][1] = 20;
    Bez.Tar_Points[4][2] = 0;

    Bez.Tar_Points[6][0] = 25;
    Bez.Tar_Points[6][1] = 15;
    Bez.Tar_Points[6][2] = 0;

    Bez.Tar_Points[8][0] = 20;
    Bez.Tar_Points[8][1] = 30;
    Bez.Tar_Points[8][2] = 0;

    Bez.Tar_Points[10][0] = 0;
    Bez.Tar_Points[10][1] = 0;
    Bez.Tar_Points[10][2] = 0;
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
    for (i = 0; i < 30; i++)
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

    VT.Speed_Limit[6] = 6;
    VT.Acc_Limit[6] = 2;
    VT.Time_Limit[6] = 10;
    VT.Time_Limit[10] = 20;
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
                VT.B_Piece[bk].time = VT.Time_Limit[i] - VT.Time_Limit[VT.B_Piece[bk - 1].p_end];
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
                VT.Dis_Piece[sk].duration = 3 * (VT.Dis_Piece[sk + 1].v1 - VT.Dis_Piece[sk + 1].v3) / (2 * VT.Dis_Piece[sk].Acc_Limit);

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

int main()
{
    Tnit_Bez_test();
    Control_Point_Calculation();
    Midpoint_Calculation();
    Bezier_Parameter_Calculation();
    Curves_Length_Calculation();
    len_compare();
    Curvature_and_Length_Calculation();

    VT_Init();
    Curve_Segment();
    Endpoint_Speed_Calculation();

    for (int i = 0; i < VT.piece_num; i++)
    {
        l2 += VT.Dis_Piece[i].Piece_Dis;
    }

    printf("结束\n");
    return 0;
}