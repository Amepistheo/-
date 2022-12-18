#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#define VertexN 5
#define EdgeN 8
using namespace std;
int index = -1;
int f_index = -1;

typedef struct {
	int weight;
	int v1;
	int v2;
}edge;

typedef struct {
	int parent;
	int depth;
}universe;

void input(int vertex1, int vertex2, int w);
void kruskal(int n, int m, edge* E, edge* F);
int find(universe* U, int i);
void merge(universe* U, int p, int q);
int equal(int p, int q);
edge set_of_edges[EdgeN];

int main() {
	edge result[EdgeN];

	input(1, 2, 3);
	input(1, 4, 5);
	input(1, 5, 7);
	input(2, 3, 1);
	input(2, 4, 4);
	input(3, 4, 8);
	input(3, 5, 4);
	input(4, 5, 3);

	kruskal(VertexN, EdgeN, set_of_edges, result);

	for (int i = 0; i <= f_index; i++)
		cout << "edge : (" << result[i].v1 << " - " << result[i].v2 << ")" << ", " << "weight : " << result[i].weight << endl;
}

void input(int vertex1, int vertex2, int w) {
	set_of_edges[++index].v1 = vertex1;
	set_of_edges[index].v2 = vertex2;
	set_of_edges[index].weight = w;
}

void kruskal(int n, int m, edge* E, edge* F) {
	universe U[VertexN + 1];
	int add[VertexN + 1] = { 0, };
	//edge 정렬
	for (int i = 0; i < m - 1; i++) {
		for (int j = i + 1; j < m; j++) {
			if (E[i].weight > E[j].weight) {
				edge temp = E[i];
				E[i] = E[j];
				E[j] = temp;
			}
		}
	}
	// U 배열 초기화
	for (int i = 1; i <= VertexN; i++) {
		U[i].parent = i;
		U[i].depth = 0;
	}
	//F 배열 초기화
	for (int i = 0; i < m; i++) {
		F[i].v1 = 0;
		F[i].v2 = 0;
		F[i].weight = 0;
	}

	int index = 0;
	while (1) {
		int i, j, p, q;
		edge e = E[index];

		i = E[index].v1;
		j = E[index].v2;

		p = find(U, i);
		q = find(U, j);

		if (!equal(p, q)) {
			merge(U, p, q);
			F[++f_index] = E[index];
		}
		index++;

		int cnt = 0;
		for (int i = 1; i <= EdgeN; i++) {
			if (U[i].parent == i)
				cnt++;
		}
		if (cnt == 1)
			break;
	}
}

int find(universe* U, int i) {
	int j;
	j = i;
	while (U[j].parent != j)
		j = U[j].parent;
	return j;
}

int equal(int p, int q) {
	int TRUE = 1;
	int FALSE = 0;
	if (p == q)
		return TRUE;
	else
		return FALSE;
}

void merge(universe* U, int p, int q) {
	if (U[p].depth == U[q].depth) {
		U[p].depth += 1;
		U[q].parent = p;
	}
	else if (U[p].depth < U[q].depth)
		U[p].parent = q;
	else
		U[q].parent = p;
}