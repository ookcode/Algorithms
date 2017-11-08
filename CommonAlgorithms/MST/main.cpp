//
//  main.cpp
//  CommonAlgorithms
//
//  Created by vincent on 2017/11/07.
//  Copyright © 2017年 vincent. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
const int M = INT_MAX; // 使用M来表示两点间无通路
const int SIZE = 9; // 点的个数

int G[SIZE][SIZE] = {
//  0   1   2   3   4   5   6   7   8
    0,  10, M,  M,  M,  11, M,  M,  M,  // 0
    10, 0,  18, M,  M,  M,  16, M,  12, // 1
    M,  M,  0,  22, M,  M,  M,  M,  8,  // 2
    M,  M,  22, 0,  20, M,  24, 16, 21, // 3
    M,  M,  M,  20, 0,  26, M,  7,  M,  // 4
    11, M,  M,  M, 26,  0,  17,  M, M,  // 5
    M,  16, M,  24, M,  17, 0,  19, M,  // 6
    M,  M,  M,  16, 7,  M,  19, 0,  M,  // 7
    M,  12, 8,  21, M,  M,  M,  M,  0,  // 8
};

void prim() {
    int lowcost[SIZE]; // 辅助数组，用来选取两点最小距离
    int adjvex[SIZE]; // 保存对应连通的顶点序号
    for(int i = 0; i < SIZE; ++i) {
        // 从v0点开始，记录v0点到所有点的距离
        lowcost[i] = G[0][i];
        adjvex[i] = 0;
    }
    // 遍历剩余所有顶点
    for(int i = 1; i < SIZE; ++i) {
        // 找出lowcost里的最小值
        int min = M;
        int minIndex = 0;
        for(int j = 1; j < SIZE; ++j) {
            if(lowcost[j] != 0 && lowcost[j] < min) {
                min = lowcost[j];
                minIndex = j;
            }
        }
        lowcost[minIndex] = 0; // 选出最小的之后，将他在lowcost中标记为0
        printf("%d - %d = %d\n", adjvex[minIndex], minIndex, min);
        for(int j = 0; j < SIZE; ++j) {
            if(lowcost[j] != 0 && G[minIndex][j] < lowcost[j]) {
                lowcost[j] = G[minIndex][j];
                adjvex[j] = minIndex;
            }
        }
    }
}

// 边结构
struct Edge {
    int begin;
    int end;
    int weight;
};

bool compare(Edge *A, Edge *B) {
    return A->weight < B->weight;
};

void kruskal() {
    // 构造边集数组
    std::vector<Edge *> edges;
    for(int i = 0; i < SIZE; ++i) {
        for(int j = i + 1; j < SIZE; ++j) {
            int weight = G[i][j];
            if(weight != M) {
                Edge *edge = new Edge();
                edge->begin = i;
                edge->end = j;
                edge->weight = weight;
                edges.push_back(edge);
            }
        }
    }
    // 按权值由小到大排序
    std::sort(edges.begin(), edges.end(), compare);
    
    // kruskal算法
    int parent[SIZE] = {0,0,0,0,0,0,0,0,0};
    for (int i = 0; i < edges.size(); ++i) {
        Edge *edge = edges[i];
        int begin = edge->begin;
        while(parent[begin] != 0) {
            begin = parent[begin];
        }
        int end = edge->end;
        while (parent[end] != 0) {
            end = parent[end];
        }
        if (begin != end) {
            parent[begin] = end;
            printf("%d - %d = %d\n", begin, end, edge->weight);
        }
    }
}

int main(int argc, const char * argv[]) {
    printf("prim算法:\n"); // 适合边多的情况
    /******************************
     * 使用邻接矩阵结构
     * 选择一个起点v0，lowcost[]记录v0到各个点的距离
     * 遍历lowcost[], 找出离v0最近的点vx(距离最小但不为0)，并将lowcost[x]置为0
     * 遍历vx的矩阵，如果vx到vi的距离比v0到vi的小，替换进lowcost[i]，并记录vi的前驱是vx
     * 循环挑选直至遍历所有点
     ******************************/
    prim();
    
    printf("kruskal算法:\n"); // 适合边少的情况
    /******************************
     * 使用边集数组结构，权值由小到大将边排序
     * 遍历所有边，判断是否已经构成回路（即不需要这条边也能连通两点了）
     例如：权值从小到大的5条边，0-1, 0-5, 1-8, 1-6, 5-6
     0 - 1   因为p[0] = 0  所以p[0] = 1，边0-1匹配
     0 - 5   因为p[0] = 1; p[1] = 0  所以p[1] = 5，边1-5匹配
     1 - 8   因为p[1] = 5; p[5] = 0  所以p[5] = 8，边5-8匹配
     1 - 6   因为p[1] = 5; p[5] = 8, p[8] = 0  所以p[8] = 6，边8-6匹配
     5 - 6   因为p[5] = 8; p[8] = 6  所以p[6] = 6形成回路，跳过
     ******************************/
    kruskal();
    return 0;
}
