#include <iostream>
using namespace std;

float minavg;
float sum_final = 0;
float Max = 999;

void optsearchtree(int n, float* p, float* minavg, int** R) {
	int i, j, k, diagonal, m;
	float** A = new float* [n + 2];
	for (int s = 0; s < n + 2; s++)
		A[s] = new float[n + 1];
	for (i = 0; i < n + 2; i++) {
		for (j = 0; j < n + 1; j++) {
			A[i][j] = Max;
		}
	}
	for (int i = 1; i <= n; i++) {
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i] = i;
		R[i][i - 1] = 0;
	}
	A[n + 1][n] = 0;
	R[n + 1][n] = 0;

	for (diagonal = 1; diagonal <= n - 1; diagonal++) {
		for (i = 1; i <= n - diagonal; i++) {
			j = i + diagonal;
				for (k = i; k <= j; k++) {
					if (A[i][k - 1] + A[k + 1][j] < A[i][j]) {
						A[i][j] = A[i][k - 1] + A[k + 1][j];
						R[i][j] = k;
					}
				}
				sum_final = 0;
				for (m = i; m <= j; m++) {
					sum_final = sum_final + p[m];
				}
				A[i][j] = A[i][j] + sum_final;
		}
		*minavg = A[1][n];
	}
	cout << endl;
	cout << "-----A[i][j]-----" << endl;
	for (int i = 1; i <= n+1; i++) {
		for (int j = 0; j <= n; j++) {
			if (j >= i)
				cout << A[i][j] << "\t";
			else
				cout << "0" << "\t";
		}
		cout << endl;
	}
	for (int s = 0; s < n + 2; s++)
		delete[]A[s];
}

int main() {
	int n;
	cout << "n: ";
	cin >> n;

	float* p = new float[n + 1];
	int** R = new int* [n + 2];
	for (int i = 1; i <= n; i++) {
		cout << "p[" << i << "] : ";
		cin >> p[i];
	}
	for (int i = 0; i < n + 2; i++)
		R[i] = new int[n + 1];
	optsearchtree(n, p, &minavg, R);
	cout << endl;
	cout << "-----R[i][j]-----" << endl;
	for (int i = 1; i <= n+1; i++) {
		for (int j = 0; j <= n; j++) {
			if (j >= i)
				cout << R[i][j] << "\t";
			else
				cout << "0" << "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "minavg : " << minavg << endl;
	for (int i = 0; i < n + 2; i++)
		delete[]R[i];
}