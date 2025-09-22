/*
https://www.acmicpc.net/problem/21609
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <numeric>
#include <math.h>
#include <limits.h>

using namespace std;

struct Axis{
    int x,y, color;
};

struct Stand{
    int maxi, rainb, stan_c, stan_r;
};

int N, M;
int grid[20][20];
bool visit[20][20];
bool boom[20][20];
bool acc_visit[20][20];

queue<Axis> q;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

// gravity, rotation
Stand count(){
    int maxi = 1, rainbow = 0, stand_c = 0, stand_r = 0;
    bool first_one = false;

    while(!q.empty()){
        auto cur = q.front();
        q.pop();

        int cx = cur.x, cy = cur.y, cc = cur.color;

        if(first_one == false){
            stand_c = cx;
            stand_r = cy;
            first_one = true;
        }
        
        for(int i = 0; i < 4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            
            if(nx < 0 || ny < 0 || nx >= N || ny >= N){continue;}
            else if (grid[nx][ny] == -1 || grid[nx][ny] == -2){continue;}

            if(!visit[nx][ny] && (grid[nx][ny] == cc || grid[nx][ny] == 0)){
                if(grid[nx][ny] == 0){
                    rainbow++;
                }
                else{
                    if(nx < stand_c && ny < stand_r){
                        stand_c = nx;
                        stand_r = ny;
                    }
                    else if(nx == stand_c && ny < stand_r){
                        stand_r = ny;
                    }
                }

                q.push({nx, ny, cc});
                maxi++;
                visit[nx][ny] = true;
            }
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(acc_visit[i][j] == 0){
                acc_visit[i][j] = visit[i][j];
            }
        }
    }

    return {maxi, rainbow, stand_c, stand_r};
}

void gravity(){
    vector<int> v;

    for(int j = 0; j < N; j++){
        int twotwo = 0;
        for(int i = N-1; i > -1; i--){
            if(grid[i][j] == -2){
                twotwo++;
            }
            else{
                v.push_back(i);
            }
        }

        for(int k = 0; k < v.size(); k++){
            if(v[k] == N-1){
                continue;
            }
            else{
                grid[v[k]][j] = grid[v[k]+twotwo][j]; 
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

    int block = 0, s_rain = INT_MAX, s_c = INT_MAX, s_r = INT_MAX, point = 0;

    cin >> N >> M;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> grid[i][j];
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(acc_visit[i][j] == 0 && grid[i][j] > 0) {
                fill(&visit[0][0], &visit[0][0] + 20*20, false);
                q.push({i, j, grid[i][j]});
                visit[i][j] = true;
                
                Stand best = count();
                if(block < best.maxi){
                    block = best.maxi;
                    s_rain = best.rainb;
                    s_c = best.stan_c;
                    s_r = best.stan_r;

                    for(int a = 0; a < N; a++){
                        for(int b = 0; b < N; b++){
                            boom[a][b] = visit[a][b];
                        }
                    }
                    
                }
                else if (block == best.maxi){
                    if(s_rain < best.rainb){
                        s_rain = best.rainb;
                        s_c = best.stan_c;
                        s_r = best.stan_r;

                        for(int a = 0; a < N; a++){
                            for(int b = 0; b < N; b++){
                                boom[a][b] = visit[a][b];
                            }
                        }
                    }
                    else if (s_c < best.stan_c){
                        s_rain = best.rainb;
                        s_c = best.stan_c;
                        s_r = best.stan_r;

                        for(int a = 0; a < N; a++){
                            for(int b = 0; b < N; b++){
                                boom[a][b] = visit[a][b];
                            }
                        }
                    }
                    else if (s_r < best.stan_r){
                        s_rain = best.rainb;
                        s_c = best.stan_c;
                        s_r = best.stan_r;

                        for(int a = 0; a < N; a++){
                            for(int b = 0; b < N; b++){
                                boom[a][b] = visit[a][b];
                            }
                        }
                    }
                }
            }
        }
    }

    for(int a = 0; a < N; a++){
        for(int b = 0; b < N; b++){
            if(boom[a][b] == 1){
                grid[a][b] = -2;
            }
        }
    }

    point += pow(block, 2);
    gravity();

    for(int a = 0; a < N; a++){
        for(int b = 0; b < N; b++){
            cout << grid[a][b];
        } cout << endl;
    }

    return 0;
}