#include <stdio.h>

// 查找目标值的左边界（第一次出现的位置）
int findLeft(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    
    while (left < right) {
        int mid = (left + right) >> 1;
        if (arr[mid] >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    // 检查是否找到了目标值
    if (arr[left] != target) {
        return -1;
    }
    return left;
}

// 查找目标值的右边界（最后一次出现的位置）
int findRight(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    
    while (left < right) {
        // 注意这里的 +1，避免死循环
        int mid = (left + right + 1) >> 1;
        if (arr[mid] <= target) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    
    // 检查是否找到了目标值
    if (arr[left] != target) {
        return -1;
    }
    return left;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    
    int arr[100000];  // 根据题目要求的范围
    
    // 读入有序数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // 处理每个查询
    while (q--) {
        int k;
        scanf("%d", &k);
        
        // 查找目标值的起始和终止位置
        int left = findLeft(arr, n, k);
        int right = findRight(arr, n, k);
        
        printf("%d %d\n", left, right);
    }
    
    return 0;
}
