#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BITS 31  // Since 0 ≤ Ai < 2^31

// 定义字典树节点结构
typedef struct TrieNode {
    struct TrieNode* left;   // 0
    struct TrieNode* right;  // 1
} TrieNode;

// 创建新节点
TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 将数字插入字典树
void insert(TrieNode* root, int num) {
    TrieNode* current = root;
    
    // 从最高位开始插入
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (bit == 0) {
            if (current->left == NULL) {
                current->left = createNode();
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = createNode();
            }
            current = current->right;
        }
    }
}

// 在字典树中查找与给定数字异或的最大值
int findMaxXor(TrieNode* root, int num) {
    TrieNode* current = root;
    int result = 0;
    
    // 从最高位开始查找
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        
        // 尽量走相反的路径以获得最大异或值
        if (bit == 0) {
            if (current->right != NULL) {
                result |= (1 << i);
                current = current->right;
            } else {
                current = current->left;
            }
        } else {
            if (current->left != NULL) {
                result |= (1 << i);
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }
    return result;
}

// 释放字典树内存
void freeTrie(TrieNode* root) {
    if (root == NULL) {
        return;
    }
    freeTrie(root->left);
    freeTrie(root->right);
    free(root);
}

int main() {
    int N;
    scanf("%d", &N);

    // 创建字典树根节点
    TrieNode* root = createNode();
    
    int max_xor = 0;
    int num;
    
    // 读入第一个数并插入字典树
    scanf("%d", &num);
    insert(root, num);
    
    // 对于后续的每个数
    for (int i = 1; i < N; i++) {
        scanf("%d", &num);
        // 先查找当前数字能得到的最大异或值
        int current_max = findMaxXor(root, num);
        if (current_max > max_xor) {
            max_xor = current_max;
        }
        // 然后将当前数字插入字典树
        insert(root, num);
    }

    printf("%d\n", max_xor);

    // 释放内存
    freeTrie(root);
    return 0;
}
