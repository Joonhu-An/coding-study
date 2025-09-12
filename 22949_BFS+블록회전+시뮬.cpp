/* https://www.acmicpc.net/problem/22949
https://ssu-gongdoli.tistory.com/128
출제자 설명이 있었습니다.

3일 쏟아부은 문제. 원래 계획은 따로 grid를 방향별로 맵을 저장하는게 아니라 실제 맵 1개와 임시 맵 1개를 활용해
움직이기 직전에 rot 기준으로 돌아간 값을 먼저 계산을 해서 현재 위치 -> 이동 -> 좌표 저장 + rot 값
이런식으로 했으나 메모리 절약은 되지만 논리적으로 너무 복잡해짐. 가능은 할거 같은데 넘 어려웡.

그래서 그냥 0, 90, 180, 270 총 4개 맵을 따로 저장해놓고 좌표 움직임 -> rot 기준으로 해당하는 맵에서
직전 좌표를 기준으로 상하좌우, 제자리를 갈 수 있는지 #, E 확인 -> 가능한 것 중에 블록 안 넘겼으면 nx, ny 값을
시계 90도로 돌려서 rx, ry를 저장하고 rot + 1 해줌. OR 블록 넘어갔으면 rot = 0 으로 변경해서 nx, ny가
해당 블록에서 #,E 따로 확인 -> 가능하면 nx, ny를 rx, ry로 시계 90도 돌리고 rot + 1.

큐에 저장되는 rot 자체가 현재 돌아간 큐
그러니까 nx, ny로 돌아간 맵에서 움직이고

블록 안 넘으면 저장된 rot와 같아서 그냥 바로 nxny 좌표상 확인 ->
 시계 90도 돌려줌 + (rot + 1)%4 해서 회전한거도 함께 저장

 블록 넘으면 rot = 0이기 때문에 rot를 0으로 바꾸고, nx,ny 좌표상 확인 ->
  시계 90도 돌려줌 + (rot+1) %4 해서 회전한거도 함께 저장.

제자리 머물기도 가능하기 때문에 그냥 visited[][] = true로 하면, 제자리 머문게 큐로 안들어감.
그래서 지나갔는지를 확인하기 보다는 해당 위치에서 더 짧은 최단거리가 발견되면? 큐에 저장하기 방식으로 가야함

int visited[좌][표][회전 4종류] > cd + 1; cd + 1 한거보다 기존 저장값이 크면 지금 값이 최단거리니까
큐에 추가함. 상하좌우 제자리 순서 상관없이 그냥 최단거리면 큐에 넣는 개념.

*/

#include <iostream> 
#include <algorithm> 
#include <vector> 
#include <string> 
#include <queue> 
using namespace std; 

int K; 
char grid[500][500][4]; 
int visited[500][500][4];
struct Axis{ 
    int x, y, rot, dist;
}; 

int dx[5] = {-1, 0, 1, 0, 0}; 
int dy[5] = {0, 1, 0, -1, 0}; 

queue<Axis> q; 

void mapRot(){ 
    for(int rot = 1; rot < 4; rot++){
        for(int i = 0; i < 4*K; i++){
            for (int j = 0; j < 4*K; j++){
                int sx = i/4 * 4, sy = j/4*4;
                int ox = i - sx, oy = j - sy;
                int rx, ry;

                if(rot == 1){ rx = sx + oy, ry = sy + 3-ox;}
                else if (rot == 2){rx = sx + 3-ox, ry = sy + 3-oy;}
                else if (rot == 3){rx = sx + 3-oy, ry = sy + ox;}

                grid[rx][ry][rot] = grid[i][j][0];
            }
        }
    }
}

pair<int, int> nextPos(int x, int y){
    int basex = x/4 * 4, basey = y/4 * 4;
    int nextx = x%4, nexty = y%4;

    return {basex + nexty, basey + 3 - nextx};
}


int move(int sx, int sy){
    fill(&visited[0][0][0], &visited[0][0][0] + 500*500*4, -1);
    q.push({sx, sy, 0, 0});
    visited[sx][sy][0] = 0;

    while(!q.empty()){
        auto cur = q.front();
        int cx = cur.x, cy = cur.y, cr = cur.rot, cd = cur.dist;
        q.pop();

        for(int i = 0; i < 5; i++){
            int rx, ry;
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            int nr = cr;

            if(nx < 0 || ny < 0 || nx >= 4*K || ny >= 4*K){continue;}

            if(cx/4 == nx/4 && cy/4 == ny/4){
                if(grid[nx][ny][nr] == '#'){continue;}
                else if(grid[nx][ny][nr] == 'E'){ return cd+1;}

                tie(rx, ry) = nextPos(nx, ny);

                nr = (nr+1)%4;
                if(visited[rx][ry][nr] == -1){
                visited[rx][ry][nr] = cd+1;
                q.push({rx, ry, nr, cd+1});
                }
                else if(visited[rx][ry][nr] > cd+1){
                    visited[rx][ry][nr] = cd+1;
                    q.push({rx, ry, nr, cd+1});
                }
            }
            else{
                nr = 0;
                if(grid[nx][ny][nr] == '#'){continue;}
                else if(grid[nx][ny][nr] == 'E'){ return cd+1;}

                tie(rx, ry) = nextPos(nx, ny);
                nr = (nr+1)%4;

                if(visited[rx][ry][nr] == -1){
                visited[rx][ry][nr] = cd+ 1;
                q.push({rx, ry, nr, cd+1});
                }
                else if(visited[rx][ry][nr] > cd+1){
                    visited[rx][ry][nr] = cd+ 1;
                    q.push({rx, ry, nr, cd+1});
                }
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
                        
            grid[i][j][0] = line[j]; 
            
            if(grid[i][j][0] == 'S'){ startx = i; starty = j;} 
        } 
    }

    mapRot();

    int answer = move(startx, starty);
    cout << answer << "\n";
    
    return 0; 
}