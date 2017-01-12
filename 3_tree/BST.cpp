#ifndef _BST_IMPL_H_
#define _BST_IMPL_H_
#include "BST.hpp"

template <typename T, typename Comp>
using TreeNode = typename BST<T, Comp>::TreeNode;	//���˰�����Գ���������ܰ�����

/********************��Ҫ����**********************/
template <typename T, typename Comp>
void BST<T, Comp>::put(T data){
	TreeNode* parent = root;
	TreeNode* temp = root;	//���root==null temp��=root ��ôtemp���ָ�����һ��nullָ�롣�������������ϱ�new����û��root�ϣ������ɽ��ţ�� 
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
			//����ҵ�һ���ģ�ʲôҲ�������ء�
			return; 
		}
	} 
	if(comp(parent->data, data)){
		parent->right /*temp*/= new TreeNode(data);	//������tempֱ�Ӹ�ֵ��Ӧ�ü�һ��parentָ�룡 
	}
	else{
		parent->left = new TreeNode(data);
	}	
}

template <typename T, typename Comp>
int BST<T, Comp>::getHeight(){	//���߶ȣ�����ʵ�֡� 
	if(root == nullptr)	return 0;
	int height = 0;
	queue<TreeNode*> q1, q2;
	q1.push(root);
	TreeNode* temp = root;
	while(!q1.empty()){
		while(!q1.empty()){	//һֱ������ֱ��q1Ϊ��Ϊֹ�� 
			TreeNode* p = q1.front();
			q1.pop();
			if(p->left != nullptr)	q2.push(p->left);
			if(p->right!= nullptr)	q2.push(p->right);
		}
		height ++; 
		std::swap(q1, q2);	//�����������С� ��ʱ�����ӦΪ�ա� 
	}
	return height;
}

template <typename T, typename Comp>
int BST<T, Comp>::getMin(){	//�õ���СԪ�ء�����ʵ�֡�
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
	if(temp == root){	//ɾ�����Ǹ��ڵ� �������ע�⣡���������֮һ���� 
		root = root->right;
		delete temp;
	}
	else if(temp->right == nullptr)	{
		delete temp;
		parent->left = nullptr;	//һ�����������=��= 
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
				//temp == rootʱ�� parent == ����ֵ����Ϊ��û����ֵ�� 
				if(temp == root){	//��Ϊ������ʽ����û�н����������ã��Ĵ��ݣ��������̫Σ�ա� Ҫ���г��������ұ���ʹ��root����ֱ�Ӳ����� 
					root = (root->left == nullptr) ? root->right : root->left;//root������ͳ�ģ�ֱ���޸�û���⣡ 
					delete temp;
				}
				else{
					if(parent->left == temp)
						parent->left = (temp->left == nullptr) ? temp->right : temp->left;	//temp����·���޸�Ҳ�޸Ĳ�����ͳ�ģ�ֻ���޸���·����˱���Ҫһ��parent�� 
					else parent->right = (temp->left == nullptr) ? temp->right : temp->left;
					delete temp;
				}
			}
			else{	//left rightȫ���� 
				TreeNode* saveDeleteNode = temp;
				parent = temp;
				temp = temp->left;
				while(temp->right){
					parent = temp;
					temp = temp->right;
				}
//				if(saveDeleteNode == root){	//Ҫɾ��rootʱ����Ҫ���г�������Ϊ�Ա�AVLTree���������û�в����ҷǵݹ鲻��Ū�� 
//					
//				}	//����Ҫ���г����ˣ�������Ϊ���������ɾ���� =��= 
				if(parent->left == temp){	//tempû���ҽ��  ��temp��Ϊ��С 
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
			return;	//������return���� 
		}
	}
}

/***************����ʵ�֣�������*******************/
template <typename T, typename Comp>
void BST<T, Comp>::preOrderTraversal1(){	//ǰ�����1 
	if(root == nullptr)	return;
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp){
			cout << temp->data << " ";
			s.push(temp);
			temp = temp->left;
		}
		if(s.empty())	break;	//���˳��̫Ư���ˣ� 
		temp = s.top()->right;
		s.pop();
	};
}

template <typename T, typename Comp>
void BST<T, Comp>::preOrderTraversal2(){	//ǰ�����2 
	if(root == nullptr)	return;
	stack<TreeNode*> s;
	TreeNode* temp;
	s.push(root);
	while(!s.empty()){
		temp = s.top();
		cout << temp->data << " ";
		s.pop();
		if(temp->right != nullptr)	s.push(temp->right);	//ǧ��Ҫ��push�ұߣ���������Ϊ����ջ���ұ߻����ߵ�ѹ�ø��ͣ�����ȵ�����ߣ��� 
		if(temp->left != nullptr)	s.push(temp->left);
	};
}

template <typename T, typename Comp>
void BST<T, Comp>::inOrderTraversal(){	//���������ʹ��ǰ�����1�ı���˳�򼴿ɡ� 
	if(root == nullptr)	return;
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp){
			s.push(temp);
			temp = temp->left;
		}
		if(s.empty())	break;	//�����ˣ� 
		temp = s.top();
		s.pop();
		cout << temp->data << " ";
		temp = temp->right;
	}
}

template <typename T, typename Comp> 
void BST<T, Comp>::postOrderTraversal(){	//���Ѻ����������μ�Leet�ⷨ�� //���߽�ǰ���[��-��-��]�Ķ���[��-��-��]���浽vectorȻ��std::reverse�� 
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp){
			s.push(temp);
			temp = temp->left;
		}
		TreeNode* q = nullptr; 	//qΪ�˱�����ʽ�㡣���Ҹ�ֵΪnullptr���Խ��н���һ�εġ��ҽ���Ƿ�null���жϡ������£������
		while(!s.empty()){
			temp = s.top();	 
			s.pop();	//��Ȼpop���м�ڵ㣬�����ҽ�㲻֪���Ƿ�null������û���Ѿ������ʣ���Ҫ������
			if(temp->right == q) {	//���Ƿ���null���Ƿ񱻷��ʣ� 
				cout << temp->data << " ";
				q = temp;	//���汻���ʵĵ㣡�� Ϊ[\]�δӵ����Ϸ��ʴ������ 
			} 
			else {	//��ǰ�ڵ��޷����ʡ���Ϊtemp->rightû�����ʹ��� ��Ȼ������ǵڶ����жϣ�q�Ѿ����ˣ��϶�!=��Ҳ�Ƴ�һ�֣�ִ�д�else����ȫ�� 
				s.push(temp);	//������ջ�� 
				temp = temp->right;	//ת�Ƶ��ұߣ� 
				break;	//ֱ������ѭ���� 
			}
		} 
		if(s.empty())	break;	//��ȫ���������������� 
	}
}

template <typename T, typename Comp>
void BST<T, Comp>::levelOrderTraversal(){	//��������� 
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

/***************��������*******************/

template <typename T, typename Comp>
BST<T, Comp>::~BST(){
	makeEmpty();
}

template <typename T, typename Comp>
void BST<T, Comp>::makeEmpty(){	//������ò��ú����������ֶΡ�����ʹ��һ��stack�� 
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
			if(temp->right == q){	//���Զ�temp���в����� 
				delete temp;	//......��������Ҳ��ȷ������в��С�������delete֮��ᷢ��ʲô������ 
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

template <typename T, typename Comp>	//��ʵ���const����û���κ����á�ֻ��Ϊ�����ض���=��= 
void BST<T, Comp>::makeEmpty() const{	//��queue+stack���������������ѽ��������²�������stack��֮�󲻶������ͺá� 
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
	root = nullptr;	//temp��ʱָ��root�Ķ��������Ǿ�����temp=nullptr������Ϊtemp����·��ֻ�ܰ�temp���nullptr��������root���ģ�������ö���ˣ� 
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
	
	b.preOrderTraversal1();cout << " �����������" << endl;
	b.preOrderTraversal2();cout << " �����������" << endl;
	b.inOrderTraversal();cout << " �����������" << endl;
	b.postOrderTraversal();cout << " �����������" << endl;
	b.levelOrderTraversal();cout << " �����������" << endl;
	cout << "���ĸ߶��ǣ�" << b.getHeight() << endl;
	cout << "������Сֵ��" << b.getMin() << endl; 
}

