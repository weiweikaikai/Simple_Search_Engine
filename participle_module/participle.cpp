#include <iostream>
#include <string>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "thulac.h"
#include <fstream>
#include <sstream>
using namespace std;
//#include "thulac_test.h"


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
    printf("the current dir is : %s\n",basePath);


    ///get the file list
    memset(basePath,'\0',sizeof(basePath));
    strcpy(basePath,"../text_data");
    readFileList(basePath);

    //THULAC lac;
    //const char *model_path = "../models";
    //std::string case_name;
    //std::string raw;
    //{
    //    
    //    case_name = "检查单分词模型模型";
    //    std::cout<<case_name<<": ";
    //    lac.init(model_path,NULL,1);
    //    raw = "我爱北京天安门"; 
    //    THULAC_result result;                                                          
    //    lac.cut(raw, result);                                                         
    //    std::string s_result = lac.toString(result);
    //    std::cout<<s_result<<std::endl;
    //    //THULAC_TEST test = THULAC_TEST(&lac, case_name);
    //    //test.testEqual("我爱北京天安门", "我 爱 北京 天安门");
    //    //test.testEqual("小明喜欢玩炉石传说", "小明 喜欢 玩 炉石 传说");
    //}

    //    {
    //        case_name = "检查带词性标注的模型";
    //        std::cout<<case_name<<": ";
    //        lac.init(model_path,NULL,0);
    //        raw = "我爱北京天安门"; 
    //        THULAC_result result;                                                          
    //        lac.cut(raw, result);                                                         
    //        std::string s_result = lac.toString(result);
    //        std::cout<<s_result<<std::endl;
    //        // THULAC_TEST test = THULAC_TEST(&lac, case_name);
    //        // test.testEqual("我爱北京天安门", "我_r 爱_v 北京_ns 天安门_ns");
    //        //test.testEqual("小明喜欢玩炉石传说", "小明_np 喜欢_v 玩_v 炉石_n 传说_n");
    //    }
    //    
    //    {
    //        case_name = "检查deli分隔符参数";
    //        lac.init(model_path,NULL,0, 0, 0,'#');
    //        THULAC_TEST test = THULAC_TEST(&lac, case_name);
    //        test.testEqual("我爱北京天安门", "我#r 爱#v 北京#ns 天安门#ns");
    //        test.testEqual("小明喜欢玩炉石传说", "小明#np 喜欢#v 玩#v 炉石#n 传说#n");
    //    }
    //    
    //    {
    //        case_name = "检查T2S分隔符参数";
    //        lac.init(model_path,NULL,1, 1);
    //        THULAC_TEST test = THULAC_TEST(&lac, case_name);
    //        test.testEqual("我愛北京天安門", "我 爱 北京 天安门");
    //        test.testEqual("小明喜歡玩爐石傳說", "小明 喜欢 玩 炉石 传说");
    //    }
    //    
    //    {
    //        case_name = "检查ufilter参数";
    //        lac.init(model_path,NULL,1, 0, 1);
    //        THULAC_TEST test = THULAC_TEST(&lac, case_name);
    //        test.testEqual("我可以爱北京天安门", "我 爱 北京 天安门");
    //    }

    //    std::cout << "下面测试程序报错的错误提示" << endl;
    //    
    //    {
    //        case_name = "model_dir不存在";
    //        try {
    //            lac.init("/program/python/python-git/thulac/model",NULL,1, 0, 1);
    //        }
    //        catch e{
    //            std::cout << e;
    //        }
    //    }
    //    THULAC_TEST::reportAll();
    return 0;
}



