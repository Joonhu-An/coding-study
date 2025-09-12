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
int visited[1000][1000];
bool falseVisited[1000][1000];

struct Two{
    int x, y, dist;
    bool already;
};

queue<Two> q;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int move(){

    fill(&visited[0][0], &visited[0][0] + 1000*1000, -1);
    fill(&falseVisited[0][0], &falseVisited[0][0] + 1000*1000, false);

    q.push({0,0,1, false});
    int a = 0;

    while(!q.empty()){
        auto cur = q.front();
        int cx = cur.x, cy = cur.y, cd = cur.dist, cb = cur.already;
        q.pop();

        for(int i = 0; i < 4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            int nd = cd;
            bool nb = cb;

            if(nx < 0 || ny < 0 || nx >= N || ny >= M){continue;}
            
            if(nx == N-1 && ny == M-1){
                minDist = min(minDist, nd+1);
                return minDist;
            }

            if(nb == false && grid[nx][ny] == 1){
                nb = true;
                visited[nx][ny] = nd+1;
                q.push({nx, ny, nd+1, nb});
                continue;
            }
            else if (nb == true && grid[nx][ny] == 1){continue;}

            if(visited[nx][ny] == -1){
                visited[nx][ny] = nd+1;
                q.push({nx, ny, nd+1, nb});
            }
            else if(visited[nx][ny] > nd + 1){
                visited[nx][ny] = nd+1;
                q.push({nx, ny, nd+1, nb});
            }  
            else if(!falseVisited[nx][ny] && nb == false){
                falseVisited[nx][ny] == true;
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