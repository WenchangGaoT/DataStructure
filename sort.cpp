#define LOCA
#include<iostream>
using namespace std;
int N;
void Insertion(int* elem,int n)
{
	if (n == 0 ||elem[n]>=elem[n-1]) return;
	for (int i = 0; i <= n-1 ; i++)
	{
		if (elem[i] > elem[n])
		{
			int* x = new int[n - i];
			for (int j = 0; j < n - i; j++)
				x[j] = elem[i + j];
			elem[i] = elem[n];
			for (int j = 0; j < n - i; j++)
				elem[i + j + 1] = x[j];
			break;
		}
	}
}
void Merge(int* merge, int left, int right)
{
	for (int i = left; i <= right; i++)
	{
		for (int j = i; j <= right; j++)
		{
			if (merge[j] < merge[i])
			{
				int x = merge[j];
				merge[j] = merge[i];
				merge[i] = x;
			}
		}
	}
}
void mergesort(int* merge, int* ans)
{
	int length = 1;
	bool t = 0;
	while (1)
	{
		length *= 2;
		for (int i = 0;i*length<N; i++)
		{
			int right = (i * length + length) < (N) ? (i * length + length) : (N);
			Merge(merge, i * length, right-1);
		}
		if (t) break;
		int ok = 1;
		for(int i=0;i<N;i++)
			if (merge[i] != ans[i]) { ok = 0; break; }
		if (ok)t = 1;
	}
}
int main()
{
	cin >> N;
	int* insert = new int[N], * merge = new int[N];
	for (int i = 0; i < N; i++)
	{
		cin >> insert[i];
		merge[i] = insert[i];
	}
	int* tem = new int[N];
	for (int i = 0; i < N; i++)
		cin >> tem[i];
	for (int i = 0; i < N; i++)
	{
		int ok = 1;
		for (int j = 0; j < N; j++)
			if (insert[j] != tem[j]) { ok = 0; break; }
		Insertion(insert, i);
		if (ok)
		{
			cout << "Insertion Sort" << endl;
			for (int j = 0; j < N; j++)
			{
				if (j != 0) cout << ' ';
				cout << insert[j];
			}
			system("pause");
			return 0;
		}
	}
	cout << "Merge Sort" << endl;
	mergesort(merge,tem);
	for (int i = 0; i < N; i++)
	{
		if (i != 0)cout << ' ';
		cout << merge[i];
	}
	system("pause");
}