/*
https://www.acmicpc.net/problem/17406

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits.h>

using namespace std;

int N, M, K;
int grid[50][50]; // 명칭 무조건 grid로 map 같이 헤더에 선언되어있는 이름은 하지마
int tmp[50][50];

struct Rotation{
    int r, c, s;
};

vector<Rotation> v;

void Rot(int r, int c, int s){

    for(int l = 0; l < s; l++){
        int x1 = r-s-1+l, y1 = c-s-1+l; // 어디를 top, bottom, left, right으로 정할지 생각하기
        int x2 = r+s-1-l, y2 = c+s-1-l;

        vector<int> rv;

        for(int j = y1; j < y2; j++){ // 항상 시계 방향으로 벡터에 넣기, 시계/반시계 돌리는건 밑에서 처리하면 될듯
            rv.push_back(tmp[x1][j]);
        }
        for(int i = x1; i < x2; i++){
            rv.push_back(tmp[i][y2]);
        }
        for(int j = y2; j > y1; j--){
            rv.push_back(tmp[x2][j]);
        }
        for(int i = x2; i > x1; i--){
            rv.push_back(tmp[i][y1]);
        }
        
        int last = rv.back();           // 필요한 경우 가장 앞에 insert하고 rv.pop_back() 해서 가장 마지막꺼 지우기.
        rv.insert(rv.begin(), last);    // 반시계로 돌릴땐 int first = rv.front(); rv.erase(rv.begin());
                                        // rv.push_back(first); 해서 젤 앞에꺼 젤 뒤로 보내고 그대로 넣으면 된다
                                        // 한번에 2칸이상 돌리면 이거도 여러번 처리 해야할듯? idx = 1 이런식으로 하면
                                        // 훨씬 간편하긴 하지만, vector index 없는걸 호출해서 사고 날 가능성 높음
        int len = rv.size();
        int idx = 0;

        for(int j = y1; j < y2; j++){   // 시계 방향 회전이니까 좌 -> 우
            tmp[x1][j] = rv[idx++ % len];
        }
        for(int i = x1; i < x2; i++){   // 상 -> 하
            tmp[i][y2] = rv[idx++ % len];
        }
        for(int j = y2; j > y1; j--){   // 우 -> 좌
            tmp[x2][j] = rv[idx++ % len];
        }    
        for(int i = x2; i > x1; i--){   // 하 -> 상
            tmp[i][y1] = rv[idx++ % len];
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int r,c,s, answer = INT_MAX;

    cin >> N >> M >> K;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> grid[i][j];
        }
    }

    vector<int> order(K);   // 순열처리를 위한 index = K개 벡터
    iota(order.begin(), order.end(), 0);    // 0부터 K-1까지 벡터마다 채우기, fill은 그냥 0으로만 채우기

    for(int i = 0; i < K; i++){
        
        cin >> r >> c >> s;
        v.push_back({r,c,s});
    }

    do{

        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                tmp[i][j] = grid[i][j];     // 회전행렬전에 복사해두기
            }
        }

        for(int idx : order){   // 이렇게 해야 order를 기준으로 모든 순차열을 다 돈다.
            Rot(v[idx].r, v[idx].c, v[idx].s);
        }
        
        for(int i = 0; i < N; i++){
                int sum = accumulate(tmp[i], tmp[i]+M,0);   // vector면 v.begin() 이런식으로 가능하긴 함.
                answer = min(answer, sum);
            }
    }while(next_permutation(order.begin(), order.end()));   // 0~K-1 까지 전체 순열조합으로 돌리면서 진행

    //next_permutation 개념이 (order.begin() 부터 order.end() 까지 있는 값을 순열로 조합하는건데)
    // 여기서는 예를 들어 0, 1, 2 이렇게 있으면 012, 021, 102, 120, 201, 210 이렇게 총 6개 조합을 돌린다
    // 6개 조합을 돌리면서 for(int idx : order)을 통해서 해당되는 회전을 진행하는데, answer = min을 통해서
    // 모든 조합에서 나오는 가장 최소값을 가져올 수 있다.
    
    cout << answer << endl;

    return 0;
}