#include<iostream>
using namespace std;
int N;
void shellsort(int a[],int j, int i) {
	int b[100], x, y = 0, z, t;
	for (x = j;;) {
		b[y] = a[x];
		if (x + i < N) { x += i; y++; }
		else break;
	}
	if (y == 0) return;
	if (y == 1) {
		if (a[j] > a[j + i]) { z = a[j + i]; a[j + i] = a[j]; a[j] = z; }
	}
	if (y > 1) {
		for (x = 0; x < y; ++x) {
			for (z = 1; z <= y; ++z) {
				if (b[x] > b[z]) { t = b[x]; b[x] = b[z]; b[z] = t; }
			}
		}
		for (x = 0; x <= y; ++x) {
			a[j + x * i] = b[x];
		}
	}
}
int main()
{
	int *a,i, j;
	cin >> N;
	a = new int[N];
	for (i = 0; i < N; i++) {
		cin >> a[i];
	}
	for (i = N / 2; i >= 1; i = i / 2)
		for (j = 0;;) 
		{
			shellsort(a,j, i);
			if (j + 1 + i < N) 
			{
				j++;
			}
			else 
			{ 
				for (int i = 0; i < N - 1; i++)
					cout << a[i] << ' ';
				cout << a[N - 1] << endl;
				break;
			}
		}
}