//
//  main.cpp
//  7种常用排序
//  冒泡排序、简单选择排序、直接插入排序、希尔排序、堆排序、归并排序、快速排序
//
//  Created by vincent on 2017/10/17.
//  Copyright © 2017年 vincent. All rights reserved.
//

#include <iostream>

// 输出排序后的结果
void show(int *array, int size, int start = 0) {
    for (int i = start; i < size; ++i) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}

// 交换两个元素
void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

/************************************
 * 冒泡排序
 * 稳定排序，O{n} ~ O{n^2}
 * 从末尾开始，与上个元素比较并交换
 * 每轮都将能最小的元素换到首位
 ************************************/
void bubblingSort() {
    const int size = 10;
    int array[size] = {1, 3, 2, 10, 6, 4, 7, 5, 8, 9};
    printf("冒泡排序: \n");
    show(array, size);
    for (int i = 0; i < size; ++i) {
        for (int j = size - 1; j > i; --j) {
            if (array[j] < array[j - 1]) {
                swap(array[j], array[j - 1]);
            }
        }
    }
    show(array, size);
}

/************************************
 * 简单选择排序
 * 稳定排序，O{n^2} ~ O{n^2}
 * 从首位开始，循环一次找出一个比首位小的值，交换
 ************************************/
void selectSort() {
    const int size = 10;
    int array[size] = {1, 3, 2, 10, 6, 4, 7, 5, 8, 9};
    printf("简单选择排序: \n");
    show(array, size);
    for (int i = 0; i < size - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < size; ++j) {
            if (array[min] > array[j]) {
                min = j;
            }
        }
        if (min != i) {
            swap(array[min], array[i]);
        }
    }
    show(array, size);
}

/************************************
 * 直接插入排序
 * 稳定排序，O{n} ~ O{n^2}
 * 循环找出一个右边比左边小的值作为哨兵
 * 向左查找所有大于哨兵的值，右移
 * 然后将哨兵插入空出的一个位置
 ************************************/
void insertSort() {
    const int size = 10;
    int array[size] = {1, 3, 2, 10, 6, 4, 7, 5, 8, 9};
    printf("直接插入排序: \n");
    show(array, size);
    int temp; // 哨兵
    for (int i = 1; i < size; ++i) {
        // 比左边的小
        if (array[i] < array[i - 1]) {
            temp = array[i]; // 哨兵位储存小的值
            int j;
            // 向左找所有大于哨兵的值，统统右移，空出一格
            for (j = i - 1; array[j] > temp; j--) {
                array[j + 1] = array[j];
            }
            array[j + 1] = temp; // 将哨兵插入
        }
    }
    show(array, size);
}

/************************************
 * 希尔排序
 * 不稳定排序，O{nlogn} ~ O{n^2}
 * 跳跃式的直接插入排序
 * 也就是将直接插入中的左右查找，替换为左右跳跃一个指定增量
 * 增量选取很关键，最后一个增量值必须等于1
 ************************************/
void shellSort() {
    const int size = 10;
    int array[size] = {1, 3, 2, 10, 6, 4, 7, 5, 8, 9};
    printf("希尔排序: \n");
    show(array, size);
    int temp; // 哨兵
    int increment = size;
    do {
        increment = increment / 3 + 1;
        for (int i = increment; i < size; ++i) {
            // 跳跃increment格来比较
            if (array[i] < array[i - increment]) {
                temp = array[i];
                int j;
                for (j = i - increment; j > 0 && array[j] > temp; j-=increment) {
                    array[j + increment] = array[j];
                }
                array[j + increment] = temp;
            }
        }
    } while (increment > 1);
    show(array, size);
}

/************************************
 * 堆排序
 * 不稳定排序，O{nlogn} ~ O{nlogn}
 * 将数组转化为完全二叉树
 * 父节点比左右子节点都大的称为大根堆，都小的称为小根堆
 * 从后往前遍历所有非叶子节点，初始化大根堆
 * 将堆顶和最后一个元素交换，得到一个最大值
 * 通过不断的调整大根堆，得到排序后的数组
 ************************************/
void heapSort() {
    const int size = 11;
    // 0号节点弃用，因为完全二叉树的计算使用1下标为根节点更易于计算
    int array[size] = {0, 1, 3, 2, 10, 6, 4, 7, 5, 8, 9};
    printf("堆排序: \n");
    show(array, size, 1);
    
    auto adjust = [&](int (&array)[size], int s, int m) {
        int temp = array[s];
        // 从s开始，乘2操作表示移动到左孩子节点
        for (int j = 2 * s; j <= m; j *= 2) {
            // 左右孩子节点比较，选中较大的节点
            if (j < m && array[j] < array[j + 1]) {
                ++j;
            }
            // 如果父节点比左右孩子节点都大，则无需操作
            if (temp >= array[j]) {
                break;
            }
            // 否则父节点和子节点换位置
            array[s] = array[j];
            s = j;
        }
        array[s] = temp;
    };
    int length = size - 1;
    // 从length / 2 开始，即遍历所有非叶子节点
    // 所有非叶子节点调整完后，堆定肯定是最大元素了
    for (int i = length / 2; i > 0; --i) {
        adjust(array, i, length);
    }
    for (int i = length; i > 1; i--) {
        // 将堆顶和最后一个元素交换，在重新调整大根堆
        swap(array[1], array[i]);
        adjust(array, 1, i - 1);
    }
    show(array, size, 1);
}

/************************************
 * 归并排序
 * 稳定排序，O{nlogn} ~ O{nlogn}
 * 稳定排序中最高效的
 * 倒置的二叉树，两两排序后合并
 ************************************/
void mergeArray(int array[], int first, int mid, int last, int temp[]) {
    // 将两个有序数列a[first...mid]和a[mid...last]合并。
    int i = first;
    int j = mid + 1;
    int m = mid;
    int n = last;
    int k = 0;
    // 如果i < mid + 1，将较小的放入temp，i右移
    // 如果i > mid + 1，将较小的放入temp，mid + 1右移
    while (i <= m && j <= n) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }
    // 处理剩余的array[i .. m]，填充到temp末尾
    while (i <= m) {
        temp[k++] = array[i++];
    }
    
    // 处理剩余的array[j .. n]，填充到temp末尾
    while (j <= n) {
        temp[k++] = array[j++];
    }
    
    // 让array = temp
    for (i = 0; i < k; i++) {
        array[first + i] = temp[i];
    }
}

void mergeSortRecursive(int array[], int first, int last, int temp[]) {
    if (first < last) {
        int mid = (first + last) / 2;
        mergeSortRecursive(array, first, mid, temp);    //左边有序
        mergeSortRecursive(array, mid + 1, last, temp); //右边有序
        mergeArray(array, first, mid, last, temp); // 再将二个有序数列合并
    }
}

void mergeSort() {
    const int size = 10;
    int array[size] = {1, 3, 2, 10, 6, 4, 7, 5, 8, 9};
    int temp[size];
    printf("归并排序: \n");
    show(array, size);
    mergeSortRecursive(array, 0, size - 1, temp);
    show(temp, size);
}

/************************************
 * 快速排序
 * 不稳定排序，O{nlogn} ~ O{n^2}
 * 适合排序大量数据
 * 设最左边为基准数
 * 右边往左找一个比基准数小的
 * 左边往右找一个比基准数大的，和上一步交换
 * 碰头后和基准数交换
 ************************************/
void quickSortRecursive(int (&array)[10], int left, int right) {
    if (left > right) {
        return;
    }
    int temp = array[left]; // 基准数
    int i = left;
    int j = right;
    while (i != j) {
        // 从右边开始找比基准数小的
        while (array[j] >= temp && i < j) {
            --j;
        }
        // 然后从左边开始找比基准数小的
        while (array[i] <= temp && i < j) {
            ++i;
        }
        if (i < j) {
            swap(array[i], array[j]);
        }
    }
    // 碰头后，与基准数交换
    swap(array[left], array[i]);
    
    // 递归处理左边的
    quickSortRecursive(array, left, i - 1);
    // 递归处理右边的
    quickSortRecursive(array, i + 1, right);
}

void quickSort() {
    const int size = 10;
    int array[size] = {1, 3, 2, 10, 6, 4, 7, 5, 8, 9};
    printf("快速排序: \n");
    show(array, size);
    quickSortRecursive(array, 0, size - 1);
    show(array, size);
}

int main(int argc, const char * argv[]) {
    bubblingSort();
    selectSort();
    insertSort();
    shellSort();
    heapSort();
    mergeSort();
    quickSort();
    return 0;
}
