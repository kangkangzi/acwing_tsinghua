#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50010

int parent[MAX_N * 3];  // 使用一维数组表示所有关系
int n, k;

// 初始化并查集
void init() {
    for (int i = 0; i < 3 * n; i++) {
        parent[i] = i;
    }
}

// 查找集合的根节点（带路径压缩）
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 合并两个集合
void union_sets(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x != root_y) {
        parent[root_x] = root_y;
    }
}

// 判断两个元素是否在同一个集合
int is_same_set(int x, int y) {
    return find(x) == find(y);
}

// 检查和更新同类关系
int check_same_type(int x, int y) {
    // 检查是否存在矛盾
    if (is_same_set(x, y + n) || is_same_set(x, y + 2 * n)) {
        return 0;  // 矛盾：已经是捕食关系
    }
    
    // 合并三个对应的集合
    union_sets(x, y);                  // 合并自身
    union_sets(x + n, y + n);          // 合并猎物
    union_sets(x + 2 * n, y + 2 * n);  // 合并天敌
    
    return 1;  // 无矛盾
}

// 检查和更新捕食关系
int check_eat_relation(int x, int y) {
    // 检查是否存在矛盾
    if (is_same_set(x, y) || is_same_set(x + 2 * n, y)) {
        return 0;  // 矛盾：已经是同类或被捕食
    }
    
    // 合并对应的集合
    union_sets(x + n, y);              // x的猎物集合与y合并
    union_sets(x, y + 2 * n);          // x与y的天敌集合合并
    union_sets(x + 2 * n, y + n);      // x的天敌集合与y的猎物集合合并
    
    return 1;  // 无矛盾
}

// 处理一条陈述
int process_statement(int d, int x, int y) {
    // test2: 检查数据范围
    if (x > n || y > n || x < 1 || y < 1) {  // 添加了对下界的检查
        return 0;  // 假话
    }
    
    // 将编号转换为0基数
    x--;
    y--;
    
    // test3: 检查自我捕食
    if (d == 2 && x == y) {
        return 0;  // 假话
    }
    
    // test1: 检查关系矛盾
    if (d == 1) {
        return check_same_type(x, y);
    } else {
        return check_eat_relation(x, y);
    }
}

int main() {
    scanf("%d %d", &n, &k);
    
    // 初始化
    init();
    
    int false_count = 0;
    // 处理每条陈述
    for (int i = 0; i < k; i++) {
        int d, x, y;
        scanf("%d %d %d", &d, &x, &y);
        
        // 如果是假话，计数加一
        if (!process_statement(d, x, y)) {
            false_count++;
        }
    }
    
    printf("%d\n", false_count);
    
    return 0;
}
