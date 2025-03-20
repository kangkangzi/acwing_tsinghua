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

int main() {
    int a[100010] = {0};  // 第一个数
    int b[100010] = {0};  // 第二个数
    int c[100010] = {0};  // 存储结果
    
    // 读入两个数
    int len_a = readNumber(a);
    int len_b = readNumber(b);
    
    // 从低位到高位逐位相加
    int carry = 0;  // 进位
    int len_c = 0;  // 结果的长度
    
    // 取较长的数字的长度作为循环次数
    int max_len = len_a > len_b ? len_a : len_b;
    
    for (int i = 0; i < max_len || carry; i++) {
        // 当前位的和等于两个数对应位的数字加上进位
        int sum = a[i] + b[i] + carry;
        c[len_c++] = sum % 10;  // 当前位的结果
        carry = sum / 10;       // 新的进位
    }
    
    // 从高位到低位输出结果
    for (int i = len_c - 1; i >= 0; i--) {
        printf("%d", c[i]);
    }
    printf("\n");
    
    return 0;
}
