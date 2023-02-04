#include<iostream>
#include<vector>
#include<string>
using namespace std;

int judge = 0;
class AVO
{
public:
	int data = 0, x = 1, tag = 0;
	vector<AVO*>next;
	int total();
};

void creat(AVO* v, int n) {
	for (int i = 1; i <= n; i++)
	{
		int num;
		cin >> num >> v[i].data;
		string str;
		getline(cin, str);
		if (str.empty())continue;
		else
		{
			int len = str.length();
			for (int j = 1; j < len; j += 2)
			{
				v[i].x = 0;
				v[str[j] - 48].next.push_back(&v[i]);
			}
		}
	}
}
int AVO::total()
{
	if (tag == 1) { judge = 1; return 0; }
	else
	{
		tag = 1;
		int t;
		if (next.empty()) { t = data; }
		else
		{
			t = data + next[0]->total();
			for (int i = 1; i < next.size(); i++)
			{
				if (data + next[i]->total() > t)
					t = data + next[i]->total();
			}
		}
		tag = 0;
		return t;
	}
}

void out(AVO* v, int n) {
	int i, x = 0, max = 0, a;
	for (int i = 1; i <= n; i++)
	{
		if (v[i].x == 1)
		{
			x++;
			a = v[i].total();
			if (a > max)max = a;
		}
	}
	if (judge == 1 || x == 0)cout << "error";
	else cout << max;
}

int main()
{
	int x;
	cin >> x;
	AVO* v = new AVO[x + 1];
	creat(v, x);
	out(v, x);
}