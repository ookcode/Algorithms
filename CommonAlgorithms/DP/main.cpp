//
//  动态规划(dynamic programming)
//  金矿模型，求最大产量
//
//  Created by vincent on 2017/10/17.
//  Copyright © 2017年 vincent. All rights reserved.
//

#include <iostream>
#include <map>
const int GoldCount = 10; // 金矿数
const int PeopleCount = 10000; // 总人数
int Golds[GoldCount] = {1000, 2500, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 9999}; // 每个金矿的金子数
int Needs[GoldCount] = {555, 1111, 1555, 2222, 2555, 3333, 3555, 4444, 5555, 6666}; // 每个金矿需要的人数
std::map<int, std::map<int, int>> MaxGold; // MaxGold[i][j]保存了i个人挖前j个金矿能得到的最大金子数量，不存在表示未知

int GetMaxGold(int people, int index) {
    int retMaxGold;
    if(MaxGold.find(people) != MaxGold.end() && MaxGold[people].find(index) != MaxGold[people].end()) {
        // [备忘录]获得保存起来的值
        retMaxGold = MaxGold[people][index];
    } else if(index == 0) {
        // [边界]开采最后一个金矿
        if(people >= Needs[index]) {
            // 人数够，得到当前金矿的金子数
            retMaxGold = Golds[index];
        } else {
            // 人数不够，得到0
            retMaxGold = 0;
        }
    } else if(people >= Needs[index]) {
        // [最优子结构]人数够，考虑开采与不开采两种情况，取最大值
        int doGet = GetMaxGold(people - Needs[index], index - 1) + Golds[index];
        int doNotGet = GetMaxGold(people, index - 1);
        retMaxGold = std::max(doGet, doNotGet);
    } else {
        // [最优子结构]人数不够，仅考虑不开采的情况
        retMaxGold  = GetMaxGold(people, index - 1);
    }
    // [备忘录]存储计算过的值
    MaxGold[people][index] = retMaxGold;
    return retMaxGold;
}

int main(int argc, const char * argv[]) {
    std::cout << GetMaxGold(PeopleCount, GoldCount - 1) << std::endl;
    return 0;
}
