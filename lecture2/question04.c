#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100005

// 运算符栈
typedef struct {
    char data[MAX_LEN];
    int top;
} OperatorStack;

// 数值栈
typedef struct {
    int data[MAX_LEN];
    int top;
} NumberStack;

// 初始化运算符栈
void init_operator_stack(OperatorStack* stack) {
    stack->top = -1;
}

// 初始化数值栈
void init_number_stack(NumberStack* stack) {
    stack->top = -1;
}

// 运算符栈的操作
void push_operator(OperatorStack* stack, char op) {
    stack->data[++stack->top] = op;
}

char pop_operator(OperatorStack* stack) {
    return stack->data[stack->top--];
}

char peek_operator(OperatorStack* stack) {
    return stack->data[stack->top];
}

int is_operator_empty(OperatorStack* stack) {
    return stack->top == -1;
}

// 数值栈的操作
void push_number(NumberStack* stack, int num) {
    stack->data[++stack->top] = num;
}

int pop_number(NumberStack* stack) {
    return stack->data[stack->top--];
}

// 获取运算符优先级
int get_priority(char op) {
    switch(op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '(': return 0;
        default: return -1;
    }
}

// 计算两个数的运算结果
int calculate(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

int evaluate_expression(char* expr) {
    OperatorStack op_stack;
    NumberStack num_stack;
    init_operator_stack(&op_stack);
    init_number_stack(&num_stack);
    
    int len = strlen(expr);
    int i = 0;
    
    while (i < len) {
        // 跳过空格
        if (expr[i] == ' ') {
            i++;
            continue;
        }
        
        // 处理数字
        if (expr[i] >= '0' && expr[i] <= '9') {
            int num = 0;
            while (i < len && expr[i] >= '0' && expr[i] <= '9') {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            push_number(&num_stack, num);
            continue;
        }
        
        // 处理右括号
        if (expr[i] == ')') {
            while (!is_operator_empty(&op_stack) && peek_operator(&op_stack) != '(') {
                char op = pop_operator(&op_stack);
                int b = pop_number(&num_stack);
                int a = pop_number(&num_stack);
                push_number(&num_stack, calculate(a, b, op));
            }
            if (!is_operator_empty(&op_stack)) {
                pop_operator(&op_stack);  // 弹出左括号
            }
            i++;
            continue;
        }
        
        // 处理其他运算符
        while (!is_operator_empty(&op_stack) && 
               expr[i] != '(' && 
               get_priority(peek_operator(&op_stack)) >= get_priority(expr[i])) {
            char op = pop_operator(&op_stack);
            int b = pop_number(&num_stack);
            int a = pop_number(&num_stack);
            push_number(&num_stack, calculate(a, b, op));
        }
        
        push_operator(&op_stack, expr[i]);
        i++;
    }
    
    // 处理剩余的运算符
    while (!is_operator_empty(&op_stack)) {
        char op = pop_operator(&op_stack);
        int b = pop_number(&num_stack);
        int a = pop_number(&num_stack);
        push_number(&num_stack, calculate(a, b, op));
    }
    
    return num_stack.data[0];
}

int main() {
    char expr[MAX_LEN];
    fgets(expr, MAX_LEN, stdin);
    
    // 去除输入中的换行符
    int len = strlen(expr);
    if (expr[len-1] == '\n') {
        expr[len-1] = '\0';
    }
    
    printf("%d\n", evaluate_expression(expr));
    return 0;
}
