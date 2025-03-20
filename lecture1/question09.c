#include <stdio.h>
#include <string.h>

// 将字符串逆序存储到数组中，返回数组的有效长度
int readNumber(int arr[]) {
    char str[100010];  // 多开10个字符的空间，避免意外
    scanf("%s", str);
    
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        // 从个位开始存储，方便计算
        arr[i] = str[len - 1 - i] - '0';
    }
    
    return len;
}

// 高精度乘法，计算大数a乘以普通整数b
int multiply(int a[], int len_a, int b, int c[]) {
    if (b == 0) {
        c[0] = 0;
        return 1;
    }
    
    // 从低位到高位逐位相乘
    int len_c = 0;
    long long carry = 0;  // 使用long long避免进位时溢出
    
    // 先计算每一位的乘积
    for (int i = 0; i < len_a; i++) {
        // 当前位的结果等于对应位的乘积加上进位
        long long product = (long long)a[i] * b + carry;
        c[len_c++] = product % 10;  // 当前位的结果
        carry = product / 10;       // 新的进位
    }
    
    // 处理最后的进位，可能有多位
    while (carry) {
        c[len_c++] = carry % 10;
        carry /= 10;
    }
    
    return len_c;
}

int main() {
    int a[100010] = {0};  // 大整数A
    int b;                // 整数B
    int c[200020] = {0};  // 存储结果，可能长度翻倍
    
    // 读入两个数
    int len_a = readNumber(a);
    scanf("%d", &b);
    
    // 计算乘积
    int len_c = multiply(a, len_a, b, c);
    
    // 从高位到低位输出结果
    for (int i = len_c - 1; i >= 0; i--) {
        printf("%d", c[i]);
    }
    printf("\n");
    
    return 0;
}
