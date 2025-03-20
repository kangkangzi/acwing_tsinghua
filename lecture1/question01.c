#include <stdio.h>

// 交换两个元素
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 快速排序实现
void quickSort(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }
    
    int i = left - 1;
    int j = right + 1;
    int pivot = arr[(left + right) >> 1];
    
    while (i < j) {
        do {
            i++;
        } while (arr[i] < pivot);
        
        do {
            j--;
        } while (arr[j] > pivot);
        
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    
    quickSort(arr, left, j);
    quickSort(arr, j + 1, right);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int arr[100000];  // 根据题目要求的范围
    
    // 读入数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // 对数组进行排序
    quickSort(arr, 0, n - 1);
    
    // 输出排序后的数组
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}
