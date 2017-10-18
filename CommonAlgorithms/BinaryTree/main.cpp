//
//  main.cpp
//  CommonAlgorithms
//
//  Created by vincent on 2017/10/17.
//  Copyright © 2017年 vincent. All rights reserved.
//

#include <iostream>
struct BinaryNode {
    char data;
    BinaryNode* lchild = nullptr;
    BinaryNode* rchild = nullptr;
};

// 先序构造二叉树
void createBinaryTree(BinaryNode *&node) {
    char ch;
    std::cin >> ch;
    if(ch == '#') {
        return;
    }
    if (node == nullptr) {
        node = new BinaryNode();
    }
    node->data = ch;
    createBinaryTree(node->lchild);
    createBinaryTree(node->rchild);
}

// 先序遍历
void preOrderTraverse(BinaryNode* node) {
    if (node == nullptr) {
        return;
    }
    printf("%c\n", node->data);
    preOrderTraverse(node->lchild);
    preOrderTraverse(node->rchild);
}

// 中序遍历
void inOrderTraverse(BinaryNode* node) {
    if (node == nullptr) {
        return;
    }
    preOrderTraverse(node->lchild);
    printf("%c\n", node->data);
    preOrderTraverse(node->rchild);
}

// 后序遍历
void postOrderTraverse(BinaryNode* node) {
    if (node == nullptr) {
        return;
    }
    preOrderTraverse(node->lchild);
    preOrderTraverse(node->rchild);
    printf("%c\n", node->data);
}

int main(int argc, const char * argv[]) {
    // 输入示例：AB#C##D##
    printf("请输入一棵二叉树(#表示无子节点):\n");
    BinaryNode *tree = new BinaryNode();
    createBinaryTree(tree);
    printf("先序遍历:\n");
    preOrderTraverse(tree);
    printf("中序遍历:\n");
    inOrderTraverse(tree);
    printf("后序遍历:\n");
    postOrderTraverse(tree);
    return 0;
}
