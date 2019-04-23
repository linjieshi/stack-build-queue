/*��ջģ�����
��ջ�ص����Ƚ�����������е��ص����Ƚ��ȳ�
����������������ջ��ģ��һ�����С������Ԫ�ؾ�����һ����ջ���Ƚ�������������
�ھ����ڶ�����ջ���Ƚ�������Ӷ��õ�ԭ����*/
#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100//�����ջ�������
#define STACKINCREMENT 10//����ÿ��׷�ӵĳ���
#define TRUE 1
#define FALSE 0

typedef char ElemType;//��ջ����
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack; 

bool  InitStack(sqStack *s)//����һ���յĶ�ջ
{
	s->base = (char *)malloc(STACK_INIT_SIZE * sizeof(sqStack));
	if (s->base==NULL)
		return FALSE;
	s->top = s->base;
	s->stackSize = STACK_INIT_SIZE;
	return TRUE;
}

bool Push(sqStack *s, char e)//ѹջ����
{
	if (s->top - s->base >= s->stackSize)//�ж϶�ջ�Ƿ���
	{
		s->base = (char *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(sqStack));//�������׷�ӿռ�
		if (s->base == NULL)
		{
			return FALSE;//�ж��Ƿ�׷�ӳɹ�
		}
		s->top = s->base + s->stackSize;
	}
	*s->top++ = e;//ѹ���µ�����Ԫ��e
	return TRUE;
}

bool  Pop(sqStack *s, char *e)//������ջ�ڵ�����Ԫ��
{
	if (s->top == s->base)//�ж϶�ջ�Ƿ�Ϊ��
	{
		return FALSE;
	}
	*e = *--s->top;
	return TRUE;
}

bool StackEmpty(sqStack s)//�ж�ջ�Ƿ�Ϊ��
{
	if (s.top == s.base)
	{
		return TRUE;
	}
	else
		return FALSE;
}

bool DestroyStack(sqStack *s)//����ջ
{
	if (s->base == NULL)
	{
		return FALSE;
	}
	free(s->base);
	return TRUE;
}

//��Ԫ��Elemȡ������
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

//�Ӷ����в���һ��Ԫ�ط���pElem����
bool EnQueue(sqStack *stack1, sqStack *stack2,char pElem)
{
	char temp;
	//�ж��Ƿ�Ϊ��
	if (StackEmpty(*stack2) == TRUE)
	{
		while (StackEmpty(*stack1) == FALSE)//stack1���ǿյģ���stack1�����Ԫ�س�ջ
		{
			Pop(stack1, &temp);//��ջԪ��ѹ��stack2��
			Push(stack2, temp);
		}
	}
	Push(stack1, pElem);//��Ҫ�����Ԫ�ط���stack2��
	return TRUE;
}


//���ö����Ƿ�Ϊ��
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
		printf("ջ��ʼ���ɹ�\n");
	}
	else {
		printf("��ʼ��ʧ��\n");
		return 1;
	}
	printf("��������һ���ַ�����ѹ�����: \n");
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