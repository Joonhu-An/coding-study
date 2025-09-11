/* https://www.acmicpc.net/problem/22949
https://nahwasa.com/entry/%EC%9E%90%EB%B0%94-%EB%B0%B1%EC%A4%80-22949-%ED%9A%8C%EC%A0%84-%EB%AF%B8%EB%A1%9C-%ED%83%90%EC%83%89-java
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
bool visited[500][500][4][2];
struct Axis{ 
    int x, y, rot, dist; bool start; 
}; 

int dx[5] = {-1, 0, 1, 0, 0}; 
int dy[5] = {0, 1, 0, 1, 0}; 

queue<Axis> q; 

pair<int, int> rotate(int x, int y, int rot){ 
    int sx = x/4 * 4, sy = y/4 * 4; 
    int ox = x - sx, oy = y - sy; 
    int nx = ox, ny = oy; 
    
    if (rot == 1){ nx = oy; ny = 3 - ox; } 
    else if (rot == 2){ nx = 3 - ox; ny = 3 - oy; } 
    else if (rot == 3){ nx = 3 - oy; ny = ox; } 
    
    if (rot == 0){
        for(int i = 0; i < 4*K; i++){
            for (int j = 0; j < 4*K; j++){
                grid_rot[i][j] = grid[i][j];
            }
        }
    }
    else{
        for(int i = 0; i < 4; i++){ 
            for(int j = 0; j < 4; j++){ 
                int tx = sx + i; 
                int ty = sy + j; 
                int rx = i, ry = j; 
                
                if(rot == 1) { rx = j; ry = 3 - i; } 
                else if(rot == 2) { rx = 3 - i; ry = 3 - j; } 
                else if(rot == 3) { rx = 3 - j; ry = i; } 
                
                grid_rot[sx + rx][sy + ry] = grid[tx][ty]; 
            } 
        } 
    }
    
    return {sx + nx, sy + ny}; 
} 

pair<int, int> rotonly(int x, int y, int rot){
    int sx = x/4 * 4, sy = y/4 * 4; 
    int ox = x - sx, oy = y - sy; 
    int nx = ox, ny = oy; 
    
    if (rot == 1){ nx = oy; ny = 3 - ox; } 
    else if (rot == 2){ nx = 3 - ox; ny = 3 - oy; } 
    else if (rot == 3){ nx = 3 - oy; ny = ox; } 

    for(int i = 0; i < 4; i++){ 
        for(int j = 0; j < 4; j++){ 
            int tx = sx + i; 
            int ty = sy + j; 
            int rx = i, ry = j; 
            
            if(rot == 1) { rx = j; ry = 3 - i; } 
            else if(rot == 2) { rx = 3 - i; ry = 3 - j; } 
            else if(rot == 3) { rx = 3 - j; ry = i; } 
        } 
    } 

    return {sx + nx, sy + ny}; 
}

int move(int sx, int sy){ 
    bool first = false;
    q.push({sx, sy, 0, 0, false}); 
    visited[sx][sy][0][false] = true;
    
    while(!q.empty()){ 
        Axis cur = q.front(); 
        int cx = cur.x, cy = cur.y, cr = cur.rot, cd = cur.dist; 
        bool start_in = cur.start; 

        q.pop(); 

        int rx = sx, ry = sy; 

        if(first == false){}
        else{ tie(rx, ry) = rotate(cx, cy, cr);}

        // 문제가 돌리고 움직이면 0,0 기준 90도 시계 돌렸을때 0,3이 되고 오른쪽으로 가면 0,4 인데
        // 움직이고 돌리면 0,0에서 오른쪽 가면 0,1 이고 돌리면 1,3이 되어버림 결과가 전혀 달라진다
        // 근데 또 돌리고 움직이면 2번째 회전 부터 문제가 발생 nx, ny는 90도 시계 기준으로 셋 되었는데
        // 여기서 다시 180도를 돌려버리면 맵은 그대로 180도 회전이지만 객체는 270도 회전해버림.

        for(int i = 0; i < 5; i++){ 

            int nx = rx + dx[i]; 
            int ny = ry + dy[i]; 
            int nrot = cr;
            int start_idx;
            bool nstart = start_in; 

            if(nx < 0 || ny < 0 || nx >= 4*K || ny >= 4*K){ continue; } 

            if(grid_rot[nx][ny] == '#'){ continue; } 
            if(grid_rot[nx][ny] == 'E'){ return cd + 1; }

            if(cx/4 != nx/4 || cy/4 != ny/4){ nrot = 0; nstart = false;}
            else{ nrot = (nrot+1)%4; nstart = true;}

            start_idx = nstart ? 1:0;

            for(int j = 0; j < 4*K; j++){
                    for(int k = 0; k < 4*K; k++){
                        if(nx == j && ny == k){
                            cout << 'H';
                        }
                        else{
                            cout << grid_rot[j][k];
                        }
                    } cout << endl;
                } cout << endl;

            if(!visited[nx][ny][nrot][start_idx]){ 
                visited[nx][ny][nrot][start_idx] = true;
                
                if(first == false){first = true;}
                else{tie(rx, ry) = rotonly(nx, ny, (4-cr)%4);};
                cout << nx << "/" << ny << "??" << rx << "/" << ry << endl;
                q.push({rx, ry, nrot, cd+1, nstart});

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
    
    cin >> K; 
    
    string line; 
    int startx, starty; 
    
    for(int i = 0; i < 4*K; i++){ 
        cin >> line; 
        
        for(int j = 0; j < 4*K; j++){ 
            char c; c = line[j]; 
            
            grid[i][j] = c; 
            grid_rot[i][j] = c; 
            
            if(grid[i][j] == 'S'){ startx = i; starty = j; } 
        } 
    } 
    
    int answer = move(startx, starty); 
    
    cout << answer << "\n"; 
    return 0; 
}