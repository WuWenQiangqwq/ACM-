#include<bits/stdc++.h>
using namespace std;

namespace wwq_bash
{
   typedef unsigned long long file_size;
   typedef vector<string> answerset;
   typedef vector<string> Cmd;
   typedef enum e
   {
       UNERROR,
       UNFIND,
       RENAME
   } Error;
   struct FileNode
  {
   string name,path;
   FileNode* Parent;
   file_size size;
   bool dir,hidden;
   vector<FileNode*> SonFile;
   FileNode(string n="",string p="",FileNode* P=NULL,file_size s=0, bool d=false,bool h=false):name(n),path(p),Parent(P),size(s),dir(d),hidden(h)
   {
   }
  };
  FileNode root("root","/",NULL,0,true,false);
  FileNode *CurrentFile;
  answerset ans;
  void init()
  {
      CurrentFile=&root;
      ans.clear();
      runcmd();
  }
  answerset parsepath(const string &path)
  {
      vector<string> ans;
      string s;
      
      if(path[0]=='/') ans.push_back("");
      else ans.push_back("c");
      int i=1;
      while(path[i]!='\0')
      {
          if(path[i]=='/')
          {
              ans.push_back(s);
              s.clear();
          }
          else s +=path[i];
      }
      return ans;
  }
  answerset parsecmd(const string &cmd)
  {
      string s="";
      Cmd c;
      int cnt=0,type=0;
      while(cmd[cnt])
      {
          if(cmd[cnt]==" "||cmd[cnt+1]=='\0') 
          {
              c.push_back(s);
              s.clear();
          }
          else s +=cmd[cnt];
      }
      return c;
  }  
  answerset& exit();
  {
      exit();
      return ans;
  }
  answerset& Pwd()
  {
      ans.push_back(CurrentFile->path);
      return ans;
  }
  answerset& ErrorHandle(Error e)
  {
      ans.clear();
      if(e==UNFIND);
      if(e==RENAME);
      return ans;
  }
  answerset& mkdir(const Cmd& path,const Cmd& args)
  {
      FileNode* f;
      if(path[0]=="c") f=CurrentFile;
      else f=&root;
      int Size =path.size();
      for(i=1;i<Size;i++)
      {
          for(int j=0;j<f->SonFile.size();j++)
          {
              if(path[i]==f->SonFile[j]->name)
              {
                  if(i<Size-1) 
                  {
                      f=f->SonFile[j];
                      break;
                  }
                  else return ErrorHandle(RENAME);
              }
              if(j==f->SonFile.size()-1&&i<Size-1) return ErrorHandle(UNFIND);
          }
      }
      bool h= (args[0]=="-h");
      f->SonFile.push_back(new FileNode(path[path.rbegin()],f->path +"/"+path[path.rbegin()],f,0,true,h);
      return ans;
  }
  answerset& find(const Cmd& path,const Cmd& args)
  {
      FileNode* f,son_f;
      	queue<FileNode*> bfs;
      bool h,r;
      for(int i=0;i<args.size();i++)
      {
        if(args[i]=="-h") h=true;
        if(args[i]=="-r") r=true;
      }
      bfs.push(f);
      while(!bfs.empty())
      {
         f=bfs.front(); bfs.pop();
	 if(f->hidden<=h)
            ans.push_back(f->path+"  "+f->size);
         for(int i=0;i<f->SonFile.size();i++)
         {
           son_f =SonFile[i];
           if(r) bfs.push(son_f);
         }
      }
     sort(begin(ans),end(ans));
     if(ans.size()==0) return ErrorHandle(UNFIND);
     return ans;
  }
    answerset& ls(const Cmd& path,const Cmd& args)
  {
      FileNode* f,son_f;
      	queue<FileNode*> bfs;
      vector<FileNode*> FileAns;
      bool h,r,s=false,d=false,ff=false;
      for(int i=0;i<args.size();i++)
      {
        if(args[i]=="-h") h=true;
        if(args[i]=="-r") r=true;
	if(args[i]=="-S") s=true;
        if(args[i]=="-f") ff=true;
        if(args[i]=="-d") d=true;
      }
      bfs.push(f);
      while(!bfs.empty())
      {
         f=bfs.front(); bfs.pop();
	 if(f->hidden<=h&&((d==f->mdr)||(!d&&!h))
           {
              FileAns.push_back(f);
           }
         for(int i=0;i<f->SonFile.size();i++)
         {
           son_f =SonFile[i];
           if(r) bfs.push(son_f);
         }
      }
     auto s1 =[](FileNode* a,FileNode* b) { return a->size==b->size?a->path<b->path: a->size<b->size};
     auto s2 =[](FileNode* a,FileNode* b) { return a->size==b->size?a->path>b->path: a->size>b->size};
     sort(begin(FileAns),end(FileAns),s?s1:s2);
     for(auto &cell :FileAns) ans.push_back(cell->path);
     if(ans.size()==0) return ErrorHandle(UNFIND);
     return ans;
  }
  answerset& cd(const Cmd& path)
  {
      FileNode* f;
      if(path[0]=="c") f=CurrentFile;
      else f=&root;
      for(i=1;i<Size;i++)
      {
          for(int j=0;j<f->SonFile.size();j++)
          {
              if(path[i]==f->SonFile[j]->name)
              {
                 f=f->SonFile[j];
                 break;
              }
              if(j==f->SonFile.size()-1&&i<Size-1) return ErrorHandle(UNFIND);
          }
      }
      return ans;
  }
  answerset& grep(const string& match,const Cmd& args)
  {
      string s("");
      for(int i=0;i<args.size();i++)
      {
          if(args[i].find(match)!=string::npos) ans.push_back(args[i]);
      }
      return ans;
  }
  answerset& touch(const Cmd& path,const Cmd& args)
  {
      FileNode* f;
      if(path[0]=="c") f=CurrentFile;
      else f=&root;
      int Size =path.size();
      for(i=1;i<Size;i++)
      {
          for(int j=0;j<f->SonFile.size();j++)
          {
              if(path[i]==f->SonFile[j]->name)
              {
                  if(i<Size-1) 
                  {
                      f=f->SonFile[j];
                      break;
                  }
                  else return ErrorHandle(RENAME);
              }
              if(j==f->SonFile.size()-1&&i<Size-1) return ErrorHandle(UNFIND);
          }
      }
      bool h=false;
      file_size Size;
      for(int i=0;i<args.size();i++)
      {
          if(args[i]=="-h") h=true;
          else Size=atoi(args[i].c_str());
      }
      f->SonFile.push_back(new FileNode(path[path.rbegin()],f->path +"/"+path[path.rbegin()],f,Size,false,h);
      return ans;
  }
  answerset& run(const string& cmd,const Cmd& path,const Cmd& args)
  {
      ans.clear();
      if(cmd=="Pwd") return Pwd();
      if(cmd=="cd") return cd(path);
      if(cmd=="mkdir") return mkdir(path,args);
      if(cmd=="touch") return touch(path,args);
      if(cmd=="find") return wwq_bash::find(path,args);
      if(cmd=="ls") return ls(path,args);
      if(cmd=="exit") return wwq_bash::exit();
      if(cmd=="grep") return grep(args,path);
  }
  void runcmd()
  {
      init();
      string s;
      getline(cin,s);
      answerset c = parsecmd(s),args;
      int cnt=0;
      while(cnt<c.size())
      {
          int k=cnt+2;
          while(k<c.size()||cnt[k]!="|") args.push_back(cnt[k]);
          args.swap(run(cmd[cnt],parsepath(cmd[cnt+1]),args));
          print(cmd[cnt],args);
          cnt =k+1;
      }
  }

}
int main()
{
    wwq_bash::init();
    return 0;
}
