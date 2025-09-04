/*
https://www.acmicpc.net/problem/17406

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int N, M, K;
int grid[50][50];
int tmp[50][50];

struct Rotation{
    int r, c, s;
};

vector<Rotation> v;

void Rot(int r, int c, int s){

    for(int l = 0; l < s; l++){
        int x1 = r-s-1+l, y1 = c-s-1+l;
        int x2 = r+s-1-l, y2 = c+s-1-l;

        vector<int> rv;

        for(int i = x1; i < x2; i++){
            rv.push_back(tmp[i][y1]);
        }
        for(int j = y1; j < y2; j++){
            rv.push_back(tmp[x2][j]);
        }
        for(int i = x2; i > x1; i--){
            rv.push_back(tmp[i][y2]);
        }
        for(int j = y2; j > y1; j--){
            rv.push_back(tmp[x1][j]);
        }
        
        int len = rv.size();
        int idx = 1;

        for(int i = x1; i < x2; i++){
            tmp[i][y1] = rv[idx++ % len];
        }
        for(int j = y1; j < y2; j++){
            tmp[x2][j] = rv[idx++ % len];
        }
        for(int i = x2; i > x1; i--){
            tmp[i][y2] = rv[idx++ % len];
        }
        for(int j = y2; j > y1; j--){
            tmp[x1][j] = rv[idx++ % len];
        }    
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int r,c,s, answer = 999;

    cin >> N >> M >> K;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> grid[i][j];
        }
    }

    vector<int> order(K);
    iota(order.begin(), order.end(), 0);

    for(int i = 0; i < K; i++){
        
        cin >> r >> c >> s;
        v.push_back({r,c,s});
    }

    do{

        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                tmp[i][j] = grid[i][j];
            }
        }

        for(auto &f : v){

            Rot(f.r, f.c, f.s);

            for(int i = 0; i < N; i++){
                for(int j = 0; j < M; j++){
                    cout << tmp[i][j] << " ";
                }
                cout << "\n";
            }
        }
        
        for(int i = 0; i < N; i++){
                int sum = accumulate(tmp[i], tmp[i]+M,0);
                answer = min(answer, sum);
            }
    }while(next_permutation(order.begin(), order.end()));

    cout << answer << endl;

    return 0;
}