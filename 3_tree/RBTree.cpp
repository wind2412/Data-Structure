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
void RBTree<T, Comp>::rotate_left(TreeNode* x){	//和AVL左旋相同。颜色也不需要在这里处理。 //而且因为有了parent属性，参数没有必要使用引用&了。 
	TreeNode* temp = x->right;
	x->right = temp->left;
	temp->left = x;
	if(x->parent == nullptr){
		root = temp;	 
		temp->parent = nullptr; 
	} 
	else{		//更新x->parent所关联的两个指针  
		temp->parent = x->parent;
		if(x->parent->left == x)	x->parent->left = temp;
		else						x->parent->right = temp;
	}
	x->parent = temp;	//假设x和x->right全都存在，可以进行直接旋转。不需要考虑别的。
	if(x->right != NIL)	x->right->parent = x;	//从temp那里得到的字节点不是NIL。 
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
		root->color = BLACK;	//根节点要黑色！！ 
	}
	else{
		insert(root, data);	//参数为nullptr的情况已经被处理完毕，可以无忧矣。 
	}
}

template <typename T, typename Comp>
void RBTree<T, Comp>::insert(TreeNode* x, const T & data){	//x已经处理完nullptr的情况，可以不考虑那么多了。 
	//由于带有parent，是线索的，别忘了进行预判！！！
	if(comp(data, x->data)){
		if(x->left != NIL)	insert(x->left, data);	//预判是不是nullptr！这个函数中必须保证传参不是nullptr啊！！ 
		//将要传参是nullptr的情况在else里处理了！因为x->left==nullptr但是x不为空，则将要生成的new TreeNode可以找到爸爸。 
		else	x->left = new TreeNode(data, x); 
	}
	else if(comp(x->data, data)){
		if(x->right != NIL)		insert(x->right, data);
		else 	x->right = new TreeNode(data, x);
	} 
	else{
		x->data = data;
		return;	//如果已有，则更新数值，而后不参与balance，直接返回。 
	}
	
	balance_insert(x);
	
}

template <typename T, typename Comp>
void RBTree<T, Comp>::balance_insert(TreeNode* x){
	//由于有旋转，因此x是根节点也是可能的。但是x自身绝不可能是nullptr => case1. 
	if(x->parent == nullptr)					x->color = BLACK;	//case1.无父结点。 
	else if(x->parent->color == BLACK)			return;				//case2.父节点为BLACK。满足性质。返回即可。	剩下的情况全建立于x->parent->color==RED. 
	else if(x->uncle() != nullptr && x->uncle()->color == RED){	//case3.父节点为RED且uncle为RED => 两者全黑，grandparent染红，并在grandparent上重来。 
		x->parent->color = BLACK;								//JULY大大的[插入删除情况1] 
		x->uncle()->color = BLACK;
		x->grandparent()->color = RED;
		balance_insert(x->grandparent());	//在grandparent上重做！ 
	} 
	else{ //case4 和 case5 一同进行！！ 
		//case4.基于父节点RED，uncle为BLACK或者【缺少！！也可！】。 又分为case4-1和case4-2. =>JULY大大的[插入修复情况2] 
		if(x->parent->right == x && x->parent == x->grandparent()->left){	//case4-1: x是右子节点且x->parent是左子节点 三者成[<]字形。那么切换到parent并左旋。变成[/]字形。 
			x = x->parent;
			rotate_left(x);	//旋转并不改变x的地址啊。因此x还指向x。只不过树的相对位置改变了。由[<]的拐点变成[/]的最底层了。降了一层。 
		}
		else if(x->parent->left == x && x->parent == x->grandparent()->right){//case4-2.三者成[>]字形，对parent右旋变成[\]字形吧。 
			x = x->parent;
			rotate_right(x); //x由本来是parent的[>]的拐点位置降为[\]的最底层了。旋转完后变成了儿子。 
		}
		//【注意！！case4有可能不符合，那就不做；但是case5是一定要做的！case4做了，case5也要做；case4不做，case5还要做！！勿忘！！】 
		//case5.现在三者呈现 [/]和[\]。x还在最底层。我们把x->parent染黑，把x->grandparent染红，然后把grandparent为目标旋转。 
		x->parent->color = BLACK;
		x->grandparent()->color = RED;
		if(x->parent->left == x && x->grandparent()->left == x->parent){	//case5-1: 成[/]字形。 
			rotate_right(x->grandparent());
		}
		else{	//case5-2：成[\]字形。 
			rotate_left(x->grandparent());
		}
	}
}

template <typename T, typename Comp>
typename RBTree<T, Comp>::TreeNode* RBTree<T, Comp>::find_left_max(TreeNode* x){	//传递参数时候，传递x->left进去.就可以找到除了x以外的left子树的最大值。 
	if(x->right == NIL)	return x;
	return find_left_max(x->right);
}

template <typename T, typename Comp>
void RBTree<T, Comp>::remove(TreeNode* x, const T & data){	//使用这种void返回值和不传递*&的remove。。。还是要预判？ 
	if(x == NIL) 	return;
	else if(comp(data, x->data))	remove(x->left, data);
	else if(comp(x->data, data))	remove(x->right, data);
	else{
		if(x->left == NIL || x->right == NIL)	remove_one_child(x);	//节点删除和指针的变换全都放在remove_one_child中了。 
		else {	//两个孩子都有。因此largest_left必然不是nullptr。 
			TreeNode* largest_left = find_left_max(x->left);
			std::swap(x->data, largest_left->data);
			remove_one_child(largest_left);
		}
	}
}

template <typename T, typename Comp>	//真正要被删除的点是参数。 
void RBTree<T, Comp>::remove_one_child(TreeNode* x){	//此时x有且仅有一个child！！single_child！！ 
	//x此时不为nullptr 
	TreeNode* child = x->left == NIL ? x->right : x->left;	//确定x仅有的一个儿子的方向是左儿子还是右儿子？
	
	//调整各种指针环节 
	if(x->parent == nullptr && x->left == NIL && x->right == NIL){	//1. x光杆司令 	//可以不变颜色直接删除 
		delete x;
		root = nullptr;
		return;
	}
	else if(x->parent == nullptr){	//2. x为root且有儿子(被1情况过滤出来)		//需要变成黑色然后删除 
		child->parent = nullptr;
		root = child;
		child->color = BLACK;	//根节点黑色
		delete x;
		return; 
	}
//	else if(child == nullptr){		//2.5.....自己添加的。 wikipedia似乎有bug。child是nullptr，就说名x是叶节点，这种情况没有考虑吧。
//		cout << "I am right." << endl;	//输出测试语句。。。 	这个语句块本应该散发到下边的else if 和 else中。但因为自己写的，因此集成一下。 
//		if(x->parent->left == x)	x->parent->left == nullptr;
//		else						x->parent->right == nullptr;
//		delete x;
//		return;
//	}
	else if(x->parent->left == x){
		x->parent->left = child;	//更新parent自身的指针。 
		child->parent = x->parent;	//如果没有上一个语句块，这里会崩的吧。 
	}
	else{
		x->parent->right = child;
		child->parent = x->parent;
	}
	
	//变色删除环节 
	if(x->color == RED)		delete x;	//3. x是红色：直接删不用管。
	else{								//4. x是黑色： 
		if(child->color == RED){	//4-1.   x是黑色 且 x->child是红色： x->child变黑，然后delete x 
			child->color = BLACK;
			delete x;
		}
		else{						//4-2.	最棘手的：x是黑色，x->child也是黑色。。。必须进入case环节。 
			balance_remove(child);	//【注意传入的是child。。。而且child是BLACK。】 【把删除的节点替换成本要被删除节点x的儿子。。】 
			delete x;
		} 
	} 
}

template <typename T, typename Comp>
void RBTree<T, Comp>::balance_remove(TreeNode* x){	//传入的x一定是BLACK颜色的。 
	//和insert一样，虽然之前已经处理完x是根节点的状况，按理来说不应该有x是root的情况。但是别忘了旋转！！能旋上来！！此谓case1.
	if(x->parent == nullptr)	return;		//case1. 这种情况，就是已经做完了。因为别忘了此函数传入的参数是child。。上一个函数中的变量x还没删除呢。。 
	else{	//基于x->parent有的情况。故而一定有sibling。 	//注意下边是几个case非并列，而是顺序模式！！ 
		if(x->sibling()->color == RED) {	//case2. x是BLACK，x->sibling是RED。 => 把兄弟染黑，把parent变红，然后如果x是parent->left，则基于parent左旋！ 
			x->parent->color = RED;
			x->sibling()->color = BLACK;
			if(x->parent->left == x)	rotate_left(x->parent);
			else						rotate_right(x->parent);
		}	//旋转完后可能触发case3. 
		
		if(x->sibling()->color == BLACK && x->parent->color == BLACK 	//case3. x->parent，x->sibling及x->sibling->left及x->sibling->right全黑。 
				&& x->sibling()->right->color == BLACK && x->sibling()->left->color == BLACK){	//此时只要把sibling染红。然后基于parent完全重做！！ 
			x->sibling()->color = RED;
			balance_remove(x->parent);
		} 
		else if(x->sibling()->color == BLACK && x->parent->color == RED //case4. 与case3是并列互斥的关系。和case3只有一点不同，就是x->parent是红的。其他也全是黑的。
				&& x->sibling()->right->color == BLACK && x->sibling()->left->color == BLACK){	//=>此时既要把sibling染红，也要把parent染黑. 
			x->sibling()->color = RED;
			x->parent->color = BLACK;
		}
		else{	//case5 & case6 顺序做。 
			//case5: x->sibling->right == BLACK && x->sibling->left == RED	=>  x->sibling->left变黑，x->sibiling自身变红，若x是左子，对x右旋。 
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
			
			//case6: x->sibling->right == RED && x->sibling->left == BLACK  => x->parent->color【赋给x->sibling->color！！】而后x->parent染黑 
			if(x->sibling()->color == BLACK		//而后把x->sibling->right也变黑，如果x是左子，对x->parent左旋！ 
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
void RBTree<T, Comp>::preOrderTraversal(){	//前序遍历1 
	if(root == nullptr)	return;
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp != NIL){
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
void RBTree<T, Comp>::inOrderTraversal(){	//中序遍历，使用前序遍历1改变下顺序即可。 
	if(root == nullptr)	return;
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while(true){
		while(temp != NIL){
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

#endif

int main()
{
	RBTree<int> b; 
	b.insert(3);
	b.insert(9);
	b.insert(2);
	b.insert(5);
	b.insert(0);
	
	b.preOrderTraversal();cout << " (先序遍历) "<< endl;
	b.inOrderTraversal();cout << "（中序遍历）" << endl;
	
	b.remove(0);
	b.remove(3);
	
	b.preOrderTraversal();cout << " （先序遍历）" << endl;
	b.inOrderTraversal();cout << " （中序遍历）" << endl;     
}
