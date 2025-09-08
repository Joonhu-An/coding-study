/*
https://www.acmicpc.net/problem/15812

모든 조합을 다 찾는 방식으로 진행했다. BFS를 이중으로 돌려서 모든 가스를 진행. 앞선 코드는 prev_permutation을 이용한 순열로 경우의수를 찾아서 진행했다.
그랬더니 계산시간이 엄청나게 오래 걸리긴함
하지만 여기서는 맨해튼 거리를 통해 거리를 구하면 어차피 시간마다 이동 가능한 거리가 같기때문에 역으로 시간을 유추할 수 있다.

예를 들어 후보지 2곳과 마을 5곳이 있다고 하면 각각 후보지에서 마을까지 맨해튼 거리를 계산한다 (총 10개의 맨해튼 거리) 그리고 맨해튼 거리 중 가장 높은 거리가
모든 마을을 감염시키는데 걸리는 시간이 된다. 가장 먼 거리를 제외한 나머지 마을은 어차피 도달했기 때문에 고려 안해도 된다. 이 중에서도 가장 최적의 후보지를 찾는
거기 때문에 후보지마다 맨해튼 거리 중 가장 먼 거리 찾고 이 중에서 가장 짧은 거기를 찾으면 그게 가장 최적화된 시간과 위치가 된다. 

마을	후보지A 거리	후보지B 거리	최소 거리
M1	        3	            5	        3
M2	        2	            4	        2
M3	        7	            1	        1
M4	        5	            2	        2
M5	        6	            6	        6

이러면 후보지와 마을 거리가 가장 차이나는 곳 A-M5, B-M5 여기에 해당하는 맨해튼의 값이 6이라면 모든 마을 감염하는데 6초가 걸린다는 소리.
다른 후보지에서 이 최소 거리의 최대 시간이 줄면 거기가 더 최적화된 곳이다.
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <string>
#include <limits.h>

using namespace std;

int N, M, minTime = INT_MAX;
int grid[20][20];

struct Place{
    int x, y;
};

struct Timeplace{
    int x, y, time;
};

vector<Place> candidate;
vector<Place> town;
queue<Timeplace> q;
bool visited[20][20];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void bfs(Place can1, Place can2){
    int time = 0, vill = 0;
    fill(&visited[0][0], &visited[0][0]+20*20, false);
    q.push({can1.x, can1.y, time});
    q.push({can2.x, can2.y, time});

    while(!q.empty()){
        int cx = q.front().x;
        int cy = q.front().y;
        int ctime = q.front().time;
        visited[cx][cy] = true;

        if(grid[cx][cy] == 1){
                vill++;
            }
        q.pop();

        for(int i = 0; i < 4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if(nx < 0 || ny < 0 || nx >= N || ny >= M || visited[nx][ny]){
                continue;
            }
            else{
                visited[nx][ny] = true;
                q.push({nx, ny, ctime+1});
            }

            if(vill == town.size()){
                minTime = min(minTime, ctime);
                break;
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

    cin >> N >> M;
    string line;
    
    for(int i = 0; i < N; i++){
        cin >> line;

        for(int j = 0; j < M; j++){
            char c = line[j] - '0';
            grid[i][j] = c;

            if(grid[i][j] == 0){
                candidate.push_back({i, j});
            }
            else if (grid[i][j] == 1){
                town.push_back({i,j});
            }
        }
    }

    for(int i = 0; i < candidate.size(); i++){
        for(int j = 0; j < candidate.size(); j++){
            bfs(candidate[i], candidate[j]);
        }
    }
    cout << minTime << "\n";
    return 0;
    
}