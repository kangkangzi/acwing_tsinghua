#include <stdio.h>
#include <string.h>

#define N 100010

int p[N];    // 存储每个点的父节点
int size[N]; // 存储每个连通块中点的数量，只有根节点的size有意义

// 初始化并查集
void init(int n) {
    for (int i = 1; i <= n; i++) {
        p[i] = i;      // 初始时每个点的父节点是自己
        size[i] = 1;   // 初始时每个连通块只有一个点
    }
}

// 查找点x所在集合的根节点，同时进行路径压缩
int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);  // 路径压缩
    }
    return p[x];
}

// 合并两个集合
void merge(int a, int b) {
    // 先找到两个集合的根节点
    int pa = find(a);
    int pb = find(b);
    if (pa != pb) {  // 如果不在同一个集合中，才需要合并
        // 将pa所在集合合并到pb中，同时更新pb的size
        size[pb] += size[pa];  // pb的大小增加pa的大小
        p[pa] = pb;           // 将pa指向pb
    }
}

// 查询点x所在连通块中点的数量
int query_size(int x) {
    int root = find(x);  // 找到x的根节点
    return size[root];   // 返回根节点记录的size
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    // 初始化并查集
    init(n);
    
    // 处理每个操作
    while (m--) {
        char op[3];
        int a, b;
        scanf("%s", op);
        
        if (op[0] == 'C') {  // 连接操作
            scanf("%d%d", &a, &b);
            merge(a, b);
        } else if (op[1] == '1') {  // Q1操作：询问是否连通
            scanf("%d%d", &a, &b);
            if (find(a) == find(b)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        } else {  // Q2操作：询问连通块大小
            scanf("%d", &a);
            printf("%d\n", query_size(a));
        }
    }
    
    return 0;
}
