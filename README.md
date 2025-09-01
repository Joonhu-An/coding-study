# 회전행렬
 
 N*N 정사각형 기준

              회전각            |         수식 (rot[i][j]에 mat[i][j] 복사)
              
    90도 시계  (270도 반시계)    |      rot[j][N-1-i] = mat[i][j]
    
    180도 (180도 반시계)              rot[N-1-i][M-1-j] = mat[i][j]
    
    207도 시계 (90도 반시계)     |       rot[M-1-j][i] = mat[i][j]


N*M 직사각형 기준

layer 단위로 순회, 한 칸씩 이동 (2,3) -> (2,4) 이런식으로 한 칸씩 다 옮겨줘야함
정사각형처럼 정해진 규칙이 따로 있진 않음.


    int N, M;
    int layers = min(N, M)/2; // layer를 기준점으로 중간 지점을 파악하고 구간별로 나눈다

    for(int layer=0; layer<layers; layer++){
        int top = layer, bottom = N-1-layer;
        int left = layer, right = M-1-layer;

        int prev = mat[top+1][left]; // 이동 시작점 저장

        // top row
        for(int j=left;j<=right;j++){
            swap(mat[top][j], prev);
        }

        // right column
        for(int i=top+1;i<=bottom;i++){
         
            swap(mat[i][right], prev);
        }
        // bottom row
        for(int j=right-1;j>=left;j--){
            swap(mat[bottom][j], prev);
        }

        // left column
        for(int i=bottom-1;i>top;i--){
            swap(mat[i][left], prev);
        }
    }

# 토러스맵

int nx = (현재 index + delta + size) % size

여기서 현재 index + delta 값이 음수인 경우를 방지하기 위해서 + size를 하는데 만약 음수값이 size보다 더 작은 경우,
좌표가 음수가 나올 수 있다. (좌표는 음수가 되어서는 안된다. (0,0) 부터 (n,n) 까지니까.

그래서

int nx = ((현재 index + delta)% size + size ) % size로 구현하면된다. -> 음수값이 발생할 수 있는 구간이면 % size 또는 + size ) % size를 통해서 양수로 올려주는 작업이 필요함.

magic_shark_fireball에서도 

        int nx = ((f.r + dx[f.d] * (f.s % N)) % N + N) % N;
        int ny = ((f.c + dy[f.d] * (f.s % N)) % N + N) % N;

이렇게 되는 이유가, f.s가 만약에 N 크기보다 더 커버리면 음수로 바로 진입할 가능성이 있음. 
(보통은 문제에서 제한을 걸지만, 해당 문제보면 s가 1000이라서 direction이 음수라면 순식간에 좌표 이탈함)
따라서 % N을 통해서 값을 정리해줘야 안정적으로 맵 안에 위치 할 수 있음. 이후 % N이나, + N 등 작업을 통해 음수 좌표가 안 나오도록 정리

