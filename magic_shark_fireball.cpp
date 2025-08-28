/*
https://www.acmicpc.net/problem/20056

어른 상어가 마법사가 되었고, 파이어볼을 배웠다.

마법사 상어가 크기가 N×N인 격자에 파이어볼 M개를 발사했다. 가장 처음에 파이어볼은 각자 위치에서 이동을 대기하고 있다. 
i번 파이어볼의 위치는 (ri, ci), 질량은 mi이고, 방향은 di, 속력은 si이다. 위치 (r, c)는 r행 c열을 의미한다.

격자의 행과 열은 1번부터 N번까지 번호가 매겨져 있고, 1번 행은 N번과 연결되어 있고, 1번 열은 N번 열과 연결되어 있다.

파이어볼의 방향은 어떤 칸과 인접한 8개의 칸의 방향을 의미하며, 정수로는 다음과 같다.

7	0	1
6	 	2
5	4	3
마법사 상어가 모든 파이어볼에게 이동을 명령하면 다음이 일들이 일어난다.

모든 파이어볼이 자신의 방향 di로 속력 si칸 만큼 이동한다.
이동하는 중에는 같은 칸에 여러 개의 파이어볼이 있을 수도 있다.
이동이 모두 끝난 뒤, 2개 이상의 파이어볼이 있는 칸에서는 다음과 같은 일이 일어난다.
같은 칸에 있는 파이어볼은 모두 하나로 합쳐진다.
파이어볼은 4개의 파이어볼로 나누어진다.
나누어진 파이어볼의 질량, 속력, 방향은 다음과 같다.
질량은 ⌊(합쳐진 파이어볼 질량의 합)/5⌋이다.
속력은 ⌊(합쳐진 파이어볼 속력의 합)/(합쳐진 파이어볼의 개수)⌋이다.
합쳐지는 파이어볼의 방향이 모두 홀수이거나 모두 짝수이면, 방향은 0, 2, 4, 6이 되고, 그렇지 않으면 1, 3, 5, 7이 된다.
질량이 0인 파이어볼은 소멸되어 없어진다.
마법사 상어가 이동을 K번 명령한 후, 남아있는 파이어볼 질량의 합을 구해보자.

입력
첫째 줄에 N, M, K가 주어진다.

둘째 줄부터 M개의 줄에 파이어볼의 정보가 한 줄에 하나씩 주어진다. 파이어볼의 정보는 다섯 정수 ri, ci, mi, si, di로 이루어져 있다.

서로 다른 두 파이어볼의 위치가 같은 경우는 입력으로 주어지지 않는다.

출력
마법사 상어가 이동을 K번 명령한 후, 남아있는 파이어볼 질량의 합을 출력한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, K;

struct Fire{
    int r, c, m, s, d;
};

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

vector<Fire> fvect;
vector<Fire> cell[50][50];

void move(){
    fill(&cell[0][0], &cell[0][0] + 50*50, vector<Fire>());
    
    for(auto &f : fvect){
        int nx = ((f.r + dx[f.d] * (f.s % N)) % N + N) % N;
        int ny = ((f.c + dy[f.d] * (f.s % N)) % N + N) % N;
        cell[nx][ny].push_back({nx, ny, f.m, f.s, f.d});
    }
    
    fvect.clear();
}

void merge(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            auto &grid = cell[i][j];
            int gridsize = grid.size();
            
            if(gridsize == 0) continue;
            else if(gridsize == 1) {
                fvect.push_back(grid[0]);
            }
            else {
                long long sum_m = 0, sum_s = 0;
                int even = 0, odd = 0;
                
                for(auto &f : grid){
                    sum_m += f.m;
                    sum_s += f.s;
                    
                    if(f.d%2 == 0){
                        even++;
                    } else {
                        odd++;
                    }
                }
                
                int nm = sum_m/5;
                if(nm == 0) continue;
                
                int ns = sum_s/gridsize;
                for(int k = 0; k < 4; k++){
                    if(even == gridsize || odd == gridsize){
                        fvect.push_back({i, j, nm, ns, k*2});
                    }
                    else fvect.push_back({i, j, nm, ns, k*2+1});
                }
            } 
        }
    }   
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
        
    cin >> N >> M >> K;
    
    int r, c, m, d, s;
    for(int i = 0; i < M; i++){
        cin >> r >> c >> m >> s >> d;
        fvect.push_back({r-1,c-1,m,s,d});

    }
    
    for(int j = 0; j < K; j++){
        move();
        merge();
    }
    
    long long answer = 0;
    for(auto &f : fvect){
        answer += f.m; 
    }
    
    cout << answer << '\n';
    return 0;
       
}