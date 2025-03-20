#include <stdio.h>

// 合并两个有序数组
void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    // 处理剩余的元素
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    // 将临时数组中的元素复制回原数组
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

// 归并排序实现
void mergeSort(int arr[], int temp[], int left, int right) {
    if (left >= right) {
        return;
    }
    
    int mid = (left + right) >> 1;
    
    // 递归排序左右两半
    mergeSort(arr, temp, left, mid);
    mergeSort(arr, temp, mid + 1, right);
    
    // 合并两个有序数组
    merge(arr, temp, left, mid, right);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int arr[100000];  // 根据题目要求的范围
    int temp[100000]; // 归并排序所需的临时数组
    
    // 读入数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // 对数组进行排序
    mergeSort(arr, temp, 0, n - 1);
    
    // 输出排序后的数组
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
} 