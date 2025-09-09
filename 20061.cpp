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
char tmp[500][500];
bool start = false;

struct Axis{
    int x, y, t, rot;
    pair<int, int> plate;
};

int dx[5] = {-1, 1, 0, 0, 0};
int dy[5] = {0, 0, -1, 1, 0};

queue<Axis> q;

pair<int, int> rotation90(int x, int y){
    int pl_x, pl_y, keep;
    pl_x = x/4;
    pl_y = y/4;

    int sx = pl_x * 4;
    int sy = pl_y * 4;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int nx = j;
            int ny = 4 - 1- i;

            tmp[sx + nx][sy + ny] = grid[sx + i][sy+j];
        }
    }
    
    keep = x;
    x = y;
    y = sx + 4 - 1 - keep;

    return {x, y};
}

pair<int, int> rotation180(int x, int y){
    int pl_x, pl_y, keep;
    pl_x = x/4;
    pl_y = y/4;

    int sx = pl_x * 4;
    int sy = pl_y * 4;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int nx = 4 - 1 - i;
            int ny = 4 - 1 - j;

            tmp[sx + nx][sy + ny] = grid[sx + i][sy+j];
        }
    }

    keep = x;
    x = sx + 4 - 1 - x;
    y = sy + 4 - 1 - keep;

    return {x, y};
}

pair<int, int> rotation270(int x, int y){
    int pl_x, pl_y, keep;
    pl_x = x/4;
    pl_y = y/4;

    int sx = pl_x * 4;
    int sy = pl_y * 4;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int nx = 4 - 1- j;
            int ny = i;

            tmp[sx + nx][sy + ny] = grid[sx + i][sy+j];
        }
    }

    keep = x;
    x = sy + 4 - 1 - y;
    y = keep;

    return {x, y};
}

int move(){

    while(!q.empty()){
        int cx = q.front().x;
        int cy = q.front().y;
        int ct = q.front().t;
        int cr = q.front().rot;
        int cpla_x, cpla_y;
        cpla_x = q.front().plate.first;
        cpla_y = q.front().plate.second;

        ct++;

        q.pop();

        //cout << "X&Y = " << cx << "/" << cy << "/" << cr << "\n";

        for(int i = 0; i < 4*K; i++){
                for(int j = 0; j < 4*K; j++){
                    tmp[i][j] = grid[i][j]; 
                }
            }

        if (cr == 0 && start == true){
            int keep = cx;
            cx = cy;
            cy = cx/4*4 + 4 - 1 - keep;
        }
        else if(cr == 1){
            pair<int,int> cur = rotation90(cx, cy);
            cx = cur.first;
            cy = cur.second;
        }
        else if(cr == 2){
            pair<int,int> cur = rotation180(cx, cy);
            cx = cur.first;
            cy = cur.second;
        }
        else if(cr == 3){
            pair<int,int> cur = rotation270(cx, cy);
            cx = cur.first;
            cy = cur.second;
        }

        //cout << "X&Y = " << cx << "/" << cy << "/" << cr << "\n";
        
        cr = (cr + 1)%4;

        for(int i = 0; i < 5; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if(nx < 0 || ny < 0 || nx >= 4*K || ny >= 4*K){
                continue;
            }
            else if(tmp[nx][ny] == '#'){
                continue;
            }
            else if(tmp[nx][ny] == 'E'){
                cout << ct << "\n";
                return 0;
            }
            else{
                if (cx/4 != nx/4 || cy/4 != ny/4){
                    cr = 0;
                }
                q.push({nx, ny, ct, cr});
                cout << "X&Y = " << nx << "/" << ny << "/" << ct << "/" << cr << "\n";
            }
        }

        start = true;
    }

    cout << "-1" << "\n";
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

    for(int i = 0; i < 4*K; i++){
        cin >> line;

        for(int j = 0; j < 4*K; j++){
            char c;
            c = line[j];

            grid[i][j] = c;
            tmp[i][j] = c;

            if(c == 'S'){
                q.push({i,j,0,0});
            }
        }
    }

    int ans = move();

    /*
    //rotation180(5,6);

    for(int i = 0; i < 4*K; i++){
        for(int j = 0; j < 4*K; j++){
            cout << tmp[i][j] << " ";   
        }

        cout << "\n";
    }*/


    return 0;    
}