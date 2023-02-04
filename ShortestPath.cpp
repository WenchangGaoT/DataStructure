#include <iostream>
#include <cstring>
using namespace std;
int totalnumb = 1000000;
class city
{
	int cost, num;
public:
	bool used = 0;
	int* con;
	city(int n,int c)
	{
		cost = c;
		con = new int[totalnumb];
	}
	void setcost(int c)
	{
		cost = c;
	}
	void setnum(int n)
	{
		num = n;
	}
	city() 
	{
		cost = num = 0;
		con = new int[totalnumb];
	}
	city(city& c)
	{
		cost = c.cost;
		num = c.num;
		con = new int[totalnumb];
		used = c.used;
		for (int i = 0; i < totalnumb; i++)
			con[i] = c.con[i];
	}
	void connect(int n,int c)
	{
		con[n] = c;
	}
	int getnum()
	{
		return num;
	}
	int getcost()
	{
		return cost;
	}
};
struct way
{
	int* route;
	int length;
	way()
	{
		route = new int[totalnumb];
		length = 0;
	}
	void copy(way& w)
	{
		route = new int[totalnumb];
		for (; length <= w.length; length++)
		{
			route[length] = w.route[length];
		}
	}
};
int* sort(city& c,city* cities,int to)
{
	int n = 0;
	int *r = new int[totalnumb];//�о����л�û�������ٽ���е�����
	for (int i = 0; i < totalnumb; i++)
		if (!cities[i].used &&i != c.getnum() && c.con[i]!=-1)
			r[n++] = i;
	int* re = new int[n+1];
	re[0] = n;
	for (int i = 0; i < n; i++)//ð������������ĳ��а� Ŀ�����->��Ŀ����е�˳������
	{
		int min = c.con[r[i]] + cities[r[i]].getcost();
		for (int j = i; j < n; j++)
		{
			if (r[j] == to)
			{
				r[j] = r[i];
				r[i] = to;
				break;
			}
			int x = c.con[r[j]] + cities[r[j]].getcost();
			if (x < min)
			{
				int m = r[i];
				r[i] = r[j];
				r[j] = m;
				min = x;
			}
		}
		re[i+1] = r[i];
	}
	return re;
}
static int ti = 0;
void search(int from, int to, city* cities,way* routes,int current)
{
	routes[ti].route[current] = from;
	routes[ti].length = current + 1;
	cities[from].used = 1;
	if (from == to)
	{
		cities[to].used = 0;
		ti++;
		for (int i = 0; i < routes[ti - 1].length; i++)
			routes[ti].route[i] = routes[ti - 1].route[i];
		routes[ti].length = current;
		return;
	}
	int* available = sort(cities[from], cities, to);
	for (int i = 1; i <= available[0]; i++)
		search(available[i], to, cities, routes, current + 1);
}
int main()
{
	cin >> totalnumb;
	city* cities = new city[totalnumb];
	for (int i = 0; i < totalnumb; i++)
	{
		cities[i].setnum(i);
		for (int j = 0; j < totalnumb; j++)
		{
			int a;
			cin >> a;
			if (i == j) continue;
			cities[i].connect(j, a);
		}
	}
	for (int i = 0; i < totalnumb; i++)
	{
		int a;
		cin >> a;
		cities[i].setcost(a);
	}
	int N;
	cin >> N;
	while (N-- > 0)
	{
		ti = 0;
		for (int i = 0; i < totalnumb; i++)
			cities[i].used = 0;
		int from, to;
		cin >> from >> to;
		way* routes;
		routes = new way[10000];
		search(from, to, cities, routes, 0);
		if (!ti) { cout << "No Path" << endl; continue; }
		cout << from;
		int leastcost = 999999, index = 0;
		for (int i = 0; i < ti && routes[i].route[routes[i].length-1]==to; i++)
		{
			int sum = 0;
			for (int j = 1; j< routes[i].length; j++)
				sum += cities[routes[i].route[j]].getcost() + cities[routes[i].route[j - 1]].con[routes[i].route[j]];
			sum -= cities[to].getcost();
			if (sum < leastcost)
			{
				leastcost = sum;
				index = i;
			}
		}
		for (int i = 1; i<routes[index].length; i++)
		{
			cout << "->" << routes[index].route[i];
		}
		cout << endl << leastcost << endl;
	}
	return 0;
}