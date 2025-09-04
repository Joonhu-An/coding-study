/*
https://www.acmicpc.net/problem/16935

금방 풀었는데 계속 오류가 생겨서 헤매였음. 원인은 직사각형 모양을 회전했을때, N과 M이 바뀌는 구간이 정말 많았음.
1~6번 진행할때도 3번이나 4번을 홀수번 (1번,3번...) 한 경우 N과 M이 바뀜. 짝수횟수 (2, 4번...)는 다시 N과 M이 같아지는 것도
고려해야함. 뿐만 아니라 grid 저장할때도 이중 for문을 했는데 이때도 직사각형일땐 N, M 바꿔야하고 마지막 출력때도 마찬가지
괜히 회전 로테이션 로직 이슈인지 알고 엄청 헤매였다. r = N하고 c = M 했는데 이렇게 많이 쓸거면 그냥 전역변수 선언하는게 나을지도
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int N, M, T;
int grid[100][100];
int tmp[100][100];
vector<int> v;

int rectangle = 0;

void Updown(){
    int r, c;
    if(rectangle %2 == 0){
        r = N;
        c = M;
    }
    else {
        r = M;
        c = N;
    }
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            int reverse = r-1-i;
            tmp[reverse][j] = grid[i][j];
        }
    }
}

void Leftright(){
    int r, c;
    if(rectangle %2 == 0){
        r = N;
        c = M;
    }
    else {
        r = M;
        c = N;
    }

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            int reverse = c-1-j;
            tmp[i][reverse] = grid[i][j];
        }
    }
}

void Rotclock(){

    if(rectangle %2 == 0){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                int x1 = N-1-i;
                tmp[j][x1] = grid[i][j];
            }
        }
    }
    else {
        for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){
                int x1 = M-1-i;
                tmp[j][x1] = grid[i][j];
            }
        }
    }
    rectangle++;
}

void Rotanticlock(){
    int r, c;
    if(rectangle %2 == 0){
        r = N;
        c = M;
    }
    else {
        r = M;
        c = N;
    }

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            int y1 = c-1-j;
            tmp[y1][i] = grid[i][j];
        }
    }
    rectangle--;
}

void Moveclock(){
    int r, c;
    if(rectangle %2 == 0){
        r = N;
        c = M;
    }
    else {
        r = M;
        c = N;
    }
    
    int r_layer = r/2, c_layer = c/2;


    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){

            if(i < r_layer && j < c_layer){
                tmp[i][j+c_layer] = grid[i][j];
            }
            else if(i < r_layer && j >= c_layer){
                tmp[i+r_layer][j] = grid[i][j];
            }
            else if(i >= r_layer && j >= c_layer){
                tmp[i][j-c_layer] = grid[i][j];
            }
            else if(i >= r_layer && j < c_layer){
                tmp[i-r_layer][j] = grid[i][j];
            }
            
        }
    }
}

void Moveanticlock(){
    int r, c;
    if(rectangle %2 == 0){
        r = N;
        c = M;
    }
    else {
        r = M;
        c = N;
    }

    int r_layer = r/2, c_layer = c/2;

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){

            if(i < r_layer && j < c_layer){
                tmp[i+r_layer][j] = grid[i][j];
            }
            else if(i < r_layer && j >= c_layer){
                tmp[i][j-c_layer] = grid[i][j];
            }
            else if(i >= r_layer && j >= c_layer){
                tmp[i-r_layer][j] = grid[i][j];
            }
            else if(i >= r_layer && j < c_layer){
                tmp[i][j+c_layer] = grid[i][j];
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

    cin >> N >> M >> T;

    for(int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> grid[i][j];
        }
    }

    for(int k = 0; k < T; k++){
        int time;
        cin >> time;
        v.push_back(time);
    }

    for(int l : v){
        if(l == 1){
            Updown();
        }
        else if(l == 2){
            Leftright();
        }
        else if(l == 3){
            Rotclock();
        }
        else if(l == 4){
            Rotanticlock();
        }
        else if(l == 5){
            Moveclock();
        }
        else if(l == 6){
            Moveanticlock();
        }

        
        if(rectangle % 2 == 0){
            for(int i = 0; i < N; i++){
                for (int j = 0; j < M; j++){
                    grid[i][j] = tmp[i][j];
                }
            }
        }
        else{
            for(int i = 0; i < M; i++){
                for (int j = 0; j < N; j++){
                    grid[i][j] = tmp[i][j];
                }
            }
        }
    }

    int r, c;

    if(rectangle % 2 == 0){
        r = N;
        c = M;
    }
    else {
        r = M;
        c = N;
    }

    for(int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            cout << tmp[i][j] << " ";
        }
        cout << "\n";
    }


    return 0;
}