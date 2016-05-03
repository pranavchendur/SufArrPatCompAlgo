#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <conio.h>
#include <fstream>
#include <string.h>

using namespace std;

int main()
{
    string sin;
    int grpcnt=0,curgrp,i,filelen=0;
    
    ifstream infile;
    infile.open("ofile.dat",ios::in );
    
    vector <string> maxread;
    vector <string> fmaxread;
    vector <string> f2maxread;
    vector <string> grpread;
    map<string,int> m;
    map <string,int> cntmap;
    map <string,int> grpmap;
    map <string,int> grpsubmap;
    vector<string> v;
    vector<string>::iterator it;
    
    while (!infile.eof()) {
    	cout<<endl<<"Word : "<<sin<<endl;
    	infile >> sin;
    	filelen += sin.length();
    	it = find(grpread.begin(),grpread.end(),sin);
    	if (it==grpread.end()) {
    		grpcnt++;
    		grpread.push_back(sin);
    		grpmap[sin]=grpcnt;
    		curgrp = grpmap[sin];
		}
		else {
			curgrp = grpmap[sin];
		}
		
		for(int i = 0; i < sin.size();i++)
	    {
	        m[sin.substr(i,sin.size()-i)] = i;
	        v.push_back(sin.substr(i,sin.size()-i));
	    }
	    
	    sort(v.begin(),v.end());
	    
	    for(int i = 0; i < v.size();i++)
	    {
	        //cout << m[v[i]] << "\t" << v[i] << endl;
	        it = find(maxread.begin(),maxread.end(),v[i]);
	        if (it!=maxread.end()) {
	        	cntmap[v[i]]++;
	        //	cout<<"Incremented : "<<v[i]<<" to "<<cntmap[v[i]]<<endl;
			}
			else {
				maxread.push_back(v[i]);
				cntmap[v[i]]=1;
				grpsubmap[v[i]]=curgrp;
			//	cout<<"Added : "<<v[i]<<endl;
			}
	    }
	    
	    v.clear();
	    m.clear();
	}
	
	//cout<<"CNTMAP Details : "<<endl;
	//for (i=0;i<maxread.size();i++) {
    //	cout<<maxread[i]<<" - Length : "<<maxread[i].length()<<" - Count : "<<cntmap[maxread[i]]<<" - Group : "<<grpsubmap[maxread[i]]<<endl;
	//}
    
    //remove all strlen < 5 && count < 3 
    for (i=0;i<maxread.size();i++) {
    	//cout<<maxread[i]<<" - Length : "<<maxread[i].length()<<" - Count : "<<cntmap[maxread[i]]<<endl;
    	
		if (maxread[i].length()>4 && cntmap[maxread[i]]>2)
			fmaxread.push_back(maxread.at(i));
	}
	
	//select only one entity from each group
	int curngrp=grpsubmap[fmaxread[0]],curmax=cntmap[fmaxread[0]]+fmaxread[0].length(),curi=0,fndmax;
	for (i=1;i<fmaxread.size();i++) {
    	//cout<<fmaxread[i]<<" - Length : "<<fmaxread[i].length()<<" - Count : "<<cntmap[maxread[i]]<<endl;
    	fndmax = cntmap[fmaxread[i]]+fmaxread[i].length();
    	if (curngrp==grpsubmap[fmaxread[i]]) {
    		if (fndmax > curmax) {
				curmax = fndmax;
				curi=i;
			}
		}
		else {
			f2maxread.push_back(fmaxread.at(curi));
			curngrp=grpsubmap[fmaxread[i]];
			curmax=cntmap[fmaxread[i]]+fmaxread[i].length();
			curi=i;
		}
			
	}
	
	
	//cout<<"After Erase CNTMAP Details : "<<endl;
	//for (i=0;i<fmaxread.size();i++) {
    //	cout<<fmaxread[i]<<" - Length : "<<fmaxread[i].length()<<" - Count : "<<cntmap[fmaxread[i]]<<" - Group : "<<grpsubmap[fmaxread[i]]<<endl;
	//}
	int totRep=0,lenRed=0;
	cout<<"f2maxread Details : "<<endl;
	for (i=0;i<f2maxread.size();i++) {
    	cout<<f2maxread[i]<<" - Length : "<<f2maxread[i].length()<<" - Count : "<<cntmap[f2maxread[i]]<<" - Group : "<<grpsubmap[f2maxread[i]]<<endl;
    	totRep += cntmap[f2maxread[i]];
    	lenRed += cntmap[f2maxread[i]]*f2maxread[i].length();
	}
	
	cout<<"Totally Returned "<<f2maxread.size()<<" patterns, which are found to be repetitive."<<endl;
	cout<<"Number of times repeated is "<<totRep<<endl;
	cout<<"Length of repeated is "<<lenRed<<endl;
	cout<<"Total words found in the file is "<<grpcnt<<endl;
	cout<<"Total file length "<<filelen<<endl;
	//float reduction = (lenRed/filelen);
	//cout<<"Through this algorithm file size can be reduced upto "<<reduction<<"%"<<endl;
    getch();
    return 0;
}
