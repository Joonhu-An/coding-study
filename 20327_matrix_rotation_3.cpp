/*
https://www.acmicpc.net/problem/20327
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

int N, T, S;
int grid[128][128];
int tmp[128][128];

struct Playset{
    int stage, level;
};

vector<Playset> v;

void one(int l){
    int layer = 1<<l, half = layer/2;
    for(int i = 0; i < S; i++){
        for (int j = 0; j < S; j++){
            if(i % layer < half){
                tmp[i+half][j] = grid[i][j];
            }
            else {
                tmp[i-half][j] = grid[i][j];
            }
        }
    }
}

void two(int l){
    int layer = 1<<l, half = layer/2;

    for(int i = 0; i < S; i++){
        for (int j = 0; j < S; j++){
            if(j % layer < half){
                tmp[i][j+half] = grid[i][j];
            }
            else {
                tmp[i][j-half] = grid[i][j];
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N >> T;
    S = 1<<N;

    for(int i = 0; i < S; i++){
        for(int j = 0; j < S; j++){
            cin >> grid[i][j];
        }
    }

    for(int k = 0; k < T; k++){
        int a, b;
        cin >> a >> b;
        v.push_back({a,b});
    }

    for(auto &p : v){

        if(p.stage == 1){
            one(p.level);
        }
        else if (p.stage == 2){
            two(p.level);
        }
        /*
        else if (p.stage == 3){
            
        }
        else if (p.stage == 4){
            
        }
        else if (p.stage == 5){
            
        }
        else if (p.stage == 6){
            
        }
        else if (p.stage == 7){
            
        }
        else if (p.stage == 8){
            
        }
        */

        for(int i = 0; i < S; i++){
            for(int j= 0; j < S; j++){
                grid[i][j] = tmp[i][j];
            }
        }
    }

    for(int i = 0; i < S; i++){
        for(int j= 0; j < S; j++){
            cout << tmp[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}