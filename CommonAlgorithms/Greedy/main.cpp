//
//  贪心算法(greedy algorithm)
//
//  钱币找零问题
//  假设有i种纸币，Values[i]元的纸币有Counts[i]张。现在要用这些钱来支付Total元，至少要用多少张纸币？
//
//  Created by vincent on 2017/10/17.
//  Copyright © 2017年 vincent. All rights reserved.
//

#include <iostream>

const int ItemCount = 7; // 纸币种类
const int Total = 444; // 目标金额
int Values[ItemCount] = {1, 2, 5, 10, 20, 50, 100}; // 纸币i的面额，已排序
int Counts[ItemCount] = {100, 1, 100, 66, 10, 5, 1}; // 纸币i的张数

int solve(int money) {
    int num = 0;
    for(int i = ItemCount - 1;i >= 0; i--) {
        // 贪心，每次都用最大的面额
        int useCount = std::min(money / Values[i], Counts[i]);
        printf("需要%d元纸币%d张，总额%d\n", Values[i], useCount, useCount * Values[i]);
        money = money - useCount * Values[i];
        num += useCount;
    }
    if(money > 0) num = -1;
    return num;
}

int main(int argc, const char * argv[]) {
    printf("至少需要%d张纸币\n", solve(Total));
    return 0;
}
