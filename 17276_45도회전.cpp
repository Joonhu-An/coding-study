/*
https://www.acmicpc.net/problem/17276
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits.h>

using namespace std;

int T, N, R, cen;
int grid[500][500];
int tmp[500][500];

void Clock(int l){
    int time = (l/45)%8 , cen = N/2; // 45도 당 1회, 그리고 360도 돌면 똑같은 회전이니까 굳이 더 할 필요 X

    if(l < 0){
        time = (8+(l/45))%8; // 반시계의 경우 굳이 코드 따로 안 짜고, -45도 = 315도 같은 원리를 활용, 조금 더 돌리기만 하자
    }

    for(int t = 0; t < time; t++){
        for(int i = 0; i < N; i++){ // 어차피 N 정사각형이기 때문에 i, j 필요 없음.
            tmp[i][cen] = grid[i][i]; // center 행과 열, 대각선 X자 형태로 2개해서 총 4개만 돌리면 된다. 오른쪽 내려가는 대각선 -> 열
            tmp[i][N-1-i] = grid[i][cen]; // 열 -> 오른쪽으로 올라가는 대각선
            tmp[cen][N-1-i] = grid[i][N-1-i]; // 오른쪽 올라가는 대각선 -> 행
            tmp[i][i] = grid[cen][i];   // 행 -> 오른쪽 내려가는 대각선
        }

        for(int i = 0; i < N; i++){ // grid를 계속 활용 해야하기 때문에 업데이트 필수
            for(int j = 0; j < N; j++){
                grid[i][j] = tmp[i][j];
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

    cin >> T;

    for(int i = 0; i < T; i++){
        cin >> N >> R;

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cin >> grid[i][j];
                tmp[i][j] = grid[i][j]; // Clock()에서 정해진 부분 말고는 tmp에 입력이 안된다, 따라서 첫 시작때
            }   // tmp에 값을 넣어줘야. 안 움직이는 고정값에도 숫자가 들어가있음.
        }

        Clock(R);      

        for(int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                cout << tmp[i][j] << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}