#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000005

// 单调队列结构体
typedef struct {
    int data[MAX_N];  // 存储元素下标
    int head;         // 队头指针
    int tail;         // 队尾指针
} MonoQueue;

// 初始化队列
void init_queue(MonoQueue* q) {
    q->head = 0;
    q->tail = 0;
}

// 判断队列是否为空
int is_empty(MonoQueue* q) {
    return q->head == q->tail;
}

// 获取队头元素下标
int get_front(MonoQueue* q) {
    return q->data[q->head];
}

// 获取队尾元素下标
int get_back(MonoQueue* q) {
    return q->data[q->tail - 1];
}

// 从队尾删除元素
void pop_back(MonoQueue* q) {
    if (!is_empty(q)) {
        q->tail--;
    }
}

// 从队头删除元素
void pop_front(MonoQueue* q) {
    if (!is_empty(q)) {
        q->head++;
    }
}

// 将元素下标加入队尾
void push_back(MonoQueue* q, int index) {
    q->data[q->tail++] = index;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    int arr[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    MonoQueue min_q, max_q;
    init_queue(&min_q);
    init_queue(&max_q);
    
    // 处理第一个窗口
    for (int i = 0; i < k; i++) {
        // 维护最小值队列
        while (!is_empty(&min_q) && arr[get_back(&min_q)] > arr[i]) {
            pop_back(&min_q);
        }
        push_back(&min_q, i);
        
        // 维护最大值队列
        while (!is_empty(&max_q) && arr[get_back(&max_q)] < arr[i]) {
            pop_back(&max_q);
        }
        push_back(&max_q, i);
    }
    
    // 输出第一个窗口的结果
    printf("%d", arr[get_front(&min_q)]);
    
    // 处理后续窗口
    for (int i = k; i < n; i++) {
        // 检查最小值队列队头是否需要移除
        if (!is_empty(&min_q) && get_front(&min_q) <= i - k) {
            pop_front(&min_q);
        }
        
        // 检查最大值队列队头是否需要移除
        if (!is_empty(&max_q) && get_front(&max_q) <= i - k) {
            pop_front(&max_q);
        }
        
        // 维护最小值队列
        while (!is_empty(&min_q) && arr[get_back(&min_q)] > arr[i]) {
            pop_back(&min_q);
        }
        push_back(&min_q, i);
        
        // 维护最大值队列
        while (!is_empty(&max_q) && arr[get_back(&max_q)] < arr[i]) {
            pop_back(&max_q);
        }
        push_back(&max_q, i);
        
        printf(" %d", arr[get_front(&min_q)]);
    }
    printf("\n");
    
    // 重置队列指针以输出最大值
    init_queue(&min_q);
    init_queue(&max_q);
    
    // 处理第一个窗口的最大值
    for (int i = 0; i < k; i++) {
        while (!is_empty(&max_q) && arr[get_back(&max_q)] < arr[i]) {
            pop_back(&max_q);
        }
        push_back(&max_q, i);
    }
    
    // 输出第一个窗口的最大值
    printf("%d", arr[get_front(&max_q)]);
    
    // 处理后续窗口的最大值
    for (int i = k; i < n; i++) {
        if (!is_empty(&max_q) && get_front(&max_q) <= i - k) {
            pop_front(&max_q);
        }
        
        while (!is_empty(&max_q) && arr[get_back(&max_q)] < arr[i]) {
            pop_back(&max_q);
        }
        push_back(&max_q, i);
        
        printf(" %d", arr[get_front(&max_q)]);
    }
    printf("\n");
    
    return 0;
}
