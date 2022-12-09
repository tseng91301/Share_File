#include<bits/stdc++.h>
using namespace std;
int excutecmd(string com,int meth);
string getrdstr(int len){
	string outp;
	for(int a=0;a<len;a++){
		char tmp1='a'+rand()%26;
		outp=outp+tmp1;
	}
	return outp;
}
string createtmpdir(){
	string name=getrdstr(15);
	int ret=excutecmd("mkdir /tmp/"+name,1);
	if(ret==256){
		createtmpdir();
	}
	return "/tmp/"+name;
}
string startphp(string dirname,string filename,int errtime){

	string port;
	if(errtime<1){
		for(int a=0;a<4;a++){
			char aa='0'+rand()%10;
			port=port+aa;
		}	
		string com="php -t "+dirname+" -S 0.0.0.0:"+port;
		cout<<"visit blacktechserver.ddnsking.com:"<<port<<"/"<<filename<<" to download file"<<endl;

		int bb=excutecmd(com,1);
		if(bb=256){
			startphp(dirname,filename,errtime+1);
		}
	}
	return port;
}
void zipfile(string dirname,string targetdir){
	excutecmd("zip '"+targetdir+"/"+dirname+"' -r '"+dirname+"'",1);
	return;
}
int excutecmd(string com,int meth){
	if(meth==0){
		com=com+"/dev/null 2>&1";
	}else if(meth==1){
		com=com+" >>/tmp/sharefilelog 2>&1";
	}
	const char* comm=com.c_str();
	int aa=system(comm);
	return aa;
}
int main(int argc,char* argv[]){
	string com1;
	//cout<<argc<<endl;
	string dirname=createtmpdir();
	dirname=dirname;
	string inputfname;
	if(argc<=1){
		cout<<"please specify file name"<<endl;
		return 0;
	}
	string opt1=argv[1];
	if(opt1=="-d"){
		if(argc<=2){
			cout<<"please specify dir name"<<endl;
			return 0;
		}
		string opt2=argv[2];
		cout<<"zipping file......"<<endl;
		zipfile(opt2,opt2+"/..");
		inputfname=opt2+".zip";
	
	}else{
		inputfname=opt1;
	}
	cout<<inputfname<<endl;
	cout<<dirname<<endl;
	excutecmd("cp '"+inputfname+"' "+dirname,1);
	startphp(dirname,inputfname,0);
	

}

