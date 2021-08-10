#include<iostream> //��׼������� 
#include<ctime>//ʱ�� 
#include<windows.h>//ͼ���豸�ӿں����� 
#include <conio.h>//�ļ�������� 
#include <stdio.h>//c����������� 
#include<time.h>
using namespace std;

#define UP 'w'			//�������Ƽ�
#define DOWN 's'		//�������Ƽ�
#define LEFT 'a'		//�������Ƽ�
#define RIGHT 'd'		//�������Ƽ�

//�г����к궨�壬ʹ��ע�ͷ�ʽ˵����;
//�г�����ȫ�ֱ�����ʹ��ע�ͷ�ʽ˵����;��Ҳ����ͨ�����ֵķ�ʽ�ڴ���ǰ���˵����;��
static const unsigned __int64 epoch = 116444736000000000L;


class Node { //��ջ�ڵ�
	public:
		int x, y; //��¼xy����
		int fx;//��¼����
		Node* next;
		Node(int x = 0, int y = 0, int fx = 0): x(x), y(y), fx(fx), next(NULL) {}
};
class Stack {
	private:
		Node* head;//ջ��ͷָ��
	public:
		Stack(): head(NULL) {} //ͷָ�븳ֵΪ��
		~Stack() { //��������,��ֹ�ڴ�й©
			Node* px;
			while (head != NULL) {
				px = head;
				head = px->next;
				delete (px);
			}
		}
		void push(int x, int y, int fx) {
			Node *px = new Node(x, y, fx); //�����½ڵ�
			px->next = head;
			head = px;
		}
		void pop() { //ջ��
			if (empty()) return; //����ջ�յ����
			Node* px = head;
			head = px->next;
			delete (px);
		}
		bool empty() { //�п�
			return head == NULL;
		}
		Node& top() { //����ջ���ڵ�
			return *head;
		}
};
void outps(Stack &stk) { //��β���·��
	Stack tmp;
	Node hc;
	while (!stk.empty()) {
		hc = stk.top();
		stk.pop();
		tmp.push(hc.x, hc.y, hc.fx);
	}
	hc = tmp.top();
	tmp.pop();
	cout << '(' << hc.x << ',' << hc.y << ')';
	while (!tmp.empty()) {
		hc = tmp.top();
		tmp.pop();
		cout << "->" << '(' << hc.x << ',' << hc.y << ')';
	}
}


int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //��������
const int MAXNN = 72;//�Թ�����С
int MAXN;//�û�������Թ���С 

//MAXN���޸�
bool OK(int x, int y) { //�жϵ��Ƿ��ڽ���
	return x > 0 && x < MAXN && y > 0 && y < MAXN;
}


int shuaxintime;//ˢ��ʱ��
int maze_map[MAXNN][MAXNN];//�Թ���ͼ��1Ϊǽ��0Ϊ�գ�2Ϊ���� 
bool vis[MAXNN][MAXNN]; //?
bool viss[MAXNN][MAXNN]; //��¼�õ��Ƿ񱻷��ʹ� 
int d[MAXNN][MAXNN];//��¼��ǰλ�������ķ������·��ʱ��
char jt[5][6] = {"  ", "��", "��", "��", "��"};//��ӡ�ƶ�·�� 


void print_maze() { //��ӡ�Թ�
	for (int i = 1; i < MAXN; i++) {
		for (int j = 1; j < MAXN; j++) {
			if (maze_map[i][j] == 1) cout << "��";
			else if (maze_map[i][j] == 2) cout << "# ";
			else cout << "  ";
		}
		cout << endl;
	}
}
void maze_path() { //������ʱͬʱ��ӡ�Թ���·��
	for (int i = 1; i < MAXN; i++) {
		for (int j = 1; j < MAXN; j++) {
			if (maze_map[i][j] == 1) cout << "��";
			else if (maze_map[i][j] == 2) cout << "# ";
			else if (d[i][j]) cout << jt[d[i][j]];
			else cout << "  ";
		}
		cout << endl;
	}
}

void maze_generate() { //Prim���ṹ�Թ�����
	srand((unsigned)time(NULL));//�������
	for (int i = 1; i < MAXN; i++) {
		for (int j = 1; j < MAXN; j++) {
			viss[i][j] = d[i][j] = vis[i][j] = 0;//�������е�δ����
			if (i == 1 || i == MAXN - 1 || j == 1 || j == MAXN - 1) maze_map[i][j] = 1;
			else if (i % 2 == 0 && j % 2 == 0) maze_map[i][j] = 0;
			else maze_map[i][j] = 1;
		}
	}
	maze_map[2][1] = maze_map[MAXN - 2][MAXN - 1] = 0; //�����յ�
	bool flag = 1;
	vis[2][2] = 1;//���ʹ����
	int nowx = 2, nowy = 2; //��ǰ���ʸ���
	while (flag) { //ֱ�����е㶼�����ʹ�
		while (1) {
			//�ж���Χ�ĵ��Ƿ񶼱����ʹ�
			bool flag2 = 1;
			int sj, dx, dy;
			for (int i = 0; i < 4; i++) {
				dx = nowx + dir[i][0] * 2;
				dy = nowy + dir[i][1] * 2;
				if (!OK(dx, dy)) continue; //Խ��
				if (vis[dx][dy]) continue; //���ʹ���
				flag2 = 0; //��û���ʹ��ĵ�
			}
			if (flag2) {
				//������ԭ�Ȳ�ȡ�ĵڶ��ֲ���
				//���ҵ��ѷ��ʵķ���󣬰����涼��ͨ
				//���������Ľ�������ڵĿ�̫���ˣ����´��ںܶ�ܶ�·��
				/*
				int ss = rand()%4,tt = rand()%4;
				for(int i=ss;i<=tt;i++){
				    dx = nowx + dir[i][0]*2;
				    dy = nowy + dir[i][1]*2;
				    if(OK(dx,dy)){
				        maze_map[nowx+dir[i][0]][nowy+dir[i][1]]=0;
				    }
				}
				*/
				break;//�˳�while
			}
			flag2 = 1;
			while (flag2) { //����ҵ���һ��û�����ʹ��ĵ�
				sj = rand() % 4;
				dx = nowx + dir[sj][0] * 2;
				dy = nowy + dir[sj][1] * 2;
				if (!OK(dx, dy)) {
					continue;   //Խ��
				}
				if (vis[dx][dy]) {
					continue;   //���ʹ���
				}
				vis[dx][dy] = 1;//���ʸõ�
				maze_map[nowx + dir[sj][0]][nowy + dir[sj][1]] = 0;
				nowx = dx;
				nowy = dy;
				break;
			}
		}
		//���Ƿ����е㶼�����ʹ�
		flag = 0;//�������ĳ�1
		for (int i = 1; i < MAXN; i++) {
			for (int j = 1; j < MAXN; j++) {
				if (i % 2 == 0 && j % 2 == 0) {
					if (!vis[i][j]) { //���е�û�����ʵ�
						flag = 1;
						break;
					}
				}
			}
			if (flag) break;
		}
		//���µ�nowx,nowy
		if (!flag) break; //���е㶼�Ѿ�������
		while (1) {
			nowx = rand() % (MAXN - 1) + 1;
			nowy = rand() % (MAXN - 1) + 1;
			if (nowx % 2 == 1) nowx++;
			if (nowy % 2 == 1) nowy++;
			if (!OK(nowx, nowy)) continue;
			if (!vis[nowx][nowy]) continue;
			//������˵���now xy�ǿ��Ե�
			break;
		}
	}
}

void read_map() { //��ȡ�Թ�
	FILE *fp1;
	char ch; //ÿ������֮����' '
	if ((fp1 = fopen("D:\\Program_file\\C-File\\temp\\map.txt", "rb")) == NULL) {
		printf("-----------in.txt�ļ�\n");
		exit(0);
	}
	fscanf(fp1, "%d", &MAXN);
	fscanf(fp1, "%c", &ch);
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			fscanf(fp1, "%d", &maze_map[i][j]);
			fscanf(fp1, "%c", &ch);
		}
	}
	fclose(fp1);
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			cout << maze_map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "��ȡ���" << endl;
}

void dfs(int sx, int sy, int tx, int ty) { //ʹ�ö�ջʵ�ֵ������������
	Stack st;//ջ
	st.push(sx, sy, 4);
	int x, y, dx, dy;
	while (!st.empty()) {
		//����Թ�����
		x = st.top().x;
		y = st.top().y;
		viss[x][y] = 1;
		d[x][y] = st.top().fx;
		Sleep(shuaxintime);
		system("cls");
		maze_path();
		cout << endl;
		cout << "������λ��:(" << x << ',' << y << ")" << endl;
		if (x == tx && y == ty) {
			cout << "���ҵ��յ�" << endl;
			cout << "��һ���� 1 ��·��:" << endl;
			cout << "��·�� 1 :" << endl;
			outps(st);
			cout << endl;
			break;
		}
		if (st.top().fx == 0) { //����
			viss[x][y] = 1;
			st.pop();
			continue;
		}
		st.top().fx = 0;
		for (int i = 0; i < 4; i++) {
			dx = x + dir[i][0];
			dy = y + dir[i][1];
			if (OK(dx, dy) && viss[dx][dy] == 0 && maze_map[dx][dy] == 0) {
				st.push(dx, dy, i + 1); //�µ���ջ
			}
		}
	}
}

gettimeofday(struct timeval* tp, void* tzp)
{
	FILETIME    file_time;
	SYSTEMTIME  system_time;
	ULARGE_INTEGER ularge;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	ularge.LowPart = file_time.dwLowDateTime;
	ularge.HighPart = file_time.dwHighDateTime;

	tp->tv_sec = (long)((ularge.QuadPart - epoch) / 10000000L);
	tp->tv_usec = (long)(system_time.wMilliseconds * 1000);

	return 0;
}

void manual(int sx, int sy, int tx, int ty) {

	cout << "�������������(��λms):";
	cin >> shuaxintime;

	Stack st;//ջ
	st.push(sx, sy, 4);
	int x, y, dx, dy, df;//x,y��Ŀǰ��λ�����꣬ 
	char direction = RIGHT;
	
	long double dif,target;
//	time_t now,t_begin,t_end;
	target = 60000.0; // 60 s
//	t_begin=time(NULL);

	struct timeval tvBegin, tvEnd;
	gettimeofday(&tvBegin, NULL);
	
	while (1) {
		//����Թ�����
		x = st.top().x;
		y = st.top().y;
		viss[x][y] = 1;
		d[x][y] = st.top().fx;
		Sleep(shuaxintime);
		system("cls");
		maze_path();
		cout << endl;
		cout << "������λ��:(" << x << ',' << y << ")" << endl;
		
//		now = time(NULL);
//		dif = difftime(now,t_begin);
//		printf("time now: %f",dif);

		gettimeofday(&tvEnd, NULL);
		double dDuration = 1000 * (tvEnd.tv_sec - tvBegin.tv_sec) + ((tvEnd.tv_usec - tvBegin.tv_usec) / 1000.0);
		printf("\nʹ�õ�ʱ�䣺%.2lfs", dDuration/1000);
		
		
		if (dDuration >= target){
			printf("\nʱ�䵽��\n\a"); // \a����ϵͳ����������һ�ֱ�﷽ʽ
			return;
		}

  		


		if (x == tx && y == ty) {
			cout << "���ҵ��յ�" << endl;
			outps(st);
			cout << endl;
			break;
		}

		if (_kbhit()) {			//�������뷵��1���Ǽ������뷵��0
			direction = _getch();
		} else {
			continue;
		}
		switch (direction) {
			case UP:
				dx = x + dir[0][0];
				dy = y + dir[0][1];
				df = 1;
				break;		//�����ƶ�
			case DOWN:
				dx = x + dir[1][0];
				dy = y + dir[1][1];
				df = 2;
				break;		//�����ƶ�
			case LEFT:
				dx = x + dir[2][0];
				dy = y + dir[2][1];
				df = 3;
				break;		//�����ƶ�
			case RIGHT:
				dx = x + dir[3][0];
				dy = y + dir[3][1];
				df = 4;
				break;	//�����ƶ�
		}
		if (OK(dx, dy) && maze_map[dx][dy] == 2) {
			cout << "���������Ϸ����" << endl;
			break;
		}
		if (OK(dx, dy) && maze_map[dx][dy] == 0) {
			if (viss[dx][dy] == 0) {
				st.push(dx, dy, df);

			} else {
				viss[x][y] = 0;
				st.pop();
				d[x][y] = 0;
			}
		} else {
			continue;
		}
	}
}

int main() {

	char hc;//������Ϸ���˳����� 
	system("cls");
	int te;

	cout << "�������Թ���1�� /  �����Թ���0��:";
	cin >> te;
	if (te)
		read_map();
	else {
		cout << "�����Զ��Թ���С" << endl;
		cout << "��Option:����Ϊ����,�Ƽ���10-40֮��ѡ" << endl;
		cout << "���Թ���С:";
		cin >> MAXN;
		MAXN++;
		maze_generate();//���������Թ�
	}


	print_maze();//��ӡ�Թ�


	cout << "���ֶ���1�� /  �Զ���0��:";
	cin >> te;
	if (te) {
		manual(2, 1, MAXN - 2, MAXN - 1);
	} else {
		//cout<<"��Option:�Թ�Ϊ���νṹ,������ֻ��һ��·��"<<endl;
		cout << "����ʼ����/�˳�����[Y/N]:";
		cin >> hc;
		if (hc == 'Y' || hc == 'y') {
			system("cls");
			print_maze();//��ӡ�Թ�
			cout << "�������20����,�Ƽ�50,����Թ��Ƚϴ�,��Ϊ��ӡ�Թ�Ҳ��Ҫʱ��,�������ü��Ϊ0" << endl;
			cout << "�������������(��λms):";
			cin >> shuaxintime;
			dfs(2, 1, MAXN - 2, MAXN - 1); //��ʼ����
		}
	}
	cout << "��������������������ַ�����" << endl;
	cin >> hc;
}
