#include <stdio.h>

// 原始矩阵和差分矩阵的大小设为1010，多开10个空间避免边界问题
int matrix[1010][1010];     // 原始矩阵
int diff_matrix[1010][1010]; // 差分矩阵
int n, m, q;

// 计算差分矩阵
void calculate_diff() {
    // 第一个元素
    diff_matrix[0][0] = matrix[0][0];
    
    // 第一行
    for (int j = 1; j < m; j++) {
        diff_matrix[0][j] = matrix[0][j] - matrix[0][j-1];
    }
    
    // 第一列
    for (int i = 1; i < n; i++) {
        diff_matrix[i][0] = matrix[i][0] - matrix[i-1][0];
    }
    
    // 其余元素
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            diff_matrix[i][j] = matrix[i][j] - matrix[i][j-1] - matrix[i-1][j] + matrix[i-1][j-1];
        }
    }
}

// 根据差分矩阵重建原始矩阵
void rebuild_matrix() {
    // 第一个元素
    matrix[0][0] = diff_matrix[0][0];
    
    // 第一行
    for (int j = 1; j < m; j++) {
        matrix[0][j] = matrix[0][j-1] + diff_matrix[0][j];
    }
    
    // 第一列
    for (int i = 1; i < n; i++) {
        matrix[i][0] = matrix[i-1][0] + diff_matrix[i][0];
    }
    
    // 其余元素
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            matrix[i][j] = matrix[i-1][j] + matrix[i][j-1] - matrix[i-1][j-1] + diff_matrix[i][j];
        }
    }
}

int main() {
    // 读入n, m, q
    scanf("%d %d %d", &n, &m, &q);
    
    // 读入原始矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    // 计算初始的差分矩阵
    calculate_diff();
    
    // 处理每个操作
    while (q--) {
        int x1, y1, x2, y2, c;
        scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &c);
        
        // 将1-based索引转换为0-based
        x1--; y1--; x2--; y2--;
        
        // 在差分矩阵中进行修改
        diff_matrix[x1][y1] += c;
        if (x2 + 1 < n && y2 + 1 < m) diff_matrix[x2+1][y2+1] += c;
        if (x2 + 1 < n) diff_matrix[x2+1][y1] -= c;
        if (y2 + 1 < m) diff_matrix[x1][y2+1] -= c;
    }
    
    // 重建矩阵
    rebuild_matrix();
    
    // 输出最终矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
