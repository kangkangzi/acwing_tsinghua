#include <stdio.h>

#define MAX_N 101  // 因为题目范围是1≤n,m≤100，所以设置MAX_N为101

// 定义节点结构体
typedef struct {
    int x;
    int y;
} Node;

// 定义队列结构
typedef struct {
    Node data[MAX_N * MAX_N];  // 队列数据
    int front;                 // 队首指针
    int rear;                  // 队尾指针
} Queue;

int n, m;                      // 迷宫大小
int maze[MAX_N][MAX_N];       // 迷宫数组
int visited[MAX_N][MAX_N];    // 访问标记数组
Queue queue;                  // 队列

// 初始化队列
void init_queue() {
    queue.front = queue.rear = 0;
}

// 入队
void enqueue(Node node) {
    queue.data[queue.rear++] = node;
}

// 出队
Node dequeue() {
    return queue.data[queue.front++];
}

// 判断队列是否为空
int is_empty() {
    return queue.front == queue.rear;
}

// 判断坐标是否在迷宫范围内
int is_valid(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

// 广度优先搜索
int bfs() {
    // 定义四个方向：上、下、左、右
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    // 初始化队列
    init_queue();
    
    // 将起点加入队列
    Node start = {1, 1};
    enqueue(start);
    visited[1][1] = 1;
    
    // 添加层分隔符
    Node separator = {-1, -1};
    enqueue(separator);
    
    int depth = 0;
    
    while (!is_empty()) {
        Node current = dequeue();
        
        // 如果是层分隔符
        if (current.x == -1 && current.y == -1) {
            depth++;
            if (!is_empty()) {
                enqueue(separator);  // 为下一层添加分隔符
            }
            continue;
        }
        
        // 如果到达终点
        if (current.x == n && current.y == m) {
            return depth;
        }
        
        // 遍历四个方向
        for (int i = 0; i < 4; i++) {
            int new_x = current.x + dx[i];
            int new_y = current.y + dy[i];
            
            // 检查新位置是否有效且未访问
            if (is_valid(new_x, new_y) && !visited[new_x][new_y] && maze[new_x][new_y] == 0) {
                Node next = {new_x, new_y};
                enqueue(next);
                visited[new_x][new_y] = 1;
            }
        }
    }
    
    return -1;  // 没有找到路径
}

int main() {
    scanf("%d %d", &n, &m);
    
    // 读入迷宫
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &maze[i][j]);
            visited[i][j] = 0;
        }
    }
    
    // 计算最短路径
    int result = bfs();
    
    // 输出结果
    printf("%d\n", result);
    
    return 0;
}
