/* https://www.acmicpc.net/problem/16927

16926 문제랑 똑같은 문제다. 왜 같은 문제가 따로 있지?
-> 했었는데 16926에선 회전 횟수가 적었지만 16297은 회전을 많이한다.
    따라서 R % len 파트 구현을 안하면 시간초과? 뜨는거 같음. 첨부터 이렇게 해서 몰랏네용
    아무튼 len 부분만 조금 다르게 풀어보았다. 기존엔 그냥 vector size 가지고 했었음.

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

    int N, M, R;
    int map[300][300];

    cin >> N >> M >> R;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> map[i][j];
        }
    }

    int layer = min(N,M)/2;

    for(int l = 0; l < layer; l++){
        int x1 = l, y1 = l;
        int x2 = N-1-l, y2 = M-1-l;

        vector<int> v;

        for(int j = y1; j < y2; j++){
            v.push_back(map[x1][j]);
        }
        for(int i=x1; i < x2; i++){
            v.push_back(map[i][y2]);
        }
        for(int j=y2; j > y1; j--){
            v.push_back(map[x2][j]);
        }
        for(int i=x2; i>x1; i--){
            v.push_back(map[i][y1]);
        }

        int len = 2*(x2 -x1 +1 + y2 -y1 + 1)-4;
        int rot = R % len;

        for(int j = y1; j < y2; j++){
            map[x1][j] = v[rot++ % len];
        }
        for(int i=x1; i < x2; i++){
            map[i][y2] = v[rot++ % len];
        }
        for(int j=y2; j > y1; j--){
            map[x2][j] = v[rot++ % len];
        }
        for(int i=x2; i>x1; i--){
            map[i][y1] = v[rot++ % len];
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
