#include<iostream>
#include"dijkstra.h"
#include<fstream>
#include<cstdio>
#include<vector>
using namespace std;

int GetKey(char l, char r, int len) {  //搴忓彿鐨勯€夋嫨锛岄槻姝㈢▼搴忓嚭閿� 锛堥槻寰℃€ц璁★級 
	string ss;
	cin >> ss;
	while (ss.length() > len || ss[0] > r || ss[0] < l) {
		cout << "> Error , try again!" << endl;
		cin >> ss;
	}
	return (int)(ss[0] - l + 1);
}

int predict(string s) {  //棰勬祴杈撳叆鍦扮偣 
	int book[50][50];
	for (int aa = 0; aa < all_area.size(); aa++) {
		cet[aa].s = all_area[aa];
		cet[aa].x = aa;
		memset(book, 0, sizeof(book));
		string a = s;
		string b = all_area[aa];
		int la = a.length();
		int lb = b.length();
		for (int i = la; i >= 1; i--)
			a[i] = a[i - 1];
		for (int i = lb; i >= 1; i--)
			b[i] = b[i - 1];
		for (int i = 0; i <= la; i++)
			book[i][0] = i;
		for (int i = 0; i <= lb; i++)
			book[0][i] = i;
		for (int i = 1; i <= la; i++) {
			for (int j = 1; j <= lb; j++) {
				int ok = 1;
				if (a[i] == b[j])
					ok = 0;
				book[i][j] = min(min(book[i - 1][j] + 1, book[i][j - 1] + 1), book[i - 1][j - 1] + ok);
			}
		}
		cet[aa].d = 1.0*book[la][lb]/(la+lb);
	}
	sort(cet, cet + all_area.size(), cmp1);
	if (cet[0].d == 0)
		return Numb[cet[0].s];
	cout << "> Which? press number:" << endl;
	for (int i = 0; i < 4; i++)
		cout << i + 1 << " . " << cet[i].s << endl;
	int key = GetKey('1', '4', 1);
	{
		return Numb[cet[key - 1].s];
	}
}

void start_read() {  //浠庢枃浠朵腑璇诲彇鏁版嵁 
	ifstream file("data.txt");
	file >> Edges;
	int x, y, c;
	for (int i = 1; i <= Edges; i++) {
		file >> edges[i].a >> edges[i].b >> edges[i].len;
		if (!Numb[edges[i].a]) {
			Numb[edges[i].a] = ++N;
			Name[N] = edges[i].a;
			all_area.push_back(edges[i].a);
		}
		if (!Numb[edges[i].b]) {
			Numb[edges[i].b] = ++N;
			Name[N] = edges[i].b;
			all_area.push_back(edges[i].b);
		}
		x = Numb[edges[i].a];
		y = Numb[edges[i].b];
		c = edges[i].len;
		P[x].push_back({y,c});
		P[y].push_back({x,c});
	}
}

void Add() {  //璇诲彇鏁版嵁 
	system("cls");
	cout << "---------------------------------------------------" << endl;
	cout << "|             choose any keys                     |" << endl;
	cout << "|             1.Update from file date.txt         |" << endl;
	cout << "|             2.Enter data to be updated          |" << endl;
	cout << "---------------------------------------------------" << endl;
	int cho;
	cin >> cho;
	if(cho==1) {
		start_read();
	} else{
		int es;
		cout << "> Enter data to be updated:" << endl;
		cin >> es;
		for (int i = Edges + 1; i <= Edges + es; i++) {
			int x, y, c;
			x = area.read();
			y = area.read();
			cin >> c;
			P[x].push_back((edge) {
				y, c
			});
			P[y].push_back((edge) {
				x, c
			});
			edges[i].a = Name[x];
			edges[i].b = Name[y];
			edges[i].len = c;
		}
		Edges += es;
	}
	cout << "> Update completed.Any key to return." << endl;
	getchar();
	getchar();
}

int start() { //涓昏浜や簰鐣岄潰 
	while(1) { 
	system("cls");
	cout << " ____  ____  _      ____  _     ____    _      ____  _     _  _____ ____ _____ _  ____  _     " << endl;
	cout << "/   _\\/  _ \\/ \\__/|/  __\\/ \\ /\\/ ___\\  / \\  /|/  _ \\/ \\ |\\/ \\/  __//  _ Y__ __Y \\/  _ \\/ \\  /|" << endl;
	cout << "|  /  | / \\|| |\\/|||  \\/|| | |||    \\  | |\\ ||| / \\|| | //| || |  _| / \\| / \\ | || / \\|| |\\ ||" << endl;
	cout << "|  \\__| |-||| |  |||  __/| \\_/|\\___ |  | | \\||| |-||| \\// | || |_//| |-|| | | | || \\_/|| | \\||" << endl;
	cout << "\\____/\\_/ \\|\\_/  \\|\\_/   \\____/\\____/  \\_/  \\|\\_/ \\|\\__/  \\_/\\____\\\\_/ \\| \\_/ \\_/\\____/\\_/  \\|" << endl;
	cout << "desinged by r3t7rn_0 & evade"<<endl;
	cout << "--------------------------------------------------" << endl;
	cout << "|              choose any keys                   |" << endl;
	cout << "|              1.Path Recommendation             |" << endl;
	cout << "|              2.Data Update                     |" << endl;
	cout << "|              3.Data Clear                      |" << endl;
	cout << "|              4.Places List                     |" << endl;
	cout << "|              5.Exit                            |" << endl;
	cout << "--------------------------------------------------" << endl;
		int cas = GetKey('1', '5', 1);
		if (cas == 1) {
			if (N == 0) {
				cout << "> No data, please update it first." << endl;
				getchar();
				getchar();
			} else {
				string a, b;
				int x, y;
				cout << "> Where do you want to go?" << endl;
				cin >> a;
				x = predict(a);
				cout << "> Where do you want to start?" << endl;
				cin >> b;
				y = predict(b);
				//x=Numb[a];
				//y=Numb[b];
				road_plan.clear();
				shortroad.clear();
				int road_cnt = 1;
				if (place[y].solve_dis(x, 0) != -1) {
					road_cnt++;
					cout << "> This is the shortest road:" << endl;
					place[y].print(x);
				}

				for (int j = 0; j < shortroad.size(); j++) {
					int i = shortroad[j];
					if (i != x && i != y) {
						///cout<<x<<" "<<y<<" "<<i<<endl;
						if (place[y].solve_dis(x, i) != -1) {
							if (road_cnt == 1) {
								road_cnt++;
								cout << "> This is the shortest road:" << endl;
							} else
								cout << "> In addition, you can bypass the " << Name[i] << "." << endl;
							place[y].print(x);
						} else
							continue;
					}
					if (road_cnt > 3)
						break;
				}

				getchar();
				getchar();
			}
		} else if (cas == 2) {
			Add();
			for (int i = 1; i <= N; i++)
				place[i].S = i;
		} else if (cas == 3) {
			cout << "> Are yuo sure ?! (Y?N)" << endl;
			string s;
			cin >> s;
			while (s.length() > 1 || (s[0] != 'Y' && s[0] != 'N')) {
				cout << "> Error, try again." << endl;
				cin >> s;
			}
			if (s[0] == 'N')
				continue;
			for (int i = 1; i <= N; i++) {
				P[i].clear();
				Numb.clear();
				Name.clear();
				dis[i] = 0;
				nxt[i] = 0;
				vis[i] = 0;
			}
			N = 0;
			cout << "> OK, Clear Successfull, any key to return." << endl;
			getchar();
			getchar();
		} else if (cas == 4) {
			area.print();
		} else if (cas == 5) {
			return -1;
		}
	}
}

int main() {
	//ShowLogo();
	Vehicle v1("foot",80);
	Vehicle v2("bike",200);
	Vehicle v3("skateboard",160);
	Vehicle v4("littleWhite",250);
	Vehicle v5("bus",300);
	Ve.push_back(v1);
	Ve.push_back(v2);
	Ve.push_back(v3);
	Ve.push_back(v4);
	Ve.push_back(v5);
	while (1) {
		if (D = start() == -1) {
			cout << "> Thanks, Good Bye~" << endl;
			break;
		}
	}

	return 0;
}
