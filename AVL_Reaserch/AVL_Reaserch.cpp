#include<math.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define LH +1//左高
#define EH 0//等高
#define RH -1//右高
#define true 1
#define false 0
#define OK 1
#define ERROR 0
typedef int Status;
typedef struct TreeNode{
    int data;
    int bf;//定义平衡因子；
    struct TreeNode *Lchild,*Rchild;
}TreeNode,*BiTree;
void Rroate(BiTree *T)//右旋处理；
{
    BiTree L;
    L=(*T)->Lchild;
    (*T)->Lchild=L->Rchild;
    L->Rchild=(*T);
    (*T)=L;
}
void Lroate(BiTree *T)//左旋处理；
{
    BiTree L;
    L=(*T)->Rchild;
    (*T)->Rchild=L->Lchild;
    L->Lchild=(*T);
    (*T)=L;
}
void LeftBalance(BiTree *T)//左旋平衡处理；
{
    BiTree L,Lr;
    L=(*T)->Lchild;
    switch(L->bf)
    {case LH:
        (*T)->bf=L->bf=EH;
        Rroate(T);
        break;
    case RH:
        Lr=L->Rchild;//若新的节点插入L的柚子树中，要进行双旋转处理；
        switch(Lr->bf)
        {case LH:
            (*T)->bf=RH;
            L->bf=EH;
            break;
        case EH:
            (*T)->bf=L->data=EH;
            break;
        case RH:
            (*T)->bf=EH;
            L->bf=LH;
            break;

        }
        Lr->bf=EH;
        Lroate(&(*T)->Lchild);
        Rroate(T);

    }

}
void RightBalance(BiTree *T)//右平衡旋转处理；
{
    BiTree L,Lr;
    L=(*T)->Rchild;
    switch(L->bf)
    {case RH:
        (*T)->bf=L->bf=EH;
        Lroate(T);
        break;
    case LH://将先T的最小不平衡子树进行右旋，然后对T进行左旋；
        Lr=L->Lchild;
        switch(Lr->bf)
        {
            case LH://Lr的平衡因子为1时，平横后L的bf为-1，L的bf为0；
            (*T)->bf=EH;
            L->bf=RH;
            break;
            case EH:
            (*T)->bf=EH;
            L->bf=EH;
            break;
            case RH:
            (*T)->bf=LH;
            L->bf=EH;

        }
        Lr->bf=EH;
        Rroate(&(*T)->Rchild);
        Lroate(T);

    }
}
int InsertAVL(BiTree *T,int e,int  *Taller)
{
    if(!(*T))
    {
        (*T)=(BiTree)malloc(sizeof(TreeNode));
        (*T)->data=e;
        (*T)->Lchild=(*T)->Rchild=NULL;
        *Taller=true;
        (*T)->bf=EH;
    }
    else
    {
        if(e==(*T)->data)
        return false;
        if(e<(*T)->data)
        {
            if(!InsertAVL(&(*T)->Lchild,e,Taller))
            return false;
            if(*Taller)
            {
                switch((*T)->bf)
                {
                    case LH:
                        LeftBalance(T);
                        *Taller=false;
                        break;
                    case   EH:
                        *Taller=true;
                        (*T)->bf=LH;
                        break;
                    case RH:
                        *Taller=false;
                        (*T)->bf=EH;
                        break;


                }
            }
        }
        else
        {
            if(!InsertAVL(&(*T)->Rchild,e,Taller))
            return false;
            if(*Taller)
            {
                switch((*T)->bf)
                {
                    case LH:
                        (*T)->bf=EH;
                        *Taller=false;
                        break;
                    case EH:
                        (*T)->bf=RH;
                        *Taller=true;
                        break;
                    case RH:
                        RightBalance(T);
                        *Taller=false;
                        break;

                }
            }
        }

    }
return true;
}
void PreVisit(BiTree T)
{
	if(T==NULL)
	 return ;
	//if(T->data==a)
	//return true;
	//printf("%d ",T->data);
	PreVisit(T->Lchild);
	PreVisit(T->Rchild);
 } 
 void Free(BiTree *T) {
 
    if (*T) {
 
        Free(&(*T)->Lchild);
        Free(&(*T)->Rchild);
        free(*T);
        *T = NULL;
    }
}
int main()
{
  int i;
  int j,k,a[600],b[600],c[600];
  scanf("%d%d",&j,&k);
  //int a[10]={2,3,1,4,5,6,10,9,8,7};
  BiTree T=NULL;
  Status taller;
 for(i=0;i<j;i++)
  {
  	scanf("%d",&a[i]);
  	
  }
  for(i=0;i<k;i++)
  {
  	scanf("%d",&b[i]);
  
  }
	for(i=0;i<j;i++)
	{
		InsertAVL(&T,a[i],&taller);
	}
	  	
  for(i=0;i<k;i++)
  {
  	if(InsertAVL(&T,b[i],&taller)==true)
  		c[i]=0;
  	else
  	c[i]=1;
  }
  for(i=0;i<k;i++)
  {
  	printf("%d ",c[i]);
  }
 // printf("�ɹ��ˣ�"); 
 printf("\n");
 Free(&T);
  return 0;
}
