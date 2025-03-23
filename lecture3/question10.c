#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 510
#define INF 0x3f3f3f3f

int cost[MAX_N][MAX_N];      // 邻接矩阵，存储边的权重
int current_cost[MAX_N];     // 当前轮次到达每个点的最小代价
int temp_cost[MAX_N];        // 临时数组，用于存储下一轮次的代价
int n, m, k;                 // n:节点数，m:边数，k:最大边数

// 初始化邻接矩阵
void init() {
    // 初始化所有边为不可达
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                cost[i][j] = 0;  // 自身到自身的距离为0
            } else {
                cost[i][j] = INF;  // 其他边初始化为无穷大
            }
        }
    }
}

// 添加边
void add_edge(int x, int y, int z) {
    // 处理重边，保留最短的边
    if (z < cost[x][y]) {
        cost[x][y] = z;
    }
}

// 计算最多经过k条边的最短路径
int bellman_ford() {
    // 初始化current_cost数组
    for (int i = 1; i <= n; i++) {
        current_cost[i] = cost[1][i];
    }
    
    // 进行k次迭代
    for (int step = 1; step < k; step++) {
        // 初始化临时数组
        for (int i = 1; i <= n; i++) {
            temp_cost[i] = current_cost[i];
        }
        
        // 遍历所有点对
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // 如果从1到i可达，且从i到j有边
                if (current_cost[i] != INF && cost[i][j] != INF) {
                    // 计算新的路径长度
                    int new_cost = current_cost[i] + cost[i][j];
                    // 更新临时数组中的值
                    if (new_cost < temp_cost[j]) {
                        temp_cost[j] = new_cost;
                    }
                }
            }
        }
        
        // 更新current_cost数组
        for (int i = 1; i <= n; i++) {
            current_cost[i] = temp_cost[i];
        }
    }
    
    // 返回到达n号点的最短距离
    return current_cost[n];
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    // 初始化邻接矩阵
    init();
    
    // 读入边并构建邻接矩阵
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add_edge(x, y, z);
    }
    
    // 计算最短路径
    int result = bellman_ford();
    
    // 输出结果
    if (result == INF) {
        printf("impossible\n");
    } else {
        printf("%d\n", result);
    }
    
    return 0;
}

