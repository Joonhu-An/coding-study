/*
https://www.acmicpc.net/problem/2206
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <limits.h>

using namespace std;

int N, M, minDist = INT_MAX;
int grid[1000][1000];
int visited[1000][1000][2];

struct Two{
    int x, y, dist, broken;
};

queue<Two> q;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int move(){

    fill(&visited[0][0][0], &visited[0][0][0] + 1000*1000*2, 0);

    q.push({0,0,0,0});
    int a = 0;

    while(!q.empty()){
        auto cur = q.front();
        int cx = cur.x, cy = cur.y, cd = cur.dist, cb = cur.broken;
        q.pop();

        for(int i = 0; i < 4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            int nd = cd;
            int nb = cb;

            if(nx < 0 || ny < 0 || nx >= N || ny >= M){continue;}
            
            if(nx == N-1 && ny == M-1){
                minDist = min(minDist, nd+1);
                return minDist;
            }

            if(nb == 0 && grid[nx][ny] == 1){
                nb = 1;
                visited[nx][ny] = nd+1;
                q.push({nx, ny, nd+1, nb});
                continue;
            }
            else if (nb == 1 && grid[nx][ny] == 1){continue;}

            if(visited[nx][ny] == 0){
                visited[nx][ny][nb] = nd+1;
                q.push({nx, ny, nd+1, nb});
            }
            else if(visited[nx][ny][nb] > nd + 1){
                visited[nx][ny][nb] = nd+1;
                q.push({nx, ny, nd+1, nb});
            }  
            else if(nb == 0){
                q.push({nx, ny, nd+1, nb});
            }
            //cout << nx << "/" << ny << "/" << nb << "\n";
        }
        
        a++;
        if(a == 999){
            break;
        }
    }

    if(minDist == INT_MAX){
        return -1;
    }

    return 0;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N >> M;
    string line;

    for(int i = 0; i < N; i++){
        cin >> line;
        for(int j = 0; j < M; j++){
            grid[i][j] = line[j] - '0';
        }
    }

    int answer = move();
    cout << answer << "\n";

    return 0;
}
