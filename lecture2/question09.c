#include <stdio.h>
#include <string.h>

#define MAX_N 100010

// Trie节点结构
struct Node {
    int cnt;    // 以该节点结尾的单词数量
    struct Node* children[26];  // 26个小写字母的子节点
};

// 创建新节点
struct Node* createNode() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->cnt = 0;
    for(int i = 0; i < 26; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// 插入字符串
void insert(struct Node* root, char* str) {
    struct Node* current = root;
    for(int i = 0; str[i]; i++) {
        int index = str[i] - 'a';
        if(current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->cnt++;  // 增加单词计数
}

// 查询字符串出现次数
int query(struct Node* root, char* str) {
    struct Node* current = root;
    for(int i = 0; str[i]; i++) {
        int index = str[i] - 'a';
        if(current->children[index] == NULL) {
            return 0;  // 字符串不存在
        }
        current = current->children[index];
    }
    return current->cnt;  // 返回出现次数
}

int main() {
    int N;
    char op[2], str[MAX_N];
    struct Node* root = createNode();
    
    scanf("%d", &N);
    while(N--) {
        scanf("%s %s", op, str);
        if(op[0] == 'I') {
            insert(root, str);
        } else {  // op[0] == 'Q'
            printf("%d\n", query(root, str));
        }
    }
    
    return 0;
}
