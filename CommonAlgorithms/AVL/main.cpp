//
//  main.cpp
//  CommonAlgorithms
//
//  Created by vincent on 2017/10/17.
//  Copyright © 2017年 vincent. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
struct BinaryNode {
    BinaryNode(int weight):data(weight){};
    int data;
    int bf = 0; // 平衡因子（左子树深度 - 右子树深度）
    BinaryNode* lchild = nullptr;
    BinaryNode* rchild = nullptr;
    
    int offset = 0; // 空格数，仅用于格式化输出
};

int Deep = 0; // 二叉树的层数
// 二叉排序树插入
void insert(BinaryNode *&node, int data, int deep = 0) {
    deep++;
    if (node == nullptr) {
        node = new BinaryNode(data);
        if (deep > Deep) {
            Deep = deep;
        }
        return;
    }
    if (data < node->data) {
        insert(node->lchild, data, deep);
    } else {
        insert(node->rchild, data, deep);
    }
}

// 平衡二叉树右旋
void rotateRight(BinaryNode *&root) {
    // 将lchild的右子树变成root的左子树
    // 将root变为lchild的右子树
    // lchild替换root
    BinaryNode *lchild = root->lchild;
    root->lchild = lchild->rchild;
    lchild->rchild = root;
    root = lchild;
}

// 平衡二叉树左旋
void rotateLeft(BinaryNode *&root) {
    // 将rchild的左子树变成root的右子树
    // 将root变为rchild的左子树
    // rchild替换root
    BinaryNode *rchild = root->rchild;
    root->rchild = rchild->lchild;
    rchild->lchild = root;
    root = rchild;
}

// 左平衡处理(右旋)
void balanceLeft(BinaryNode *&root) {
    BinaryNode *L = root->lchild;
    switch (L->bf) {
        case -1:
        {
            BinaryNode *Lr = L->rchild;
            switch (Lr->bf) {
                case -1:
                    root->bf = 0;
                    L->bf = 1;
                    break;
                case 0:
                    root->bf = 0;
                    L->bf = 0;
                    break;
                case 1:
                    root->bf = -1;
                    L->bf = 0;
                    break;
            }
            Lr->bf = 0;
            rotateLeft(L);
            rotateRight(root);
            break;
        }
        case 1:
        {
            // 正常右旋
            root->bf = 0;
            L->bf = 0;
            rotateRight(root);
            break;
        }
    }
}

// 右平衡处理(左旋)
void balanceRight(BinaryNode *&root) {
    BinaryNode *R = root->rchild;
    switch (R->bf) {
        case 1:
        {
            BinaryNode *Rl = R->lchild;
            switch (Rl->bf) {
                case -1:
                    root->bf = 1;
                    R->bf = 0;
                    break;
                case 0:
                    root->bf = 0;
                    R->bf = 0;
                    break;
                case 1:
                    root->bf = 0;
                    R->bf = -1;
                    break;
            }
            Rl->bf = 0;
            rotateRight(R);
            rotateLeft(root);
            break;
        }
        case -1:
        {
            // 正常左旋
            root->bf = 0;
            R->bf = 0;
            rotateLeft(root);
            break;
        }
    }
}

// 平衡二叉树插入
bool insertAVL(BinaryNode *&node, int data, bool *taller) {
    if (node == nullptr) {
        node = new BinaryNode(data);
        *taller = true;
    } else if (data < node->data) {
        if(!insertAVL(node->lchild, data, taller)) {
            return false;
        }
        if (*taller) {
            switch (node->bf) {
                case -1: // 原本右子树高，现在等高了
                    node->bf = 0;
                    *taller = false;
                    break;
                case 0: // 原本左右子树等高，现在左子树增高
                    node->bf = 1;
                    // 增高的情况下，需将该节点到根节点的所有节点都修改
                    *taller = true;
                    break;
                case 1: // 原本左子树高，再次增高需要重新平衡
                    balanceLeft(node);
                    *taller = false;
                    break;
            }
        }
    } else {
        if(!insertAVL(node->rchild, data, taller)) {
            return false;
        }
        if (*taller) {
            switch (node->bf) {
                case -1: // 原本右子树高，再次增高需要重新平衡
                    balanceRight(node);
                    *taller = false;
                    break;
                case 0: // 原本左右子树等高，现在右子树增高
                    node->bf = -1;
                    *taller = true;
                    break;
                case 1: // 原本左子树高，现在等高了
                    node->bf = 0;
                    *taller = false;
                    break;
            }
        }
    }
    return true;
}

// 层序遍历
void floorOrderTraverse(BinaryNode *node, int deep) {
    std::vector<BinaryNode *> line[deep];
    // 添加根节点
    node->offset = 70;
    line[0].push_back(node);
    // 添加子节点
    for (int i = 0; i < deep; ++i) {
        for (int j = 0; j < line[i].size(); ++j) {
            BinaryNode *node = line[i][j];
            BinaryNode *&lchild = node->lchild;
            BinaryNode *&rchild = node->rchild;
            if (lchild == nullptr) {
                lchild = new BinaryNode(0);
            }
            if (rchild == nullptr) {
                rchild = new BinaryNode(0);
            }
            lchild->offset = node->offset - (deep - i);
            rchild->offset = node->offset + (deep - i);
            line[i + 1].push_back(lchild);
            line[i + 1].push_back(rchild);
        }
    }
    // 格式化输出
    for (int i = 0; i < deep; ++i) {
        int size = (int)line[i].size();
        int offset = 0;
        for (int j = 0; j < size; ++j) {
            BinaryNode *node = line[i][j];
            int nodeOffset = node->offset;
            printf("");
            for (; offset < nodeOffset; ++offset) {
                printf(" ");
            }
            if (node->data == 0) {
                printf("");
            } else {
                printf("%d", node->data);
            }
        }
        printf("\n");
    }
}

int main(int argc, const char * argv[]) {
    int datas[10] = {3,2,1,4,5,6,7,10,9,8};
    bool status = false;
    BinaryNode *tree = new BinaryNode(datas[0]);
    for (int i = 1; i < 10; ++i) {
        insertAVL(tree, datas[i], &status);
    }
    floorOrderTraverse(tree, Deep);
    return 0;
}
