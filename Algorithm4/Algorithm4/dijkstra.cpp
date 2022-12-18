#include <iostream>
#define INF 9999
#define N 5
using namespace std;

typedef struct
{
	int weight, v1, v2;
}edge;

int index = 0;

void dijkstra(int n, int(*W)[N + 1], edge* F)
{
	int vnear;
	edge e;

	int touch[N + 1];
	int length[N + 1];

	for (int i = 2; i <= n; i++) {
		touch[i] = 1;
		length[i] = W[1][i];
	}

	while (1) {
		int min = INF;
		for (int i = 2; i <= n; i++) {
			if (0 <= length[i] && length[i] <= min)	{
				min = length[i];
				vnear = i;
			}
		}
		e.v1 = touch[vnear];
		e.v2 = vnear;
		F[++index] = e;
		for (int i = 2; i <= n; i++)
		{
			if (length[vnear] + W[vnear][i] < length[i])
			{
				length[i] = length[vnear] + W[vnear][i];
				touch[i] = vnear;
			}
		}
		length[vnear] = -1;

		if (index == n - 1)
			break;
	}
}

int main()
{
	int W[N + 1][N + 1] = { {0,0,0,0,0,0},
						{0,0,10,3,INF,20},
						{0,INF,0,INF,INF, INF},
						{0,INF,6,0,15,INF},
						{0,INF,25,INF,0,6},
						{0,INF,3,INF,INF,0}
	};

	edge F[N];

	dijkstra(N, W, F);
	for (int i = 1; i <= index; i++)
	{
		cout << F[i].v1 << " -> " << F[i].v2 << endl; 
	}
}


