#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100;
const int INF = 1e9;

int n;
char maze[4][MAX_N * 4][MAX_N * 4];
bool visited[4][MAX_N * 4][MAX_N * 4];
int dx[] = {0, 1, 0, -1, 0};
int dy[] = {0, 0, 1, 0, -1};

struct State {
    int x, y, rot, dist;
    State(int x, int y, int rot, int dist) : x(x), y(y), rot(rot), dist(dist) {}
};

void rotate(int r, int c, int rot) {
    // 회전된 좌표 계산
    int base_r = r / 4 * 4, base_c = c / 4 * 4;
    r %= 4;
    c %= 4;
    if (rot == 1) {
        swap(r, c);
        r = 3 - r;
    } else if (rot == 2) {
        r = 3 - r;
        c = 3 - c;
    } else if (rot == 3) {
        swap(r, c);
        c = 3 - c;
    }
    return base_r + r, base_c + c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    pair<int, int> start, end;
    for (int i = 0; i < 4 * n; i++) {
        for (int j = 0; j < 4 * n; j++) {
            char ch;
            cin >> ch;
            maze[0][i][j] = ch;
            if (ch == 'S') start = {i, j};
            else if (ch == 'E') end = {i, j};
        }
    }

    // 회전된 미로 상태 계산
    for (int rot = 1; rot < 4; rot++) {
        for (int i = 0; i < 4 * n; i++) {
            for (int j = 0; j < 4 * n; j++) {
                maze[rot][i][j] = maze[0][i][j];
            }
        }
    }

    queue<State> q;
    q.push(State(start.first, start.second, 0, 0));
    visited[0][start.first][start.second] = true;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.x == end.first && cur.y == end.second) {
            cout << cur.dist << '\n';
            return 0;
        }

        for (int i = 0; i < 5; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx < 0 || ny < 0 || nx >= 4 * n || ny >= 4 * n) continue;

            int nrot = (cur.rot + 1) % 4;
            if (visited[nrot][nx][ny] || maze[nrot][nx][ny] == '#') continue;

            visited[nrot][nx][ny] = true;
            q.push(State(nx, ny, nrot, cur.dist + 1));
        }
    }

    cout << -1 << '\n';
    return 0;
}
