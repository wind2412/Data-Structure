#ifndef _RBTREE_IMPL_H_
#define _RBTREE_IMPL_H_
#include "RBTree.hpp"
#include <stack>

#define NIL RBTree<T, Comp>::TreeNode::NIL

template <typename T, typename Comp>
using TreeNode = typename RBTree<T, Comp>::TreeNode;

// template <typename T, typename Comp>	//deleted.
// auto & NIL = RBTree<T, Comp>::TreeNode::NIL;

//template <typename T, typename Comp>
//using NIL =  RBTree<T, Comp>::TreeNode* RBTree<T, Comp>::TreeNode::NIL;

template <typename T, typename Comp>
void RBTree<T, Comp>::rotate_left(TreeNode* x){	//��AVL������ͬ����ɫҲ����Ҫ�����ﴦ�� //������Ϊ����parent���ԣ�����û�б�Ҫʹ������&�ˡ� 
	TreeNode* temp = x->right;
	x->right = temp->left;
	temp->left = x;
	if(x->parent == nullptr){
		root = temp;	 
		temp->parent = nullptr; 
	} 
	else{		//����x->parent������������ָ��  
		temp->parent = x->parent;
		if(x->parent->left == x)	x->parent->left = temp;
		else						x->parent->right = temp;
	}
	x->parent = temp;	//����x��x->rightȫ�����ڣ����Խ���ֱ����ת������Ҫ���Ǳ�ġ�
	if(x->right != NIL)	x->right->parent = x;	//��temp����õ����ֽڵ㲻��NIL�� 
}

template <typename T, typename Comp>
void RBTree<T, Comp>::rotate_right(TreeNode* x){
	TreeNode* temp = x->left;
	x->left = temp->right;
	temp->right = x;
	if(x->parent == nullptr){
		root = temp;
		temp->parent = nullptr;
	}
	else{
		temp->parent = x->parent;
		if(x->parent->left == x)	x->parent->left = temp;
		else						x->parent->right = temp;
	}
	x->parent = temp;
	if(x->left != NIL)	x->left->parent = x;
}

template <typename T, typename Comp>
void RBTree<T, Comp>::insert(const T & data){
	if(root == nullptr){
		root = new TreeNode(data, nullptr);
		root->color = BLACK;	//���ڵ�Ҫ��ɫ���� 
	}
	else{
		insert(root, data);	//����Ϊnullptr������Ѿ���������ϣ����������ӡ� 
	}
}

template <typename T, typename Comp>
void RBTree<T, Comp>::insert(TreeNode* x, const T & data){	//x�Ѿ�������nullptr����������Բ�������ô���ˡ� 
	//���ڴ���parent���������ģ������˽���Ԥ�У�����
	if(comp(data, x->data)){
		if(x->left != NIL)	insert(x->left, data);	//Ԥ���ǲ���nullptr����������б��뱣֤���β���nullptr������ 
		//��Ҫ������nullptr�������else�ﴦ���ˣ���Ϊx->left==nullptr����x��Ϊ�գ���Ҫ���ɵ�new TreeNode�����ҵ��ְ֡� 
		else	x->left = new TreeNode(data, x); 
	}
	else if(comp(x->data, data)){
		if(x->right != NIL)		insert(x->right, data);
		else 	x->right = new TreeNode(data, x);
	} 
	else{
		x->data = data;
		return;	//������У��������ֵ�����󲻲���balance��ֱ�ӷ��ء� 
	}
	
	balance_insert(x);
	
}

template <typename T, typename Comp>
void RBTree<T, Comp>::balance_insert(TreeNode* x){
	//��������ת�����x�Ǹ��ڵ�Ҳ�ǿ��ܵġ�����x�������������nullptr => case1. 
	if(x->parent == nullptr)					x->color = BLACK;	//case1.�޸���㡣 
	else if(x->parent->color == BLACK)			return;				//case2.���ڵ�ΪBLACK���������ʡ����ؼ��ɡ�	ʣ�µ����ȫ������x->parent->color==RED. 
	else if(x->uncle() != nullptr && x->uncle()->color == RED){	//case3.���ڵ�ΪRED��uncleΪRED => ����ȫ�ڣ�grandparentȾ�죬����grandparent�������� 
		x->parent->color = BLACK;								//JULY����[����ɾ�����1] 
		x->uncle()->color = BLACK;
		x->grandparent()->color = RED;
		balance_insert(x->grandparent());	//��grandparent�������� 
	} 
	else{ //case4 �� case5 һͬ���У��� 
		//case4.���ڸ��ڵ�RED��uncleΪBLACK���ߡ�ȱ�٣���Ҳ�ɣ����� �ַ�Ϊcase4-1��case4-2. =>JULY����[�����޸����2] 
		if(x->parent->right == x && x->parent == x->grandparent()->left){	//case4-1: x�����ӽڵ���x->parent�����ӽڵ� ���߳�[<]���Ρ���ô�л���parent�����������[/]���Ρ� 
			x = x->parent;
			rotate_left(x);	//��ת�����ı�x�ĵ�ַ�������x��ָ��x��ֻ�����������λ�øı��ˡ���[<]�Ĺյ���[/]����ײ��ˡ�����һ�㡣 
		}
		else if(x->parent->left == x && x->parent == x->grandparent()->right){//case4-2.���߳�[>]���Σ���parent�������[\]���ΰɡ� 
			x = x->parent;
			rotate_right(x); //x�ɱ�����parent��[>]�Ĺյ�λ�ý�Ϊ[\]����ײ��ˡ���ת������˶��ӡ� 
		}
		//��ע�⣡��case4�п��ܲ����ϣ��ǾͲ���������case5��һ��Ҫ���ģ�case4���ˣ�case5ҲҪ����case4������case5��Ҫ���������������� 
		//case5.�������߳��� [/]��[\]��x������ײ㡣���ǰ�x->parentȾ�ڣ���x->grandparentȾ�죬Ȼ���grandparentΪĿ����ת�� 
		x->parent->color = BLACK;
		x->grandparent()->color = RED;
		if(x->parent->left == x && x->grandparent()->left == x->parent){	//case5-1: ��[/]���Ρ� 
			rotate_right(x->grandparent());
		}
		else{	//case5-2����[\]���Ρ� 
			rotate_left(x->grandparent());
		}
	}
}

template <typename T, typename Comp>
typename RBTree<T, Comp>::TreeNode* RBTree<T, Comp>::find_left_max(TreeNode* x){	//���ݲ���ʱ�򣬴���x->left��ȥ.�Ϳ����ҵ�����x�����left���������ֵ�� 
	if(x->right == NIL)	return x;
	return find_left_max(x->right);
}

template <typename T, typename Comp>
void RBTree<T, Comp>::remove(TreeNode* x, const T & data){	//ʹ������void����ֵ�Ͳ�����*&��remove����������ҪԤ�У� 
	if(x == NIL) 	return;
	else if(comp(data, x->data))	remove(x->left, data);
	else if(comp(x->data, data))	remove(x->right, data);
	else{
		if(x->left == NIL || x->right == NIL)	remove_one_child(x);	//�ڵ�ɾ����ָ��ı任ȫ������remove_one_child���ˡ� 
		else {	//�������Ӷ��С����largest_left��Ȼ����nullptr�� 
			TreeNode* largest_left = find_left_max(x->left);
			std::swap(x->data, largest_left->data);
			remove_one_child(largest_left);
		}
	}
}

template <typename T, typename Comp>	//����Ҫ��ɾ���ĵ��ǲ����� 
void RBTree<T, Comp>::remove_one_child(TreeNode* x){	//��ʱx���ҽ���һ��child����single_child���� 
	//x��ʱ��Ϊnullptr 
	TreeNode* child = x->left == NIL ? x->right : x->left;	//ȷ��x���е�һ�����ӵķ���������ӻ����Ҷ��ӣ�
	
	//��������ָ�뻷�� 
	if(x->parent == nullptr && x->left == NIL && x->right == NIL){	//1. x���˾�� 	//���Բ�����ɫֱ��ɾ�� 
		delete x;
		root = nullptr;
		return;
	}
	else if(x->parent == nullptr){	//2. xΪroot���ж���(��1������˳���)		//��Ҫ��ɺ�ɫȻ��ɾ�� 
		child->parent = nullptr;
		root = child;
		child->color = BLACK;	//���ڵ��ɫ
		delete x;
		return; 
	}
//	else if(child == nullptr){		//2.5.....�Լ���ӵġ� wikipedia�ƺ���bug��child��nullptr����˵��x��Ҷ�ڵ㣬�������û�п��ǰɡ�
//		cout << "I am right." << endl;	//���������䡣���� 	������鱾Ӧ��ɢ�����±ߵ�else if �� else�С�����Ϊ�Լ�д�ģ���˼���һ�¡� 
//		if(x->parent->left == x)	x->parent->left == nullptr;
//		else						x->parent->right == nullptr;
//		delete x;
//		return;
//	}
	else if(x->parent->left == x){
		x->parent->left = child;	//����parent�����ָ�롣 
		child->parent = x->parent;	//���û����һ�����飬�������İɡ� 
	}
	else{
		x->parent->right = child;
		child->parent = x->parent;
	}
	
	//��ɫɾ������ 
	if(x->color == RED)		delete x;	//3. x�Ǻ�ɫ��ֱ��ɾ���ùܡ�
	else{								//4. x�Ǻ�ɫ�� 
		if(child->color == RED){	//4-1.   x�Ǻ�ɫ �� x->child�Ǻ�ɫ�� x->child��ڣ�Ȼ��delete x 
			child->color = BLACK;
			delete x;
		}
		else{						//4-2.	��ֵģ�x�Ǻ�ɫ��x->childҲ�Ǻ�ɫ�������������case���ڡ� 
			balance_remove(child);	//��ע�⴫�����child����������child��BLACK���� ����ɾ���Ľڵ��滻�ɱ�Ҫ��ɾ���ڵ�x�Ķ��ӡ����� 
			delete x;
		} 
	} 
}

template <typename T, typename Comp>
void RBTree<T, Comp>::balance_remove(TreeNode* x){	//�����xһ����BLACK��ɫ�ġ� 
	//��insertһ������Ȼ֮ǰ�Ѿ�������x�Ǹ��ڵ��״����������˵��Ӧ����x��root����������Ǳ�������ת������������������νcase1.
	if(x->parent == nullptr)	return;		//case1. ��������������Ѿ������ˡ���Ϊ�����˴˺�������Ĳ�����child������һ�������еı���x��ûɾ���ء��� 
	else{	//����x->parent�е�������ʶ�һ����sibling�� 	//ע���±��Ǽ���case�ǲ��У�����˳��ģʽ���� 
		if(x->sibling()->color == RED) {	//case2. x��BLACK��x->sibling��RED�� => ���ֵ�Ⱦ�ڣ���parent��죬Ȼ�����x��parent->left�������parent������ 
			x->parent->color = RED;
			x->sibling()->color = BLACK;
			if(x->parent->left == x)	rotate_left(x->parent);
			else						rotate_right(x->parent);
		}	//��ת�����ܴ���case3. 
		
		if(x->sibling()->color == BLACK && x->parent->color == BLACK 	//case3. x->parent��x->sibling��x->sibling->left��x->sibling->rightȫ�ڡ� 
				&& x->sibling()->right->color == BLACK && x->sibling()->left->color == BLACK){	//��ʱֻҪ��siblingȾ�졣Ȼ�����parent��ȫ�������� 
			x->sibling()->color = RED;
			balance_remove(x->parent);
		} 
		else if(x->sibling()->color == BLACK && x->parent->color == RED //case4. ��case3�ǲ��л���Ĺ�ϵ����case3ֻ��һ�㲻ͬ������x->parent�Ǻ�ġ�����Ҳȫ�Ǻڵġ�
				&& x->sibling()->right->color == BLACK && x->sibling()->left->color == BLACK){	//=>��ʱ��Ҫ��siblingȾ�죬ҲҪ��parentȾ��. 
			x->sibling()->color = RED;
			x->parent->color = BLACK;
		}
		else{	//case5 & case6 ˳������ 
			//case5: x->sibling->right == BLACK && x->sibling->left == RED	=>  x->sibling->left��ڣ�x->sibiling�����죬��x�����ӣ���x������ 
			if(x->sibling()->color == BLACK 
				&& x->sibling()->right->color == BLACK && x->sibling()->left->color == RED){
				x->sibling()->color = RED;
				if(x->parent->left == x){
					x->sibling()->left->color = BLACK;
					rotate_right(x->sibling());
				}
				else{
					x->sibling()->right->color = BLACK;
					rotate_left(x->sibling());
				} 
			}
			
			//case6: x->sibling->right == RED && x->sibling->left == BLACK  => x->parent->color������x->sibling->color����������x->parentȾ�� 
			if(x->sibling()->color == BLACK		//�����x->sibling->rightҲ��ڣ����x�����ӣ���x->parent������ 
				&& x->sibling()->right->color == RED && x->sibling()->left->color == BLACK){
				x->sibling()->color = x->parent->color;
				x->parent->color = BLACK;
				if(x->parent->left == x){
					x->sibling()->right->color = BLACK;
					rotate_left(x->parent);
				}
				else{
					x->sibling()->left->color = BLACK;
					rotate_right(x->parent);
				}
			}
		}
	}
} 

template <typename T, typename Comp>
void RBTree<T, Comp>:: make_empty(TreeNode* x){
	if(x == NIL)	return;
	make_empty(x->left);
	make_empty(x->right);
	delete x;
}

template <typename T, typename Comp>
void RBTree<T, Comp>::preOrderTraversal(){	//ǰ�����1 
	if(root == nullptr)	return;
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp != NIL){
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
void RBTree<T, Comp>::inOrderTraversal(){	//���������ʹ��ǰ�����1�ı���˳�򼴿ɡ� 
	if(root == nullptr)	return;
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp != NIL){
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

#endif

int main()
{
	RBTree<int> b; 
	b.insert(3);
	b.insert(9);
	b.insert(2);
	b.insert(5);
	b.insert(0);
	
	b.preOrderTraversal();cout << " (�������) "<< endl;
	b.inOrderTraversal();cout << "�����������" << endl;
	
	b.remove(0);
	b.remove(3);
	
	b.preOrderTraversal();cout << " �����������" << endl;
	b.inOrderTraversal();cout << " �����������" << endl;     
}
