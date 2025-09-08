#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <string>
#include <limits.h>

using namespace std;

int N, M, T, minTime = INT_MAX;
int grid[20][20];
bool visited[20][20];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

struct Oneplace{
    int x, y;
};

vector<Oneplace> drop;
queue<Oneplace> q;
queue<Oneplace> timeQ;

void spread(){
    fill(&visited[0][0], &visited[0][0] + 20 * 20, false);
    int town = 0;
    int time = 0;  
    int out = 0;

    while(!q.empty()){
        while(!q.empty()){

            int cx = q.front().x;
            int cy = q.front().y;
            
            visited[cx][cy] = true;
            q.pop();

            for(int i = 0; i < 4; i++){
                int nx = cx + dx[i];
                int ny = cy + dy[i];

                if(nx < 0 || ny < 0 || nx >= N || ny >= M || visited[nx][ny]){
                    continue;
                }
                else{
                    if(!visited[nx][ny] && grid[nx][ny] == 1){
                        town++;
                    }
                    timeQ.push({nx, ny});
                    visited[nx][ny] = true;
                }
            }
        }
        time++;
        if (town == T){
            minTime = min(minTime,time);
        }

        int check = timeQ.size();
        for(int i = 0; i < check; i++){
            q.push({timeQ.front().x, timeQ.front().y});
            timeQ.pop();
        }

    }

}

void poi(){

    vector<bool> select(drop.size());
    fill(select.begin(), select.begin()+2, true);

    do{
        for(int i = 0; i < drop.size(); i++){
            if (select[i]) {
                q.push({drop[i]});
            }
        }

        spread();

    }while(prev_permutation(select.begin(), select.end()));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    T = 0;
    string line;
    char c;

    cin >> N >> M;

    for(int i = 0; i < N; i++){
        cin >> line;

        for(int j = 0; j < M; j++){
            c = line[j];
            grid[i][j] = c - '0';

            if(grid[i][j] == 0){
                drop.push_back({i, j});
            }
            else if (grid[i][j] == 1){
                T++;
            }
        }
    }

    poi();

    cout << minTime << '\n';

    return 0;
    
}