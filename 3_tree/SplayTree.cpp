#include "SplayTree.hpp"

//此函数设置后要和父节点打交道。且可以不用传入引用＆实现。因为没有直接改变x。 
template <typename T, typename Comp>	//注意模板实现的默认参数不需要重复写。。。 
void SplayTree<T, Comp>::zig_only(SplayNode* x){	//right_rotation
	SplayNode* temp = x->left;	//创建左子节点指针 
	x->left = temp->right;		//x的左儿子拽下来 
	if(temp->right)	temp->right->parent = x;	//设置temp->right->parent 
	temp->right = x;	//设置temp->right
	temp->parent = x->parent;	//设置temp->parent
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

//有没有祖先什么的判断条件全在调用旋转的时候在加入。 
template <typename T, typename Comp>
void SplayTree<T, Comp>::zig_zig(SplayNode* x){	// [/]=>[\]	先right_rotate(x->grandparent) 再right_rotate(x->parent) 
	zig_only(x->parent->parent);	//远程旋转了祖先grandfather. 
	zig_only(x->parent);	//再近程旋转father. 
}

//旋转之后的结果是，某个节点和它上边的指针会一起旋转。所以指针x还是指向它原先指向的对象没有变。 但是父亲变了！原先的爷爷变成父亲了。 
template <typename T, typename Comp>
void SplayTree<T, Comp>::zig_zag(SplayNode* x){	// [<]=>[>]	先left_rotate(x->parent) 这时x会向上升一级 再right_rotate(x->parent) 
	zag_only(x->parent);	 
	zig_only(x->parent);	 
}

//镜像 
template <typename T, typename Comp>
void SplayTree<T, Comp>::zag_zig(SplayNode* x){	// [>]=>[<]	先right_rotate(x->parent) 这时x会向上升一级 再left_rotate(x->parent) 
	zig_only(x->parent);	 
	zag_only(x->parent);	 
}

//镜像 
template <typename T, typename Comp>
void SplayTree<T, Comp>::zag_zag(SplayNode* x){	// [\]=>[/]	先left_rotate(x->grandparent) 再left_rotate(x->parent) 
	zag_only(x->parent->parent);	//远程旋转了祖先grandfather. 
	zag_only(x->parent);	//再近程旋转father. 
}

template <typename T, typename Comp>
void SplayTree<T, Comp>::splay(SplayNode* x){	
	while(x->parent){	//只要有父节点时（不论有没有祖先），only有parent就zig_only，有grandparent就zig_zig. 直到到达根部位置。 
		if(x->parent->parent == nullptr){
			if(x->parent->left == x)	zig_only(x->parent);	//单旋转别忘了x->parent。。。 
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

//和以前一样，找到并插入就执行splay。 
template <typename T, typename Comp>
void SplayTree<T, Comp>::insert(T const & data){
	SplayNode* temp = root;
	SplayNode* p = nullptr;
	while(temp){
		p = temp;	//必须有一个一直是temp->parent的p！否则new的时候由于temp==null会变成无根之木！ 
		if(comp(temp->data, data))	temp = temp->right;
		else temp = temp->left;	//即使是[等于]，也向左边放。后续只要一直遵循这个规则就不会出问题。 
	}
	temp = new SplayNode(data, p);	//迭代下，不能像递归一样，if(root==nullptr) root = new....绝不可以写在while前边。。。否则就接替着new root进行while了。。 
	//把p的儿子设置为temp
	if(p == nullptr)	root = temp;	//考虑root==nullptr的情况。这样while会直接跳过。
	else if(comp(p->data, temp->data))	p->right = temp;
	else p->left = temp;	//由于上边遵循了相等也付给左边的法则，这里同样遵守。
	 
	//splay.
	splay(temp);	//旋转过后，temp还是指向new T。而且，旋转的效果使得new T变成了root。
	
	size ++; 
	 
}

template <typename T, typename Comp>
typename SplayTree<T, Comp>::SplayNode* SplayTree<T, Comp>::find(T const & data){	//typename超级重要！！ 
	SplayNode* temp = root;
	while(temp != nullptr){
		if(comp(temp->data, data))	temp = temp->right;
		else if(comp(data, temp->data))	temp = temp->left;
		else{
			splay(temp);	//旋转一下！ 
			return temp;
		}
	}
	return nullptr;
}

//移走x->parent到x的link接到y上，y接到x->parent上。 
template <typename T, typename Comp>
void SplayTree<T, Comp>::replace(SplayNode* x, SplayNode* y){	//更改x的parent的x方向的儿子为y 
	if(!x->parent)	root = y;
	else if(x->parent->left == x) x->parent->left = y;
	else x->parent->right = y;
	//还要设置y的parent为x->parent.
	//注意，x的parent并没有取消。也就是现在x和y都指向同一个parent。
	if(y != nullptr)	y->parent = x->parent; 	//别忘判断y == nullptr.因为y可能是null。但是x一定有实体。因为x都有parent。 
}

//找到后先splay再删除根节点。 
template <typename T, typename Comp>
void SplayTree<T, Comp>::remove(T const & data){
	SplayNode* temp = find(data);	//找到并提到root来 这时temp == root。 
	if(temp == nullptr)	return;  
	
	//执行删除。 
	SplayNode* z = root;	//保留现在的root！！一会replace之后，有可能root就换了！！小心！！ 
	if(temp->left == nullptr)	replace(temp, temp->right);
	else if(temp->right == nullptr)	replace(temp, temp->left);
	else{
		//找到左子树最大结点 
		SplayNode* beforeTemp;
		temp = temp->left;
		while(temp->right != nullptr){
			beforeTemp = temp;
			temp = temp->right;
		}
		//分为两种情况：1.最大节点就是root->left. 2.深度大于1.
		if(root->left != temp){
			replace(temp, temp->left);	//temp节点与parent的link交接给temp->left.
			temp->left = root->left;
			temp->left->parent = temp;
		} 
		replace(root, temp);	//insert 1, insert 5, insert 3, 之后删除3会由于root在replace中变成和temp一样的1而导致崩溃！应该使用原先的root！ 
		temp->right = /*root*/z->right;	//此算法并不是值替换！！而是直接替换结点！！ 
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


