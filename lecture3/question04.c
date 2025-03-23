#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STATES 362880  // 9! = 362880，所有可能的状态数

// 定义状态结构体
typedef struct {
    char board[3][3];  // 3x3的棋盘
} Status;

// 定义字典树节点
typedef struct TrieNode {
    struct TrieNode* children[9];  // 9个分支，对应0-8
    int is_end;                    // 是否是结束节点
} TrieNode;

// 创建新的字典树节点
TrieNode* create_node() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    for (int i = 0; i < 9; i++) {
        node->children[i] = NULL;
    }
    node->is_end = 0;
    return node;
}

// 将棋盘状态转换为一维数组
void board_to_array(Status status, int arr[9]) {
    int idx = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arr[idx++] = status.board[i][j] == 'x' ? 0 : status.board[i][j] - '0';
        }
    }
}

// 在字典树中插入状态
void insert_status(TrieNode* root, Status status) {
    int arr[9];
    board_to_array(status, arr);
    
    TrieNode* current = root;
    for (int i = 0; i < 9; i++) {
        int index = arr[i];
        if (current->children[index] == NULL) {
            current->children[index] = create_node();
        }
        current = current->children[index];
    }
    current->is_end = 1;
}

// 在字典树中查找状态
int find_status(TrieNode* root, Status status) {
    int arr[9];
    board_to_array(status, arr);
    
    TrieNode* current = root;
    for (int i = 0; i < 9; i++) {
        int index = arr[i];
        if (current->children[index] == NULL) {
            return 0;
        }
        current = current->children[index];
    }
    return current->is_end;
}

// 释放字典树内存
void free_trie(TrieNode* root) {
    if (root == NULL) return;
    for (int i = 0; i < 9; i++) {
        free_trie(root->children[i]);
    }
    free(root);
}

// 定义队列节点结构体
typedef struct {
    Status status;     // 状态
    int steps;        // 到达该状态的步数
} QueueNode;

// 定义队列结构
typedef struct {
    QueueNode data[362880];  // 9! = 362880，所有可能的状态数
    int front;
    int rear;
} Queue;

// 目标状态
const Status TARGET = {
    {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', 'x'}
    }
};

Queue queue;  // 队列
TrieNode* visited_trie;  // 访问标记字典树

// 初始化队列
void init_queue() {
    queue.front = queue.rear = 0;
}

// 入队
void enqueue(Status status, int steps) {
    queue.data[queue.rear].status = status;
    queue.data[queue.rear].steps = steps;
    queue.rear++;
}

// 出队
QueueNode dequeue() {
    return queue.data[queue.front++];
}

// 判断队列是否为空
int is_empty() {
    return queue.front == queue.rear;
}

// 计算阶乘
int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// 计算状态的哈希值（使用康托展开）
int hash_status(Status status) {
    int hash = 0;
    int nums[9];
    int count = 0;
    
    // 将棋盘转换为一维数组
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            nums[count++] = status.board[i][j] == 'x' ? 0 : status.board[i][j] - '0';
        }
    }
    
    // 计算康托展开
    for (int i = 0; i < 9; i++) {
        int count = 0;
        for (int j = i + 1; j < 9; j++) {
            if (nums[j] < nums[i]) count++;
        }
        hash += count * factorial(8 - i);
    }
    
    return hash;
}

// 判断状态是否相等
int is_equal(Status a, Status b) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a.board[i][j] != b.board[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// 找到x的位置
void find_x(Status status, int* x, int* y) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (status.board[i][j] == 'x') {
                *x = i;
                *y = j;
                return;
            }
        }
    }
}

// 交换两个位置
void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// 广度优先搜索
int bfs(Status start) {
    // 初始化队列和字典树
    init_queue();
    visited_trie = create_node();
    
    // 将初始状态加入队列
    enqueue(start, 0);
    insert_status(visited_trie, start);
    
    // 定义四个方向：上、下、左、右
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    while (!is_empty()) {
        QueueNode current = dequeue();
        
        // 如果到达目标状态
        if (is_equal(current.status, TARGET)) {
            free_trie(visited_trie);
            return current.steps;
        }
        
        // 找到x的位置
        int x, y;
        find_x(current.status, &x, &y);
        
        // 尝试四个方向
        for (int i = 0; i < 4; i++) {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            
            // 检查新位置是否有效
            if (new_x >= 0 && new_x < 3 && new_y >= 0 && new_y < 3) {
                // 创建新状态
                Status new_status = current.status;
                swap(&new_status.board[x][y], &new_status.board[new_x][new_y]);
                
                // 如果新状态未访问过
                if (!find_status(visited_trie, new_status)) {
                    insert_status(visited_trie, new_status);
                    enqueue(new_status, current.steps + 1);
                }
            }
        }
    }
    
    free_trie(visited_trie);
    return -1;  // 没有找到解决方案
}

int main() {
    // 读入初始状态
    Status start;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf(" %c", &start.board[i][j]);
        }
    }
    
    // 计算最少移动次数
    int result = bfs(start);
    
    // 输出结果
    printf("%d\n", result);
    
    return 0;
}

