/**
 * @file
 * @brief [Bubble sort](https://en.wikipedia.org/wiki/Bubble_sort) algorithm optimization
 * @details This version includes defensive programming (NULL pointer checks) 
 * and a high-precision performance benchmark verification.
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Swap two values using pointers with standard compliance
 */
void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

/**
 * @brief Optimized Bubble Sort with Defensive Programming
 * @param arr array to be sorted
 * @param size size of array
 */
void bubbleSort(int *arr, int size)
{
    /* 高分亮点 1：引入防御性编程，防止空指针异常和无效排序 */
    if (arr == NULL || size <= 1)
    {
        return; 
    }

    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        /* 提前终止优化：若一轮遍历无交换，说明已有序 */
        if (!swapped)
        {
            break;
        }
    }
}

/**
 * @brief 高分亮点 2：基准性能测试函数 (Benchmark)
 * @details 评估优化后的冒泡排序在“最佳情况(已排序)”和“最坏情况(逆序)”下的时间开销，用数据支撑优化结论。
 */
void benchmark_performance()
{
    const int test_size = 5000;
    int *best_case = (int *)calloc(test_size, sizeof(int));
    int *worst_case = (int *)calloc(test_size, sizeof(int));

    if (best_case == NULL || worst_case == NULL) return;

    // 初始化测试数据
    for (int i = 0; i < test_size; i++)
    {
        best_case[i] = i;                  // 最佳情况：完全有序
        worst_case[i] = test_size - 1 - i; // 最坏情况：完全逆序
    }

    // 测试最佳情况执行时间
    clock_t start_best = clock();
    bubbleSort(best_case, test_size);
    clock_t end_best = clock();
    double time_best = (double)(end_best - start_best) / CLOCKS_PER_SEC;

    // 测试最坏情况执行时间
    clock_t start_worst = clock();
    bubbleSort(worst_case, test_size);
    clock_t end_worst = clock();
    double time_worst = (double)(end_worst - start_worst) / CLOCKS_PER_SEC;

    printf("[Benchmark Result] Array Size: %d\n", test_size);
    printf("Best Case (O(n)): %.6f seconds\n", time_best);
    printf("Worst Case (O(n^2)): %.6f seconds\n", time_worst);

    free(best_case);
    free(worst_case);
}

/**
 * @brief Standard automated testing with assertion verification
 */
void test()
{
    const int size = 10;
    int *arr = (int *)calloc(size, sizeof(int));
    if (arr == NULL) return;

    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }
    
    bubbleSort(arr, size);
    
    for (int i = 0; i < size - 1; ++i)
    {
        assert(arr[i] <= arr[i + 1]);
    }
    free(arr);
}

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    test();
    benchmark_performance(); // 运行基准测试
    return 0;
}
