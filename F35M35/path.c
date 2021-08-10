#include <math.h>
#include <malloc.h>
#include <stdio.h>

typedef unsigned long int u32;
typedef long int int32;
typedef unsigned int u16;
typedef unsigned char u8;
typedef float f32;

#define MAX_NUM_OF_POINT 30   // 点个数上限
#define CURVATURE_POINT_NUM 5 // 各段求曲率的点个数
#define CON_POINT_RATIO 0.4   // 控制点距中间点位置 与 两目标点位置的比值，Control point ratio

typedef struct
{
    f32 Tar_Points[MAX_NUM_OF_POINT][3];                  // Target point list ，目标点与中间点序列，指向MtoC里的 目标点序列
    u32 Tar_P_Num;                                        // target points number ，目标点数量
    f32 Con_points[MAX_NUM_OF_POINT - 1][3];              // Control point list ，控制点序列
    f32 Bez_a[MAX_NUM_OF_POINT][3];                       // 参数 a ，分x、y、z方向
    f32 Bez_b[MAX_NUM_OF_POINT][3];                       // 参数 b ，分x、y、z方向
    f32 Bez_c[MAX_NUM_OF_POINT][3];                       // 参数 c ，分x、y、z方向
    f32 Bez_A[MAX_NUM_OF_POINT];                          // 参数 A
    f32 Bez_B[MAX_NUM_OF_POINT];                          // 参数 B
    f32 Bez_C[MAX_NUM_OF_POINT];                          // 参数 C
    f32 Curve_Len[MAX_NUM_OF_POINT];                      // 各段曲线长度
    f32 Curvature[MAX_NUM_OF_POINT][CURVATURE_POINT_NUM]; // 各段多点曲率存储

} Bezier_Curve; // 贝塞尔曲线结构体

void Control_Point_Calculation(void);
void Cross_Product(f32 A[3], f32 B[3], f32 C[3]);
f32 Vector_Length(f32 A[3]);
void Tnit_Bez(void);

Bezier_Curve Bez;

/* 函数：Control_Point_Calculation
 * 功能：计算出控制点位置
 * 参数：void
 * 返回值：void
 * */
void Control_Point_Calculation(void)
{
    /* 计算起点和终点的控制点 */
    int i = 0, j = 0;
    printf("起点与终点控制点\n");
    for (i = 0; i < 3; i++)
    { // 第一个控制点
        Bez.Con_points[0][i] = Bez.Tar_Points[0][i] * (1 - CON_POINT_RATIO) + Bez.Tar_Points[2][i] * CON_POINT_RATIO;
        // 最后一个控制点
        Bez.Con_points[Bez.Tar_P_Num - 2][i] =
            Bez.Tar_Points[Bez.Tar_P_Num - 1][i] * (1 - CON_POINT_RATIO) +
            Bez.Tar_Points[Bez.Tar_P_Num - 3][i] * CON_POINT_RATIO;
        printf("%f   %f\n", Bez.Con_points[0][i], Bez.Con_points[Bez.Tar_P_Num - 2][i]);
    }
    printf("----------------------------\n");
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
        printf("------------------\n");
        printf(" %d    %d \n", i - 1, i);
        // 计算BA、BC，并且单位化
        for (j = 0; j < 3; j++)
        {
            BA_vec[j] = Bez.Tar_Points[i - 2][j] - Bez.Tar_Points[i][j];
            BC_vec[j] = Bez.Tar_Points[i + 2][j] - Bez.Tar_Points[i][j];
        }
        BA_len = Vector_Length(BA_vec);
        BC_len = Vector_Length(BC_vec);

        printf("BA : %f  %f  %f\n", BA_vec[0], BA_vec[1], BA_vec[2]);
        printf("BC : %f  %f  %f\n", BC_vec[0], BC_vec[1], BC_vec[2]);
        printf("BAL: %f     BCL : %f\n", BA_len, BC_len);

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

        printf("N : %f  %f  %f\n", N_vec[0], N_vec[1], N_vec[2]);
        printf("M : %f  %f  %f\n", M_vec[0], M_vec[1], M_vec[2]);
        printf("K : %f  %f  %f\n", K_vec[0], K_vec[1], K_vec[2]);

        // 计算参数t1,t2
        t1 = CON_POINT_RATIO * BC_len / Vector_Length(K_vec);
        t2 = -CON_POINT_RATIO * BA_len / Vector_Length(K_vec);

        // 计算前后控制点
        for (j = 0; j < 3; j++)
        {
            Bez.Con_points[i - 1][j] = Bez.Tar_Points[i][j] + K_vec[j] * t2;
            Bez.Con_points[i][j] = Bez.Tar_Points[i][j] + K_vec[j] * t1;
            printf("%f   %f\n", Bez.Con_points[i - 1][j], Bez.Con_points[i][j]);
        }
    }
    printf("结束\n");
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

/* 函数：Tnit_Bez_test
 * 功能：初始化贝塞尔结构体 的测试版本，给定目标点数据
 * 参数：void
 * 返回值：void
 * */
void Tnit_Bez_test(void)
{
    Bez.Tar_P_Num = 7;

    Bez.Tar_Points[0][0] = 0;
    Bez.Tar_Points[0][1] = 0;
    Bez.Tar_Points[0][2] = 0;

    Bez.Tar_Points[2][0] = 0;
    Bez.Tar_Points[2][1] = 15;
    Bez.Tar_Points[2][2] = 5;

    Bez.Tar_Points[4][0] = 20;
    Bez.Tar_Points[4][1] = 0;
    Bez.Tar_Points[4][2] = 15;

    Bez.Tar_Points[6][0] = 0;
    Bez.Tar_Points[6][1] = 0;
    Bez.Tar_Points[6][2] = 20;
}

int main()
{
    Tnit_Bez_test();
    Control_Point_Calculation();
    return 0;
}