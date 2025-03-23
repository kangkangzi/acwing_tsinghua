#include <stdio.h>

#define MAX_N 8  // 因为题目范围是1≤n≤7，所以设置MAX_N为8

int n;              // 输入的n
int visited[MAX_N]; // 访问标记数组
int stack[MAX_N];   // 模拟栈
int top = -1;       // 栈顶指针

// 打印当前排列
void print_permutation() {
    for (int i = 0; i <= top; i++) {
        printf("%d", stack[i]);
        if (i < top) printf(" ");
    }
    printf("\n");
}

// 深度优先搜索函数
void dfs() {
    // 如果栈中元素个数等于n，说明找到一个排列
    if (top == n - 1) {
        print_permutation();
        return;
    }
    
    // 遍历所有可能的数字
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            // 将当前数字压入栈
            stack[++top] = i;
            visited[i] = 1;
            
            // 递归搜索
            dfs();
            
            // 回溯
            visited[i] = 0;
            top--;
        }
    }
}

int main() {
    scanf("%d", &n);
    
    // 初始化visited数组
    for (int i = 1; i <= n; i++) {
        visited[i] = 0;
    }
    
    // 开始深度优先搜索
    dfs();
    
    return 0;
}
