#include <string>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "thulac.h"
#include <fstream>
#include <sstream>
#include<iostream>
using namespace std;

void print(const THULAC_result& result, bool seg_only, char separator) {
    for(int i = 0; i < result.size() - 1; i++) {
        if(i != 0) cout << " ";
        if(seg_only) {
            cout << result[i].first;
        }
        else {
            cout << result[i].first << separator << result[i].second;
        }
    }
    cout << endl;
}


int readFileList(char *basePath) {
  
    DIR *dir;
    struct dirent *ptr;
    char base[1024];

    if ((dir=opendir(basePath)) == NULL) {
        perror("Open dir error...");
        exit(1);
    }
    int cur = 0;
    while ((ptr=readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0) {   //current dir OR parrent dir
            continue;
        }
        else if(ptr->d_type == 8) {   //file
            char* user_specified_dict_name=NULL;
            const char* model_path_char = "../lib/THULAC/models";
            char input_path[512] ={'\0'};
            snprintf(input_path,sizeof(input_path)-1,"%s/%s",basePath,ptr->d_name);
            char output_path[512]={'\0'};
            snprintf(output_path,sizeof(output_path)-1,"%s/%s","../thual_data",ptr->d_name);   

            char separator = '_';

            bool useT2S = false;
            bool seg_only = false;
            bool useFilter = false;
            bool multi_thread = false;

            useT2S = true;
            seg_only = true;
            useFilter = true;
            multi_thread = true;
            THULAC lac;
            //lac.init(model_path_char, user_specified_dict_name, seg_only, useT2S, useFilter);
            lac.init(model_path_char, NULL, 1);
            std::ifstream finput;
            if(input_path) {
                finput.open(input_path);
                cin.rdbuf(finput.rdbuf());
            }
            std::ofstream foutput;
            if(output_path) {
                foutput.open(output_path);
                cout.rdbuf(foutput.rdbuf());
            }
            std::string raw;
            THULAC_result result;
            clock_t start = clock();
            while(getline(cin, raw,'\n')) {
                lac.cut(raw, result);
                print(result, seg_only, separator);
            }
            clock_t end = clock();
            double duration = (double)(end - start) / CLOCKS_PER_SEC;
            std::cerr<<duration<<" seconds"<<std::endl;
            finput.close();
            foutput.close();
        }
    }
        return 0;
}




int main() {

    DIR *dir;
    char basePath[1024];

    //get the current absoulte path
    memset(basePath,'\0',sizeof(basePath));
    getcwd(basePath, sizeof(basePath)-1);
    //printf("the current dir is : %s\n",basePath);


    ///get the file list
    memset(basePath,'\0',sizeof(basePath));
    strcpy(basePath,"../text_data");
    readFileList(basePath); //读取text_data目录中的文件进行分词并放到thual_data目录中

    return 0;
}



