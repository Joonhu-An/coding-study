/* 
https://www.acmicpc.net/problem/20058

마법사 상어는 파이어볼과 토네이도를 조합해 파이어스톰을 시전할 수 있다. 오늘은 파이어스톰을 크기가 2^N × 2^N인 격자로 나누어진 얼음판에서 연습하려고 한다. 
위치 (r, c)는 격자의 r행 c열을 의미하고, A[r][c]는 (r, c)에 있는 얼음의 양을 의미한다. A[r][c]가 0인 경우 얼음이 없는 것이다.

파이어스톰을 시전하려면 시전할 때마다 단계 L을 결정해야 한다. 파이어스톰은 먼저 격자를 2^L × 2^L 크기의 부분 격자로 나눈다. 
그 후, 모든 부분 격자를 시계 방향으로 90도 회전시킨다. 이후 얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸은 얼음의 양이 1 줄어든다. 
(r, c)와 인접한 칸은 (r-1, c), (r+1, c), (r, c-1), (r, c+1)이다. 아래 그림의 칸에 적힌 정수는 칸을 구분하기 위해 적은 정수이다.

마법사 상어는 파이어스톰을 총 Q번 시전하려고 한다. 모든 파이어스톰을 시전한 후, 다음 2가지를 구해보자.

남아있는 얼음 A[r][c]의 합
1. 남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수
2. 얼음이 있는 칸이 얼음이 있는 칸과 인접해 있으면, 두 칸을 연결되어 있다고 한다. 덩어리는 연결된 칸의 집합이다.

입력
첫째 줄에 N과 Q가 주어진다. 둘째 줄부터 2N개의 줄에는 격자의 각 칸에 있는 얼음의 양이 주어진다. r번째 줄에서 c번째 주어지는 정수는 A[r][c] 이다.

마지막 줄에는 마법사 상어가 시전한 단계 L1, L2, ..., LQ가 순서대로 주어진다.

출력
첫째 줄에 남아있는 얼음 A[r][c]의 합을 출력하고, 둘째 줄에 가장 큰 덩어리가 차지하는 칸의 개수를 출력한다. 단, 덩어리가 없으면 0을 출력한다.

제한
2 ≤ N ≤ 6
1 ≤ Q ≤ 1,000
0 ≤ A[r][c] ≤ 100
0 ≤ Li ≤ N

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, Q;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int map[64][64];
int rot_map[64][64];
bool visited[64][64];
int lessthree[64][64];

queue<pair<int, int>> q;

void rotation(int r){

    int size = 1 << r;
    int total = 1 << N;
    int point = size / 2;

    for (int sx = 0; sx < total; sx += size) {
        for (int sy = 0; sy < total; sy += size) {

            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    rot_map[sx + y][sy + size - 1 - x] = map[sx + x][sy + y];
                }
            }
        }
    }    



    for(int i = 0; i < total; i++){
        for (int j = 0; j < total; j++){
            map[i][j] = rot_map[i][j];
        }
    }    
}

void check(int x, int y){
    int near = 0;

    for(int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(nx >= 0 && ny >= 0 && nx < 1<<N && ny < 1<<N){
            if (map[nx][ny] > 0){
                near++;
            }
        }
    }

    if(near >= 3){
        visited[x][y] = true;
    }
}

void melt(){
    for(int i = 0; i < (1<<N); i++){
            for (int j = 0; j < (1<<N); j++){
                if(map[i][j] == 0){
                    continue;
                }
                else if(!visited[i][j]){
                    map[i][j] -= 1;
                }
        }
    }
}

int counting(){
    int ice_sum = 0;

    for(int i = 0; i < (1<<N); i++){
            for (int j = 0; j < (1<<N); j++){
                    ice_sum += map[i][j];
        }
    }

    return ice_sum;
}

int howBig(int x, int y){
    int maximum = 0;

    if(map[x][y] != 0){
        maximum++;
    }

    if(!visited[x][y]){
        q.push({x,y});
        visited[x][y] = true;
    
        while(!q.empty()){
            int cx = q.front().first;
            int cy = q.front().second;
            q.pop();

            for(int i = 0; i < 4; i++){
                int nx = cx + dx[i];
                int ny = cy + dy[i];

                if(nx >= 0 && ny >= 0 && nx < 1<<N && ny < 1<<N){
                    if (map[nx][ny] > 0 && !visited[nx][ny]){
                        maximum++;
                        visited[nx][ny] = true;
                        q.push({nx,ny});
                    }
                }
            }
        }
    }
    
    return maximum;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N >> Q;

    for(int i = 0; i < (1<<N); i++){
        for (int j = 0; j < (1<<N); j++){
            cin >> map[i][j];
        }
    }

    vector<int> rotate(Q);
    
    for(int k = 0; k < Q; k++){
        cin >> rotate[k];
    }

    for(int l = 0; l < Q; l++){
        rotation(rotate[l]);
        
        fill(&visited[0][0], &visited[0][0] + 64*64, false);

        for(int i = 0; i < (1<<N); i++){
            for (int j = 0; j < (1<<N); j++){
                if(map[i][j] != 0){
                    check(i, j);
                }
            }
        }

        melt();  
    }

    int size_big = 0;

    fill(&visited[0][0], &visited[0][0] + 64*64, false);

    for(int i = 0; i < (1<<N); i++){
            for (int j = 0; j < (1<<N); j++){
                    size_big = max(size_big, howBig(i,j));
        }
    }  

    int sum_answer;
    sum_answer = counting();
    cout << sum_answer << endl;
    cout << size_big << endl;

    return 0;
}


/*
for(int i = 0; i < (1<<N); i++){
            for (int j = 0; j < (1<<N); j++){
                cout << lessthree[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        */
