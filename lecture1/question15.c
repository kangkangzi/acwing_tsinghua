#include <stdio.h>

// 数组大小设为100010，多开10个空间避免边界问题
int arr[100010];        // 原始数组
int hash[100010];       // 哈希表，记录每个数字出现的次数
int n;
int count = 0;          // 哈希表中不同元素的个数
int global_length = 0;  // 全局最长长度

// 增加一个元素到哈希表中
void add_element(int x) {
    hash[x]++;
    // 如果这个数之前没出现过，增加count
    if (hash[x] == 1) {
        count++;
    }
}

// 从哈希表中删除一个元素
void remove_element(int x) {
    hash[x]--;
    // 如果这个数的计数变为0，减少count
    if (hash[x] == 0) {
        count--;
    }
}

int main() {
    // 读入n
    scanf("%d", &n);
    
    // 读入数组
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // 双指针算法
    int left = 0, right = 0;
    int current_length = 0;  // 当前区间长度
    
    while (right < n) {
        // 增加右指针指向的元素
        add_element(arr[right]);
        
        // 如果当前元素导致重复，移动左指针直到不重复
        while (hash[arr[right]] > 1) {
            remove_element(arr[left]);
            left++;
        }
        
        // 更新当前区间长度和全局最长长度
        current_length = right - left + 1;
        if (current_length > global_length) {
            global_length = current_length;
        }
        
        right++;
    }
    
    // 输出结果
    printf("%d\n", global_length);
    
    return 0;
}
