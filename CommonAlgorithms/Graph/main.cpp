//
//  main.cpp
//  CommonAlgorithms
//
//  Created by vincent on 2017/11/06.
//  Copyright © 2017年 vincent. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>
// 边表
struct EdgeNode {
    int index;
    EdgeNode *next = nullptr;
};

// 顶点表
struct VectorNode {
    char data;
    bool visited = false;
    EdgeNode *firstEdge = nullptr;
};

//顶点集合
std::vector<VectorNode *> vectors;

// 添加一条无向边(vi,vj)
void addEdge(char i, char j) {
    int vi = (int)(i - 65);
    int vj = (int)(j - 65);
    
    // 头插法
    EdgeNode * node = new EdgeNode();
    node->index = vj;
    node->next = vectors[vi]->firstEdge;
    vectors[vi]->firstEdge = node;
    
    node = new EdgeNode();
    node->index = vi;
    node->next = vectors[vj]->firstEdge;
    vectors[vj]->firstEdge = node;
}

// 深度优先遍历(类似前序遍历)
void DFS(int i) {
    vectors[i]->visited = true;
    printf("%c\n", vectors[i]->data);
    EdgeNode *node = vectors[i]->firstEdge;
    while (node) {
        if(!vectors[node->index]->visited) {
            DFS(node->index);
        }
        node = node->next;
    }
}

// 广度优先遍历(类似层序遍历)
std::list<int> assitQueue; // 辅助队列
void BFS(int i) {
    assitQueue.push_back(i);
    vectors[i]->visited = true;
    printf("%c\n", vectors[i]->data);
    while (!assitQueue.empty()) {
        int index = assitQueue.front();
        assitQueue.pop_front();
        EdgeNode *node = vectors[index]->firstEdge;
        while (node) {
            if(!vectors[node->index]->visited) {
                vectors[node->index]->visited = true;
                assitQueue.push_back(node->index);
                printf("%c\n", vectors[node->index]->data);
            }
            node = node->next;
        }
    }
}

int main(int argc, const char * argv[]) {
    // 建立顶点表
    for (int i = 0; i < 10; ++i) {
        VectorNode *node = new VectorNode();
        node->data = (char)(i + 65); // start with A
        vectors.push_back(node);
    }
    // 建立边表
    addEdge('A', 'F');
    addEdge('A', 'B');
    addEdge('B', 'G');
    addEdge('B', 'I');
    addEdge('B', 'C');
    addEdge('C', 'I');
    addEdge('C', 'D');
    addEdge('D', 'I');
    addEdge('D', 'G');
    addEdge('D', 'H');
    addEdge('D', 'E');
    addEdge('E', 'H');
    addEdge('E', 'F');
    addEdge('F', 'G');
    addEdge('G', 'H');
    
    printf("深度优先遍历:\n");
    for (int i = 0; i < vectors.size(); ++ i) { // 连通图只会执行一次
        if(!vectors[i]->visited) {
            DFS(i);
            printf("-\n");
        }
    }
    
    // clean
    for (int i = 0; i < vectors.size(); ++i) {
        vectors[i]->visited = false;
    }
    
    printf("广度优先遍历:\n");
    for (int i = 0; i < vectors.size(); ++ i) { // 连通图只会执行一次
        if(!vectors[i]->visited) {
            BFS(i);
            printf("-\n");
        }
    }
    
    return 0;
}
