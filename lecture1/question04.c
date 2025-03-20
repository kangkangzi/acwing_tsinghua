#include <stdio.h>

// 合并两个有序数组并统计逆序对
long long merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    long long inv_count = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            // 当选择右边的数时，左边剩余的数都构成逆序对
            temp[k++] = arr[j++];
            inv_count += mid - i + 1;
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
    
    return inv_count;
}

// 归并排序实现，返回逆序对的数量
long long mergeSort(int arr[], int temp[], int left, int right) {
    long long inv_count = 0;
    
    if (left < right) {
        int mid = (left + right) >> 1;
        
        // 递归统计左右两半的逆序对
        inv_count += mergeSort(arr, temp, left, mid);
        inv_count += mergeSort(arr, temp, mid + 1, right);
        
        // 合并两个有序数组，并统计跨越中点的逆序对
        inv_count += merge(arr, temp, left, mid, right);
    }
    
    return inv_count;
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
    
    // 计算逆序对的数量
    long long result = mergeSort(arr, temp, 0, n - 1);
    
    // 输出逆序对的数量
    printf("%lld\n", result);
    
    return 0;
}
