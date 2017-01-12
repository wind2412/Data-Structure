#include "SplayTree.hpp"

//�˺������ú�Ҫ�͸��ڵ�򽻵����ҿ��Բ��ô������ã�ʵ�֡���Ϊû��ֱ�Ӹı�x�� 
template <typename T, typename Comp>	//ע��ģ��ʵ�ֵ�Ĭ�ϲ�������Ҫ�ظ�д������ 
void SplayTree<T, Comp>::zig_only(SplayNode* x){	//right_rotation
	SplayNode* temp = x->left;	//�������ӽڵ�ָ�� 
	x->left = temp->right;		//x�������ק���� 
	if(temp->right)	temp->right->parent = x;	//����temp->right->parent 
	temp->right = x;	//����temp->right
	temp->parent = x->parent;	//����temp->parent
	if(temp->parent == nullptr)	root = temp; 
	else if(temp->parent->left == x)	temp->parent->left = temp;
	else temp->parent->right = temp;
	x->parent = temp;
}

template <typename T, typename Comp>
void SplayTree<T, Comp>::zag_only(SplayNode* x){	//left_rotation
	SplayNode* temp = x->right;
	x->right = temp->left;
	if(temp->left) temp->left->parent = x;
	temp->left = x;
	temp->parent = x->parent;
	if(temp->parent == nullptr) root = temp;
	else if(temp->parent->left == x) temp->parent->left = temp;
	else temp->parent->right = temp;
	x->parent = temp; 
}

//��û������ʲô���ж�����ȫ�ڵ�����ת��ʱ���ڼ��롣 
template <typename T, typename Comp>
void SplayTree<T, Comp>::zig_zig(SplayNode* x){	// [/]=>[\]	��right_rotate(x->grandparent) ��right_rotate(x->parent) 
	zig_only(x->parent->parent);	//Զ����ת������grandfather. 
	zig_only(x->parent);	//�ٽ�����תfather. 
}

//��ת֮��Ľ���ǣ�ĳ���ڵ�����ϱߵ�ָ���һ����ת������ָ��x����ָ����ԭ��ָ��Ķ���û�б䡣 ���Ǹ��ױ��ˣ�ԭ�ȵ�үү��ɸ����ˡ� 
template <typename T, typename Comp>
void SplayTree<T, Comp>::zig_zag(SplayNode* x){	// [<]=>[>]	��left_rotate(x->parent) ��ʱx��������һ�� ��right_rotate(x->parent) 
	zag_only(x->parent);	 
	zig_only(x->parent);	 
}

//���� 
template <typename T, typename Comp>
void SplayTree<T, Comp>::zag_zig(SplayNode* x){	// [>]=>[<]	��right_rotate(x->parent) ��ʱx��������һ�� ��left_rotate(x->parent) 
	zig_only(x->parent);	 
	zag_only(x->parent);	 
}

//���� 
template <typename T, typename Comp>
void SplayTree<T, Comp>::zag_zag(SplayNode* x){	// [\]=>[/]	��left_rotate(x->grandparent) ��left_rotate(x->parent) 
	zag_only(x->parent->parent);	//Զ����ת������grandfather. 
	zag_only(x->parent);	//�ٽ�����תfather. 
}

template <typename T, typename Comp>
void SplayTree<T, Comp>::splay(SplayNode* x){	
	while(x->parent){	//ֻҪ�и��ڵ�ʱ��������û�����ȣ���only��parent��zig_only����grandparent��zig_zig. ֱ���������λ�á� 
		if(x->parent->parent == nullptr){
			if(x->parent->left == x)	zig_only(x->parent);	//����ת������x->parent������ 
			else zag_only(x->parent);
		}
		else if(x->parent->left == x && x->parent->parent->left == x->parent){
			zig_zig(x);
		}	
		else if(x->parent->left == x && x->parent->parent->right== x->parent){
			zag_zig(x);
		}
		else if(x->parent->right== x && x->parent->parent->left == x->parent){
			zig_zag(x);
		}
		else{
			zag_zag(x);
		}
	}
}

//����ǰһ�����ҵ��������ִ��splay�� 
template <typename T, typename Comp>
void SplayTree<T, Comp>::insert(T const & data){
	SplayNode* temp = root;
	SplayNode* p = nullptr;
	while(temp){
		p = temp;	//������һ��һֱ��temp->parent��p������new��ʱ������temp==null�����޸�֮ľ�� 
		if(comp(temp->data, data))	temp = temp->right;
		else temp = temp->left;	//��ʹ��[����]��Ҳ����߷š�����ֻҪһֱ��ѭ�������Ͳ�������⡣ 
	}
	temp = new SplayNode(data, p);	//�����£�������ݹ�һ����if(root==nullptr) root = new....��������д��whileǰ�ߡ���������ͽ�����new root����while�ˡ��� 
	//��p�Ķ�������Ϊtemp
	if(p == nullptr)	root = temp;	//����root==nullptr�����������while��ֱ��������
	else if(comp(p->data, temp->data))	p->right = temp;
	else p->left = temp;	//�����ϱ���ѭ�����Ҳ������ߵķ�������ͬ�����ء�
	 
	//splay.
	splay(temp);	//��ת����temp����ָ��new T�����ң���ת��Ч��ʹ��new T�����root��
	
	size ++; 
	 
}

template <typename T, typename Comp>
typename SplayTree<T, Comp>::SplayNode* SplayTree<T, Comp>::find(T const & data){	//typename������Ҫ���� 
	SplayNode* temp = root;
	while(temp != nullptr){
		if(comp(temp->data, data))	temp = temp->right;
		else if(comp(data, temp->data))	temp = temp->left;
		else{
			splay(temp);	//��תһ�£� 
			return temp;
		}
	}
	return nullptr;
}

//����x->parent��x��link�ӵ�y�ϣ�y�ӵ�x->parent�ϡ� 
template <typename T, typename Comp>
void SplayTree<T, Comp>::replace(SplayNode* x, SplayNode* y){	//����x��parent��x����Ķ���Ϊy 
	if(!x->parent)	root = y;
	else if(x->parent->left == x) x->parent->left = y;
	else x->parent->right = y;
	//��Ҫ����y��parentΪx->parent.
	//ע�⣬x��parent��û��ȡ����Ҳ��������x��y��ָ��ͬһ��parent��
	if(y != nullptr)	y->parent = x->parent; 	//�����ж�y == nullptr.��Ϊy������null������xһ����ʵ�塣��Ϊx����parent�� 
}

//�ҵ�����splay��ɾ�����ڵ㡣 
template <typename T, typename Comp>
void SplayTree<T, Comp>::remove(T const & data){
	SplayNode* temp = find(data);	//�ҵ����ᵽroot�� ��ʱtemp == root�� 
	if(temp == nullptr)	return;  
	
	//ִ��ɾ���� 
	SplayNode* z = root;	//�������ڵ�root����һ��replace֮���п���root�ͻ��ˣ���С�ģ��� 
	if(temp->left == nullptr)	replace(temp, temp->right);
	else if(temp->right == nullptr)	replace(temp, temp->left);
	else{
		//�ҵ������������ 
		SplayNode* beforeTemp;
		temp = temp->left;
		while(temp->right != nullptr){
			beforeTemp = temp;
			temp = temp->right;
		}
		//��Ϊ���������1.���ڵ����root->left. 2.��ȴ���1.
		if(root->left != temp){
			replace(temp, temp->left);	//temp�ڵ���parent��link���Ӹ�temp->left.
			temp->left = root->left;
			temp->left->parent = temp;
		} 
		replace(root, temp);	//insert 1, insert 5, insert 3, ֮��ɾ��3������root��replace�б�ɺ�tempһ����1�����±�����Ӧ��ʹ��ԭ�ȵ�root�� 
		temp->right = /*root*/z->right;	//���㷨������ֵ�滻��������ֱ���滻��㣡�� 
		temp->right->parent = temp;
		
		
	}
	delete z;
	
	size --;
}

int main()
{
	SplayTree<int> s;
	s.insert(3);
	s.insert(5);
	s.insert(7);
	s.insert(9);
	s.insert(1);
	s.preorderTraversal() << endl;
	cout << s.find(3)-> data;
	s.preorderTraversal() << endl;
	s.remove(3);
	s.preorderTraversal() << endl;
	s.remove(5);
	s.preorderTraversal() << endl;
	s.remove(9);
	s.preorderTraversal() << endl;
	s.remove(7);
	s.preorderTraversal() << endl;
	s.remove(1);
	return 0; 
}


