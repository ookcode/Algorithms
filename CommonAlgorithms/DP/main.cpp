//
//  动态规划(dynamic programming)
//
//  0-1背包模型
//  给定ItemCount个物品, 物品i的重量是Weights[i], 价值Values[i], 背包的容量为TotalWeight
//  问应该如何选择装入背包的物品，使得背包内物品的总价值最大？

//  Created by vincent on 2017/10/17.
//  Copyright © 2017年 vincent. All rights reserved.
//

#include <iostream>

const int ItemCount = 4; // 物品数量
const int TotalWeight = 10; // 背包容量
int Values[ItemCount] = {111, 222, 332, 444}; // 物品i的价值
int Weights[ItemCount] = {1, 3, 5, 6}; // 物品i的重量

// 方式1：二维数组算法
// max[i][j]表示前i个物品放在j容量的背包里的最大价值
int max[ItemCount + 1][TotalWeight + 1];
int GetMax(int totalWeight, int targetIndex) {
    // 0行和0列全部填充为0，用于辅助计算
    for (int i = 0; i <= TotalWeight; ++i) {
        max[0][i] = 0;
        printf("%d\t", i);
    }
    for(int i = 0; i <= ItemCount; ++i) {
        max[i][0] = 0;
    }
    printf("\n");
    
    for (int i = 1; i <= ItemCount; ++i) {
        int index = i - 1;
        printf("%d\t", i);
        for (int j = 1; j <= TotalWeight; ++j) {
            // 容量j的背包能装i号物品
            if (j >= Weights[index]) {
                // [最优子结构]容量够，考虑装与不装index号物品两种情况，取最大值
                int doPut = max[i - 1][j - Weights[index]] + Values[index];
                int doNotPut = max[i - 1][j];
                max[i][j] = std::max(doPut, doNotPut);
                printf("%d\t", max[i][j]);
            } else {
                // [最优子结构]容量不够，仅考虑不装入index号物品的情况
                max[i][j] = max[i - 1][j];
                printf("%d\t", max[i][j]);
            }
        }
        printf("\n");
    }
    return max[targetIndex + 1][totalWeight];
}

// 回溯装入的物品
int Result[ItemCount];
void Find(int i, int j) {
    if (i >= 0) {
        if (max[i][j] == max[i - 1][j]) {
            // 与上一行价值相等，说明没有装入
            Result[i - 1] = 0;
            Find(i - 1, j);
        } else {
            int value = j - Weights[i - 1];
            int doPut = max[i - 1][j - Weights[i - 1]] + Values[i - 1];
            if (value > 0 && max[i][j] == doPut) {
                Result[i - 1] = 1; // 标记被装入
                Find(i - 1, j - Weights[i - 1]);
            }
        }
    }
}

// 方式2：递归算法
int GetMaxRecursive(int lastWeight, int index) {
    int retMaxGold;
    if(index == 0) {
        // [边界] 装最后一个物品
        if(lastWeight >= Weights[index]) {
            // 容量够，获得最后一个物品的价值
            retMaxGold = Values[index];
        } else {
            // 容量不够，获得到0
            retMaxGold = 0;
        }
    } else if(lastWeight >= Weights[index]) {
        // [最优子结构]容量够，考虑装与不装index号物品两种情况，取最大值
        int doPut = GetMaxRecursive(lastWeight - Weights[index], index - 1) + Values[index];
        int doNotPut = GetMaxRecursive(lastWeight, index - 1);
        retMaxGold = std::max(doPut, doNotPut);
    } else {
        // [最优子结构]容量不够，仅考虑不装入index号物品的情况
        retMaxGold  = GetMaxRecursive(lastWeight, index - 1);
    }
    return retMaxGold;
}

int main(int argc, const char * argv[]) {
    printf("方式1：背包内最大价值：%d\n", GetMax(TotalWeight, ItemCount - 1));
    printf("选中物品(1表示选中)：");
    Find(ItemCount, TotalWeight);
    for (int i = 0; i < ItemCount; ++i) {
        if(Result[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n方式2：背包内最大价值：%d\n", GetMaxRecursive(TotalWeight, ItemCount - 1));
    
    return 0;
}
