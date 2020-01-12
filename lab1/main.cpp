#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct Mystack{
  char ch;
  double num;
  struct Mystack *next;
}MYSTACK,*LINK;  //符号存储的数据结构，同时作为符号栈和double栈使用


LINK push(LINK head,char ch);  //将符号压入栈
LINK pop(LINK head);  //弹栈
LINK pushnum(LINK headnum,double n);  //将数字压栈
char top(LINK head);  //得到栈顶的字符
double topnum(LINK hesdnum); //得到栈顶的数字
int isempty(LINK head);  //判断栈是否为空栈，是返回1否则返回0
int dis(char ch);  //返回运算符对于的数字，来判断优先级
double twonum(double num1,double num2,char ch); //对两个数字进行一些运算操作


int checkbrackets(char in[]);  //检查括号匹配
int checkchar(char in[]);  //检查字符种类是否合法
int checkpipei(char in[]);  //检查字符序列是否合法



double compute(LINK head,LINK headnum,char in[]);  //计算表达式的值

void printhouzhui(LINK head,char in[]);  //输出后缀表达式
void printstack(LINK head);  //打印栈中的字符



int main()
{
    LINK head,headnum;  //用head和headnum来区分字符和数字双栈的的头指针
    char in[100];
    headnum = (LINK)malloc(sizeof(MYSTACK));
    headnum -> next = NULL;
    head = (LINK)malloc(sizeof(MYSTACK));
    head -> next = NULL;
    while(1){
        printf("请输入任意中缀表达式：\n");
        gets(in);
        if(strcmp(in,"quit")==0)
            break;
        else if(checkbrackets(in)&&checkchar(in)&&checkpipei(in)){ //如果检查为合法输入
        printhouzhui(head,in);
        printf("\n%.6lf\n",compute(head,headnum,in));
        }
        else
           printf("Input error!\n");
    }
    return 0;
}

LINK push(LINK head,char in_ch){
  LINK pt;
  pt = (LINK)malloc(sizeof(MYSTACK));
  pt -> ch = in_ch;
  pt -> next = head;
  return pt;
}

LINK pushnum(LINK headnum,double n){
   LINK pt;
   pt = (LINK)malloc(sizeof(MYSTACK));
   pt -> num = n;
   pt -> next = headnum;
   return pt;
}

LINK pop(LINK head){
    LINK pt;
    pt = head -> next;
    head -> next = NULL;
    return pt;
}

char top(LINK head){

    return head -> ch;

}

double topnum(LINK headnum){
   return headnum -> num;
}

int isempty(LINK head){
 if(head -> next == NULL)
      return 1;
 return 0;
}


int dis(char ch){
  switch(ch){
   case '^' : return 4;
   case '*' : return 3;
   case '/' : return 3;
   case '%' : return 2;
   case '+' : return 1;
   case '-' : return 1;
   default  : return 0;
  }
}

double twonum(double num1,double num2,char ch){
  switch(ch){
  case '+' :return num1+num2;
  case '-' :return num2-num1;
  case '*' :return num1*num2;
  case '/' :return num2/num1;
  case '^' :return pow(num2,num1);
  case '%' :return fmod(num2,num1);
  default :return 1.0;
  }
}

void printstack(LINK head){
    while(head -> next != NULL){
        printf("%c\n",head -> ch);
        head = head -> next;
    }
    printf("\n");
}



void printhouzhui(LINK head,char in[]){
    int i = 0,j = 0;
    int flag = 0,ff = 0;
    char re[100];
    while(in[i] != '#'&&in[i] != '\0'){
        if(!isempty(head)){
             printstack(head);
        }
        if(in[i] == ' ')
        {
            i++;
            continue;
        }
        else if(in[i] <= 57 && in[i] >= 48){
            if(ff){    //处理浮点数
                re[j] = in[i];
                j++;
                i++;
                continue;
            }
            if(i == 0){
                re[j] = in[i];
                j++;
                i++;
                continue;
            }
            re[j] = ' ';
            re[j+1] = in[i];
            j += 2;
            i++;
            continue;
        }
        else{
            if(in[i] == '.'){
                ff = 1;
                re[j] = in[i];
                j++;
                i++;
                continue;
            }
            else if(isempty(head)){
                ff = 0;
                head = push(head,in[i]);
                i++;
                continue;
            }
            else if(in[i] == 40){  //遇到左括号
                ff = 0;
                flag ++;
                head = push(head,in[i]);
                i++;
                continue;
            }
            else if(top(head) == 40){  //前一个是左括号
                ff = 0;
                if(!flag){  //右括号全出现以后
                    head = pop(head);
                    continue;
                }
                else{
                    head = push(head,in[i]);
                    i++;
                    continue;
                }
            }
            else if(in[i] == 41){  //遇到右括号
                ff = 0;
                flag --;
                i++;
                continue;
            }
            else if(dis(top(head)) < dis(in[i]))  //若运算优先级大于栈顶字符
            {
                ff = 0;
                head = push(head,in[i]);
                i++;
                continue;
            }
            else{
                ff = 0;
                re[j] = ' ';
                re[j+1] = top(head);
                j += 2;
                head = pop(head);
                continue;
            }
        }
    }
    while(!isempty(head)){  //处理栈中剩余的元素
        printstack(head);
        if(top(head) != 40){
            re[j] = ' ';
            re[j+1] = top(head);
            j += 2;
        }
        head = pop(head);
    }
    re[j] = '\0';
    printf("%s\n",re);
}




//思路与后缀表达式大体一样，有细微差别
double compute(LINK head,LINK headnum,char in[]){
  int i = 0,flag = 0,ll = 0,ff = 0;
  double num1,num2;
  char ch;
  headnum = pushnum(headnum,0.0);
  while(in[i]!= '\0'&&in[i] != '#'){
     if(in[i] == ' '){
            i++;
            continue;
        }
     else if(in[i] >= 48 && in[i] <= 57){
        if(ll)      //处理多位整数
            headnum -> num = (headnum -> num)*10 + in[i] - 48;
        else if(ff){    //处理多位浮点数
            headnum -> num = (headnum -> num) + pow(0.1,ff)*(in[i] - 48);
            ll = 0;
            ff++;
            i++;
            continue;
        }
        else
            headnum = pushnum(headnum,in[i]-48);
        i++;
        ll = 1;
        continue;
    }
    else{
        ll = 0;
        if(in[i] == '.'){
          ff ++;
          i++;
          continue;
        }

        else if(isempty(head)){
            ff = 0;
            head = push(head,in[i]);
            i++;
            continue;
        }
        else if(in[i] == 40){
            ff = 0;
            head = push(head,in[i]);
            i++;
            continue;
        }
        else if(top(head) == 40){
            flag ++;
            ff = 0;
            if(in[i] == 41){
                head = pop(head);
                i++;
                continue;
            }
            else if(!flag)
               head = pop(head);
            else{
               head = push(head,in[i]);
               i++;
            }
            continue;
        }
        else if(in[i] == 41){  //遇到右括号要去掉这一层运算以及相应的左括号
            flag --;
            ff = 0;
            while(top(head) != 40){
            num1 = topnum(headnum);
            headnum = pop(headnum);
            num2 = topnum(headnum);
            headnum = pop(headnum);
            ch = top(head);
            head = pop(head);
            headnum = pushnum(headnum,twonum(num1,num2,ch));
            }
            continue;
        }
        else if(dis(in[i]) <= dis(top(head))){
           ff = 0;
           num1 = topnum(headnum);
           headnum = pop(headnum);
           num2 = topnum(headnum);
           headnum = pop(headnum);
           ch = top(head);
           head = pop(head);
           headnum = pushnum(headnum,twonum(num1,num2,ch));
           continue;
        }
        else{
            ff = 0;
            head = push(head,in[i]);
            i++;
        }
    }
  }
while(!isempty(head)){
    if(top(head)==40)
        head = pop(head);
    num1 = topnum(headnum);
    headnum = pop(headnum);
    num2 = topnum(headnum);
    headnum = pop(headnum);
    ch = top(head);
    head = pop(head);
    headnum = pushnum(headnum,twonum(num1,num2,ch));
}
  return headnum -> num;
}


int checkbrackets(char in[]){
   int flag = 0,i = 0;
   while(in[i] != '#' && in[i] != '\0'){
    if(in[i] == 40)
        flag ++;
    if(in[i] == 41)
        flag --;
    i++;
   }
   if(!flag)
      return 1;
   return 0;
}

int checkchar(char in[]){
   int i = 0,flag = 1;
   while(in[i] != '#'  && in[i] != '\0'){
    if((in[i]>=48&&in[i]<=57)||in[i] == ' '||in[i] == '+'||in[i] == '-'||in[i] == '*'||in[i] == '/'||in[i] == '.'||in[i] == 40||in[i]==41||in[i]=='^'||in[i]=='%')
    {
        i++;
        continue;
    }
    else{
        flag = 0;
        break;
    }
   }
   if((in[i-1]>=48&&in[i-1]<=57)||(in[i-1]==41)) ;
   else   flag = 0;
   return flag;
}

int checkpipei(char in[]){
    int i = 0,flag = 1;
    LINK pt;
    pt = (LINK)malloc(sizeof(MYSTACK));
    pt -> next = NULL;
    while(in[i]!= '#' && in[i] != '\0'){
       if(in[i] == ' '){
        i++;
        continue;
       }
       else if(isempty(pt)){
          pt = push(pt,in[i]);
          i++;
        continue;
       }
       else if(top(pt) == in[i]){
          if((in[i]>=48&&in[i]<=57)||in[i]==40||in[i]==41){
          pt = push(pt,in[i]);
          i++;
          continue;
          }
          else{
            flag = 0;
            break;
          }
       }
       else if(top(pt) == 40){
          if((in[i]>=48&&in[i]<=57)||in[i] == 40){
            pt = push(pt,in[i]);
            i++;
            continue;
          }
          else{
            flag = 0;
            break;
          }
       }
       else if(top(pt) == 41){
        pt = push(pt,in[i]);
        i++;
        continue;
       }
       else if(in[i]==40){
         pt = push(pt,in[i]);
         i++;
         continue;
       }
       else if(in[i] == 41){
         if((top(pt)>=48&&top(pt)<=57)||top(pt)==41){
            pt = push(pt,in[i]);
            i++;
            continue;
        }
         else{
            flag = 0;
            break;
        }
       }
       else if(in[i]>=48&&in[i]<=57){
         pt = push(pt,in[i]);
         i++;
         continue;
       }
       else if(top(pt)!=in[i] && !(in[i]>=48&&in[i]<=57)  && !(top(pt)<=57&&top(pt)>=48)){
         flag = 0;
         break;
       }
       else{
         pt = push(pt,in[i]);
         i++;
       }
    }
    return flag;
}
