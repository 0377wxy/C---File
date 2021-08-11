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

void len_compare()
{
    printf("---------------------\n");
    for (int i = 0; i < Bez.Tar_P_Num - 1; i++)
    {
        f32 len = 0;
        for (int j = 0; j < 3; j++)
        {
            len += pow(Bez.Tar_Points[i][j] - Bez.Tar_Points[i + 1][j], 2);
            printf("           %f  %f\n", Bez.Tar_Points[i][j], Bez.Tar_Points[i + 1][j]);
        }
        len = sqrt(len);
        printf("%f  %f\n", len, Bez.Curve_Len[i]);
    }
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
    printf("结束\n");
    return 0;
}