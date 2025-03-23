#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义栈的最大大小
#define MAX_M 100000

// 栈结构
typedef struct {
    long long* data;  // 使用long long以支持最大10^9的数据
    int top;         // 栈顶指针
} Stack;

// 初始化栈
void init_stack(Stack* stack, int size) {
    stack->data = (long long*)malloc(sizeof(long long) * size);
    stack->top = -1;  // 栈空时top为-1
}

// 入栈操作
void push(Stack* stack, long long x) {
    stack->data[++stack->top] = x;
}

// 出栈操作
void pop(Stack* stack) {
    stack->top--;
}

// 判断栈是否为空
int empty(Stack* stack) {
    return stack->top == -1;
}

// 查询栈顶元素
long long query(Stack* stack) {
    return stack->data[stack->top];
}

// 清理栈内存
void cleanup(Stack* stack) {
    free(stack->data);
}

int main() {
    int M;
    scanf("%d", &M);
    
    Stack stack;
    init_stack(&stack, M);
    
    char op[10];
    long long x;
    
    for (int i = 0; i < M; i++) {
        scanf("%s", op);
        if (strcmp(op, "push") == 0) {
            scanf("%lld", &x);
            push(&stack, x);
        }
        else if (strcmp(op, "pop") == 0) {
            pop(&stack);
        }
        else if (strcmp(op, "empty") == 0) {
            printf("%s\n", empty(&stack) ? "YES" : "NO");
        }
        else if (strcmp(op, "query") == 0) {
            printf("%lld\n", query(&stack));
        }
    }
    
    cleanup(&stack);
    return 0;
}
