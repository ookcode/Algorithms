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
    // 线索化
    bool ltag = false; // false表示子节点，true表示前驱
    bool rtag = false; // false表示子节点，true表示后继
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
void preOrderTraverse(BinaryNode *node) {
    if (node == nullptr) {
        return;
    }
    printf("%c\n", node->data);
    preOrderTraverse(node->lchild);
    preOrderTraverse(node->rchild);
}

// 中序遍历
void inOrderTraverse(BinaryNode *node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraverse(node->lchild);
    printf("%c\n", node->data);
    inOrderTraverse(node->rchild);
}

// 后序遍历
void postOrderTraverse(BinaryNode *node) {
    if (node == nullptr) {
        return;
    }
    postOrderTraverse(node->lchild);
    postOrderTraverse(node->rchild);
    printf("%c\n", node->data);
}

// 中序线索化
BinaryNode *tempPre = nullptr;
void inOrderTreading(BinaryNode *node) {
    if (node == nullptr) {
        return;
    }
    inOrderTreading(node->lchild);
    if(!node->lchild) {
        node->ltag = true;
        node->lchild = tempPre;
    }
    if(tempPre && !tempPre->rchild) {
        tempPre->rtag = true;
        tempPre->rchild = node;
    }
    tempPre = node;
    inOrderTreading(node->rchild);
}

// 线索化后的中序遍历
void inOrderTreadingTraverse(BinaryNode *node) {
    BinaryNode *p = node;
    while(p) {
        while (p->ltag == false) {
            p = p->lchild;
        }
        printf("%c\n", p->data);
        while (p->rtag == true) {
            p = p->rchild;
            printf("%c\n", p->data);
        }
        p = p->rchild;
    }
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
    printf("中序线索化遍历:\n");
    inOrderTreading(tree);
    inOrderTreadingTraverse(tree);
    return 0;
}
