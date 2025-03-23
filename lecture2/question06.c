#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

// 栈结构体
typedef struct {
    long long data[MAX_N];  // 存储数据的数组
    int top;               // 栈顶指针
} Stack;

// 初始化栈
void init_stack(Stack* s) {
    s->top = -1;
}

// 判断栈是否为空
int is_empty(Stack* s) {
    return s->top == -1;
}

// 获取栈顶元素
long long peek(Stack* s) {
    return s->data[s->top];
}

// 入栈操作
void push(Stack* s, long long x) {
    s->data[++s->top] = x;
}

// 出栈操作
void pop(Stack* s) {
    s->top--;
}

int main() {
    int n;
    scanf("%d", &n);
    
    long long a[MAX_N];    // 原始数组
    long long left[MAX_N]; // 存储每个数左边第一个比它小的数
    Stack s;
    
    // 读入数组
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    
    // 初始化栈
    init_stack(&s);
    
    // 处理第一个数
    left[0] = -1;
    push(&s, a[0]);
    
    // 处理剩余的数
    for (int i = 1; i < n; i++) {
        // 当栈不为空且栈顶元素大于等于当前数时，弹出栈顶
        while (!is_empty(&s) && peek(&s) >= a[i]) {
            pop(&s);
        }
        
        // 如果栈为空，说明左边没有比当前数小的数
        if (is_empty(&s)) {
            left[i] = -1;
        } else {
            // 栈顶元素就是左边第一个比当前数小的数
            left[i] = peek(&s);
        }
        
        // 将当前数入栈
        push(&s, a[i]);
    }
    
    // 输出结果
    for (int i = 0; i < n; i++) {
        printf("%lld", left[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
    
    return 0;
}
