//
//  main.cpp
//  CommonAlgorithms
//
//  Created by vincent on 2017/10/17.
//  Copyright © 2017年 vincent. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

std::map<char, std::vector<int>> CODE;

struct BinaryNode {
    char data = '#';
    int weight = 0;
    std::vector<int> bits;
    BinaryNode* lchild = nullptr;
    BinaryNode* rchild = nullptr;
};

bool compare(BinaryNode *A, BinaryNode *B) {
    return A->weight < B->weight;
};

void createHuffmanTree(std::vector<BinaryNode *>& trees) {
    std::sort(trees.begin(), trees.end(), compare);
    auto first = trees.begin();
    auto second = first + 1;
    BinaryNode *tree = new BinaryNode();
    tree->lchild = *first;
    tree->rchild = *second;
    tree->weight = tree->lchild->weight + tree->rchild->weight;
    trees.erase(first, second + 1);
    trees.push_back(tree);
    if (trees.size() != 1) {
        createHuffmanTree(trees);
    }
}

void createHuffmanCode(BinaryNode* node) {
    if(node->data != '#') {
        CODE[node->data].insert(CODE[node->data].begin(), node->bits.begin(), node->bits.end());
    }
    if(node->lchild) {
        node->lchild->bits.insert(node->lchild->bits.end(), node->bits.begin(), node->bits.end());
        node->lchild->bits.push_back(0);
        createHuffmanCode(node->lchild);
    }
    if(node->rchild) {
        node->rchild->bits.insert(node->rchild->bits.end(), node->bits.begin(), node->bits.end());
        node->rchild->bits.push_back(1);
        createHuffmanCode(node->rchild);
    }
}

std::vector<int> encode(const std::string& letters) {
    std::vector<int> result;
    for (auto iter = letters.begin(); iter != letters.end(); ++iter) {
        if(CODE.find(*iter) != CODE.end()) {
            auto bits = CODE.find(*iter)->second;
            result.insert(result.end(), bits.begin(), bits.end());
        }
    }
    return result;
}

std::string decode(std::vector<int>& codes, BinaryNode* root) {
    BinaryNode *node = root;
    std::string result;
    for(auto iter = codes.begin(); iter != codes.end(); ++iter) {
        int bit = *iter;
        if((bit == 0 && node->lchild == nullptr) || (bit == 1 && node->rchild == nullptr)) {
            result.push_back(node->data);
            node = root;
        }
        node = (bit == 0) ? node->lchild : node->rchild;
    }
    if(node->lchild == nullptr && node->rchild == nullptr) {
        result.push_back(node->data);
    }
    return result;
}

void printBits(std::vector<int>& bits, bool linebreak = false) {
    for(auto iter = bits.begin(); iter != bits.end(); ++iter) {
        printf("%d", *iter);
    }
    if(linebreak) {
        printf("\n");
    }
}

int main(int argc, const char * argv[]) {
    // 字母和权重
    std::map<char, int> data;
    data['A'] = 5;
    data['B'] = 10;
    data['C'] = 15;
    data['D'] = 30;
    data['E'] = 40;
    
    // 构造哈夫曼树
    std::vector<BinaryNode *> trees;
    for (auto iter = data.begin(); iter != data.end(); ++iter) {
        BinaryNode *tree = new BinaryNode();
        tree->weight = iter->second;
        tree->data = iter->first;
        trees.push_back(tree);
    }
    createHuffmanTree(trees);
    
    // 保存各字母的哈夫曼编码
    createHuffmanCode(trees[0]);
    for (auto iter = CODE.begin(); iter != CODE.end(); ++iter) {
        printf("%c = ", iter->first);
        printBits(iter->second, true);
    }
    
    // 编码
    std::string letters = "EABECDED";
    std::vector<int> code = encode(letters);
    printf("encode: %s -> ", letters.c_str());
    printBits(code, true);
    
    // 解码
    std::string result = decode(code, trees[0]);
    printf("decode: ");
    printBits(code);
    printf(" -> %s\n", result.c_str());
    return 0;
}
