#include <stdio.h>
#include <stdlib.h>

#define SI 100

char str[SI];
int i;


typedef struct yi{
  char data;
  struct yi *lc,*rc;
}*node,NODE;  //�������ڵ�

typedef struct {
  node que[SI];
  int start,rear;
}seque;  //�������ڵ����

typedef struct{
  char data,parent,tag;
}cache;  //�������ַ�


node createbtree();  //����������
node findx(node btree,char ch); //����Ԫ��ch�������ĸ��ڵ�

void preprint(node btree);  //����ݹ����
void prefdgprint(node btree); //����ǵݹ����
void midprint(node btree); //����ݹ����
void midfdgprint(node btree); //����ǵݹ����
void endprint(node btree); //����ݹ����
void endfdgprint(node btree); //�����ǵݹ����
void cengxuprint(node btree); //�������
void printbtree(node btree); //��ӡ������
void printmenu();  //��ӡ�˵�
int findsameparent(node btree);  //Ѱ�������ڵ�����Ĺ�ͬ����
void isfullbtree(node btree);  //�ж��Ƿ�����ȫ������

int main()
{
   node btree;
   int sel;
   while(1){
      printmenu();
      scanf("%d",&sel);
      switch(sel){
      case 0 :printf("����ѡ���˳�����!��лʹ��!\n");
              exit(0);
      case 1 :printf("�밴�����������������Ϣ��(��ʽΪ:���� ���ڵ����� Ϊ���ڵ�����ң���������L��R��,�м䲻���ո��ԡ�###������)\n");
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
              printf("���������������������룡\n");
      }
   }
   return 0;
}


void printmenu(){
   printf("* * * * * * * * * * * * * * * * * * * * *\n");
   printf("* 0:�˳�.                               *\n");
   printf("* 1:�������������Ϣ.                   *\n");
   printf("* 2:����ݹ�����������������������.   *\n");
   printf("* 3:����ǵݹ�����������������������. *\n");
   printf("* 4:����ݹ�����������������������.   *\n");
   printf("* 5:����ǵݹ�����������������������. *\n");
   printf("* 6:����ݹ�����������������������.   *\n");
   printf("* 7:����ǵݹ�����������������������. *\n");
   printf("* 8:��������������������������.       *\n");
   printf("* 9:����������㣬����������������.   *\n");
   printf("* 10:�ж��Ƿ�Ϊ��ȫ������.              *\n");
   printf("* * * * * * * * * * * * * * * * * * * * *\n");
}


//����������
node createbtree(){
   cache in;
   seque pt;
   node tree,root;
   pt.start = pt.rear = 0;
   root = (node)malloc(sizeof(NODE));
   while(1){
       getchar();
       //����һ���ڵ�
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
       if(in.parent == '#')  //������ڵ�Ϊ��
           root = tree;
       else{
            while(pt.start != pt.rear && pt.que[pt.start] -> data != in.parent)  //������в��գ����Ҷ��еĵ�һ��Ԫ�ز�������Ԫ�صĸ��ڵ㣬��һ��Ԫ�س���
               pt.start = (pt.start + 1) % SI ;
            if(in.tag == 'R' or in.tag == 'r')  //�����������
                pt.que[pt.start] -> rc = tree;
            else  //�����������
                pt.que[pt.start] -> lc = tree;
       }

   }
  return root;
}

//����ݹ����
void  preprint(node btree){
   if(btree != NULL){
    str[i++] = btree -> data;
    preprint(btree -> lc);
    preprint(btree -> rc);
   }
}

//����ǵݹ����
void prefdgprint(node btree){
   node pt[SI];  //����һ��ָ������
   int top = -1;  //��ʼ��
   while(top != -1 || btree != NULL){  //ջ���ջ���������
       while(btree != NULL){  //���������
           pt[++top] = btree -> rc;  //�ҽڵ���ջ
           str[i++] = btree -> data;  //�����ַ�������
           btree = btree -> lc; //���½ڵ�Ϊ������
       }
       if(top != -1){  //���ջ��Ϊ�գ�ȡ��ջ����Ԫ��
           btree = pt[top--];
       }
   }
}

//����ݹ����
void midprint(node btree){
   if(btree != NULL){
    midprint(btree -> lc);
    str[i++] = btree -> data;
    midprint(btree -> rc);
   }
}

//����ǵݹ����
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

//����ݹ����
void endprint(node btree){
   if(btree != NULL){
    endprint(btree -> lc);
    endprint(btree -> rc);
    str[i++] = btree -> data;
   }
}

//����ǵݹ����
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

//�������
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

//��ӡ������
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

//Ѱ�������ڵ�����Ĺ�������
int findsameparent(node btree){
   char ch1,ch2;
   node p;
   node flag1,flag2;
   printf("�����������ڵ����֣����������\n");
   getchar();
   scanf("%c %c",&ch1,&ch2);
   if(ch1 == ch2){
      printf("�������������ڵ���ͬ��\n");
      return 0;
   }
   flag1 = findx(btree,ch1);
   flag2 = findx(btree,ch2);
   if(flag1 == NULL||flag2 == NULL){
       printf("����������������в����ڵ�Ԫ�أ�\n");
       return 0;
   }
   else{
       while(1){
          p = btree;
          if(findx(btree -> lc,ch1) != NULL && findx(btree -> lc,ch2) != NULL)  //����������������ڵ�Ĺ������ȣ����½ڵ�Ϊ������
              btree = btree -> lc;
          else if(findx(btree -> rc,ch1)!= NULL && findx(btree -> rc ,ch2) != NULL)  //����������������ڵ�Ĺ������ȣ����½ڵ�Ϊ������
              btree = btree -> rc;
          else  //�����ȫ����ߣ�Ҳ��ȫ���ұߣ���pΪ����Ĺ�������
              break;
       }
       printf("��������Ƚڵ���:%c\n",p -> data);
   }
    return 0;
}


//Ѱ��Ԫ��ch���ڽڵ㣬���������򷵻�NULL
node findx(node btree,char ch){  //����
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

//�ж����ǲ�����ȫ��
void isfullbtree(node btree){ //����ɨ��
   int j = 0,flag = 1,k;
   node p,l,r;
   str[i] = '\0';
   cengxuprint(btree);  //�������д���str��
   while(str[j] != '\0'){
      p = findx(btree,str[j]);
      l = p -> lc;
      r = p -> rc;
      if(l == NULL && r != NULL){  //���������Ϊ�գ�����������Ϊ�գ�������ȫ������
         flag = 0;
         break;
      }
      if(r == NULL){  //�������������Ϊ�յĽڵ㣬�����Ľڵ㶼����������
          for(k = j+1;str[k] != '\0';k++){
               p = findx(btree,str[k]);
               l = p -> lc;
               r = p -> rc;
               if(l != NULL || r != NULL){  //�����������������ȫ������
                   flag = 0;
                   break;
               }
          }
          break;
      }
      j++;
   }
   if(flag)
      printf("����һ����ȫ��������\n");
   else
      printf("�ⲻ��һ����ȫ��������\n");
}
