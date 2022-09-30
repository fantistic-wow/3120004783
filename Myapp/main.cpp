#include<stdio.h>
#include<math.h>
#include<windows.h>
#include <stack> 
#define MaxSize 100

char Symbol(){//���������
	char S[4]={'+','-','x','/'};
    return S[rand()%4];
}

int Number(int r){//���ɲ�����
	return(rand()%r+1);
}

int gcd(int x,int y){//�����Լ��
	if(y==0)
		return x;
	return gcd(y,x%y);
}


/*typedef struct tree_node//�������ṹ 
{
	struct tree_node* left;
	struct tree_node* right;
	char key;
}tree_node;

tree_node* tree_create_node(char key)//����������� 
{
	tree_node* node = (struct tree_node*)malloc(sizeof(struct tree_node));
	if (node == NULL)
		return NULL;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return node;
}

typedef struct//ջ�ṹ 
{
    char Data[MaxSize];   // �洢����
    int top=0;       //ջ��ָ��
}SeqStack;

char push(SeqStack &L, char e){//��ջ 
	if(L.top==MaxSize -1)
    {
        return 0;
    }
    L.Data[L.top++] = e;
    return e;
} 

char Pop(SeqStack &L){//��ջ 
     if(L.top == 0)
    {
         return 0;
    }
    printf("��ջǰ��L.Data[L.top-1]=%c ,L.top=%d\n",L.Data[L.top-1],L.top);
    int v = L.Data[--L.top];
    printf("��ջ��L.Data[L.top-1]=%c ,L.top=%d\n",L.Data[L.top-1],L.top);
    printf("%c \n",v);
    return v;
}*/

float Cal(char a,float b,float c)//���㺯����aΪ�����,b��c�ֱ�Ϊ����
{
    switch(a)
    {
    case '+':
        return (b+c);
        break;
    case '-':
        return (b-c);
        break;
    case '*':
        return (b*c);
        break;
    case '/':
        return (1.0*b/c);
        break;
    }
}


int Answer(char *str){// ����׺���ʽ��Ϊ��׺���ʽ�������� 
	FILE *fp;
	float stack1[100];
    char stack2[100];
    int top1=-1,top2=-1;
    int i = 0;
    char a;
    float b,c;
    while(str[i] != '\0')
    {
        if(str[i] == '+' || str[i] == '-') 
        {
            if(top2==-1) 
            {
                stack2[++top2]=str[i];
            }
            else
            {
                while(stack2[top2] == '+' || stack2[top2] == '-' || stack2[top2] == '*' || stack2[top2] == '/')
                {
                    a=stack2[top2--];
                    c=stack1[top1--];
                    b=stack1[top1--];
                    stack1[++top1]=Cal(a,b,c);
                }
                stack2[++top2]=str[i];
            }
        }

        else if(str[i] == '*' || str[i] == '/')
        {
            if(top2==-1)
            {
                stack2[++top2]=str[i];
            }
            else
            {
                while(stack2[top2] == '*' || stack2[top2] == '/')
                {
                    a=stack2[top2--];
                    c=stack1[top1--];
                    b=stack1[top1--];
                    stack1[++top1]=Cal(a,b,c);
                }
                stack2[++top2]=str[i];
            }
        }
        else
        {
            stack1[++top1]=str[i]-'0';
        }
        i++;
    }
    while(top2!=-1)
    {
        a=stack2[top2--];
        c=stack1[top1--];
        b=stack1[top1--];
        stack1[++top1]=Cal(a,b,c);
    }
    fp=fopen("Answers.txt","a");
    fprintf(fp,"%0.2f\n",stack1[top1]);
    fclose(fp);
    return stack1[top1];
}




int Create(int t,int r){//������Ŀ
	FILE *fp;
	for(int j=1;j<=t;j++){
		int num[5]={0,0,0,0,0};
		char sym[4]={'0','0','0','0'};
		int k=0;
		char ex[10];
		int n=rand()%3+1;
		num[0]=Number(r);
		for(int i=0;i<n;i++){
		num[i+1]=Number(r);
		sym[i]=Symbol();
		}
		fp=fopen("Exercises.txt","a");
    	fprintf(fp,"��Ŀ%d : %d",j,num[0]);
    	ex[k++]=num[0]+'0';
    	for(int i=0;sym[i]!='0';i++){
        fprintf(fp," %c",sym[i]);
        ex[k++]=sym[i];
        fprintf(fp," %d",num[i+1]);
        ex[k++]=num[i+1]+'0';
    	}
    	ex[k]='\0';
    	printf("��Ŀ%d: %s\n",j,ex);
    	fprintf(fp,"\n");
    	fclose(fp);
    	Answer(ex);
    	//tree_create(ex,sizeof(ex));
	}	
    	return 0;
}

int main(){
	FILE *fp1,*fp2;
	fp1=fopen("Exercises.txt","w");//��ʼ���ļ� 
	fp2=fopen("Answers.txt","w");
    fclose(fp1);
    fclose(fp2);
    int n,r;
    printf("����Ҫ���ɵ���Ŀ����Ϊ:");
    scanf("%d",&n);
    Create(n,9);
    printf("��Ŀ������\n");
}


