#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1024  //最大容量，可修改

typedef struct yi{
  int num;
  struct yi *lc,*rc;
}*node,N; //BST树的节点

int flag = 0; //在BST删除一个树中没有的元素时，作为标志打印错误信息
int cnt;  //计数
int a[MAX_SIZE]; //保存测试数据


void printmenu();  //打印菜单
void insert_BST(node &F,int data); //插入
void delete_BST(node &F,int data); //删除
int deletemin(node &F,int data); //寻找右儿子的最左节点，并删除改节点
void creat_BST(node &F); //建立BST查找树
void halfsearch(int data); //折半查找
void writetest(); //生成测试数据
void getsort(node F); //得到BST树的中序遍历序列，保存在数组a[]中
void search_BST(node F,int data); //在BST查找树中查找元素data
void countBST(node F); //计算BST的查找成功与失败的平均次数
void counthalf();  //计算BST查找成功和失败的平均次数
int main()
{
    node F = NULL;  //BST树
int sel,data;
    while(1){
       printmenu();
       scanf("%d",&sel);
       switch(sel){
          case 0:exit(0);
          case 1:free(F);
                 F = NULL;
                 creat_BST(F);
                 break;
          case 2:printf("Input the num you want to insert:\n");
                 scanf("%d",&data);
                 insert_BST(F,data);
                 break;
          case 3:printf("Input the number you want to delete:\n");
                 scanf("%d",&data);
                 flag = 0;
                 delete_BST(F,data);
                 if(!flag) printf("Cant't find this number in the BSTtree\n");
                 break;
          case 4:printf("Input the number you want to search:\n");
                 scanf("%d",&data);
                 search_BST(F,data);
                 break;
          case 5:cnt = 0;
                 getsort(F);
                 break;
          case 6:printf("Input a number you want to search:\n");
                 scanf("%d",&data);
                 halfsearch(data);
                 break;
          case 7:writetest();
                 break;
          case 8:countBST(F);
                 break;
          case 9:counthalf();
                 break;
          default:
              printf("Input error!\n");
       }

       system("pause");
    }

    return 0;
}

void printmenu(){
  printf("0.quit\n");
  printf("1.creat BSTtree\n");
  printf("2.insert a number\n");
  printf("3.delete a number\n");
  printf("4.search a number\n");
  printf("5.sort the BSTtree\n");
  printf("6.half search\n");
  printf("7.correct the test trace\n");
  printf("8.test the quality of of BST\n");
  printf("9.count the quality of half\n");
}

void insert_BST(node &F,int data){
  node p;
  if(F == NULL) //将data插入到叶的位置
  {
      p = (node)malloc(sizeof(N));
      p -> num = data;
      p -> rc = NULL;
      p -> lc = NULL;
      F = p;
  }
  else if(F -> num == data){  //如果BST树中已经存在data
    printf("Failed.You want to insert a number that exits in the BSTtree.\n");
  }
  else if(F -> num > data)  //data小于根节点的值，插入左边
    insert_BST(F -> lc,data);
  else  //data大于根节点的值，插入右边
    insert_BST(F -> rc,data);
}

void delete_BST(node &F,int data){
   if(F == NULL)  //如果BST为空，直接返回
      return;
   if(data > F -> num ) //如果data的值大于根节点的值，删右边
     delete_BST(F -> rc ,data);
   else if(data < F -> num)  //如果data的值小于根节点的值，删左边
     delete_BST(F -> lc,data);
   else{  //找到要删除的节点
     flag = 1;  //BST查找树中有要删的数据
     printf("Delete successfully!\n");
     //寻找继承节点
     if(F -> lc == NULL)  //左儿子为空，右儿子继承
        F = F -> rc;
     else if(F -> rc == NULL) //右儿子为空，左儿子继承
        F = F -> lc;
     else
        F -> num = deletemin(F -> rc,data); //左右儿子都不空，寻找右儿子的最左节点继承
   }
}

int deletemin(node &F,int data){
    int tmp;
    node p;
  if(F -> lc == NULL){  //找到最左节点
    tmp = F -> num; //保存返回数据
    p = F;
    F = F -> rc; //该节点左儿子为空，直接右儿子继承
    free(p); //删除该节点
    return tmp;
  }
  else
    return deletemin(F -> lc,data); //左儿子不为空，继续找左儿子的左儿子
}

void creat_BST(node &F){
  int i;
  for(i = 0;i < MAX_SIZE;i++)
    insert_BST(F,a[i]); //将测试数据一个一个依次插入BST树中
}

void search_BST(node F,int data){
  clock_t start,finish;//用于保存时刻
  double time; //时间段
  cnt = 0; //计数器置0
  start = clock(); //计时器开始
  while(F != NULL){
        cnt ++;  //比较次数+1
     if(F -> num == data){  //找到
        finish = clock();  //计时器结束
        time = (double)(finish - start); //计算查找时间
        //printf("Find it!Time all %lf\n",time / CLOCKS_PER_SEC); //打印查找成功信息
        return;
     }
     else if(F -> num > data) //data小于根节点的值，根节点更新为左儿子，继续查找
        F = F -> lc;
     else   //data大于根节点的值，找右儿子
        F = F -> rc;
  }
  finish = clock(); //没有找到，计时结束
  time = (double)(finish - start); //求不成功时间
  //printf("Unfind it!Time all %lf\n",time/CLOCKS_PER_SEC); //打印失败信息
  return ;
}


void getsort(node F){
   if(F != NULL){
      if(F -> lc) //左不空，遍历左
        getsort(F -> lc);
      a[cnt++] = F -> num;//访问根节点
      if(F -> rc) //右不空，遍历右
        getsort(F -> rc);
   }
}

void halfsearch(int data){
   int left,right,mid;
   double time;
   clock_t start,finish;  //记录时刻
   start = clock(); //计时开始
   cnt = 0; //计数器置0
   left = 0;right = MAX_SIZE - 1;  //初始化left,right
   while(left <= right){
      mid = (left+right)>>1; //参考位置
      cnt ++; //比较次数+1
      if(a[mid] == data){  //找到
         finish = clock();//计时结束
         time = (double)(finish - start); //计算查找时间
         //printf("Find it!Time all %.lf\n",time); //打印查找成功的消息
         return;
      }
      //未找到
      else if(a[mid] > data)//比中间的小，上左边找
         right = mid - 1;
      else //比中间的大，上右边找
         left = mid + 1;
   }
   //查找失败
   finish = clock(); //计时结束
   time = (double)(finish - start); //计算查找时间
   //printf("Unfind!Time all %lf\n",time/CLOCKS_PER_SEC); //打印失败时间
}

void writetest(){
  int sel,i,j,t,m;
  printf("Input number 2 or 1 to choose a test data example.\n");
  scanf("%d",&sel);
   if(sel == 2||sel == 1){  //选择一个测试序列，其中1为顺序，2为乱序
     for(i = 0;i < MAX_SIZE;i++)
       a[i] = (i+1)<<1;
     if(sel == 2)
       for(i = 0;i < (MAX_SIZE >> 7);i++){ //调整次数控制
         srand((int)time(NULL));
         for(j = 1;j < MAX_SIZE - 3;j++){
           m = rand();
           if(m%3){  //根据随机数是否被3整除来决定是否需要交换
             t = a[j];
             a[j] = a[MAX_SIZE - (m%MAX_SIZE)];
             a[MAX_SIZE - (m%MAX_SIZE)] = t;
          }
        }
     }
  }
  else
    printf("You input a invalid number!\n");
}

void countBST(node F){
  long sum = 0;
  int i;
  //查找成功平均次数计算
  for(i = 0;i < MAX_SIZE;i++){
    search_BST(F,a[i]);  //查一个计数一个
    sum += cnt;
  }
  sum = sum / MAX_SIZE;
  printf("The BST search successfully for %ld times\n",sum);
  //查找失败平均次数计算
  sum = 0;
  for(i = 0;i < MAX_SIZE;i++){
    search_BST(F,a[i]-1);
    sum += cnt;
  }
  sum = sum / MAX_SIZE;
  printf("The BST search unsuccessfully for %ld times\n",sum);
}

void counthalf(){
  long sum = 0;
  int i;
  //查找成功平均次数计算
  for(i = 0;i < MAX_SIZE;i++){
    halfsearch(a[i]);
    sum += cnt;
  }
  sum = sum / MAX_SIZE;
  printf("The half search successfully for %ld times\n",sum);
  //查找失败平均次数计算
  sum = 0;
  for(i = 0;i < MAX_SIZE;i++){
    halfsearch(a[i]+1);
    sum += cnt;
  }
  sum = sum / MAX_SIZE;
  printf("The half search unsuccessfully for %ld times\n",sum);
}
