#include"hash_chain.h"
#include <fstream> 
//往哈希表中添加一项
void hash_t::hash_add_entry(char*w) {
    if (w == NULL) {
        return ; 
    }
    hash_node_t *node = (hash_node_t*)malloc(sizeof(hash_node_t));
    node->word = w;
    node->next = NULL;

    unsigned int hash_value = BKDRHash(w)%buckets;
    if(nodes[hash_value] == NULL) {
        nodes[hash_value] = node;
    } else {
        //将新节点插入 头插
        if(!is_exist(w)) {
            node->next = nodes[hash_value]->next;
            nodes[hash_value]->next = node;
        }
    }
}
//是否存在某个单词
bool hash_t::is_exist(char*w) {
    if(w == NULL) {
        return false; 
    }
    unsigned int hash_value = BKDRHash(w)%buckets;
    if(nodes[hash_value] == NULL) {
        return false;    
    }
    if (0 == strcmp(nodes[hash_value]->word,w)) {
        return true; 
    }
    hash_node_t* cur = nodes[hash_value]->next;
    while(cur) {
        if (0 == strcmp(cur->word,w)) {
            return true; 
        }
        cur = cur->next;
    }
    return false;
}

void hash_t::Print() {

    std::ofstream foutput;                                                 
    const char*output_path="./word_dictionary.txt"; //将单词词典打印到这个文件                                                                                         
    foutput.open(output_path); 

    for (int i=0;i<buckets; ++i) {
      foutput<<i<<": ";
      if (nodes[i]) {
          foutput<<nodes[i]->word<<"->";
          hash_node_t* cur = nodes[i]->next;                                       
          while(cur) {
              foutput<<cur->word<<"->"; 
              cur = cur->next; 
          }
      }
      foutput<<endl;
    }
    foutput.close();
}


// BKDR Hash Function 默认的hash函数
unsigned int hash_t:: BKDRHash(char *str) {
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..                 
    unsigned int hash = 0;                                                     

    while (*str) { 
        hash = hash * seed + (*str++);                                         
    }                                                                          
    return (hash & 0x7FFFFFFF);
}
//test
//int main()
//{
//    hash_t hash(10);
//    hash.hash_add_entry((char*)"hello");
//    hash.hash_add_entry((char*)"世界");
//    hash.hash_add_entry((char*)"哈哈");
//    hash.hash_add_entry((char*)"我的天");
//    hash.hash_add_entry((char*)"你是谁");
//    hash.hash_add_entry((char*)"青蛙");
//    hash.Print();
//    return 0;
//}
