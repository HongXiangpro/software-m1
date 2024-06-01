#include <stdio.h>
#include <stdlib.h>

#define N 100


int compare(char a, char b)
{
    int flag=0;
    if(b == '(')
    {
        return 1;
    }
    else if(a =='+'||a == '-')
    {
        switch (b)
        {
        case '+':
            flag = 0;
            break;
        case '-':
            flag = 0;
            break;
        case '*':
            flag = 1;
            break;
        }
    }
    else if(a == '*'||a =='/')
    {
        flag = 0;
    }
    else if(a=='#')
    {
        flag = 1;
    }
    return flag;
}

struct stack_op
{
    char op;
    struct stack_op *next;
};
typedef struct stack_op STACKOP;

void newops(STACKOP* ops)
{
    ops = (STACKOP*)malloc(sizeof(struct stack_op));
    if (ops != NULL)
    {
        (ops)->op = '#';
        (ops)->next = NULL;
    }
    else
    {
        printf("No enough memory!");
        exit(0);
    }
}
//入栈
void push(STACKOP **ops,char c)
{
    STACKOP *p ;
    p=(STACKOP*)malloc(sizeof(STACKOP));
    if (ops != NULL)
    {
        p->op=c;
        p->next=*ops;
        *ops = p;
    }
    else
    {
        printf("No enough memory!");
        exit(0);
    }
}
//弹栈
char pop(STACKOP **ops)
{
    char s;
    STACKOP *p=*ops;
    s =p->op;
    *ops =(*ops)->next;
    free(p);
    return s;
}

//转后缀
void transform(char* input ,char* output)
{
    STACKOP *ops = NULL;
    newops(ops);
    //flag用来判断前一个input的性质(1:操作符,0:数字,-1:负号,2:小数点)
    int i=0, j=0,flag=1;
    char op;
    while(input[i]!='\0')
    {
        //处理数字
        if(input[i]>='0'&&input[i]<='9')
        {
            //前一个是操作符加空格分开,是数字,负号,小数点不加空格
            if(flag == 1)
            {
                *(output+j) = ' ';
                j++;
            }
            *(output+j) = input[i];
            j++;
            i++;
            flag=0;
        }
        //处理数字
        else{
            //判断负号
            if(input[i]=='-'&&flag == 1)
            {
                *(output+j) = ' ';
                j++;
                *(output+j) = input[i];
                j++;
                i++;
                flag =-1;
            }
            //处理小数点
            else if(input[i]=='.'&&flag == 0)
            {
                *(output+j) = input[i];
                j++;
                i++;
                flag = 2;
            }
            //处理右括号
            else if(input[i]==')')
            {
                op=pop(&ops);
                while(op!='('&&ops->op!='#')
                {
                    *(output+j)=op;
                    j++;
                }
                if(ops->op=='#'){printf("没有左括号");}
                i++;
                flag=1;
            }
            //处理入栈符号
            else if(compare(ops->op,input[i])==1)
            {
                push(&ops,input[i]);
                i++;
                flag = 1;
            }
            //处理弹栈符号
            else if(compare(ops->op,input[i])==0)
            {
                do{
                    op = pop(&ops);
                    *(output+j) = op;
                    j++;
                }while(compare(ops->op,input[i])==1);
                push(&ops,input[i]);
                i++;
            }
            flag = 1;
        }
    }
    //处理input完后栈内的操作符
    while(ops->op!='#')
    {
        op = pop(&ops);
        *(output+j) = op;
        j++;
    }
    *(output+j)='\0';
}

int main()
{
    char input[N],output[N];
    gets(input);
    transform(input,output);
    puts(output);
    return 0;
}
