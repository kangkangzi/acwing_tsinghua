#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 210
#define INF 0x3f3f3f3f

int length[MAX_N][MAX_N];    // 存储任意两点间的最短距离
int n, m, k;                // n:节点数，m:边数，k:询问数

// 初始化距离矩阵
void init() {
    // 初始化所有距离为无穷大
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                length[i][j] = 0;  // 自身到自身的距离为0
            } else {
                length[i][j] = INF;  // 其他距离初始化为无穷大
            }
        }
    }
}

// 添加边
void add_edge(int x, int y, int z) {
    // 处理重边，保留最短的边
    if (z < length[x][y]) {
        length[x][y] = z;
    }
}

// Floyd算法求任意两点间的最短路径
void floyd() {
    // 三重循环实现Floyd算法
    for (int k = 1; k <= n; k++) {           // 中间节点
        for (int i = 1; i <= n; i++) {       // 起点
            for (int j = 1; j <= n; j++) {   // 终点
                // 如果经过k的路径更短，则更新
                if (length[i][k] != INF && length[k][j] != INF) {
                    if (length[i][j] > length[i][k] + length[k][j]) {
                        length[i][j] = length[i][k] + length[k][j];
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    // 初始化距离矩阵
    init();
    
    // 读入边并构建距离矩阵
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add_edge(x, y, z);
    }
    
    // 使用Floyd算法计算任意两点间的最短路径
    floyd();
    
    // 处理k个询问
    for (int i = 0; i < k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        
        // 输出结果
        if (length[x][y] == INF) {
            printf("impossible\n");
        } else {
            printf("%d\n", length[x][y]);
        }
    }
    
    return 0;
}
