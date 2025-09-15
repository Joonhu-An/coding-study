/*
https://www.acmicpc.net/problem/2206
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <limits.h>

using namespace std;

int N, M;
int grid[1000][1000];
int visited[1000][1000][2];

struct Two{
    int x, y, dist, broken;
};

queue<Two> q;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int move(){

    fill(&visited[0][0][0], &visited[0][0][0] + 1000*1000*2, -1);
    q.push({0, 0, 1, 0});
    
    while(!q.empty()){
        auto cur = q.front();
        int cx = cur.x, cy = cur.y, cd = cur.dist, cb = cur.broken;
        q.pop();

        for(int i = 0; i < 4; i++){
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            int nd = cur.dist + 1, nb = cb;

            if(N == 1 && M == 1){
                return 1;
            }
            else if (nx == N && N == 1 && ny == M-1){
                return nd;
            }
            else if (ny == M && M == 1 && nx == N-1){
                return nd;
            }

            if(nx < 0 || ny < 0 || nx >= N || ny >= M){continue;}

            if(nx == N-1 && ny == M-1){
                return nd;
            }

            if(nb == 0 && grid[nx][ny] == 1){
                nb = 1;
                q.push({nx, ny, nd, nb});
                visited[nx][ny][nb] = nd;
            }
            else if (grid[nx][ny] == 1){continue;}

            if(visited[nx][ny][nb] == -1){
                visited[nx][ny][nb] = nd;
                q.push({nx, ny, nd, nb});
            }

            if(visited[nx][ny][nb] > nd){
                visited[nx][ny][nb] = nd;
                q.push({nx, ny, nd, nb});               
            }
        }
    }

    return -1;
    
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
