#include <stdio.h>
#include <stdlib.h>

#define N 100010

// 堆中元素的结构体
typedef struct {
    int data;   // 数值
    int order;  // 插入顺序
} HeapNode;

HeapNode heap[N];     // 小顶堆数组
int heap_size = 0;    // 堆的当前大小
int* pos[N];         // 存储第i个插入元素在堆中的位置
int count = 0;       // 插入计数器

// 交换两个堆节点
void swap(HeapNode* a, HeapNode* b) {
    // 更新位置数组
    pos[a->order] = (int*)((long)pos[a->order] ^ (long)pos[b->order]);
    pos[b->order] = (int*)((long)pos[b->order] ^ (long)pos[a->order]);
    pos[a->order] = (int*)((long)pos[a->order] ^ (long)pos[b->order]);
    
    // 交换节点
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// 向上调整堆
void up(int p) {
    while (p > 1) {  // p = 1 是堆顶
        if (heap[p].data < heap[p/2].data) {  // 如果当前节点小于父节点
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
        // 如果右儿子存在且小于左儿子，s指向右儿子
        if (s + 1 <= heap_size && heap[s + 1].data < heap[s].data) {
            s++;
        }
        
        // 如果最小的儿子小于当前节点，交换
        if (heap[s].data < heap[p].data) {
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
    count++;  // 更新插入计数
    heap_size++;
    heap[heap_size].data = x;
    heap[heap_size].order = count;
    pos[count] = (int*)heap_size;  // 记录位置
    up(heap_size);  // 向上调整
}

// 删除堆顶元素
void delete_min() {
    pos[heap[1].order] = NULL;  // 标记已删除
    heap[1] = heap[heap_size];  // 将最后一个元素移到堆顶
    pos[heap[1].order] = (int*)1;  // 更新位置
    heap_size--;  // 堆大小减1
    down(1);  // 向下调整堆顶
}

// 删除第k个插入的数
void delete_kth(int k) {
    int p = (int)(long)pos[k];  // 获取第k个数的位置
    if (p == 0 || pos[k] == NULL) return;  // 如果已经被删除，直接返回
    
    pos[k] = NULL;  // 标记已删除
    heap[p] = heap[heap_size];  // 用最后一个元素替换
    pos[heap[p].order] = (int*)(long)p;  // 更新最后一个元素的位置
    heap_size--;
    
    up(p);    // 可能需要向上调整
    down(p);  // 可能需要向下调整
}

// 修改第k个插入的数
void change_kth(int k, int x) {
    int p = (int)(long)pos[k];  // 获取第k个数的位置
    if (p == 0 || pos[k] == NULL) return;  // 如果已经被删除，直接返回
    
    int old = heap[p].data;
    heap[p].data = x;
    
    if (x < old) {
        up(p);    // 如果新值更小，向上调整
    } else {
        down(p);  // 如果新值更大，向下调整
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    while (n--) {
        char op[3];
        scanf("%s", op);
        
        if (op[0] == 'I') {  // 插入操作
            int x;
            scanf("%d", &x);
            insert(x);
        } else if (op[0] == 'P') {  // 输出最小值
            printf("%d\n", heap[1].data);
        } else if (op[0] == 'D' && op[1] == 'M') {  // 删除最小值
            delete_min();
        } else if (op[0] == 'D') {  // 删除第k个插入的数
            int k;
            scanf("%d", &k);
            delete_kth(k);
        } else if (op[0] == 'C') {  // 修改第k个插入的数
            int k, x;
            scanf("%d%d", &k, &x);
            change_kth(k, x);
        }
    }
    
    return 0;
}
