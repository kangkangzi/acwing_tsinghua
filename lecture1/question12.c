#include <stdio.h>

// 原始矩阵和前缀和矩阵的大小设为1010，多开10个空间避免边界问题
int matrix[1010][1010];      // 原始矩阵
long long pre_matrix[1010][1010];  // 前缀和矩阵，使用long long避免溢出
int n, m, q;

// 计算前缀和矩阵
void calculate_prefix() {
    // 第一个元素
    pre_matrix[0][0] = matrix[0][0];
    
    // 第一行
    for (int j = 1; j < m; j++) {
        pre_matrix[0][j] = pre_matrix[0][j-1] + matrix[0][j];
    }
    
    // 第一列
    for (int i = 1; i < n; i++) {
        pre_matrix[i][0] = pre_matrix[i-1][0] + matrix[i][0];
    }
    
    // 其余元素
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            pre_matrix[i][j] = pre_matrix[i-1][j] + pre_matrix[i][j-1] - 
                              pre_matrix[i-1][j-1] + matrix[i][j];
        }
    }
}

// 计算区域和，注意处理边界情况
long long get_sum(int x1, int y1, int x2, int y2) {
    // 将1-based索引转换为0-based
    x1--; y1--; x2--; y2--;
    
    // 计算区域和
    long long sum = pre_matrix[x2][y2];
    
    // 减去上方和左方的区域，加回重复减去的区域
    if (x1 > 0) sum -= pre_matrix[x1-1][y2];
    if (y1 > 0) sum -= pre_matrix[x2][y1-1];
    if (x1 > 0 && y1 > 0) sum += pre_matrix[x1-1][y1-1];
    
    return sum;
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
    
    // 计算前缀和矩阵
    calculate_prefix();
    
    // 处理查询
    while (q--) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        
        // 计算并输出查询结果
        printf("%lld\n", get_sum(x1, y1, x2, y2));
    }
    
    return 0;
}
