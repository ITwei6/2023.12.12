#include "comm.hpp"

//进程b如果想和进行a通过共享内存通信，需要用自己的key来和共享内存进行匹配
//因为共享内存被进程a创建完了，进程b只需匹配
//进程b匹配完也需要将自己的地址空间挂接到共享内存上。

//实现同步---在通信之前创建命名管道，并打开命名管道，往命名管道里输入固定信息，才能往
//共享内存里输入。
int main()
{
   //1.获取到共享内存
   int shmid=GetSM();

   //2.挂接到地址空间
   char* shmaddr=(char*)shmat(shmid,nullptr,0);
   
   //3.开始通信
  while(true)
  {
    cout<<"Please enter:";
     cin>>shmaddr;
  }

   //4.不用了，去关联
   shmdt(shmaddr);
}