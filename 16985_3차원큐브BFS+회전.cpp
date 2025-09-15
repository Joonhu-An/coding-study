/*
https://www.acmicpc.net/problem/16985
*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int grid[5][5][5][4];
int visited[5][5][5];
int cube[5][5][5];

int min_dist = INT_MAX;

struct Axis{
    int x, y, z, dist;
};

vector<int> location = {0, 1, 2, 3, 4};
vector<int> mix_loca;
vector<int> spin_mix = {0, 1, 2, 3};

queue<Axis> q;

int dx[6] = {-1, 1, 0, 0, 0, 0};
int dy[6] = {0, 0, -1, 1, 0, 0,};
int dz[6] = {0, 0, 0, 0, -1, 1};

int bfs(int best){
    if(cube[0][0][0] == 0 || cube[4][4][4] == 0) {return INT_MAX;}

    fill(&visited[0][0][0], &visited[0][0][0] + 5*5*5, -1);
    while(!q.empty()){
        q.pop();
    }

    q.push({0,0,0,0});
    visited[0][0][0] = 0;

    while(!q.empty()){
        auto cur = q.front();
        q.pop();
        int cx = cur.x, cy = cur.y, cz = cur.z, cd = cur.dist;

        if(cd > best){continue;}

        for(int i = 0; i < 6; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            int nz = cz + dz[i];
            int nd = cd;

            if(nx < 0 || ny < 0 || nz < 0 || nx >= 5 || ny >= 5 || nz >= 5){continue;}
            if(nx == 4 && ny == 4 && nz == 4){
                return nd+1;
            }

            if(cube[nx][ny][nz] == 0){continue;}


            if(visited[nx][ny][nz] == -1){
                q.push({nx, ny, nz, nd+1});
                visited[nx][ny][nz] = nd+1;
            }

            if(visited[nx][ny][nz] > nd+1){
                q.push({nx, ny, nz, nd+1});
                visited[nx][ny][nz] = nd+1;
            }
        }
    }
    return INT_MAX;
}

void mixed(){

    for (int mask = 0; mask < 4*4*4*4*4; mask++){
        int tmp = mask;
        int rot[5];
        
        for(int i = 0; i < 5; i++){
            rot[i] = tmp % 4;
            tmp /= 4;
        }

        for(int k = 0; k < 5; k++){
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    cube[i][j][k] = grid[i][j][location[k]][rot[k]];
                }
            }
        }
        
        if(min_dist == 12){
            break;
        }
        min_dist = min(min_dist, bfs(min_dist));
    }
}

int permut(){
    do{
        mixed();
        if(min_dist == 12){
                return min_dist;
        }
        
    }while(next_permutation(location.begin(), location.end()));

    return min_dist;
}

void rotation(){
    for(int r = 1; r < 4; r++){
        for(int k = 0; k < 5; k++){
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    grid[j][5-1-i][k][r] = grid[i][j][k][r-1];
                }
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

    for(int k = 0; k < 5; k++){
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                cin >> grid[i][j][k][0];
            }
        }
    }

    rotation();
    int answer = permut();

    if (answer == INT_MAX){
        answer = -1;
    }

    cout << answer << "\n";
    
    return 0;
}