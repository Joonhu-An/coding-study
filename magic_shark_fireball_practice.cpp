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

    move();

    for(auto &f: fvect){
        cout << f.r << " / " << f.c << " / " << f.m << " / " << f.s << " / " << f.d;
    }
    
    return 0;
}

/*  freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */