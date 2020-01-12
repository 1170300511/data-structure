#include <stdio.h>
#include <stdlib.h>

#define SI 100

char str[SI];
int i;


typedef struct yi{
  char data;
  struct yi *lc,*rc;
}*node,NODE;  //二叉树节点

typedef struct {
  node que[SI];
  int start,rear;
}seque;  //二叉树节点队列

typedef struct{
  char data,parent,tag;
}cache;  //存三个字符


node createbtree();  //建立二叉树
node findx(node btree,char ch); //查找元素ch在书中哪个节点

void preprint(node btree);  //先序递归遍历
void prefdgprint(node btree); //先序非递归遍历
void midprint(node btree); //中序递归遍历
void midfdgprint(node btree); //中序非递归遍历
void endprint(node btree); //后序递归遍历
void endfdgprint(node btree); //后续非递归遍历
void cengxuprint(node btree); //层序遍历
void printbtree(node btree); //打印二叉树
void printmenu();  //打印菜单
int findsameparent(node btree);  //寻找两个节点最近的共同祖先
void isfullbtree(node btree);  //判断是否是完全二叉树

int main()
{
   node btree;
   int sel;
   while(1){
      printmenu();
      scanf("%d",&sel);
      switch(sel){
      case 0 :printf("您已选择退出程序!感谢使用!\n");
              exit(0);
      case 1 :printf("请按层序输入二叉树的信息：(格式为:数据 父节点数据 为父节点的左（右）子树输入L（R）,中间不留空格，以“###”结束)\n");
              btree = createbtree();
              printbtree(btree);
              printf("\n");
              break;
      case 2 :i = 0;
              preprint(btree);
              str[i] = '\0';
              printf("%s\n",str);
              break;
      case 3 :i = 0;
              prefdgprint(btree);
              str[i] = '\0';
              printf("%s\n",str);
              break;
      case 4 :i = 0;
              midprint(btree);
              str[i] = '\0';
              printf("%s\n",str);
              break;
      case 5 :i = 0;
              midfdgprint(btree);
              str[i] = '\0';
              printf("%s\n",str);
              break;
      case 6 :i = 0;
              endprint(btree);
              str[i] = '\0';
              printf("%s\n",str);
              break;
      case 7 :i = 0;
              endfdgprint(btree);
              str[i] = '\0';
              printf("%s\n",str);
              break;
      case 8 :i = 0;
              cengxuprint(btree);
              str[i] = '\0';
              printf("%s\n",str);
              break;
      case 9 :i = findsameparent(btree);
              break;
      case 10:i = 0;
              isfullbtree(btree);
              break;
      default :
              printf("您的输入有误，请重新输入！\n");
      }
   }
   return 0;
}


void printmenu(){
   printf("* * * * * * * * * * * * * * * * * * * * *\n");
   printf("* 0:退出.                               *\n");
   printf("* 1:输入二叉树的信息.                   *\n");
   printf("* 2:先序递归遍历二叉树并输出遍历序列.   *\n");
   printf("* 3:先序非递归遍历二叉树并输出遍历序列. *\n");
   printf("* 4:中序递归遍历二叉树并输出遍历序列.   *\n");
   printf("* 5:中序非递归遍历二叉树并输出遍历序列. *\n");
   printf("* 6:后序递归遍历二叉树并输出遍历序列.   *\n");
   printf("* 7:后序非递归遍历二叉树并输出遍历序列. *\n");
   printf("* 8:层序遍历二叉树并输出遍历序列.       *\n");
   printf("* 9:输入两个结点，输出他们最近的祖先.   *\n");
   printf("* 10:判断是否为完全二叉树.              *\n");
   printf("* * * * * * * * * * * * * * * * * * * * *\n");
}


//创建二叉树
node createbtree(){
   cache in;
   seque pt;
   node tree,root;
   pt.start = pt.rear = 0;
   root = (node)malloc(sizeof(NODE));
   while(1){
       getchar();
       //读入一个节点
       scanf("%c",&in.data);
       scanf("%c",&in.parent);
       scanf("%c",&in.tag);
       if(in.data == '#' && in.parent == '#')
          break;
       tree = (node)malloc(sizeof(NODE));
       tree -> data = in.data;
       tree -> rc = NULL;
       tree -> lc = NULL;
       pt.que[pt.rear] = tree;
       pt.rear = (pt.rear + 1)% SI;
       if(in.parent == '#')  //如果父节点为空
           root = tree;
       else{
            while(pt.start != pt.rear && pt.que[pt.start] -> data != in.parent)  //如果队列不空，而且队列的第一个元素不是输入元素的父节点，第一个元素出队
               pt.start = (pt.start + 1) % SI ;
            if(in.tag == 'R' or in.tag == 'r')  //如果是右子树
                pt.que[pt.start] -> rc = tree;
            else  //如果是左子树
                pt.que[pt.start] -> lc = tree;
       }

   }
  return root;
}

//先序递归遍历
void  preprint(node btree){
   if(btree != NULL){
    str[i++] = btree -> data;
    preprint(btree -> lc);
    preprint(btree -> rc);
   }
}

//先序非递归遍历
void prefdgprint(node btree){
   node pt[SI];  //创建一个指针数组
   int top = -1;  //初始化
   while(top != -1 || btree != NULL){  //栈不空或者树不空
       while(btree != NULL){  //如果树不空
           pt[++top] = btree -> rc;  //右节点入栈
           str[i++] = btree -> data;  //计入字符串数组
           btree = btree -> lc; //更新节点为左子树
       }
       if(top != -1){  //如果栈不为空，取出栈顶的元素
           btree = pt[top--];
       }
   }
}

//中序递归遍历
void midprint(node btree){
   if(btree != NULL){
    midprint(btree -> lc);
    str[i++] = btree -> data;
    midprint(btree -> rc);
   }
}

//中序非递归遍历
void midfdgprint(node btree){
    node pt[SI];
    int top = -1;
    while(top != -1 || btree != NULL){
         while(btree != NULL){
            pt[++top] = btree;
            btree = btree -> lc;
         }
         if(top != -1){
            btree = pt[top--];
            str[i++] = btree -> data;
            btree = btree -> rc;
         }
    }
}

//后序递归遍历
void endprint(node btree){
   if(btree != NULL){
    endprint(btree -> lc);
    endprint(btree -> rc);
    str[i++] = btree -> data;
   }
}

//后序非递归遍历
void endfdgprint(node btree){
   node pt[SI],pr;
   int top = -1;
   while(top != -1 || btree != NULL ){
       while(btree != NULL){
           pt[++top] = btree;
           pr = btree -> rc;
           btree = btree -> lc;
           if(btree == NULL)
              btree = pr;
       }
       btree = pt[top--];
       str[i++] = btree -> data;
       if(top != -1 && pt[top] -> lc == btree)
           btree = pt[top] -> rc;
       else
           btree = NULL;
   }
}

//层序遍历
void cengxuprint(node btree){
    node pt[SI];
    int s = 0,e = 0;
    pt[e] = btree;
    e = (e+1)%SI;
    while(s != e){
       btree = pt[s];
       if(btree -> lc != NULL){
           pt[e] = btree -> lc;
           e = (e+1)%SI;
       }
       if(btree -> rc != NULL){
           pt[e] = btree -> rc;
           e = (e+1)%SI;
       }
       str[i++] = btree -> data;
       s++;
    }
}

//打印二叉树
void printbtree(node btree){
    if(btree != NULL){
        if(btree -> lc != NULL || btree -> rc != NULL)
            printf("<");
        printf("%c ",btree -> data);
        printbtree(btree -> lc);
        if(btree -> lc == NULL && btree -> rc != NULL)
            printf("# ");
        printbtree(btree -> rc);
        if(btree -> rc == NULL && btree -> lc != NULL)
            printf("# ");
        if(btree -> lc != NULL || btree -> rc != NULL)
            printf(">");
    }
}

//寻找两个节点最近的公共祖先
int findsameparent(node btree){
   char ch1,ch2;
   node p;
   node flag1,flag2;
   printf("请输入两个节点名字，不需隔开：\n");
   getchar();
   scanf("%c %c",&ch1,&ch2);
   if(ch1 == ch2){
      printf("输入有误！两个节点相同！\n");
      return 0;
   }
   flag1 = findx(btree,ch1);
   flag2 = findx(btree,ch2);
   if(flag1 == NULL||flag2 == NULL){
       printf("输入错误！输入了树中不存在的元素！\n");
       return 0;
   }
   else{
       while(1){
          p = btree;
          if(findx(btree -> lc,ch1) != NULL && findx(btree -> lc,ch2) != NULL)  //如果左子树是两个节点的公共祖先，更新节点为左子树
              btree = btree -> lc;
          else if(findx(btree -> rc,ch1)!= NULL && findx(btree -> rc ,ch2) != NULL)  //如果右子树是两个节点的公共祖先，更新节点为右子树
              btree = btree -> rc;
          else  //如果不全在左边，也不全在右边，则p为最近的公共祖先
              break;
       }
       printf("最近的祖先节点是:%c\n",p -> data);
   }
    return 0;
}


//寻找元素ch所在节点，不在树中则返回NULL
node findx(node btree,char ch){  //遍历
   node bque[SI];
   int top = -1;
   while(top != -1 || btree != NULL){
       while(btree != NULL){
           bque[++top] = btree;
           if(btree -> data == ch)
               return btree;
           btree = btree -> lc;
       }
       if(top != -1){
           btree = bque[top];
           bque[top--] = NULL;
           btree = btree -> rc;
       }
   }
   return NULL;
}

//判断树是不是完全树
void isfullbtree(node btree){ //层序扫描
   int j = 0,flag = 1,k;
   node p,l,r;
   str[i] = '\0';
   cengxuprint(btree);  //层序序列存在str中
   while(str[j] != '\0'){
      p = findx(btree,str[j]);
      l = p -> lc;
      r = p -> rc;
      if(l == NULL && r != NULL){  //如果左子树为空，而右子树不为空，则不是完全二叉树
         flag = 0;
         break;
      }
      if(r == NULL){  //如果出现右子树为空的节点，则后面的节点都不能有子树
          for(k = j+1;str[k] != '\0';k++){
               p = findx(btree,str[k]);
               l = p -> lc;
               r = p -> rc;
               if(l != NULL || r != NULL){  //如果有子树，不是完全二叉树
                   flag = 0;
                   break;
               }
          }
          break;
      }
      j++;
   }
   if(flag)
      printf("这是一个完全二叉树！\n");
   else
      printf("这不是一个完全二叉树！\n");
}
