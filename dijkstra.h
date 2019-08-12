#include<iostream>
#include<fstream>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
#include<cstring>
#include<stack>
#include<cstdio>
using namespace std;
map<string, int> Numb;
map<int, string> Name;
map<stack<int>, int> road_plan;
vector<int> shortroad;

class Vehicle{  //交通工具类 
	public:
		Vehicle(){name="no";v=0;}
		Vehicle(const string s,double vv):name(s),v(vv){}
		void ShowVehicle(){
			cout<<"[ Vehicle's name: "<<name<<" ,Vehicle's speed: "<<v<<"m/s ,";
		}
		void showTime(double dis){
			cout << " The time you will spend : ";
			printf("%.2f minutes ] \n", dis / v);
		}
	private:
		string name;
		double v;
};
vector<Vehicle> Ve;
//vector<Vehicle>::iterator It;

struct edge { //存边权 
	int t;
	int w;
};
vector<edge> P[10001];
vector<string> all_area;
int dis[10001]; 
int vis[10001];
int nxt[10001];
int M, N, D, Edges;

class point { //存储及处理地点 
	public:
		string name;
		int number;
		int read() {
			string ss;
			cin >> ss;
			if (!Numb[ss]) {
				Numb[ss] = ++N;
				Name[N] = ss;
				all_area.push_back(ss);
			}
			return Numb[ss];
		}
		void print() {
			if (N == 0) {
				cout << "> No data, please update it first." << endl;
				getchar();
				getchar();
				return;
			}
			for (int i = 0; i < N; i++)
				cout << all_area[i] << " ";
			cout << endl;
			getchar();
			getchar();
		}
} area;

class node {
	public:
		int x;
		int d;
		bool operator<(const node &a) const {
			return d > a.d;
		}
};

class nod {
	public:
		int x;
		int h;
		int f;
		bool operator<(const nod &a) const {
			return f > a.f;
		}
};

class edgesave {
public: 
	string a;
	string b;
	int len;
} edges[10001];

class change_need {
private:
	string s;
	int x;
	double d;
	friend int predict(string s);
	friend bool cmp1(change_need a, change_need b);
} cet[1001];

bool cmp1(change_need a, change_need b) {
	return a.d < b.d;
}

class solve {  //dijkstra核心算法 

	public:
		int S;
		stack<int> stk;
		int solve_dis(int T, int K) {
			while (!stk.empty())
				stk.pop();
			priority_queue<node> Q;
			memset(vis, 0, sizeof(vis));
			memset(dis, 0x7f, sizeof(dis));
			dis[S] = 0;
			vis[S] = 1;
			vis[K] = 1;
			Q.push((node) {
				S, 0
			});
			while (!Q.empty()) {
				node p = Q.top();
				Q.pop();
				if (dis[p.x] != p.d)
					continue;
				vis[p.x] = 1;
				for (int i = 0; i < P[p.x].size(); i++)
					if (!vis[P[p.x][i].t] && dis[P[p.x][i].t] > dis[p.x] + P[p.x][i].w) {
						dis[P[p.x][i].t] = dis[p.x] + P[p.x][i].w;
						nxt[P[p.x][i].t] = p.x;
						Q.push((node) {
							P[p.x][i].t, dis[P[p.x][i].t]
						});
					}
			}
			if (dis[T] >= 99999)
				return -1;
			else {
				int xx = T;
				//cout << S << " to " << T << " is " << dis[T] << endl;
				//string road_hash="";

				while (xx != S) {
					stk.push(xx);
					xx = nxt[xx];
					if (K == 0)
						shortroad.push_back(xx);
				}
				stk.push(S);
				if (road_plan[stk] == 1) {
					//cout<<K<<" "<<"is old "<<endl;
					return -1;
				}
				road_plan[stk] = 1;
				return 0;
			}
		}
		void print(int T) {
			double dists = 1.0 * dis[T];
			if (stk.empty())
				return;
			
			
			cout << "[ Distance:";
			if (dists >= 1000)
				printf("%.2f KM ]: ", dists / 1000.0);
			else
				printf("%.2f M ]: ", dists);
			cout << "[ " << Name[stk.top()];
			stk.pop();
			while (!stk.empty()) {
				cout << "-->" << Name[stk.top()];
				stk.pop();
			}
			cout << " ]" << endl;
		//	vector<Vehicle>::iterator It;
			for(int i=0;i<Ve.size();i++){
				Ve[i].ShowVehicle();
				Ve[i].showTime(dists);
				/*cout << "[ Time : ";
				printf("%.2f minutes ] ", dists / It.v);*/
			}
				
			cout<<endl;

			//cout<<dis[T]<<" "<<stk.size()<<endl;
		}
} place[10001];
