#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100005

// 队列结构体
typedef struct {
    long long data[MAX_SIZE];  // 存储数据的数组
    int head;                  // 队头指针
    int tail;                  // 队尾指针
} Queue;

// 初始化队列
void init_queue(Queue* q) {
    q->head = 0;
    q->tail = 0;
}

// 判断队列是否为空
int is_empty(Queue* q) {
    return q->head == q->tail;
}

// 入队操作
void push(Queue* q, long long x) {
    q->data[q->tail] = x;
    q->tail++;
}

// 出队操作
void pop(Queue* q) {
    q->head++;
}

// 查询队头元素
long long query(Queue* q) {
    return q->data[q->head];
}

int main() {
    int M;
    scanf("%d", &M);
    
    Queue q;
    init_queue(&q);
    
    char op[10];
    long long x;
    
    for (int i = 0; i < M; i++) {
        scanf("%s", op);
        if (strcmp(op, "push") == 0) {
            scanf("%lld", &x);
            push(&q, x);
        }
        else if (strcmp(op, "pop") == 0) {
            pop(&q);
        }
        else if (strcmp(op, "empty") == 0) {
            printf("%s\n", is_empty(&q) ? "YES" : "NO");
        }
        else if (strcmp(op, "query") == 0) {
            printf("%lld\n", query(&q));
        }
    }
    
    return 0;
}
