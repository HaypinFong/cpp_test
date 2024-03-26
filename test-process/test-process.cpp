#include<iostream>
#include<unistd.h>
#include<assert.h>
#include<string>
#include<cstring>
#include<cstdio>
#include<sys/wait.h>
#include<sys/types.h>
using namespace std;
 
int main()
{
    //1.创建管道
    int pipefd[2]={0};//pipefd[0]:读端，pipefd[1]:写端
    int n=pipe(pipefd);
    assert(n!=-1);
    (void)n;//debug下assert有效，release下assert无效。只定义不使用n容易报警告
 
#ifdef DEBUG
    cout<<"pipefd[0]:"<<pipefd[0]<<endl;//3
    cout<<"pipefd[1]:"<<pipefd[1]<<endl;//4
#endif
    //2.创建子进程
    pid_t id=fork();
    assert(id!=-1);
    if(id==0)
    {
        //子进程
        //3.构建单向通信的信道,父进程写入,子进程读取
        //3.1关闭子进程不需要的fd
        close(pipefd[1]);
        char buffer[1024];
        while(true)
        {
            cout<<"我是子进程["<<getpid()<<endl;
            //ssize_t s=read(pipefd[0],buffer,sizeof(buffer)-1);
            //if(s>0)
            //{
            //    buffer[s]=0;//手动添加/0
            //    cout<<"我是子进程["<<getpid()<<"]Father#"<<buffer<<endl;   
            //}
            sleep(1);
        }
        
        exit(0);
    }
    //父进程
    //3.构建单向通信的信道
    //3.1关闭父进程不需要的fd
    close(pipefd[0]);
    string message="我是父进程，我正在给你发消息";
    int count=0;
    char send_buffer[1024];
    while(true)
    {
        //3.2构建一个变化的字符串
        snprintf(send_buffer,sizeof(send_buffer),"%s[%d]:%d",message.c_str(),getpid(),count++);
        //3.3写入
        //write(pipefd[1],send_buffer,strlen(send_buffer));
        cout<<"我是父进程["<<getpid()<<endl;
        //3.4故意sleep
        sleep(1);
    }
    pid_t res=waitpid(id,nullptr,0);
    assert(res>0);
    (void)res;
    close(pipefd[1]);
    return 0;
}