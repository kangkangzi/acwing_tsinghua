#include <stdio.h>

// 交换两个元素
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 向下调整堆
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// 构建大根堆
void buildHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

// 获取第k小的元素
int findKthSmallest(int arr[], int n, int k) {
    // 如果k大于数组长度，返回-1表示错误
    if (k > n) return -1;
    
    // 创建一个大小为k的堆
    int heap[k];
    
    // 将前k个元素放入堆中
    for (int i = 0; i < k; i++) {
        heap[i] = arr[i];
    }
    
    // 构建大根堆
    buildHeap(heap, k);
    
    // 处理剩余的元素
    for (int i = k; i < n; i++) {
        // 如果当前元素小于堆顶元素
        if (arr[i] < heap[0]) {
            // 替换堆顶元素并重新调整堆
            heap[0] = arr[i];
            heapify(heap, k, 0);
        }
    }
    
    // 返回堆顶元素，即第k小的元素
    return heap[0];
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    int arr[100000];  // 根据题目要求的范围
    
    // 读入数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // 找到第k小的元素并输出
    int result = findKthSmallest(arr, n, k);
    printf("%d\n", result);
    
    return 0;
}
