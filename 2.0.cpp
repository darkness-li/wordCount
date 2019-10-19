#include<iostream>
#include<string.h>
#include<stdlib.h>
#include <sstream>
#include <stdlib.h>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<string.h>
#include<map>
using namespace std;
int n = 3;
int m=0;
//string s = "welcome hello welcome Hello Ye Ye ye ye Welcome com";

string readFileIntoString(char * filename)
{
ifstream ifile(filename);
//将文件读入到ostringstream对象buf中
ostringstream buf;
char ch;
while(buf&&ifile.get(ch))
buf.put(ch);
//返回与流对象buf关联的字符串
return buf.str();
}
int check(char a[]){  //检查分割后的每个单词是否符合条件 ，如果前四个字母都合法，说明是一个合法单词，返回1，否则返回0 
	int k,kk,i;
	k=strlen(a);
	kk=1;
	for(i=0;i<4;i++){
		if((a[i]>=65&&a[i]<=90)||(a[i]>=97&&a[i]<=122))
		continue;
		else{
			kk=0;
			break;
		}
	}
	return kk;
}
int wordcount(string s){
	int length,k,flag,count,i;
	char a[500000];
	length=s.length();
	//s[length]='\n';
	k=0;count=0;
	for(i=0;i<=length;i++){
		if((s[i]>=48&&s[i]<=57)||(s[i]>=65&&s[i]<=90)||(s[i]>=97&&s[i]<=122)){
			a[k]=s[i];
			k++;
		}
		else{
			if(k==0)
			continue;
			if(k!=0){
				flag=check(a);
				if(flag==1)
				count++;
				k=0;
				memset(a, 0, sizeof(a));
			}
			
		}
	}
	return count;
}

vector<string> split(const string& str,const string& delim){
	vector<string> res;
	vector<string> result;
	string ss;
	if("" == str) return res;
	
	char* strs = new char[str.length() + 1];
	strcpy(strs,str.c_str());
	
	char* d = new char[delim.length() + 1];
	strcpy(d,delim.c_str());
	
	char* p = strtok(strs,d);
	while(p){
		string s = p;
		res.push_back(s);
		p = strtok(NULL,d);
	} 
//	for(int yy = 0; yy < res.size(); yy++){
//		cout<<res[yy]<<endl;
//	}
	for(int kk = 0; kk <= res.size()-n; ++kk){
		ss="";
		for(int i = kk; i < kk + n -1; i++){
			ss += res[i];
			ss += ' ';
		}
		ss += res[kk+n-1];
		//cout<<"ss: "<<ss<<endl;
		result.push_back(ss);
	}
	
	
	return result;
}


bool cmp(const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
}

int main(int argc,char *argv[])
{
	ifstream infile;
	ofstream outfile;
	char ch;
	//对命令行参数的处理 
	string si="-i",so="-o",sm="-m",sn="-n";
	int inputpos=0,outputpos=0,mpos=0,npos=0;
	for(int i=0;i<argc;i++)
	{
		if(argv[i]==si)inputpos=i+1;
		if(argv[i]==so)outputpos=i+1;
		if(argv[i]==sm)mpos=i+1;
		if(argv[i]==sn)npos=i+1;
	}
	infile.open(argv[inputpos]);
	int magic=0;//无需理解 
	int count=0,countn=0,countt=0,count0=0,countc=0,countrn=0;//换行(countn) 制表符(countt) 空格(count0) 字符(countc) 有效行数(countrn)的统计 
	while(!infile.eof())
    {
    	count++;
    	char temp;
       temp=infile.get();
       if(temp=='\n'||temp=='\r')
	   {
	   	countn++;countrn++;
	   	if(magic==1)countrn--;
		magic=1;
	   }
	   else magic=0;
       if(temp=='\t')countt++; 
       if(temp==' ')count0++;
    }
    countrn++;
    infile.close();
	string sign="mn";//默认实现所有功能 
	int m,n=0;//m,n后的参数的初始化 
	char save[100];
	int pt=0;
	
		int flag = 0;
	string s = readFileIntoString(argv[inputpos]);
	s.replace(s.find("\n"),1," ");
	//转小写 
	transform(s.begin(),s.end(),s.begin(),::tolower);
//	cout<<s<<endl;
	//以空格分割 
	vector<string> all_str = split(s," ");
//	for(int i = 0; i < all_str.size(); ++i){
//		cout<<all_str[i]<<endl;
//	}
	//定义map 
	map<string,int> mp;
	for(int i = 0; i < all_str.size(); ++i){
		flag = 0;
		for(map<string,int>::iterator j = mp.begin(); j != mp.end(); ++j){
			pair<string,int> it = *j;
			if(all_str[i] == it.first){
				it.second++;
				mp.erase(all_str[i]);
				mp.insert(it);
				flag = 1;
			}
		}
		
		if(!flag){
			pair<string,int> p_tmp(all_str[i], 1);
			mp.insert(p_tmp);
		}
	}
//	pair<string,int> ppp("hhh",1);
//	mp.insert(ppp);
	
//	for(map<string,int>::iterator i = m.begin(); i != m.end(); ++i){
//		pair<string,int> p = *i;
//		cout<<p.first<<" "<<p.second<<endl;
//	}
	int changdu = 0;
	vector< pair<string, int> > vec(mp.begin(), mp.end());
    sort(vec.begin(), vec.end(), cmp);
	
//	cout<<readFileIntoString(argv[inputpos])<<endl;
	if(argc==9)	m= atoi(argv[mpos]),n=atoi(argv[npos]);
	if(argc==7)
	{
		if(mpos!=0)
		{
		sign="om";
		m=atoi(argv[mpos]);//only "m"-methed		
		}
		else if(npos!=0)
		{
			sign="on";
			n=atoi(argv[npos]);//only "n"-methed
		}

		else cout<<"something goes wrong?"<<endl;
	}
	
	int wordsum=0;//wordsum用于记录文件的的单词总数 
	string s2;//字符串变量s用来保存input.txt里的内容 
	s2=readFileIntoString(argv[inputpos]);
	wordsum=wordcount(s2);//调用Wordcount函数得到结果 


	outfile.open(argv[outputpos]);
	//流的写入 
	{
		outfile<<"characters:"<<count<<endl;
		outfile<<"words:"<<wordsum<<endl;
		outfile<<"lines:"<<countrn<<endl;
		for (int i = 0; i < vec.size(); ++i){
			outfile <<"<"<<vec[i].first<<">: "<<vec[i].second<<endl;
		    	cout<<"<"<<vec[i].first<<">: "<<vec[i].second<<endl;
		    	
		}
        
//		if(m!=0){
//			if (vec.size()<=m)
//				changdu = vec.size();
//			else changdu = m;
//    	for (int i = 0; i < changdu; ++i)
//       		outfile <<"<"<<vec[i].first<<">: "<<vec[i].second<<endl;
//	}else{
//		if (vec.size()<=10)
//			changdu = vec.size();
//		else changdu = 10;
//		for (int i = 0; i < changdu; ++i)
//        	outfile <<"<"<<vec[i].first<<">: "<<vec[i].second<<endl;
//	}
	}
	outfile.close();
	return 0;
}
