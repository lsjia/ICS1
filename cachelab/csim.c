//罗思佳 2021201679
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cachelab.h"
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <limits.h>
typedef struct
{
    int valid_bit;
    int tag;
    int LRU_counter;
} cache_line, *cache_set, **cache;

int S, s, E, b;
int hit_count, miss_count, eviction_count;
bool isDisplay = false;
cache Cache = NULL; //定义一个空的二维数组

extern void printSummary(int hits,       /* number of  hits */
                         int misses,     /* number of misses */
                         int evictions); /* number of evictions */

void init_cache() //初始化cache
{
    Cache = (cache)malloc(sizeof(cache_set) * S);
    int i,j;
    for (i = 0; i < S; i++)
    {
        Cache[i] = (cache_set)malloc(sizeof(cache_line) * E);
        for (j = 0; j < E; j++)
        {
            Cache[i][j].valid_bit = 0;
            Cache[i][j].tag = -1;
            Cache[i][j].LRU_counter = -1;
        }
    }
}

void delete_cache() //释放cache
{
    int i;
    for (i = 0; i < S; i++)
    {
        free(Cache[i]);
    }
    free(Cache);
}

int getLRU_block(int set_index) //获取最久未使用的index
{
    int max_LRU_counter = INT_MIN;
    int max_LRU_index = -1;
    int i;
    for (i = 0; i < E; i++)
    {
        if (Cache[set_index][i].LRU_counter > max_LRU_counter)
        {
            max_LRU_counter = Cache[set_index][i].LRU_counter;
            max_LRU_index = i;
        }
    }
    return max_LRU_index;
}

void update_cache(unsigned int address)//更新cache
{
    int set_index = (address >> b) & (0xffffffffU >> (64 - s));//得到set的序号
    int _tag = address >> (s + b);//得到标识
    
    int i;
    for (i = 0; i < E; i++)
    {
        if (Cache[set_index][i].tag == _tag) //找到了
        {
            Cache[set_index][i].LRU_counter = 0;
            hit_count++;
            if (isDisplay)
                printf("hit ");
            return;
        }
    }
    int j;
    for (j = 0; j < E; j++) //看有没有未使用的line
    {
        if (Cache[set_index][j].valid_bit == 0)
        {
            Cache[set_index][j].valid_bit = 1;
            Cache[set_index][j].tag = _tag;
            Cache[set_index][j].LRU_counter = 0;
            miss_count++;
            if (isDisplay)
                printf("miss ");
            return;
        }
    }

    //没有空的cache_line,需要进行替换
    miss_count++;
    eviction_count++;
    int LRU_index = getLRU_block(set_index);//获取最久未使用的块的index
    Cache[set_index][LRU_index].tag = _tag;
    Cache[set_index][LRU_index].LRU_counter = 0;
    if (isDisplay)
        printf("miss eviction ");
}

void update_LRU_counter() //更新时间戳
{
    int i,j;
    for (i = 0; i < S; i++)
    {
        for (j = 0; j < E; j++)
        {
            if (Cache[i][j].valid_bit == 1)
                Cache[i][j].LRU_counter++;
        }
    }
}

void stimulate(char *filename)//总的模拟函数
{
    FILE *pFile;
    pFile = fopen(filename, "r");
    if (pFile == NULL) //未成功打开
    {
        printf("fail to open");
        exit(1);
    }

    char identifier;
    unsigned int address;
    int size;

    while (fscanf(pFile, " %c %x,%d\n", &identifier, &address, &size) > 0)
    {
        if (isDisplay)
        {
            printf("%c %x,%d ", identifier, address, size);
        }
        switch (identifier)
        {
        case 'L':
            update_cache(address);
            break;
        case 'S':
            update_cache(address);
            break;
        case 'M':
            update_cache(address);//需要调用2次
            update_cache(address);
        }

        if (isDisplay)
            printf("\n");
        update_LRU_counter();//每次要整体更新时间戳
    }
    fclose(pFile);
    delete_cache();//用完释放空间
}
int main(int argc, char *argv[])
{

    hit_count = 0;
    miss_count = 0;
    eviction_count = 0;
    int opt;
    char *tracefile;

    while (-1 != (opt = (getopt(argc, argv, "hvs:E:b:t:"))))
    {
        switch (opt)
        {
        case 'v':
            isDisplay = true;
            break;
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            strcpy(tracefile, optarg);
            break;
        }
    }

    if (s <= 0 || E <= 0 || b <= 0 || tracefile == NULL) //处理无效输入
    {
        printf("invalid input\n");
        return -1;
    }

    S = 1 << s;//S = 2^s

    init_cache();

    stimulate(tracefile);

    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
