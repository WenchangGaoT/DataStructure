#include<iostream>
using namespace std;
void swap(int& a1, int& a2)
{
	int a = a1;
	a1 = a2;
	a2 = a;
}
int main()
{
	int N, M;
	cin >> N >> M;
	int* H = new int[N + 1];
	H[0] = 1;
	while (N-- > 0)
	{
		int xi;
		cin >> xi;
		int size = H[0];
		H[size] = xi;
		if (H[size] <= H[size / 2]);
		else
		{
			for (int i = size / 2; i > 0; i--)
			{
				if (i > size)
				{
					i /= 2;
					i++;
					continue;
				}
				if (i > size / 2) continue;
				int changed = 0;
				if (H[2 * i] > H[i]) { swap(H[2 * i], H[i]); changed = 1; }
				if (2 * i + 1 <= size && H[2 * i + 1] > H[i]) { swap(H[2 * i + 1], H[i]); changed = 1; }
				if (changed)
				{
					i *= 2;
					i += 2;
				}
			}
		}
		H[0]++;
	}
	while (M-- > 0)
	{
		int in;
		cin >> in;
		int n = in;
		while (n != 0)
		{
			cout << H[n] << ' ';
			n /= 2;
		}
		cout << endl;
	}
}