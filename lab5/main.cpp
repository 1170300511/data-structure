#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#define MAX_SIZE 10//������������޸ģ�0λ����

int MAX;
int flag;
int a[MAX_SIZE+1]; //ѡ������Ĳ�������
int b[MAX_SIZE+1]; //������Ĳ�������
void selsort();  //ѡ������
void heapsort(); //�����򣬴����
void heap(int n,int k); //�������Ӻ���
int main()
{
    int i;
    printf("1:���� 2������ 3������\n");
    scanf("%d",&flag);
    printf("�ų�ǰ������(С��%d)\n",MAX_SIZE);
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
            srand((int)time(NULL));    //�������ָ������
        for(i = 1;i <= MAX_SIZE;i++){
           a[i] = b[i] = rand()%MAX_SIZE;
       }
    }
    heapsort(); //������
    selsort();  //ѡ������
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
  //start = clock();  //��ʱ��ʼ
  for(i = 1;i < MAX_SIZE && i <= MAX ;i++){
    k = i;
    for(j = i+1;j <= MAX_SIZE;j++){
        if(a[j] > a[k])
            k = j;
    }
    if(i!=k){  //�����Ҫ����
        tmp = a[i];
        a[i] = a[k];
        a[k] = tmp;
    }
  }
  QueryPerformanceCounter(&nEndTime);
  time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart;
  //finish = clock(); //��ʱ����
  //time = (double)(finish - start);
  //printf("select sort time all %lf\n",time / CLOCKS_PER_SEC);
  printf("select sort time all %lf us\n",time*1000);
}

//������
void heapsort(){
  int i,tmp;
  //clock_t start,finish;
  double time;
  LARGE_INTEGER nFreq;
  LARGE_INTEGER nBeginTime;
  LARGE_INTEGER nEndTime;
  QueryPerformanceFrequency(&nFreq);
  QueryPerformanceCounter(&nBeginTime);
  //start = clock(); //��ʱ����ʼ
  for(i = MAX_SIZE >>1; i > 0;i--)
     heap(MAX_SIZE,i); //��ʼ����
  for(i = MAX_SIZE;i > 1 && i >= (MAX_SIZE - MAX + 1);i--){
      tmp = b[i];  //�����Ѷ��Ͷѵף��ѳ���-1
      b[i] = b[1];
      b[1] = tmp;
      heap(i - 1,1);
  }
  //finish = clock(); //��ʱ����
  //time = (double)(finish - start);  //������ʱ��
  //printf("The heap sort time all %lf\n",time / CLOCKS_PER_SEC);
  QueryPerformanceCounter(&nEndTime);
  time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart;
  printf("The heap sort time all %lf us\n",time*1000);
}

//�������Ӻ���
void heap(int n,int k){
   int tmp;
   while((k<<1) <= n){ //���k�Ƿ�Ҷ�ڵ�
      if(n == (k<<1)){  //���k�ڵ�ֻ��
         if(b[n] < b[k]){ //���Ҷ�ڵ�ȸ��ڵ��ֵ����Ҫ����
            tmp = b[n];
            b[n] = b[k];
            b[k] = tmp;
         }
         break;
      }
      else{ //�������������
        if(b[2*k] > b[k] && b[2*k+1] <= b[2*k]){  //����ڸ��ڵ��ң������ң��������͸��ڵ㽻��
            tmp = b[2*k];
            b[2*k] = b[k];
            b[k] = tmp;
            k = k << 1;
        }
        else if((2*k < n)&& b[2*k+1] > b[k] && b[2*k] <= b[2*k+1]){ //�Ҵ��ڸ��ڵ㣬���Ҵ������������͸��ڵ㽻��
            tmp = b[2*k+1];
            b[2*k+1] = b[k];
            b[k] = tmp;
            k = (k << 1) + 1;
        }
        else  //���ڵ��������������ֹͣ����
          break;
      }
   }
}
