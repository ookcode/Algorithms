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
const int M = 65535; // 使用M来表示两点间无通路
const int SIZE = 9; // 点的个数

int G[SIZE][SIZE] = {
//  0   1   2   3   4   5   6   7   8
    0,  1 , 5,  M,  M,  M,  M,  M,  M,  // 0
    1,  0,  3,  7,  5,  M,  M,  M,  M,  // 1
    5,  3,  0,  M,  1,  7,  M,  M,  M,  // 2
    M,  7,  M,  0,  2,  M,  3,  M,  M,  // 3
    M,  5,  1,  2,  0,  3,  6,  9,  M,  // 4
    M,  M,  7,  M,  3,  0,  M,  5,  M,  // 5
    M,  M,  M,  3,  6,  M,  0,  2,  7,  // 6
    M,  M,  M,  M,  9,  5,  2,  0,  4,  // 7
    M,  M,  M,  M,  M,  M,  7,  4,  0,  // 8
};

void dijkstra() {
    int finals[SIZE]; // finals[w] = 1表示已经求得v0到vw的最短路径
    int lowcost[SIZE]; // 储存v0到每个点的最短路径
    int path[SIZE]; // 储存每个点的上一个点，倒序即可推出任一点的路径
    for(int i = 0; i < SIZE; ++i) printf("%d\t", i);
    printf("\n-------------------------------------------------------\n");
    
    for(int i = 0; i < SIZE; ++i) {
        finals[i] = 0; // 初始化finals，表示所有顶点均未求得最短路径
        lowcost[i] = G[0][i]; // 初始化v0到各个点的距离
        path[i] = 0;
        printf("%d\t", lowcost[i]);
    }
    printf("\n");
    finals[0] = 1; // v0至v0不需要求
    for (int i = 1; i < SIZE; ++i) {
        int min = M;
        int minIndex = 0;
        for (int j = 0; j < SIZE; ++j) {
            // 找到离v0最近的顶点
            if (finals[j] == 0 && lowcost[j] < min) {
                min = lowcost[j];
                minIndex = j;
            }
        }
        finals[minIndex] = 1; // 最近的顶点finals设置为1
        for (int j = 0; j < SIZE; ++j) {
            // v1到vx的距离+v0到v1的距离如果小于v0直接到vx时
            if (finals[j] == 0 && min + G[minIndex][j] < lowcost[j]) {
                lowcost[j] = min + G[minIndex][j];
                path[j] = minIndex;
            }
        }
        for(int j = 0; j < SIZE; ++j) printf("%d\t", lowcost[j]);
        printf("\n");
    }
    
    int target = 8;
    int sum = 0;
    printf("v%d到v0的最短路径：", target);
    while (target != 0) {
        int pre = path[target];
        sum += G[target][pre];
        target = pre;
        printf("-> %d ", target);
    }
    printf("\n总路程：%d\n\n", sum);
}

void floyd() {
    int D[SIZE][SIZE]; // 矩阵G的副本，用于存储各个点到各个点的最短距离
    int P[SIZE][SIZE]; // 储存点的前驱
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            D[i][j] = G[i][j];
            P[i][j] = j;
        }
    }
    
    // D[x][y] = min(D[x][y], D[x][i] + D[i][y]
    // 先中转i点(i=0~8)，判断直达近还是中转后近
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < SIZE; ++k) {
                if (D[j][k] > D[j][i] + D[i][k]) {
                    // 例:1->2 分解成 1->0 + 0->2
                    D[j][k] = D[j][i] + D[i][k];
                    P[j][k] = P[j][i];
                }
            }
        }
    }
    
    // 打印最终D矩阵
    printf("\n-------------------------------------------------------\n");
    for (int j = 0; j < SIZE; ++j) {
        for (int k = 0; k < SIZE; ++k) {
            printf("%d\t", D[j][k]);
        }
        printf("\n");
    }
    // 打印最终P矩阵
    printf("-------------------------------------------------------\n");
    for (int j = 0; j < SIZE; ++j) {
        for (int k = 0; k < SIZE; ++k) {
            printf("%d\t", P[j][k]);
        }
        printf("\n");
    }
    
    int start = 0;
    int end = 8;
    printf("v%d到v%d的最短路径：", start, end);
    int pre = end;
    while (pre != start) {
        pre = P[pre][start];
        printf("-> %d ", pre);
    }
    printf("\n总路程：%d\n\n", D[start][end]);
}

int main(int argc, const char * argv[]) {
    printf("dijkstra算法:\n"); // O(n^2)，指定起点v0，计算v0到各个点的最短距离
    /*
     * 选择一个起点v0，lowcost[]记录v0到各个点的距离
     * 遍历lowcost[]，找出离v0最近的点vx(距离最小但不为0)，距离min，将finals[x]置为1表示已经是最短路径
     * 遍历vx的矩阵，如果min + (vx-vi) < (v0-vi)，那么lowcost[i] = min + vx-vi，并记录vi的前驱是vx
     * 循环挑选直至遍历所有点
     */
    dijkstra();
    
    printf("floyd算法:\n"); // O(n^3)， 能够知道任意点到任意点的最短距离
    /*
     * D[x][y] = min(D[x][y], D[x][i] + D[i][y]
     * 直接处理邻接矩阵
     * 三层循环处理
     * 最外层循环第一次：如果v1-2 < v1-0 + v0-2，则v1-2 = v1-0 + v0-2，并记录P[1][2]的前驱是P[1][0] = 0
     * 最外层循环第二次：如果v2-3 < v2-1 + v1-3，则v2-3 = v1-0 + v0-2，并记录P[2][3]的前驱是P[2][1] = 1
     * 直至遍历所有的点，最终得到的邻接矩阵存储了到各个点的最短距离
     */
    floyd();
    return 0;
}
