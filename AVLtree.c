#include <stdio.h>
#include <stdlib.h>
void main(){}
//平衡二叉树节点定义
struct Node
{
	int data;
	int deepth;
	struct Node* left;
	struct Node* right;
};
//创建新节点
struct Node* NewNode(int data)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->data = data;
	temp->deepth = 1;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
	//一个新节点的初始状态如上，并返回其指针以供其他函数使用
}
//比大小函数是给深度相关的操作使用的
int MaxNum(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}
//该函数用于检索特定节点的深度，注意，本算法的深度是从叶往根数的，即叶节点深度1，根节点深度最大
int Deepth(struct Node* i)
{
	if (i == NULL)
		return 0;
	return i->deepth;
}
//该函数用于检测特定节点的平衡因子，设定平衡因子正负性为左大于右为正
int Bindex(struct Node* j)
{
	if (j == NULL)
		return 0;
	return Deepth(j->left) - Deepth(j->right);
}
//找某一子树中最小节点
struct Node* FindMin(struct Node* i)
{
	while (i->left != NULL)
		i = i->left;
	return i;
}
//左旋函数,将以节点i为最小不平衡二叉树进行局部左旋
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
//右旋
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
//插入函数
struct Node* Insert(struct Node* root, int data)
{
	if (root == NULL)
		return NewNode(data);
	if (data < root->data)
		root->left = Insert(data, root->left);
	else if (data > root->data)
		root->right = Insert(data, root->right);
	else return root;                                                                  //找到插入位置
	root->deepth = MaxNum(Deepth(root->left), Deepth(root->right)) + 1;
	int BalanceI = Bindex(root);
	if (BalanceI > 1 && data < root->left->data)                                       //LL情况右旋一次
		return RRotate(root); 
	if (BalanceI<-1 && data>root->right->data)                                         //RR情况左旋一次
		return LRotate(root);
	if (BalanceI < -1 && data < root->right->data)                                     //RL情况根右子右旋根再左旋
	{
		root->right = RRotate(root->right);
		return LRotate(root);
	}
	if (BalanceI > 1 && data > root->left->data)                                       //LR情况根左子左旋根再右旋
	{
		root->left = LRotate(root->left);
		return RRotate(root);
	}
	return root;
}
//删除函数
struct Node* Delete(struct Node* root, int data)
{
	if (root == NULL)
		return root;
	if (data < root->data)
		root->left = Delete(root->left, data);
	else if (data > root->data)
		root->right = Delete(root->right, data);
	else                                                                               //找到被删节点位置
	{
		if (root->left == NULL && root->right == NULL)                                 //为叶子的话可直接删
		{
			free(root);
			root = NULL;
		}
		if (root->left == NULL && root->right != NULL)                                 //左无右有先用右孩子替换它
		{
			struct Node* temp = root->right;
			root = root->right;
			free(temp);
		}
		if (root->left != NULL && root->right == NULL)                                 //左有右无先用左孩子替换它
		{
			struct Node* temp = root->left;
			root = root->left;
			free(temp);
		}
		if (root->left != NULL && root->right != NULL)                                 //左右都有先用右小子替换它
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
	if (BalanceI > 1 && Bindex(root->left) >= 0)                                         //删除位置在LL右旋一次
		return RRotate(root);
	if (BalanceI < -1 && Bindex(root->right) <= 0)                                       //删除位置在RR左旋一次
		return LRotate(root);
	if (BalanceI < -1 && Bindex(root->right) >= 0)                                       //删除位置在RL右子右旋根再左旋              
	{
		root->right = RRotate(root->right);
		return LRotate(root);
	}
	if (BalanceI > 1 && Bindex(root->left) <= 0)                                         //删除位置在LR左子左旋根再右旋
	{
		root->left = LRotate(root->left);
		return RRotate(root);
	}
	return root;
}
