/* https://www.acmicpc.net/problem/16926

정해진 구간만큼 회전시키는 경우는 했었지만 layer로 나눠서 층마다 돌리는 건 아이디어가 필요한거 같다.
쉬운 문제랬는데 안 떠올라서 넘 어려웡

*/

#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, M, T;
    cin >> N >> M >> T;
    int map[300][300];
    
    int layer = min(N,M)/2; // layer끼리만 돌릴거라서 나눠주는게 필요함

    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> map[i][j];
        }
    }

    for (int l = 0; l < layer; l++){
        vector<int> v;

        int x1 = l, y1 = l;
        int x2 = N-1-l, y2 = M-1-l; // 첫번째 layer라면 l = 0 따라서 x2에서 가장 큰 값은 그냥 N-1 
        // 만약에 3번째 layer라면 l =2, x1 시작점도 위에서 2칸 내려온 2, x2 가장 큰 값도 가장 아래에서 2칸 올라온 N-1-2

        for(int j = y1; j < y2; j++){ //(0,0)에서 부터 (0, j) 까지 출발 좌->우
            v.push_back(map[x1][j]);  // 여기선 한 방향으로만 도는게 중요함. 시계든 반시계든
        }                             // 왜냐면 모서리 부분은 2번 값을 넣어서 중복이 되기 때문에 덮어 씌우는 과정이 발생함
                                      // 근데 여기서 좌->우, 우->좌, 하->상 이런식으로 섞어버리면 모서리가 다르게 덮어씌워짐
        for(int i = x1; i < x2; i++){ // 상->하
            v.push_back(map[i][y2]);
        }
        for(int j = y2; j > y1; j--){ // 우->좌
            v.push_back(map[x2][j]);
        }
        for(int i = x2; i > x1; i--){ // 하->상 
            v.push_back(map[i][y1]);
        }

        int len = v.size(); // len 길이를 먼저 파악하고
        int rot = T % len; // 얼마나 이동을 하는지 판단. 만약에 길이가 10인데 11번을 이동하면 한번만 움직이는거랑 결과가 같음
        int idx = rot;
        
        for(int j = y1; j < y2; j++){
            map[x1][j]= v[idx++ % len]; // 벡터에 넣어뒀던 값들을 map으로 옮겨넣음. 기존에 시계 방향으로 값을 넣어뒀기 때문에
        }                               // rot 값만큼 플러스로 올리면 rot값 만큼 반시계로 움직인 효과가 나타남
        for(int i = x1; i < x2; i++){   // A 위치에 A+2를 넣으면 1 2 3 에서 3이 1의 위치로 간다. 이후 idx++ 해줘서
            map[i][y2] = v[idx++ % len]; // for문 돌리면서 해당 라인 전체를 이동 시켜줍니당.
        }
        for(int j = y2; j > y1; j--){
            map[x2][j] = v[idx++ % len];
        }
        for(int i = x2; i > x1; i--){
            map[i][y1] = v[idx++ % len];
        }

    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cout << map[i][j] << " ";
        }

        cout << endl;
    }

    return 0;
}