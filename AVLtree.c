#include <stdio.h>
#include <stdlib.h>
void main(){}
//ƽ��������ڵ㶨��
struct Node
{
	int data;
	int deepth;
	struct Node* left;
	struct Node* right;
};
//�����½ڵ�
struct Node* NewNode(int data)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->data = data;
	temp->deepth = 1;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
	//һ���½ڵ�ĳ�ʼ״̬���ϣ���������ָ���Թ���������ʹ��
}
//�ȴ�С�����Ǹ������صĲ���ʹ�õ�
int MaxNum(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}
//�ú������ڼ����ض��ڵ����ȣ�ע�⣬���㷨������Ǵ�Ҷ�������ģ���Ҷ�ڵ����1�����ڵ�������
int Deepth(struct Node* i)
{
	if (i == NULL)
		return 0;
	return i->deepth;
}
//�ú������ڼ���ض��ڵ��ƽ�����ӣ��趨ƽ������������Ϊ�������Ϊ��
int Bindex(struct Node* j)
{
	if (j == NULL)
		return 0;
	return Deepth(j->left) - Deepth(j->right);
}
//��ĳһ��������С�ڵ�
struct Node* FindMin(struct Node* i)
{
	while (i->left != NULL)
		i = i->left;
	return i;
}
//��������,���Խڵ�iΪ��С��ƽ����������оֲ�����
struct Node* LRotate(struct Node* i)
{
	struct Node* j = i->right;
	struct Node* k = j->left;
	j->left = i;
	i->right = k;
	i->deepth = MaxNum(Deepth(i->left), Deepth(i->right)) + 1;
	j->deepth = MaxNum(Deepth(j->left), Deepth(j->right)) + 1;
	return j;
}
//����
struct Node* RRotate(struct Node* i)
{
	struct Node* j = i->left;
	struct Node* k = j->right;
	j->right = i;
	i->left = k;
	i->deepth = MaxNum(Deepth(i->left), Deepth(i->right)) + 1;
	j->deepth = MaxNum(Deepth(j->left), Deepth(j->right)) + 1;
	return j;
}
//���뺯��
struct Node* Insert(struct Node* root, int data)
{
	if (root == NULL)
		return NewNode(data);
	if (data < root->data)
		root->left = Insert(data, root->left);
	else if (data > root->data)
		root->right = Insert(data, root->right);
	else return root;                                                                  //�ҵ�����λ��
	root->deepth = MaxNum(Deepth(root->left), Deepth(root->right)) + 1;
	int BalanceI = Bindex(root);
	if (BalanceI > 1 && data < root->left->data)                                       //LL�������һ��
		return RRotate(root); 
	if (BalanceI<-1 && data>root->right->data)                                         //RR�������һ��
		return LRotate(root);
	if (BalanceI < -1 && data < root->right->data)                                     //RL���������������������
	{
		root->right = RRotate(root->right);
		return LRotate(root);
	}
	if (BalanceI > 1 && data > root->left->data)                                       //LR���������������������
	{
		root->left = LRotate(root->left);
		return RRotate(root);
	}
	return root;
}
//ɾ������
struct Node* Delete(struct Node* root, int data)
{
	if (root == NULL)
		return root;
	if (data < root->data)
		root->left = Delete(root->left, data);
	else if (data > root->data)
		root->right = Delete(root->right, data);
	else                                                                               //�ҵ���ɾ�ڵ�λ��
	{
		if (root->left == NULL && root->right == NULL)                                 //ΪҶ�ӵĻ���ֱ��ɾ
		{
			free(root);
			root = NULL;
		}
		if (root->left == NULL && root->right != NULL)                                 //�������������Һ����滻��
		{
			struct Node* temp = root->right;
			root = root->right;
			free(temp);
		}
		if (root->left != NULL && root->right == NULL)                                 //�����������������滻��
		{
			struct Node* temp = root->left;
			root = root->left;
			free(temp);
		}
		if (root->left != NULL && root->right != NULL)                                 //���Ҷ���������С���滻��
		{
			struct Node* temp = FindMin(root->right);
			root->data = temp->data;
			root->right = Delete(root->right, root->data);
		}
	}
	if (root == NULL)
		return root;
	root->deepth = MaxNum(Deepth(root->left), Deepth(root->right));
	int BalanceI = Bindex(root);
	if (BalanceI > 1 && Bindex(root->left) >= 0)                                         //ɾ��λ����LL����һ��
		return RRotate(root);
	if (BalanceI < -1 && Bindex(root->right) <= 0)                                       //ɾ��λ����RR����һ��
		return LRotate(root);
	if (BalanceI < -1 && Bindex(root->right) >= 0)                                       //ɾ��λ����RL����������������              
	{
		root->right = RRotate(root->right);
		return LRotate(root);
	}
	if (BalanceI > 1 && Bindex(root->left) <= 0)                                         //ɾ��λ����LR����������������
	{
		root->left = LRotate(root->left);
		return RRotate(root);
	}
	return root;
}
