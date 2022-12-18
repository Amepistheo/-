#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int n = 4;
const int W = 8;
int w[n + 1] = { 0, 4, 2, 3, 5 }; 
int p[n + 1] = { 0, 7, 5, 6, 9 }; 
string* include = new string[n + 1];
string* bestset = new string[n + 1];
int prm_node_cnt = 0;
int nprm_node_cnt = 0;
int numbest = 0;
int maxprofit = 0;

void knapsack(int i, int profit, int weight);
bool promising(int i, int profit, int weight);

int main() {
    knapsack(0, 0, 0);
    
    for (int j = 1; j <= numbest; ++j)
        cout << "w" << j << ": " << bestset[j] << endl;

    cout << endl << "Maxprofit : $" << maxprofit << endl;
    cout << "promising node : " << prm_node_cnt << endl;
    cout << "nonpromising node : " << nprm_node_cnt << endl;
    

    delete[] include;
    delete[] bestset;
    return 0;
}

void knapsack(int i, int profit, int weight){
    if (weight <= W && profit > maxprofit){
        maxprofit = profit;
        numbest = i;
        copy(include, include + n + 1, bestset);
    }

    if (promising(i, profit, weight)){
        ++prm_node_cnt; 
        include[i + 1] = "YES"; 
        knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
        include[i + 1] = "NO";  
        knapsack(i + 1, profit, weight);
    }
     else
        ++nprm_node_cnt; 
}

bool promising(int i, int profit, int weight) {
    int j, k;
    int totweight;
    float bound;

    if (weight >= W)
            return false;
     else {
        j = i + 1;
        bound = (float)profit;
        totweight = weight;
           
        while (j <= n && totweight + w[j] <= W) {
             totweight = totweight + w[j];
             bound = bound + p[j];
             ++j;
         }
         k = j;
         if (k <= n) 
            bound = bound + (W - totweight) * (p[k] / w[k]);

         return (bound > maxprofit);
     }
}