/*************************************************************************
	> File Name: inverted_index.h
	> Author: wk
	> Mail: 18402927708@163.com
	> Created Time: Tue 30 Jan 2018 05:49:39 PM CST
 ************************************************************************/

#ifndef _INVERTED_INDEX_H
#define _INVERTED_INDEX_H
#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include "hash_chain.h"
using namespace std;

#define MAXLINE 1024  
 

class InvertedIndex  
{  
    public:  
        InvertedIndex():hash() {}  
        ~InvertedIndex() {
            result_index_.clear();
        }  
        int readFileList(const char *basePath);
        int StatWords(const char* file_name);  
        map<string,map<string,int> > result_index() {
            return result_index_;
        }  
        void print() {
            map<string,map<string,int> >::iterator it = result_index_.begin();
            std::ofstream foutput;                                              
            const char*output_path="./invertedindex.txt"; //将建立的倒排索引打印到这个文件    
                foutput.open(output_path);                                      
            while(it != result_index_.end()) {
                foutput<<it->first.c_str()<<"->";
                map<string,int>::iterator it1= (it->second).begin(); 
                while(it1 != (it->second).end()) {
                    foutput<<"["<<it1->first.c_str()<<":"<<it1->second<<"]"<<endl;
                    ++it1; 
                }
                ++it;
            }
            foutput.close();
            hash.Print();
        }

    private:  
        //存放倒排索引结果，key是单词，value也是map，该map的key是文件名，value是该单词在该文件中出现的次数  
        map<string,map<string,int> > result_index_;  
        hash_t hash; //单词词典
        int ParseWordsByLine(char* str_line, const char* file_name);  
        void InsertWordToMap(char* word, const char* file_name);  
};  




#endif
