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

// 比较两个大数的大小
// 返回值：若a>b返回1，a=b返回0，a<b返回-1
int compare(int a[], int len_a, int b[], int len_b) {
    if (len_a != len_b) {
        return len_a > len_b ? 1 : -1;
    }
    
    // 从高位开始比较
    for (int i = len_a - 1; i >= 0; i--) {
        if (a[i] != b[i]) {
            return a[i] > b[i] ? 1 : -1;
        }
    }
    
    return 0;  // 两数相等
}

// 高精度减法，计算a-b的结果存入c，返回结果的长度
int subtract(int a[], int len_a, int b[], int len_b, int c[]) {
    int len_c = 0;
    int borrow = 0;  // 借位
    
    for (int i = 0; i < len_a; i++) {
        // 当前位的差等于被减数减去减数再减去借位
        int diff = a[i] - borrow;
        if (i < len_b) diff -= b[i];
        
        // 处理借位
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        c[len_c++] = diff;
    }
    
    // 去掉前导零
    while (len_c > 1 && c[len_c - 1] == 0) {
        len_c--;
    }
    
    return len_c;
}

int main() {
    int a[100010] = {0};  // 第一个数
    int b[100010] = {0};  // 第二个数
    int c[100010] = {0};  // 存储结果
    
    // 读入两个数
    int len_a = readNumber(a);
    int len_b = readNumber(b);
    
    // 比较两个数的大小
    int cmp = compare(a, len_a, b, len_b);
    
    // 计算结果
    int len_c;
    if (cmp >= 0) {
        // 如果a>=b，直接计算a-b
        len_c = subtract(a, len_a, b, len_b, c);
    } else {
        // 如果a<b，计算b-a，并在最后加上负号
        len_c = subtract(b, len_b, a, len_a, c);
        printf("-");
    }
    
    // 从高位到低位输出结果
    for (int i = len_c - 1; i >= 0; i--) {
        printf("%d", c[i]);
    }
    printf("\n");
    
    return 0;
}