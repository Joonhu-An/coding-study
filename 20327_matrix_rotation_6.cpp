/*
https://www.acmicpc.net/problem/20327
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

int N, T, S;
int grid[128][128];
int tmp[128][128];

struct Playset{
    int stage, level;
};

vector<Playset> v;

void one(int l){ // 상하 대칭 변경
    int size = 1<<l;

    for(int si = 0; si < S; si += size){
        for(int sj = 0; sj < S; sj+= size){

            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    tmp[si+size-1-i][sj+j] = grid[si+i][sj+j];
                }
            }
        }
    }
}

void two(int l){ // 좌우 대칭 이동
    int size = 1<<l;

    for(int si = 0; si < S; si += size){
        for(int sj = 0; sj < S; sj+= size){

            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    tmp[si+i][sj+size-1-j] = grid[si+i][sj+j];
                }
            }
        }
    }
}

void three(int l){ // 구간내 시계방향 90도, 구간별로 돌리기 위해선 2중 포문이 2개나 필요하다
    int size = 1<<l;

    for(int si = 0; si < S; si += size){ // size 크기에 따른 구간별 사이즈
        for(int sj = 0; sj < S; sj+= size){

            for(int i = 0; i < size; i++){ // 여기서 90도 시계 방향으로 돌린다 size 크기 내부에 있는 애들만 돌림
                for(int j = 0; j < size; j++){
                    tmp[si+j][sj+size-1-i] = grid[si+i][sj+j];
                    // si, sj를 통해서 쪼개어놓은 크기만큼 더해줘야함
                    // 2*2 로 쪼개어두었으면 매번 2만큼씩 더 해줘야함
                }
            }
        }
    }
}

void four(int l){ // 구간내 반시계 90도
    int size = 1<<l;

    for(int si = 0; si < S; si += size){
        for(int sj = 0; sj < S; sj+= size){

            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    tmp[si+size-1-j][sj+i] = grid[si+i][sj+j];
                }
            }
        }
    }
}

void five(int l){ // 구간내 변화없고 구간끼리 상하 위치 교체
    int size = 1<<l;
    int block  = S/size;

    for(int si = 0; si < block; si++){
        for(int sj = 0; sj < block; sj++){
            int ni = block - 1 - si;
            int nj = sj;

            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    tmp[ni * size + i][nj * size +j] = grid[si * size + i][sj * size + j];
                }
            }
        }
    }
}

void six(int l){ // 구간내 변화없고 구간끼리 좌우 위치 교체
    int size = 1<<l;
    int block  = S/size;

    for(int si = 0; si < block; si++){
        for(int sj = 0; sj < block; sj++){
            int ni = si;
            int nj = block - 1 -sj;

            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    tmp[ni * size + i][nj * size +j] = grid[si * size + i][sj * size + j];
                }
            }
        }
    }
}

void seven(int l){ // 구간내 변화없고 구간들이 시계 90도 이동. 그냥 전체 시계90도 돌린 다음 구간내 반시계 90도 돌리기 사용했음
    /*
    1 2 3 4                 l = 1 일때 구간은 2*2 ->        13 9 5 1        ->       9 10 1 2
    5 6 7 8                  -> 일단 시계 90도 전체 돌린다   14 10 6 2                13 14 5 6
    9 10 11 12                                            15 11 7 3                11 12 3 4
    13 14 15 16                                           16 12 8 4                15 16 7 8
    */
    int size = 1<<l;

    for(int i = 0; i < S; i++){
        for(int j = 0; j < S; j++){
            tmp[j][S-1-i] = grid[i][j];
        }
    }

    for(int i = 0; i < S; i++){
        for(int j= 0; j < S; j++){
            grid[i][j] = tmp[i][j];
        }
    }

    for(int si = 0; si < S; si += size){
        for(int sj = 0; sj < S; sj+= size){

            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    tmp[si+size-1-j][sj+i] = grid[si+i][sj+j];
                }
            }
        }
    }
}

void eight(int l){ // 구간내 변화없고 구간들이 반시계 90도 이동. 그냥 전체 시계90도 돌린 다음 구간내 시계 90도 돌리기 사용했음
    int size = 1<<l;

    for(int i = 0; i < S; i++){
        for(int j = 0; j < S; j++){
            tmp[S-1-j][i] = grid[i][j];
        }
    }

    for(int i = 0; i < S; i++){
        for(int j= 0; j < S; j++){
            grid[i][j] = tmp[i][j];
        }
    }

    for(int si = 0; si < S; si += size){
        for(int sj = 0; sj < S; sj+= size){

            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    tmp[si+j][sj+size-1-i] = grid[si+i][sj+j];
                }
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

    cin >> N >> T;
    S = 1<<N;

    for(int i = 0; i < S; i++){
        for(int j = 0; j < S; j++){
            cin >> grid[i][j];
        }
    }

    for(int k = 0; k < T; k++){
        int a, b;
        cin >> a >> b;
        v.push_back({a,b});
    }

    for(auto &p : v){

        if(p.stage == 1){
            one(p.level);
        }
        else if (p.stage == 2){
            two(p.level);
        }
        else if (p.stage == 3){
            three(p.level);  
        }
        else if (p.stage == 4){
            four(p.level);
        }
        else if (p.stage == 5){
            five(p.level);
        }
        else if (p.stage == 6){
            six(p.level);
        }
        else if (p.stage == 7){
            seven(p.level);
        }
        else if (p.stage == 8){
            eight(p.level);
        }

        for(int i = 0; i < S; i++){
            for(int j= 0; j < S; j++){
                grid[i][j] = tmp[i][j];
            }
        }
    }

    for(int i = 0; i < S; i++){
        for(int j= 0; j < S; j++){
            cout << tmp[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}