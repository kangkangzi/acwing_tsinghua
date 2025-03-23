#include <stdio.h>
#include <stdlib.h>

#define N 100010

int heap[N];  // 大顶堆数组
int heap_size = 0;  // 堆的当前大小

// 交换两个元素
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 向上调整堆
void up(int p) {
    while (p > 1) {  // p = 1 是堆顶
        if (heap[p] > heap[p/2]) {  // 如果当前节点大于父节点
            swap(&heap[p], &heap[p/2]);  // 交换当前节点和父节点
            p = p/2;  // 继续向上调整
        } else {
            break;
        }
    }
}

// 向下调整堆
void down(int p) {
    int s = p * 2;  // s是左儿子
    while (s <= heap_size) {  // 当还有儿子时
        // 如果右儿子存在且大于左儿子，s指向右儿子
        if (s + 1 <= heap_size && heap[s + 1] > heap[s]) {
            s++;
        }
        
        // 如果最大的儿子大于当前节点，交换
        if (heap[s] > heap[p]) {
            swap(&heap[s], &heap[p]);
            p = s;  // 继续向下调整
            s = p * 2;
        } else {
            break;
        }
    }
}

// 插入元素
void insert(int x) {
    heap[++heap_size] = x;  // 将新元素插入到堆的末尾
    up(heap_size);  // 向上调整
}

// 删除堆顶元素
void delete_top() {
    heap[1] = heap[heap_size];  // 将最后一个元素移到堆顶
    heap_size--;  // 堆大小减1
    down(1);  // 向下调整堆顶
}

// 获取堆顶元素
int get_top() {
    return heap[1];
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    // 读入前m个数，建立初始堆
    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        insert(x);
    }
    
    // 处理剩余的数
    for (int i = m; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x < get_top()) {  // 如果当前数小于堆顶
            delete_top();  // 删除堆顶
            insert(x);     // 插入新数
        }
    }
    
    // 将堆中元素按从小到大顺序存入数组
    int result[N];
    int size = heap_size;
    for (int i = size - 1; i >= 0; i--) {
        result[i] = get_top();
        delete_top();
    }
    
    // 输出结果
    for (int i = 0; i < m; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    return 0;
}
