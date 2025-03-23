#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100010
#define MAX_M 200010

// 定义边结构
typedef struct Edge {
    int start;      // 起点
    int terminal;   // 终点
    int weight;     // 权重
} Edge;

Edge edges[MAX_M];  // 边数组
int parent[MAX_N];  // 并查集父节点数组
int n, m;          // 节点数量和边数量

// 并查集查找函数（路径压缩）
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 比较函数，用于排序
int compare_edges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Kruskal算法
long long kruskal() {
    // 初始化并查集
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    
    // 按权重排序所有边
    qsort(edges, m, sizeof(Edge), compare_edges);
    
    long long total_weight = 0;  // 使用long long避免溢出
    int connected_edges = 0;     // 已连接的边数
    
    // 遍历所有边
    for (int i = 0; i < m && connected_edges < n - 1; i++) {
        int start_root = find(edges[i].start);
        int terminal_root = find(edges[i].terminal);
        
        // 如果两个顶点不在同一个集合中
        if (start_root != terminal_root) {
            // 合并两个集合
            parent[start_root] = terminal_root;
            total_weight += edges[i].weight;
            connected_edges++;
        }
    }
    
    // 检查是否所有节点都已连通
    if (connected_edges != n - 1) {
        return -1;  // 表示无法构成最小生成树
    }
    
    return total_weight;
}

int main() {
    scanf("%d %d", &n, &m);
    
    // 读入所有边
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].start, &edges[i].terminal, &edges[i].weight);
    }
    
    // 计算最小生成树
    long long result = kruskal();
    
    // 输出结果
    if (result == -1) {
        printf("impossible\n");
    } else {
        printf("%lld\n", result);
    }
    
    return 0;
}
