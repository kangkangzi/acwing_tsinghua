#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N1 510    // 左部点数的最大值
#define MAX_N2 510    // 右部点数的最大值
#define MAX_M 100010  // 边数的最大值

// 定义邻接表节点
typedef struct AdjNode {
    int vertex;           // 右部点的编号
    struct AdjNode* next;
} AdjNode;

// 定义左部点的邻接表头节点
typedef struct {
    AdjNode* first;
} LeftNode;

LeftNode left_nodes[MAX_N1];  // 左部点的邻接表
int match[MAX_N2];            // 右部点匹配的左部点
int visited[MAX_N2];          // 记录右部点是否在当前轮次中被访问过
int n1, n2, m;                // n1:左部点数，n2:右部点数，m:边数

// 创建新的邻接表节点
AdjNode* create_adj_node(int vertex) {
    AdjNode* new_node = (AdjNode*)malloc(sizeof(AdjNode));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

// 添加边：从左部点left到右部点right
void add_edge(int left, int right) {
    AdjNode* new_node = create_adj_node(right);
    new_node->next = left_nodes[left].first;
    left_nodes[left].first = new_node;
}

// 寻找增广路径
int find(int x) {
    // 遍历x能到达的所有右部点
    AdjNode* current = left_nodes[x].first;
    while (current != NULL) {
        int right = current->vertex;
        
        // 如果这个右部点在本轮还未被访问
        if (!visited[right]) {
            visited[right] = 1;  // 标记为已访问
            
            // 如果right未被匹配，或者right当前的匹配点能找到新的匹配
            if (match[right] == 0 || find(match[right])) {
                match[right] = x;  // 更新匹配
                return 1;
            }
        }
        
        current = current->next;
    }
    
    return 0;  // 未找到增广路
}

// 求最大匹配
int hungarian() {
    int max_match = 0;
    memset(match, 0, sizeof(match));  // 初始时右部点都未匹配
    
    // 尝试为每个左部点寻找匹配
    for (int i = 1; i <= n1; i++) {
        memset(visited, 0, sizeof(visited));  // 重置访问标记
        if (find(i)) {
            max_match++;
        }
    }
    
    return max_match;
}

// 释放内存
void free_graph() {
    for (int i = 1; i <= n1; i++) {
        AdjNode* current = left_nodes[i].first;
        while (current != NULL) {
            AdjNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    scanf("%d %d %d", &n1, &n2, &m);
    
    // 初始化邻接表
    for (int i = 1; i <= n1; i++) {
        left_nodes[i].first = NULL;
    }
    
    // 读入边并构建邻接表
    for (int i = 0; i < m; i++) {
        int left, right;
        scanf("%d %d", &left, &right);
        add_edge(left, right);
    }
    
    // 计算并输出最大匹配数
    printf("%d\n", hungarian());
    
    // 释放内存
    free_graph();
    
    return 0;
}
