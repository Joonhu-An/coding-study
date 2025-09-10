/*
https://www.acmicpc.net/problem/22949
시작 지점이 (0,0) 아니고 (1,1) 그리고 좌표가 (x,y)가 아니라 (y,x)
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int K;
char grid[500][500];
char grid_rot[500][500];
bool visited[500][500][4];

struct Axis{
    int x, y, rot, dist;
    bool reset;
};

int dx[5] = {-1, 1, 0, 0, 0};
int dy[5] = {0, 0, -1, 1, 0};

queue<Axis> q;

pair<int, int> rotate(int x, int y, int rot, bool reset){
    int sx = x/4 * 4, sy = y/4 * 4;
    
    int nx = x, ny = y;
    int lx, ly;

    if(rot == 0){
        for(int i = sx; i < sx+4; i++){
            for(int j = sy; j < sy+4; j++){
                grid_rot[i][j] = grid[i][j];
            }
        }

        if(reset == true){
            nx = y;
            ny = sx + 4 - 1 - x%4;
        }
    }
    else if (rot == 1){
        for(int i = sx; i < sx+4; i++){
            for(int j = sy; j < sy+4; j++){
                lx = i - sx;
                ly = j - sy;

                nx = ly;
                ny = 3 - lx;
                grid_rot[sx + nx][sy+ ny] = grid[i][j];
            }
        }
    }
    else if (rot == 2){
        for(int i = sx; i < sx+4; i++){
            for(int j = sy; j < sy+4; j++){
                lx = i - sx;
                ly = j - sy;

                nx = 3 - lx;
                ny = 3 - ly;

                grid_rot[sx+ nx][sy+ ny] = grid[i][j];
            }
        }
    }
    else if (rot == 3){
        for(int i = sx; i < sx+4; i++){
            for(int j = sy; j < sy+4; j++){

                lx = i - sx;
                ly = j - sy;

                nx = 3 - ly;
                ny = lx;

                grid_rot[sx+ nx][sy + ny] = grid[i][j];
            }
        }
    }

    cout << "여기보세요" << rot;

    for(int i = 0; i<4*K;i++){
        for(int j = 0; j <4*K;j++){
            cout << grid_rot[i][j];
        } cout << "\n";
    } cout << "\n";
    
    return {sx + nx, sy + ny};
}

int move(int sx, int sy){

    q.push({sx, sy, 0, 1, false});
    visited[sx][sy][0] = true;

    while(!q.empty()){
        int cx = q.front().x;
        int cy = q.front().y;
        int cr = q.front().rot;
        int ct = q.front().dist;
        bool start = q.front().reset;
        q.pop();
 
        auto[rx, ry] = rotate(cx, cy, cr, start);
        cout << "HERE : " << cx << "/" << cy << "/" << cr << "/" << start << "\n";
        
        if(grid_rot[rx][ry] == 'E'){
            cout << ct << "\n";
            return 0;
        }
    
        int nrot = (cr+1)%4;
        if(cx/4 != rx/4 || cy/4 != ry/4){
            nrot = 0;
            start = false;
        }
        else if(cr%4 == 0 && start == false) {
            start = true;
        }

        for(int i = 0; i < 5; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if(nx < 0 || ny < 0 || nx >= 4*K || ny >= 4*K){
                continue;
            }

            auto[rx2, ry2] = rotate(nx, ny, nrot, start);
            cout << "HERE : " << cx << "/" << cy << "/" << cr << "/" << start << "\n" << "\n";
            if(grid_rot[rx2][ry2] == '#'){
                continue;
            }

            if(!visited[nx][ny][nrot]){
                visited[nx][ny][nrot] = true;
                q.push({nx, ny, nrot, ct+1, start});
            }
        }
    }
    return 0;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> K;

    string line;
    int startx, starty;

    for(int i = 0; i < 4*K; i++){
        cin >> line;

        for(int j = 0; j < 4*K; j++){
            char c;
            c = line[j];

            grid[i][j] = c;

            if(grid[i][j] == 'S'){
                startx = i;
                starty = j;
            }
        }
    }

    move(startx, starty);

    return 0;    
}