#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#define MAX_SIZE 10//最大容量，可修改，0位不用

int MAX;
int flag;
int a[MAX_SIZE+1]; //选择排序的测试数据
int b[MAX_SIZE+1]; //堆排序的测试数据
void selsort();  //选择排序
void heapsort(); //堆排序，大根堆
void heap(int n,int k); //堆排序子函数
int main()
{
    int i;
    printf("1:正序 2：无序 3：逆序\n");
    scanf("%d",&flag);
    printf("排出前几个？(小于%d)\n",MAX_SIZE);
    scanf("%d",&MAX);
    if(flag == 1){
    for(i = 1;i <= MAX_SIZE;i++){
           a[i] = b[i] = MAX_SIZE - i;
       }
    }
    else if(flag == 3){
        for(i = 1;i <= MAX_SIZE;i++){
           a[i] = b[i] = i;
       }
    }
    else {
            srand((int)time(NULL));    //随机生成指定序列
        for(i = 1;i <= MAX_SIZE;i++){
           a[i] = b[i] = rand()%MAX_SIZE;
       }
    }
    heapsort(); //堆排序
    selsort();  //选择排序
    return 0;
}


void selsort(){
  int i,j,k,tmp;
  //clock_t start,finish;
  double time;
  LARGE_INTEGER nFreq;
  LARGE_INTEGER nBeginTime;
  LARGE_INTEGER nEndTime;
  QueryPerformanceFrequency(&nFreq);
  QueryPerformanceCounter(&nBeginTime);
  //start = clock();  //计时开始
  for(i = 1;i < MAX_SIZE && i <= MAX ;i++){
    k = i;
    for(j = i+1;j <= MAX_SIZE;j++){
        if(a[j] > a[k])
            k = j;
    }
    if(i!=k){  //如果需要交换
        tmp = a[i];
        a[i] = a[k];
        a[k] = tmp;
    }
  }
  QueryPerformanceCounter(&nEndTime);
  time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart;
  //finish = clock(); //计时结束
  //time = (double)(finish - start);
  //printf("select sort time all %lf\n",time / CLOCKS_PER_SEC);
  printf("select sort time all %lf us\n",time*1000);
}

//堆排序
void heapsort(){
  int i,tmp;
  //clock_t start,finish;
  double time;
  LARGE_INTEGER nFreq;
  LARGE_INTEGER nBeginTime;
  LARGE_INTEGER nEndTime;
  QueryPerformanceFrequency(&nFreq);
  QueryPerformanceCounter(&nBeginTime);
  //start = clock(); //计时器开始
  for(i = MAX_SIZE >>1; i > 0;i--)
     heap(MAX_SIZE,i); //初始化堆
  for(i = MAX_SIZE;i > 1 && i >= (MAX_SIZE - MAX + 1);i--){
      tmp = b[i];  //交换堆顶和堆底，堆长度-1
      b[i] = b[1];
      b[1] = tmp;
      heap(i - 1,1);
  }
  //finish = clock(); //计时结束
  //time = (double)(finish - start);  //计算总时间
  //printf("The heap sort time all %lf\n",time / CLOCKS_PER_SEC);
  QueryPerformanceCounter(&nEndTime);
  time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart;
  printf("The heap sort time all %lf us\n",time*1000);
}

//堆排序子函数
void heap(int n,int k){
   int tmp;
   while((k<<1) <= n){ //如果k是非叶节点
      if(n == (k<<1)){  //如果k节点只有
         if(b[n] < b[k]){ //如果叶节点比根节点的值大，需要交换
            tmp = b[n];
            b[n] = b[k];
            b[k] = tmp;
         }
         break;
      }
      else{ //如果有两株子树
        if(b[2*k] > b[k] && b[2*k+1] <= b[2*k]){  //左大于根节点且，大于右，左子树和根节点交换
            tmp = b[2*k];
            b[2*k] = b[k];
            b[k] = tmp;
            k = k << 1;
        }
        else if((2*k < n)&& b[2*k+1] > b[k] && b[2*k] <= b[2*k+1]){ //右大于根节点，且右大于左，右子树和根节点交换
            tmp = b[2*k+1];
            b[2*k+1] = b[k];
            b[k] = tmp;
            k = (k << 1) + 1;
        }
        else  //根节点大于两株子树，停止遍历
          break;
      }
   }
}
