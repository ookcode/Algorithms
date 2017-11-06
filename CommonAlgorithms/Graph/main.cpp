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

// 深度优先遍历
void DFS(int i) {
    // 打印顶点
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

// 广度优先遍历
std::list<VectorNode *> assitQueue;
void BFS(int i) {
}

int main(int argc, const char * argv[]) {
    // 建立顶点表
    for (int i = 0; i < 9; ++i) {
        VectorNode *node = new VectorNode();
        node->data = (char)(i + 65); // start with A
        vectors.push_back(node);
    }
    // 建立边表
    addEdge('A', 'F');
    addEdge('A', 'B');
    addEdge('B', 'I');
    addEdge('B', 'G');
    addEdge('B', 'C');
    addEdge('C', 'I');
    addEdge('C', 'D');
    addEdge('D', 'I');
    addEdge('D', 'H');
    addEdge('D', 'G');
    addEdge('D', 'E');
    addEdge('E', 'H');
    addEdge('E', 'F');
    addEdge('F', 'G');
    addEdge('G', 'H');
    
    printf("深度优先遍历:\n");
    DFS(0);
    printf("广度优先遍历:\n");
    BFS(0);
    return 0;
}
