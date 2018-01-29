/*
 *************************************************************************
 *    File Name:  text_extract.cpp
 *       Author: Taomee Shanghai,Inc.
 *         Mail: weeks@taomee.com
 * Created Time: Mon 29 Jan 2018 05:10:58 PM CST
 * 
 *  Description: ...
 * 
 ************************************************************************
*/
#include<iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <boost/regex.hpp>
#include <fstream>
#include <sstream>


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
			char file_name[512] ={'\0'};
			snprintf(file_name,sizeof(file_name)-1,"%s/%s",basePath,ptr->d_name);
			fstream out(file_name,ios::in);
			stringstream buffer;
			buffer<<out.rdbuf();
			string data(buffer.str());
			string pattern="[\u4e00-\u9fa5]"; //匹配所有汉字
			//string pattern="^((https|http|ftp|rtsp|mms)?:\/\/)[^\s]+"; //匹配url
			boost::regex reg(pattern.c_str()); 
			//  string result = boost::regex_replace(data,reg,""); //将匹配出来的替换为空 
			string::const_iterator start(data.begin());
			string::const_iterator end(data.end());
			boost::match_results<string::const_iterator> what;
			char outfile_name[512] ={'\0'};
			snprintf(outfile_name,sizeof(outfile_name)-1,"%s/%s","../text_data",ptr->d_name);	
			fstream in(outfile_name,ios::out);
			while(boost::regex_search(start,end,what,reg,boost::match_default)){
				// cout<<what[1].str()<<" => "<<what[2].str()<<what[3].str()<<endl;
				string result(what[0].first,what[0].second);
				in<<result;
				// cout<<next<<endl;
				start=what[0].second;
			}
			++cur;
			if (cur > 5) {
				break;
			}
			//printf("d_name:%s/%s\n",basePath,ptr->d_name);
		}
		else if(ptr->d_type == 10) {   ///link file
			//printf("d_name:%s/%s\n",basePath,ptr->d_name);
		}
		else if(ptr->d_type == 4) { //dir
			memset(base,'\0',sizeof(base));
			strcpy(base,basePath);
			strcat(base,"/");
			strcat(base,ptr->d_name);
			readFileList(base);
		}
    }
    closedir(dir);
    return 1;
}


int main(void)
{
    DIR *dir;
    char basePath[1024];


    ///get the current absoulte path
    memset(basePath,'\0',sizeof(basePath));
    getcwd(basePath, sizeof(basePath)-1);
    printf("the current dir is : %s\n",basePath);


    ///get the file list
    memset(basePath,'\0',sizeof(basePath));
    strcpy(basePath,"../web_data");
    readFileList(basePath);
    return 0;
}
