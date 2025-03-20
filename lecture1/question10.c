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

// 判断当前位置是否可以减去除数
// cur[]是当前要参与比较的数字，pos是当前数字的长度，b是除数
int divide_valid(int cur[], int pos, int b) {
    // 将cur[]转换为实际数字进行比较
    long long num = 0;
    for (int i = pos - 1; i >= 0; i--) {
        num = num * 10 + cur[i];
    }
    return num >= b;
}

// 执行减法操作，返回商
// cur[]是被除数的一部分，pos是当前处理的位数，b是除数
int do_subtract(int cur[], int pos, int b) {
    int count = 0;  // 记录可以减去多少次
    
    // 当可以继续减时，进行减法操作
    while (divide_valid(cur, pos, b)) {
        // 执行减法
        long long num = 0;
        for (int i = pos - 1; i >= 0; i--) {
            num = num * 10 + cur[i];
        }
        
        // 计算减法后的结果
        num -= b;
        count++;
        
        // 将结果写回数组
        for (int i = 0; i < pos; i++) {
            cur[i] = num % 10;
            num /= 10;
        }
    }
    
    return count;
}

int main() {
    int a[100010] = {0};  // 被除数A
    int b;                // 除数B
    int quotient[100010] = {0};  // 存储商
    int len_q = 0;  // 商的长度
    
    // 读入两个数
    int len_a = readNumber(a);
    scanf("%d", &b);
    
    // 临时数组，用于存储当前要处理的数字
    int cur[100010] = {0};
    int cur_len = 0;
    
    // 从高位开始处理
    for (int i = len_a - 1; i >= 0; i--) {
        // 将当前数字加入临时数组
        for (int j = cur_len; j > 0; j--) {
            cur[j] = cur[j-1];
        }
        cur[0] = a[i];
        cur_len++;
        
        // 计算当前位的商
        quotient[i] = do_subtract(cur, cur_len, b);
        
        // 更新cur_len（去掉前导零）
        while (cur_len > 1 && cur[cur_len-1] == 0) {
            cur_len--;
        }
    }
    
    // 找到商的第一个非零位
    int start = len_a - 1;
    while (start > 0 && quotient[start] == 0) {
        start--;
    }
    
    // 输出商
    for (int i = start; i >= 0; i--) {
        printf("%d", quotient[i]);
    }
    printf("\n");
    
    // 输出余数（cur数组中剩余的数）
    long long remainder = 0;
    for (int i = cur_len - 1; i >= 0; i--) {
        remainder = remainder * 10 + cur[i];
    }
    printf("%lld\n", remainder);
    
    return 0;
}
