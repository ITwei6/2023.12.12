#include <iostream>

using namespace std;
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
//key值的获取根据系统调用ftok(pathname,pro_id)

const string pathname="/home/tao";
const int pro_id=0x6666;
int size= 4096;

//这是用户自己决定的
//Log log;
key_t GetKey()
{
    key_t k=ftok(pathname.c_str(),pro_id);
    if(k<0) 
    {
       // log(Fatal,"ftok error:%s",strerror(errno));//致命错误
        exit(1);
    }
    //普通日志：成功
    //log(Info,"ftok success key is %d",k);
    return k;
}

int GetMEm(int flag=IPC_CREAT|IPC_EXCL|0666)//默认是创建，权限是0666
{
    int key=GetKey();
    int shmid=shmget(key,size,flag);//确保每次创建的都是新的共享内存
    if(shmid<0)
    {
     //   log(Fatal,"Creat shmget error:%s",strerror(errno));
        exit(2);
    }
    //log(Info,"Creat shmget success shmid is%d",shmid);
    return shmid;
}

//进程a是创建共享内存的，而进程b是要获取共享内存的，我们可以通过传不同的参数
//调用同一个GetMem来完成，因为获取共享内存，我们就不加上IPC_EXCL就可以实现
//如果共享内存以及存在，就直接返回该共享内存。

int CreatSM()
{
    return GetMEm();//默认是创建
}
int GetSM()
{
    return GetMEm(IPC_CREAT);//只传入IPC_CREAT就是获取原先存在的共享内存
}



