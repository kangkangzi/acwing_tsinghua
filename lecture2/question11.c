#include <stdio.h>
#include <string.h>

#define N 100010

int p[N];  // 存储每个点的父节点

// 初始化并查集
void init(int n) {
    for (int i = 1; i <= n; i++) {
        p[i] = i;  // 初始时每个点的父节点是自己
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
        p[pa] = pb;  // 将a所在集合的根节点指向b所在集合的根节点
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    // 初始化并查集
    init(n);
    
    // 处理每个操作
    while (m--) {
        char op[2];
        int a, b;
        scanf("%s%d%d", op, &a, &b);
        
        if (op[0] == 'M') {  // 合并操作
            merge(a, b);
        } else {  // 查询操作
            if (find(a) == find(b)) {  // 如果两个点的根节点相同，说明在同一个集合中
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
    }
    
    return 0;
}
