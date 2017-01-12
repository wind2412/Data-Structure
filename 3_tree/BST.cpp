#ifndef _BST_IMPL_H_
#define _BST_IMPL_H_
#include "BST.hpp"

template <typename T, typename Comp>
using TreeNode = typename BST<T, Comp>::TreeNode;	//试了半天才试出来。这个很棒！！

/********************重要函数**********************/
template <typename T, typename Comp>
void BST<T, Comp>::put(T data){
	TreeNode* parent = root;
	TreeNode* temp = root;	//如果root==null temp又=root 那么temp就又复制了一个null指针。。。所以在他上边new还是没在root上，必须隔山打牛。 
	while(temp){
		if(comp(temp->data, data)){
			parent = temp;
			temp = temp->right;
		}
		else if(comp(data, temp->data)){
			parent = temp;
			temp = temp->left;
		}
		else {
			//如果找到一样的，什么也不做返回。
			return; 
		}
	} 
	if(comp(parent->data, data)){
		parent->right /*temp*/= new TreeNode(data);	//不能用temp直接赋值！应该加一个parent指针！ 
	}
	else{
		parent->left = new TreeNode(data);
	}	
}

template <typename T, typename Comp>
int BST<T, Comp>::getHeight(){	//树高度，迭代实现。 
	if(root == nullptr)	return 0;
	int height = 0;
	queue<TreeNode*> q1, q2;
	q1.push(root);
	TreeNode* temp = root;
	while(!q1.empty()){
		while(!q1.empty()){	//一直持续，直到q1为空为止！ 
			TreeNode* p = q1.front();
			q1.pop();
			if(p->left != nullptr)	q2.push(p->left);
			if(p->right!= nullptr)	q2.push(p->right);
		}
		height ++; 
		std::swap(q1, q2);	//交换两个队列。 这时左队列应为空。 
	}
	return height;
}

template <typename T, typename Comp>
int BST<T, Comp>::getMin(){	//得到最小元素。迭代实现。
	if(root == nullptr)	return -1;
	TreeNode* temp = root;
	while(temp->left){
		temp = temp->left;
	} 
	return temp->data;
}

template <typename T, typename Comp>
void BST<T, Comp>::deleteMin(){
	TreeNode* temp = root;
	TreeNode* parent = temp;
	while(temp->left){
		parent = temp;
		temp = temp->left;
	} 
	if(temp == root){	//删除的是根节点 这个必须注意！！这是情况之一！！ 
		root = root->right;
		delete temp;
	}
	else if(temp->right == nullptr)	{
		delete temp;
		parent->left = nullptr;	//一定别忘了这句=。= 
	}
	else {	//temp->right != nullptr
		parent->left = temp->right;
		delete temp;
	}
}

template <typename T, typename Comp>
void BST<T, Comp>::deleteNode(T data){
	TreeNode* parent, * temp = root;
	while(temp){
		if(comp(temp->data, data)){
			parent = temp;
			temp = temp->right;
		}
		else if(comp(data, temp->data)){
			parent = temp;
			temp = temp->left; 
		}
		else{
			if(temp->left == nullptr || temp->right == nullptr){
				//temp == root时， parent == 垃圾值。因为并没被赋值。 
				if(temp == root){	//因为迭代方式而且没有结点参数的引用＆的传递，这种情况太危险。 要单列出来。而且必须使用root进行直接操作。 
					root = (root->left == nullptr) ? root->right : root->left;//root就是正统的！直接修改没问题！ 
					delete temp;
				}
				else{
					if(parent->left == temp)
						parent->left = (temp->left == nullptr) ? temp->right : temp->left;	//temp是旁路！修改也修改不了正统的！只能修改旁路！因此必须要一个parent！ 
					else parent->right = (temp->left == nullptr) ? temp->right : temp->left;
					delete temp;
				}
			}
			else{	//left right全都有 
				TreeNode* saveDeleteNode = temp;
				parent = temp;
				temp = temp->left;
				while(temp->right){
					parent = temp;
					temp = temp->right;
				}
//				if(saveDeleteNode == root){	//要删除root时，需要单列出来。因为对比AVLTree，这个函数没有参数且非递归不好弄。 
//					
//				}	//不需要单列出来了！！！因为并不是真的删除啊 =。= 
				if(parent->left == temp){	//temp没有右结点  即temp已为最小 
					saveDeleteNode->data = temp->data;
					parent->left = temp->left;
					delete temp; 
				}
				else {	// parent->right == temp
					saveDeleteNode->data = temp->data;
					parent->right = temp->left;
					delete temp; 
				}
				
			}
			return;	//别忘了return！！ 
		}
	}
}

/***************遍历实现（迭代）*******************/
template <typename T, typename Comp>
void BST<T, Comp>::preOrderTraversal1(){	//前序遍历1 
	if(root == nullptr)	return;
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp){
			cout << temp->data << " ";
			s.push(temp);
			temp = temp->left;
		}
		if(s.empty())	break;	//这个顺序太漂亮了！ 
		temp = s.top()->right;
		s.pop();
	};
}

template <typename T, typename Comp>
void BST<T, Comp>::preOrderTraversal2(){	//前序遍历2 
	if(root == nullptr)	return;
	stack<TreeNode*> s;
	TreeNode* temp;
	s.push(root);
	while(!s.empty()){
		temp = s.top();
		cout << temp->data << " ";
		s.pop();
		if(temp->right != nullptr)	s.push(temp->right);	//千万要先push右边！！！！因为是入栈，右边会比左边的压得更低，因此先弹出左边！！ 
		if(temp->left != nullptr)	s.push(temp->left);
	};
}

template <typename T, typename Comp>
void BST<T, Comp>::inOrderTraversal(){	//中序遍历，使用前序遍历1改变下顺序即可。 
	if(root == nullptr)	return;
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp){
			s.push(temp);
			temp = temp->left;
		}
		if(s.empty())	break;	//别忘了！ 
		temp = s.top();
		s.pop();
		cout << temp->data << " ";
		temp = temp->right;
	}
}

template <typename T, typename Comp> 
void BST<T, Comp>::postOrderTraversal(){	//极难后续遍历。参见Leet解法。 //或者将前序的[根-左-右]改动成[根-右-左]保存到vector然后std::reverse。 
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp){
			s.push(temp);
			temp = temp->left;
		}
		TreeNode* q = nullptr; 	//q为了保存访问结点。而且赋值为nullptr可以进行仅仅一次的【右结点是否null的判断】，见下，妙！！！
		while(!s.empty()){
			temp = s.top();	 
			s.pop();	//虽然pop了中间节点，但是右结点不知道是否null或者有没有已经被访问，还要谨慎。
			if(temp->right == q) {	//看是否是null？是否被访问？ 
				cout << temp->data << " ";
				q = temp;	//保存被访问的点！！ 为[\]形从底向上访问打基础。 
			} 
			else {	//当前节点无法访问。因为temp->right没被访问过。 当然，如果是第二轮判断，q已经变了，肯定!=。也推迟一轮，执行此else。安全。 
				s.push(temp);	//重新入栈。 
				temp = temp->right;	//转移到右边！ 
				break;	//直接跳出循环！ 
			}
		} 
		if(s.empty())	break;	//完全跳出的条件！！！ 
	}
}

template <typename T, typename Comp>
void BST<T, Comp>::levelOrderTraversal(){	//层序遍历。 
	if(root == nullptr)	return;
	queue<TreeNode*> q;
	TreeNode* temp = root;
	q.push(temp);
	while(!q.empty()){
		TreeNode* p = q.front();
		q.pop();
		cout << p->data << " ";
		if(p->left != nullptr)	q.push(p->left);
		if(p->right != nullptr)	q.push(p->right);
	}
}

/***************析构函数*******************/

template <typename T, typename Comp>
BST<T, Comp>::~BST(){
	makeEmpty();
}

template <typename T, typename Comp>
void BST<T, Comp>::makeEmpty(){	//析构最好采用后续遍历的手段。仅仅使用一个stack。 
	if(root == nullptr)	return;
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp){
			s.push(temp);
			temp = temp->left;
		}
		TreeNode* q = nullptr;
		while(!s.empty()){
			temp = s.top();
			s.pop();
			if(temp->right == q){	//可以对temp进行操作。 
				delete temp;	//......到现在我也不确定这个行不行。。。。delete之后会发生什么？？？ 
				q = temp;
			} 
			else{
				s.push(temp);
				temp = temp->right;
				break;
			}			
		}
		if(s.empty())	break;
	}
	root = nullptr; 
} 

template <typename T, typename Comp>	//其实这个const函数没有任何作用。只是为了重载而已=。= 
void BST<T, Comp>::makeEmpty() const{	//用queue+stack方法进行析构。把结点从上往下层序推入stack。之后不断析构就好。 
	if(root == nullptr)	return;
	queue<TreeNode*> q;
	stack<TreeNode*> s;
	TreeNode* temp = root;
	q.push(temp);
	s.push(temp);
	while(!q.empty()){
		temp = q.front();
		q.pop();
		if(temp->left != nullptr){
			q.push(temp->left);
			s.push(temp->left); 
		}
		if(temp->right != nullptr){
			q.push(temp->right);
			s.push(temp->right); 
		}
	}
	while(!s.empty()){
		temp = s.top();
		s.pop();
//		cout << temp->data << " ";
		delete temp; 
	}
	root = nullptr;	//temp此时指向root的东西，但是决不能temp=nullptr！！因为temp是旁路！只能把temp变成nullptr！！但是root不改！犯错误好多次了！ 
}

#endif

int main()
{
	BST<int> b(new typename BST<int>::TreeNode(1)); 
	b.put(3);
	b.put(9);
	b.put(2);
	b.put(5);
	b.put(0);
	b.put(7);
	b.put(8);
	b.put(4);
	b.put(1);
	b.put(6);
	b.put(10);

	b.deleteMin();
	b.deleteMin();
	b.deleteNode(3);
//	b.deleteNode(9); 
//	b.deleteNode(2);
	
	b.preOrderTraversal1();cout << " （先序遍历）" << endl;
	b.preOrderTraversal2();cout << " （先序遍历）" << endl;
	b.inOrderTraversal();cout << " （中序遍历）" << endl;
	b.postOrderTraversal();cout << " （后序遍历）" << endl;
	b.levelOrderTraversal();cout << " （层序遍历）" << endl;
	cout << "树的高度是：" << b.getHeight() << endl;
	cout << "树的最小值：" << b.getMin() << endl; 
}

