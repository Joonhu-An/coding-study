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

    for(auto &f: fvect){
        int nx = ((f.r + dx[f.d] * (f.s % N)) % N + N) % N;
        int ny = ((f.c + dy[f.d] * (f.s % N)) % N + N) % N;
        cell[nx][ny].push_back({nx, ny, f.m, f.s, f.d});
    }

    fvect.clear();
}

void merge(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            auto &grid = cell[i][j];
            int gridsize = grid.size();

            if(gridsize == 0) continue;
            else if (gridsize == 1){
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
                    }
                    else {
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

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N >> M >> K;

    int r, c, m, s, d;

    for(int i = 0; i < M; i++){
        cin >> r >> c >> m >> s >> d;
        fvect.push_back({r-1, c-1, m, s, d});
    }

    for(int j = 0; j < K; j++){
        move();
        merge();
    }

    long long answer = 0;
    for(auto &f : fvect){
        answer += f.m;
    }
    
    cout << answer << endl;

    return 0;
}

/*  freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cout << f.r << "/" << f.c << "/ 질량 : " << f.m << "/ 속도 : " << f.s << "/ 방향 : " << f.d << "/" << nx << "/" << ny << endl;
    4 2 1
    1 1 5 2 2
    1 4 7 1 6

    8
    */