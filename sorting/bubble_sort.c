
/**
 * @file
 * @brief [冒泡排序](https://en.wikipedia.org/wiki/Bubble_sort) 算法实现
 * @details 本文件包含了经典的冒泡排序算法实现，包含数组打印、元素交换、
 * 核心排序逻辑以及基于断言（assert）的自动化测试用例。
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief 在终端打印输出数组的所有元素
 * @param arr 指向待显示整型数组的指针
 * @param n 数组中元素的个数
 */
void display(const int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * @brief 通过指针交换两个变量的值
 * @param first 指向第一个待交换整型变量的指针
 * @param second 指向第二个待交换整型变量的指针
 */
void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

/**
 * @brief 冒泡排序算法的具体实现
 * @param arr 指向待排序整型数组的指针
 * @param size 数组中元素的总个数
 * @details 
 * 核心原理：通过双层循环重复遍历数组，每次比较相邻的两个元素。
 * 如果前一个元素大于后一个元素，则调用 swap 函数交换它们的位置。
 * 每一轮外层循环结束，当前未排序部分的最大值都会像“气泡”一样浮动到它的最终正确位置。
 */
void bubbleSort(int *arr, int size)
{
    // 外层循环：控制整体排序的轮数。
    // 每执行完一轮，就会有一个当前最大元素被固定在末尾，因此总共需要执行 size - 1 轮。
    for (int i = 0; i < size - 1; i++)
    {
        // swapped 变量作为优化标记，用于记录在本轮内层循环中是否发生过数据交换。
        bool swapped = false; 
        
        // 内层循环：负责对当前未排序部分进行相邻元素的比较和交换。
        // 随着外层循环 i 的增加，末尾已经有 i 个元素排好序了，因此内层循环边界为 size - 1 - i。
        for (int j = 0; j < size - 1 - i; j++)
        { 
            // 比较相邻元素：如果左边的元素比右边的元素大，则需要调整顺序
            if (arr[j] > arr[j + 1])
            { 
                swap(&arr[j], &arr[j + 1]); // 调用指针交换函数
                swapped = true;             // 发生了交换，将标记设置为 true
            }
        }
        
        // 最佳时间复杂度优化判断：
        // 如果在整整一轮的内层比较中没有发生任何一次数据交换，
        // 说明此时整个数组已经完全有序，不需要再进行后续无效的循环比较。
        if (!swapped)
        {
            // 立即中断外层循环，提前结束程序，显著提升在局部或完全有序数组下的执行效率。
            break;
        }
    }
}

/**
 * @brief 自动化单元测试函数
 * @details 动态分配一个长度为 10 的数组，随机生成 0 到 99 之间的整数进行填充。
 * 调用 bubbleSort 进行排序，最后使用 assert 宏逐一验证数组是否真正达到了升序排列。
 */
void test()
{
    const int size = 10;
    // 使用 calloc 动态分配内存，并初始化为 0
    int *arr = (int *)calloc(size, sizeof(int));

    /* 循环生成 size 个从 0 到 100 之间的随机数并存入数组 */
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }
    
    // 执行排序算法
    bubbleSort(arr, size);
    
    // 遍历整个数组，使用断言验证相邻两个元素是否满足前一个小于等于后一个
    for (int i = 0; i < size - 1; ++i)
    {
        assert(arr[i] <= arr[i + 1]);
    }
    
    // 测试完成后，必须及时释放动态分配的内存，防止内存泄漏
    free(arr);
}

/** * @brief 程序主入口
 * @param argc 命令行参数个数
 * @param argv 命令行参数字符串数组
 * @return int 返回码 0 代表程序正常退出
 */
int main(int argc, const char *argv[])
{
    /* 使用当前系统时间作为随机数种子，确保每次运行生成的随机数不同 */
    srand(time(NULL));
    
    // 运行测试用例
    test();
    
    return 0;
}
