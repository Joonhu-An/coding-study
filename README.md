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