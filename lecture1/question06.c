#include <stdio.h>
#include <math.h>

// 计算 x³ - n
double f(double x, double n) {
    return x * x * x - n;
}

// 二分查找三次方根
double findCubeRoot(double n) {
    double left, right;
    
    // 确定初始区间
    if (n >= 0) {
        left = 0;
        right = fmax(1, n);  // 如果n<1，右边界取1；否则取n
    } else {
        right = 0;
        left = fmin(-1, n);  // 如果n>-1，左边界取-1；否则取n
    }
    
    // 当区间长度大于精度要求时继续二分
    while (right - left > 1e-8) {
        double mid = (left + right) / 2;
        double fmid = f(mid, n);
        
        if (fmid == 0) {
            return mid;
        } else if (fmid < 0) {
            left = mid;
        } else {
            right = mid;
        }
    }
    
    // 返回左右边界的中点
    return (left + right) / 2;
}

int main() {
    double n;
    scanf("%lf", &n);
    
    double result = findCubeRoot(n);
    
    // 按照题目要求输出6位小数
    printf("%.6f\n", result);
    
    return 0;
}