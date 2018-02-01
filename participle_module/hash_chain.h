
#ifndef _HASH_CHAIN_H
#define _HASH_CHAIN_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;



#define  DEFALT_BUCKET  1024

//链表节点
typedef struct hash_node {
	char* word ;
	struct hash_node *next;
}hash_node_t;
//哈希函数指针

//哈希表结构
class hash_t {
public:
    // BKDR Hash Function 默认的hash函数
    unsigned int BKDRHash(char *str);
    //创建哈希表
    hash_t(unsigned int bk=DEFALT_BUCKET) {
        buckets = bk;
        //hash_func = BKDRHash;

        size_t size = buckets * sizeof(hash_node_t*);
        nodes= (hash_node_t**)malloc(size);
        memset(nodes,0,size);
    }
    ~hash_t() {
        if (nodes) {
            dealloc();
        }
    }
    void dealloc() {
        for(int i=0; i<buckets; ++i) {
            if(nodes[i] != NULL) {
                hash_node_t *cur = nodes[i];

                while(cur!= NULL) {
                    free(cur);
                    cur=cur->next;
                }
            }
        }
        free(nodes);
        nodes = NULL;
    }
    void hash_add_entry(char*w);  
    bool is_exist(char*w);
    void Print();
private:
    unsigned int buckets;  //当前桶的个数
    //hashfunc_t  hash_func; //哈希函数
    hash_node_t  **nodes;  //链表中节点的地址

};


#endif
