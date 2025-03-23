#include <stdio.h>

#define MAX_N 10  // 因为题目范围是1≤n≤9，所以设置MAX_N为10

int n;                    // 输入的n
char board[MAX_N][MAX_N]; // 棋盘矩阵
int attack[MAX_N][MAX_N]; // 攻击范围标记矩阵

// 打印当前棋盘状态
void print_board() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 标记皇后的攻击范围
void mark_attack(int row, int col) {
    // 标记同一行
    for (int j = 0; j < n; j++) {
        attack[row][j]++;
    }
    
    // 标记同一列
    for (int i = 0; i < n; i++) {
        attack[i][col]++;
    }
    
    // 标记主对角线（左上到右下）
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        attack[i][j]++;
    }
    for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++) {
        attack[i][j]++;
    }
    
    // 标记副对角线（右上到左下）
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        attack[i][j]++;
    }
    for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--) {
        attack[i][j]++;
    }
}

// 取消标记皇后的攻击范围
void unmark_attack(int row, int col) {
    // 取消标记同一行
    for (int j = 0; j < n; j++) {
        attack[row][j]--;
    }
    
    // 取消标记同一列
    for (int i = 0; i < n; i++) {
        attack[i][col]--;
    }
    
    // 取消标记主对角线
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        attack[i][j]--;
    }
    for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++) {
        attack[i][j]--;
    }
    
    // 取消标记副对角线
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        attack[i][j]--;
    }
    for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--) {
        attack[i][j]--;
    }
}

// 深度优先搜索函数
void dfs(int depth) {
    // 如果已经放置了n个皇后，打印结果
    if (depth == n) {
        print_board();
        return;
    }
    
    // 在当前行尝试放置皇后
    for (int j = 0; j < n; j++) {
        if (attack[depth][j] == 0) {
            // 放置皇后
            board[depth][j] = 'Q';
            mark_attack(depth, j);
            
            // 递归搜索下一行
            dfs(depth + 1);
            
            // 回溯
            board[depth][j] = '.';
            unmark_attack(depth, j);
        }
    }
}

int main() {
    scanf("%d", &n);
    
    // 初始化棋盘和攻击矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = '.';
            attack[i][j] = 0;
        }
    }
    
    // 开始深度优先搜索
    dfs(0);
    
    return 0;
}
