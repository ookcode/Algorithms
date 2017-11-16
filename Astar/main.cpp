//
//  main.cpp
//
//  A*寻路算法
//
//  Created by vincent on 2017/10/17.
//  Copyright © 2017年 vincent. All rights reserved.
//

#include <iostream>
#include <list>

// 节点结构
struct Node {
    Node(int _x, int _y):x(_x), y(_y){};
    int x; // 地图坐标x
    int y; // 地图坐标y
    int g; // 距离起点的距离
    int h; // 距离终点的距离
    int f; // g + h
    Node *p = nullptr; // 父节点
};

// 地图，0表示通路，1表示障碍，5表示路径
const int Size = 10;
int Map[Size][Size] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  1,  1,  1,  1,  1,  1,  1,  0,
    0,  0,  0,  0,  0,  1,  0,  0,  1,  0,
    5,  0,  1,  1,  0,  1,  1,  5,  1,  0,
    0,  1,  1,  0,  0,  1,  1,  0,  1,  0,
    0,  1,  0,  0,  1,  1,  0,  0,  1,  0,
    0,  1,  0,  1,  1,  0,  0,  1,  1,  0,
    0,  1,  0,  0,  0,  0,  0,  1,  0,  0,
    0,  1,  0,  0,  0,  0,  0,  1,  0,  0,
};

// 开放列表
std::list<Node *> openList;
// 关闭列表
std::list<Node *> closeList;

// 寻路算法
bool Astar(Node *start, Node *end) {
    openList.push_back(start);
    while (!openList.empty()) {
        // 选出f值最小的节点
        auto min = openList.begin();
        for (auto iter = openList.begin(); iter != openList.end(); ++iter) {
            if ((*iter)->f < (*min)->f) {
                min = iter;
            }
        }
        Node *node = *min;
        openList.erase(min);
        closeList.push_back(node);
        // 处理周围的四个点
        int surrounds[4][2] = {
            node->x, node->y - 1, // 上
            node->x, node->y + 1, // 下
            node->x - 1, node->y, // 左
            node->x + 1, node->y, // 右
        };
        for (int i = 0; i < 4; ++i) {
            int x = surrounds[i][0];
            int y = surrounds[i][1];
            // 跳过超出边界的点
            if (x < 0 || x >= Size || y < 0 || y >= Size) {
                continue;
            }
            // 跳过不可通行的点
            if (Map[x][y] == 1) {
                continue;
            }
            // 跳过在关闭列表里的点
            bool isInCloseList = false;
            for (auto iter = closeList.begin(); iter != closeList.end(); ++iter) {
                if (x == (*iter)->x && y == (*iter)->y) {
                    isInCloseList = true;
                    break;
                }
            }
            if (isInCloseList) {
                continue;
            }
            // 跳过在开放列表里的点
            bool isInOpenList = false;
            for (auto iter = openList.begin(); iter != openList.end(); ++iter) {
                if (x == (*iter)->x && y == (*iter)->y) {
                    isInOpenList = true;
                    break;
                }
            }
            if (isInOpenList) {
                continue;
            }
            // 判断是否到达终点
            if (x == end->x && y == end->y) {
                end->p = node;
                return true;
            }
            // 剩下的加入开放列表
            Node *newNode = new Node(x, y);
            newNode->g = abs(x - start->x) + abs(y - start->y);
            newNode->h = abs(x - end->x) + abs(y - end->y);
            newNode->f = newNode->g + newNode->h;
            newNode->p = node;
            openList.push_back(newNode);
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    Node *start = new Node(4, 0);
    Node *end = new Node(4, 7);
    Map[start->x][start->y] = 5;
    Map[end->x][end->y] = 5;
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            printf("%d\t", Map[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------开始寻路-------------------------\n");
    bool isReachEnd = Astar(start, end);
    if (isReachEnd) {
        Node *node = end;
        while (node) {
            Map[node->x][node->y] = 5;
            node = node->p;
        }
    }
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            printf("%d\t", Map[i][j]);
        }
        printf("\n");
    }
    return 0;
}
