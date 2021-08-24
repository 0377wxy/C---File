#include <math.h>
#include <stdio.h>

#define  UNIFORM_MOTION         0              // ?????????uniform motion
#define  VARIBLE_ACC            1              // ??????????Variable acceleration
#define  UNIFORM_ACC            2
#define  CUR_COE                5              //???????????????????????  ???????    curvature coefficient
#define  INT_CYC                10             //?��?????    interrupt cycle      ms
#define  SPD_LIM                3              //??????????  ??????????
#define MAX_NUM_OF_POINT 30   // 点个数上�?
#define CURVATURE_POINT_NUM 8 // 各段求曲率的点个�?
#define CON_POINT_RATIO 0.4

typedef unsigned long int u32;
typedef long int int32;
typedef unsigned int u16;
typedef unsigned char u8;
typedef float f32;

void Control_Point_Calculation(void);
void Cross_Product(f32 A[3], f32 B[3], f32 C[3]);
f32 Vector_Length(f32 A[3]);
void Init_Bez(void);
void Midpoint_Calculation(void);
void Bezier_Parameter_Calculation(void);
void Curves_Length_Calculation(void);
f32 Distance_Integral(f32 t, f32 A, f32 B, f32 C);
f32 Point_Curvature(f32 t, f32 a[3], f32 b[3], f32 c[3]);
void Curvature_and_Length_Calculation();
void len_compare();
void Init_Bez_test();
f32 Get_Spd(f32 cur_time);
void Spd_Init();
void Spd_plan(f32 Total_Time);

typedef struct
{
    f32 Tar_Points[MAX_NUM_OF_POINT][3];                           // Target point list ��Ŀ������м�����У�ָ��MtoC��� Ŀ�����??  cm
    u32 Tar_P_Num;                                                 // target points number ��Ŀ�������
    f32 Con_points[MAX_NUM_OF_POINT - 1][3];                       // Control point list �����Ƶ�����       cm
    f32 Bez_a[MAX_NUM_OF_POINT][3];                                // ���� a ����x��y��z����
    f32 Bez_b[MAX_NUM_OF_POINT][3];                                // ���� b ����x��y��z����
    f32 Bez_c[MAX_NUM_OF_POINT][3];                                // ���� c ����x��y��z����
    f32 Bez_A[MAX_NUM_OF_POINT];                                   // ���� A
    f32 Bez_B[MAX_NUM_OF_POINT];                                   // ���� B
    f32 Bez_C[MAX_NUM_OF_POINT];                                   // ���� C
    f32 Curve_Len[MAX_NUM_OF_POINT];                               // �������߳���    cm
    f32 To_Point_Curve_Len[MAX_NUM_OF_POINT][CURVATURE_POINT_NUM]; // �����߿�ʼ�����ʵ�� ���߳��� To_Point_Curve_Len      cm
    f32 Curvature[MAX_NUM_OF_POINT][CURVATURE_POINT_NUM];          // ���ζ�����ʴ洢����Ӧ��������߳���           /cm
} Bezier_Curve;

typedef struct
{
    f32 Piece_Dis;                               // ?????��?? , piece distance           cm
    f32 Uni_Start;                               // ��ʼ���ٶε�ʱ��             s
    f32 Uni_End;                                 // �������ٶε�ʱ��             s
    f32 Uni_Spd;
    f32 Start_Speed;                             // ??????????????????     m/s
    f32 End_Speed;                               // ???????????????????    m/s
    f32 Duration = 0;                            // ???????                   s
}Distance_Piece;              // ��???????


typedef struct
{
    Distance_Piece Dis_Piece[60];                                   // ��?????
    f32 total_dis = 0;
    f32 Acc = 2;                            // ?????????         m/s^2
}V_T_Diagram;                   // v_t? ?????

V_T_Diagram v_t_Dia;
Bezier_Curve Bez;

int num = 0;

int main()
{
    Init_Bez_test();
    Control_Point_Calculation();
    Midpoint_Calculation();
    Bezier_Parameter_Calculation();
    Curves_Length_Calculation();
    len_compare();
    Curvature_and_Length_Calculation();
    Spd_Init();
    Spd_plan(20);
    f32 i = 0;
    for (;i < 20;i += 0.1)
    {
        f32 spd = Get_Spd(i);
        printf("%f\n",spd);
    }
}

f32 Get_Spd(f32 cur_time)
{
    f32 time = 0;
    int i = 0;
    while (cur_time > time)
    {
        time += v_t_Dia.Dis_Piece[i].Duration;
        i++;
    }
    i--;
    time = time - v_t_Dia.Dis_Piece[i].Duration;
    if (cur_time < v_t_Dia.Dis_Piece[i].Uni_Start)
    {
        f32 u = (cur_time - time) / (v_t_Dia.Dis_Piece[i].Uni_Start - time);
        return v_t_Dia.Dis_Piece[i].Start_Speed + 3 * (v_t_Dia.Dis_Piece[i].Uni_Spd - v_t_Dia.Dis_Piece[i].Start_Speed) * powf(u,2) + 2 * (v_t_Dia.Dis_Piece[i].Start_Speed - v_t_Dia.Dis_Piece[i].Uni_Spd) * powf(u,3);
    }else if (cur_time >= v_t_Dia.Dis_Piece[i].Uni_Start && cur_time <= v_t_Dia.Dis_Piece[i].Uni_End)
    {
        return v_t_Dia.Dis_Piece[i].Uni_Spd;
    }else
    {
        f32 u = (cur_time - v_t_Dia.Dis_Piece[i].Uni_End) / (time + v_t_Dia.Dis_Piece[i].Duration - v_t_Dia.Dis_Piece[i].Uni_End);
        return v_t_Dia.Dis_Piece[i].Uni_Spd + 3 * (v_t_Dia.Dis_Piece[i].End_Speed - v_t_Dia.Dis_Piece[i].Uni_Spd) * powf(u,2) + 2 * (v_t_Dia.Dis_Piece[i].Uni_Spd - v_t_Dia.Dis_Piece[i].End_Speed) * powf(u,3);
    }
}

void Spd_Init()
{
    int i;
    f32 Dis = 0;
    f32 Used_Dis = 0;
    v_t_Dia.Dis_Piece[0].Start_Speed = 0;
    for(i = 0; i < 6; i++)
    {
        int j = 0;
        if (i == 0)
            j++;
        for (; j < CURVATURE_POINT_NUM; j++)
        {
            f32 Spd;
            Spd = Bez.Curvature[i][j] * CUR_COE;
            if (j == 0)
                Dis += Bez.To_Point_Curve_Len[i][0];
            else
                Dis += Bez.To_Point_Curve_Len[i][j] - Bez.To_Point_Curve_Len[i][j - 1];
            if (Spd < SPD_LIM) {
                if (num != 0)
                    v_t_Dia.Dis_Piece[num].Start_Speed = v_t_Dia.Dis_Piece[num - 1].End_Speed;
                v_t_Dia.Dis_Piece[num].End_Speed = Spd;
                v_t_Dia.Dis_Piece[num].Piece_Dis += Dis;
                Used_Dis += Dis;
                Dis = 0;
                num++;
            }
        }
        v_t_Dia.total_dis += Bez.To_Point_Curve_Len[i][j - 1];
    }
    if (Used_Dis - v_t_Dia.total_dis < 0.01)
        v_t_Dia.Dis_Piece[num - 1].End_Speed = 10;
    else
    {
        v_t_Dia.Dis_Piece[num].Start_Speed = v_t_Dia.Dis_Piece[num - 1].End_Speed;
        v_t_Dia.Dis_Piece[num].Piece_Dis = v_t_Dia.total_dis - Used_Dis;
        v_t_Dia.Dis_Piece[num].End_Speed = 10;
        num++;
    }
}

void Spd_plan(f32 Total_Time)
{
    int i;
    for (i = 0; i < num; i++)
    {
        v_t_Dia.Dis_Piece[i].Duration = Total_Time * (v_t_Dia.Dis_Piece[i].Piece_Dis / v_t_Dia.total_dis);
        if (i == num - 1)break;
        if (3 * fabsf(powf(v_t_Dia.Dis_Piece[i].Start_Speed,2) - powf(v_t_Dia.Dis_Piece[i].End_Speed,2))/(2 * v_t_Dia.Acc) > v_t_Dia.Dis_Piece[i].Piece_Dis)
        {
            v_t_Dia.Dis_Piece[i].Piece_Dis += v_t_Dia.Dis_Piece[i + 1].Piece_Dis;
            v_t_Dia.Dis_Piece[i].End_Speed = v_t_Dia.Dis_Piece[i + 1].End_Speed;
            int j = i + 1;
            for (;j < num - 1; j++)
                v_t_Dia.Dis_Piece[j] = v_t_Dia.Dis_Piece[j + 1];
            num--;
            i--;
        }
    }
    for (i = num - 1; i > 0; i--)
    {
        if (3 * fabsf(powf(v_t_Dia.Dis_Piece[i].Start_Speed,2) - powf(v_t_Dia.Dis_Piece[i].End_Speed,2))/(2 * v_t_Dia.Acc) > v_t_Dia.Dis_Piece[i].Piece_Dis)
        {
            v_t_Dia.Dis_Piece[i - 1].Piece_Dis += v_t_Dia.Dis_Piece[i].Piece_Dis;
            v_t_Dia.Dis_Piece[i - 1].End_Speed = v_t_Dia.Dis_Piece[i].End_Speed;
            v_t_Dia.Dis_Piece[i - 1].Duration += v_t_Dia.Dis_Piece[i].Duration;
            num--;
        }
    }
    while(1)
    {
        f32 a = 3 / (-2 * v_t_Dia.Acc);
        f32 b = v_t_Dia.Dis_Piece[i].Duration + (3 * (v_t_Dia.Dis_Piece[i].Start_Speed + v_t_Dia.Dis_Piece[i].End_Speed) / (2 * v_t_Dia.Acc));
        f32 c = -(v_t_Dia.Dis_Piece[i].Piece_Dis + (3 * (powf(v_t_Dia.Dis_Piece[i].Start_Speed,2) + powf(v_t_Dia.Dis_Piece[i].End_Speed,2))) / (4 * v_t_Dia.Acc));
        f32 Uni = (-b + sqrtf(powf(b,2) - 4 * a * c)) / (2 * a);
        if (Uni > v_t_Dia.Dis_Piece[i].Start_Speed && Uni > v_t_Dia.Dis_Piece[i].End_Speed)
        {
            v_t_Dia.Dis_Piece[i].Uni_Spd = Uni;
            break;
        }
        a = 3 / (2 * v_t_Dia.Acc);
        b = v_t_Dia.Dis_Piece[i].Duration + (3 * (-v_t_Dia.Dis_Piece[i].Start_Speed - v_t_Dia.Dis_Piece[i].End_Speed) / (2 * v_t_Dia.Acc));
        c = -(v_t_Dia.Dis_Piece[i].Piece_Dis + (3 * (-powf(v_t_Dia.Dis_Piece[i].Start_Speed,2) - powf(v_t_Dia.Dis_Piece[i].End_Speed,2))) / (4 * v_t_Dia.Acc));
        Uni = (-b + sqrtf(powf(b,2) - 4 * a * c)) / (2 * a);
        if (Uni < v_t_Dia.Dis_Piece[i].Start_Speed && Uni < v_t_Dia.Dis_Piece[i].End_Speed)
        {
            v_t_Dia.Dis_Piece[i].Uni_Spd = Uni;
            break;
        }
        Uni = (v_t_Dia.Dis_Piece[i].Piece_Dis - (3 * (powf(v_t_Dia.Dis_Piece[i].End_Speed,2) - powf(v_t_Dia.Dis_Piece[i].Start_Speed,2)) / (4 * v_t_Dia.Acc))) / (v_t_Dia.Dis_Piece[i].Duration - (3 * (v_t_Dia.Dis_Piece[i].End_Speed - v_t_Dia.Dis_Piece[i].Start_Speed))/ (2 * v_t_Dia.Acc));
        if (Uni > v_t_Dia.Dis_Piece[i].Start_Speed && Uni < v_t_Dia.Dis_Piece[i].End_Speed)
        {
            v_t_Dia.Dis_Piece[i].Uni_Spd = Uni;
            break;
        }
        Uni = (v_t_Dia.Dis_Piece[i].Piece_Dis - (3 * (powf(v_t_Dia.Dis_Piece[i].Start_Speed,2) - powf(v_t_Dia.Dis_Piece[i].End_Speed,2)) / (4 * v_t_Dia.Acc))) / (v_t_Dia.Dis_Piece[i].Duration - (3 * (v_t_Dia.Dis_Piece[i].Start_Speed - v_t_Dia.Dis_Piece[i].End_Speed))/ (2 * v_t_Dia.Acc));
        if (Uni < v_t_Dia.Dis_Piece[i].Start_Speed && Uni > v_t_Dia.Dis_Piece[i].End_Speed)
        {
            v_t_Dia.Dis_Piece[i].Uni_Spd = Uni;
            break;
        }
    }
    f32 time = 0;
    for (i = 0; i < num; i++)
    {
        v_t_Dia.Dis_Piece[i].Uni_Start = time + 3 * fabsf(v_t_Dia.Dis_Piece[i].Start_Speed - v_t_Dia.Dis_Piece[i].Uni_Spd) / (2 * v_t_Dia.Acc);
        v_t_Dia.Dis_Piece[i].Uni_End = time + v_t_Dia.Dis_Piece[i].Duration - (3 * fabsf(v_t_Dia.Dis_Piece[i].End_Speed - v_t_Dia.Dis_Piece[i].Uni_Spd) / (2 * v_t_Dia.Acc));
        time += v_t_Dia.Dis_Piece[i].Duration;
    }
}





/* ������Control_Point_Calculation
 * ���ܣ���������Ƶ�λ??
 * ������void
 * ����ֵ��void
 * */
void Control_Point_Calculation(void)
{
    /* ���������յ�Ŀ���??*/
    int i = 0, j = 0;
    for (i = 0; i < 3; i++)
    { // ��һ�����Ƶ�
        Bez.Con_points[0][i] = Bez.Tar_Points[0][i] * (1 - CON_POINT_RATIO) + Bez.Tar_Points[2][i] * CON_POINT_RATIO;
        // �R?��һ�����Ƶ�
        Bez.Con_points[Bez.Tar_P_Num - 2][i] =
                Bez.Tar_Points[Bez.Tar_P_Num - 1][i] * (1 - CON_POINT_RATIO) +
                Bez.Tar_Points[Bez.Tar_P_Num - 3][i] * CON_POINT_RATIO;
    }

    /* ��������Ŀ��Ƶ� */
    f32 BA_vec[3], BC_vec[3]; // ����BA��BC
    f32 BA_len, BC_len;       // ����ģ��
    f32 N_vec[3];             // N = BA X BC
    f32 M_vec[3];             // M = (BA + BC)/2
    f32 K_vec[3];             // K = N X M
    f32 t1;                   // ���¶�?����֮��Ŀ��Ƶ� �M?�õĵĲ�����Ϊ��??
    f32 t2;                   // ���϶�?����֮��Ŀ��Ƶ� �M?�õĵĲ�����Ϊ��??
    for (i = 2; i < Bez.Tar_P_Num - 1; i += 2)
    {
        // ����BA��BC�����ҵ�λ��
        for (j = 0; j < 3; j++)
        {
            BA_vec[j] = Bez.Tar_Points[i - 2][j] - Bez.Tar_Points[i][j];
            BC_vec[j] = Bez.Tar_Points[i + 2][j] - Bez.Tar_Points[i][j];
        }
        BA_len = Vector_Length(BA_vec);
        BC_len = Vector_Length(BC_vec);
        for (j = 0; j < 3; j++) // ��λ??
        {
            BA_vec[j] = BA_vec[j] / BA_len;
            BC_vec[j] = BC_vec[j] / BC_len;
        }

        // ����N��M��K
        Cross_Product(BA_vec, BC_vec, N_vec); // ����N
        for (j = 0; j < 3; j++)               // ����M
        {
            M_vec[j] = (BA_vec[j] + BC_vec[j]) / 2;
        }
        Cross_Product(N_vec, M_vec, K_vec); // ����K

        // �������t1,t2
        t1 = CON_POINT_RATIO * BC_len / Vector_Length(K_vec);
        t2 = -CON_POINT_RATIO * BA_len / Vector_Length(K_vec);

        // ����ǰ�����??
        for (j = 0; j < 3; j++)
        {
            Bez.Con_points[i - 1][j] = Bez.Tar_Points[i][j] + K_vec[j] * t2;
            Bez.Con_points[i][j] = Bez.Tar_Points[i][j] + K_vec[j] * t1;
        }
    }
}

/* ������Cross_Product
 * ���ܣ���?? C = A X B
 * ������f32 A[3] , f32 B[3] ,f32 C[3]
 * ����ֵ��void
 * */
void Cross_Product(f32 A[3], f32 B[3], f32 C[3])
{
    C[0] = A[1] * B[2] - A[2] * B[1];
    C[1] = -(A[0] * B[2] - A[2] * B[0]);
    C[2] = A[0] * B[1] - A[1] * B[0];
}

/* ������Vector_Length
 * ���ܣ�����������
 * ������f32 A[3]
 * ����ֵ��f32
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

/* ������Midpoint_Calculation
 * ���ܣ��м�����,Ϊ���Ƶ�����ĵ�
 * ������void
 * ����ֵ��void
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

/* ������Bezier_Parameter_Calculation
 * ���ܣ��������������㣬abcABC
 * ������void
 * ����ֵ��void
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

/* ������Curves_Length_Calculation
 * ���ܣ�������������߳���
 * ������void
 * ����ֵ��void
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

/* ������Distance_Integral
 * ���ܣ�??�ȣ��٣��Ļ��֣�ֻ��������??
 * ������f32 t,f32 A,f32 B,f32 C
 * ����ֵ��f32
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

/* ������Point_Curvature
 * ���ܣ�����ĳ����??
 * ������f32 t,f32 a, f32 b, f32 c
 * ����ֵ��f32
 * */
f32 Point_Curvature(f32 t, f32 a[3], f32 b[3], f32 c[3])
{
    f32 B_1[3]; // ��?�׵�??
    f32 B_2[3]; // ���׵���
    int i = 0, j = 0;
    for (j = 0; j < 3; j++)
    {
        B_1[j] = 2 * a[j] * t + b[j];
        B_2[j] = 2 * a[j];
    }
    f32 quly = sqrt(pow(B_2[2] * B_1[1] - B_2[1] * B_1[2], 2) + pow(B_2[0] * B_1[2] - B_2[2] * B_1[0], 2) + pow(B_2[1] * B_1[0] - B_2[0] * B_1[1], 2)) / pow(pow(B_1[0], 2) + pow(B_1[1], 2) + pow(B_1[2], 2), 3 / 2);
    return quly;
}

/* ������Curvature_and_Length_Calculation
 * ���ܣ��������Ӧ���ȼ���
 * ������void
 * ����ֵ��void
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

/* ������Tnit_Bez_test
 * ���ܣ���ʼ���������ṹ�� �Ĳ��԰汾������Ŀ�����??
 * ������void
 * ����ֵ��void
 * */
void Init_Bez_test(void)
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



















































//int main(){
//
//    for (int i = 1 ; i <= v_t_Dia.Dis_Piece[5].Duration; i++){
//        v_t_Dia.time_in_piece = i;
//        f32 spd = Get_Spd(5);
//        printf("?????:%lf m/s\n",spd);
//    }
//}
//
//
//f32 Get_Spd(int32 cur_piece)
//{
//    Spd_Init();
//}
//
//void Spd_Init(void)
//{
//    v_t_Dia.Dis_Piece[0].Speed_Mode = 1;
//    v_t_Dia.Dis_Piece[0].Start_Speed = 0;
//    v_t_Dia.Dis_Piece[MAX_NUM_OF_POINT - 2].End_Speed = 0;
//    v_t_Dia.Dis_Piece[MAX_NUM_OF_POINT - 2].End_Spd_Flag  = 1;
//
//    for (int j = 0; j < MAX_NUM_OF_POINT; ++j) {
//        for (int i = 0; i < CURVATURE_POINT_NUM; ++i) {
//            int temp;
//            temp = CUR_COE * Bez.Curvature[j][i];
//            if (v_t_Dia.Dis_Piece[j].Spd_Limit > temp)
//                v_t_Dia.Dis_Piece[j].Spd_Limit = temp;
//        }
//
//        if (v_t_Dia.Dis_Piece[j].Speed_Mode == VARIBLE_ACC && v_t_Dia.Dis_Piece[j].End_Spd_Flag == 0)
//        {
//            v_t_Dia.Dis_Piece[j].End_Speed = -(
//                    (2 * v_t_Dia.Dis_Piece[j].Duration * v_t_Dia.Dis_Piece[j].Acc_Limit) / 3 -
//                    v_t_Dia.Dis_Piece[j].Start_Speed);
//        if (v_t_Dia.Dis_Piece[j].End_Speed > v_t_Dia.Dis_Piece[j].Spd_Limit)
//        {
//            v_t_Dia.Dis_Piece[j].End_Speed = v_t_Dia.Dis_Piece[j].Spd_Limit;
//            v_t_Dia.Dis_Piece[j].End_Spd_Flag = 1;
//        }
//        if (v_t_Dia.Dis_Piece[j].End_Spd_Flag = 1)
//        {
//            f32 route = v_t_Dia.Dis_Piece[j].Start_Speed * v_t_Dia.Dis_Piece[j].Duration + (v_t_Dia.Dis_Piece[j].End_Speed - v_t_Dia.Dis_Piece[j].Start_Speed) * v_t_Dia.Dis_Piece[j].Duration + (v_t_Dia.Dis_Piece[j].Start_Speed - v_t_Dia.Dis_Piece[j].End_Speed) * v_t_Dia.Dis_Piece[j].Duration / 2;
//
//            v_t_Dia.Dis_Piece[j].
//        }
//            v_t_Dia.Dis_Piece[j + 1].Start_Speed = v_t_Dia.Dis_Piece[j].End_Speed;
//        }else if (v_t_Dia.Dis_Piece[j].Speed_Mode == UNIFORM_MOTION){
//            v_t_Dia.Dis_Piece[j].End_Speed = v_t_Dia.Dis_Piece[j + 1].Uni_Speed;
//        }
//    }
//}
//
//f32 Gen_Spd(int32 cur_piece)      //Generate_Speed
//{
//    switch(v_t_Dia.Dis_Piece[cur_piece].Speed_Mode)
//    {
//        case UNIFORM_MOTION:
//            return v_t_Dia.Dis_Piece[cur_piece].Uni_Speed;
//        case UNIFORM_ACC:
//            if(fabs((v_t_Dia.Dis_Piece[cur_piece].End_Speed - v_t_Dia.Dis_Piece[cur_piece].Start_Speed)/v_t_Dia.Dis_Piece[cur_piece].Duration) <= v_t_Dia.Dis_Piece[cur_piece].Acc_Limit)
//                spd =  (v_t_Dia.Dis_Piece[cur_piece].End_Speed - v_t_Dia.Dis_Piece[cur_piece].Start_Speed) / v_t_Dia.Dis_Piece[cur_piece].Duration * v_t_Dia.time_in_piece;
//            break;
//        case VARIBLE_ACC:
//            f32 u = v_t_Dia.time_in_piece / v_t_Dia.Dis_Piece[cur_piece].Duration;
//            return v_t_Dia.Dis_Piece[cur_piece].Start_Speed + 3 * (v_t_Dia.Dis_Piece[cur_piece].End_Speed - v_t_Dia.Dis_Piece[cur_piece].Start_Speed) * powf(u,2) + 2 * (v_t_Dia.Dis_Piece[cur_piece].Start_Speed - v_t_Dia.Dis_Piece[cur_piece].End_Speed) * powf(u,3);
//    }
//}