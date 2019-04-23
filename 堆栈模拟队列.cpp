/*堆栈模拟队列
堆栈特点是先进后出，而队列的特点是先进先出
所以我们用两个堆栈来模拟一个队列。输入的元素经过第一个堆栈的先进后出后变成逆序的
在经过第二个堆栈的先进后出，从而得到原队列*/
#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100//定义堆栈最大容量
#define STACKINCREMENT 10//定义每次追加的长度
#define TRUE 1
#define FALSE 0

typedef char ElemType;//堆栈定义
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack; 

bool  InitStack(sqStack *s)//建立一个空的堆栈
{
	s->base = (char *)malloc(STACK_INIT_SIZE * sizeof(sqStack));
	if (s->base==NULL)
		return FALSE;
	s->top = s->base;
	s->stackSize = STACK_INIT_SIZE;
	return TRUE;
}

bool Push(sqStack *s, char e)//压栈操作
{
	if (s->top - s->base >= s->stackSize)//判断堆栈是否满
	{
		s->base = (char *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(sqStack));//如果满了追加空间
		if (s->base == NULL)
		{
			return FALSE;//判断是否追加成功
		}
		s->top = s->base + s->stackSize;
	}
	*s->top++ = e;//压入新的数据元素e
	return TRUE;
}

bool  Pop(sqStack *s, char *e)//弹出堆栈内的数据元素
{
	if (s->top == s->base)//判断堆栈是否为空
	{
		return FALSE;
	}
	*e = *--s->top;
	return TRUE;
}

bool StackEmpty(sqStack s)//判断栈是否为空
{
	if (s.top == s.base)
	{
		return TRUE;
	}
	else
		return FALSE;
}

bool DestroyStack(sqStack *s)//销毁栈
{
	if (s->base == NULL)
	{
		return FALSE;
	}
	free(s->base);
	return TRUE;
}

//将元素Elem取出队列
bool DeQueue(sqStack *stack1,sqStack *stack2,char *Elem)
{
	char temp;
	if (StackEmpty(*stack2) == TRUE && StackEmpty(*stack1) == TRUE)
	{
		return FALSE;
	}
	if (StackEmpty(*stack2) == FALSE)
	{
		Pop(stack2, Elem);
	}
	else 
	{
		while (StackEmpty(*stack1) == FALSE)
		{
			Pop(stack1, &temp);
			Push(stack2, temp);
		}
		Pop(stack2, Elem);
	}
	return TRUE;
}

//从队列中插入一个元素放入pElem，。
bool EnQueue(sqStack *stack1, sqStack *stack2,char pElem)
{
	char temp;
	//判断是否为空
	if (StackEmpty(*stack2) == TRUE)
	{
		while (StackEmpty(*stack1) == FALSE)//stack1不是空的，将stack1里面的元素出栈
		{
			Pop(stack1, &temp);//出栈元素压入stack2中
			Push(stack2, temp);
		}
	}
	Push(stack1, pElem);//将要放入的元素放入stack2中
	return TRUE;
}


//判用队列是否为空
bool EmptyQueue(sqStack stack1,sqStack stack2)
{
	if (StackEmpty(stack1) == TRUE && StackEmpty(stack2) == TRUE)
		return TRUE;
	else
		return FALSE;
}

int main()
{
	sqStack S1, S2;
	char ch;
	char temp;
	if (InitStack(&S1) == 1 && InitStack(&S2) == 1) {
		printf("栈初始化成功\n");
	}
	else {
		printf("初始化失败\n");
		return 1;
	}
	printf("现在输入一串字符串，压入队列: \n");
	ch = getchar();
	while (ch != '\n' && EnQueue(&S1, &S2, ch)) {
		ch = getchar();
	}

	while (EmptyQueue(S1, S2) == FALSE) {
		DeQueue(&S1, &S2, &temp);
		printf("%c ", temp);
	}
	printf("\n");
	system("pause");
	return 0;
}