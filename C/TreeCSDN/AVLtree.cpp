
#include<iostream>
#include"AVLtree.hpp"


using namespace std;
int main(int argc, char* argv[])
{
	AVLTree<int> a;
	for (int i = 0; i < 10; i++)
		a.insert(i);
	cout << "树高" << a.height() << endl;
	cout << "前序遍历:" << endl;
	a.preOrder();
	cout << "中序遍历:" << endl;
	a.InOrder();
	cout << "后序遍历:" << endl;
	a.postOrder();
	cout << "删除元素10" << endl;
	a.remove(10);
	AVLTreeNode<int>* b = a.search_iterator(10);
	if (b != nullptr)
		cout << b->key;
	-101 -
	else
		cout << "无此元素" << endl;
	getchar();
	return 0;
}