#include <iostream>
#include "AVLTree.hpp"
using namespace std;


//注意：此AVL有注释和函数名是错的！一个树满足left-left分布，那么根节点root要进行right-rotation！！！全写反了！！ 
template <typename T>
int AVLTree<T>::height(AVLNode<T>* x) const{
	return x == nullptr ? 0 : x->height;
}

template <typename T>
void AVLTree<T>::insert(AVLNode<T>* &x, const T & data){
	if(x == nullptr)	x = new AVLNode<T>(data, nullptr, nullptr);
	else if(x->data == data){
		x->data = data;
		return; //其实不需要balance.但是这么写也只能减少一轮的balance. 
	}
	else if(x->data > data)	insert(x->left, data);
	else insert(x->right, data);
	
	//注意这个时候，是在new完之后的情况！所以在最底层！ 不用额外再写height更新语句了！因为最底层的子节点不需要更新！ 
	balance(x);	 
}

//旋转时候会更新其高度。 
template <typename T>
void AVLTree<T>::balance(AVLNode<T>* &x){
	if(x == nullptr)	return;	//防止remove时候崩！！ 
	//x自身的height不用管。只管left和right的height.注意是在insert之后的最底层，左右子节点height值全是正确的，因此可以直接判断。
	if(height(x->left) - height(x->right) > 1){	 //至少一重leftRotation 
		if(height(x->left->left) > height(x->left->right)){	//left-left-Rotation
			leftRotation(x);	//x一定会被修改。 
		} 
		else {	//判断过最外层if，因此一定insert在x->left->left或者x->left->right。因而不存在这两者height相等的情况。 
			leftRightRotation(x);	//就一定是插在了x->left->right. left-right-Rotation. 
		}
	}
	else if(height(x->right) - height(x->left) > 1){	//至少一重rightRotation 
		if(height(x->right->right) > height(x->right->left)){
			rightRotation(x);
		}	
		else{
			rightLeftRotation(x);
		}
	}
	
	//如果两个if全没有执行，由于已经插入，就更新一下结点好了。
	x->height = std::max(height(x->left), height(x->right)) + 1; 
} 

//这时树呈现两个节点/的形状。此函数被调用是由于有data insert到x->left->left，变成3个结点的/了。
//但是我们只需要考虑x和x->left两个节点就好，然后向右折弯。 第三个结点坠在x->left下边当做大一号的儿子结点。 
template <typename T>
void AVLTree<T>::leftRotation(AVLNode<T>* &x){	
	AVLNode<T>* temp = x->left;
	x->left = temp->right;
	temp->right = x;
	x->height = std::max(height(x->left), height(x->right)) + 1;	//现在x在下边，从底向上更新高度。子节点不需要更新，因为没有变化。
	temp->height = std::max(height(temp->left), height(temp->right)) + 1;
	x = temp;	//root更新为temp。 由于x为引用＆传递，因此可以直接修改x。 
}

template <typename T>
void AVLTree<T>::rightRotation(AVLNode<T>* &x){
	AVLNode<T>* temp = x->right;
	x->right = temp->left;
	temp->left = x;
	x->height = std::max(height(x->left), height(x->right)) + 1;
	temp->height = std::max(height(temp->left), height(temp->right)) + 1;
	x = temp;
}

template <typename T>
void AVLTree<T>::leftRightRotation(AVLNode<T>* &x){	//要自底向上旋转。故而先rightRotation后leftRotation. 
	rightRotation(x->left);
	leftRotation(x);
}

template <typename T>
void AVLTree<T>::rightLeftRotation(AVLNode<T>* &x){	 
	leftRotation(x->right);
	rightRotation(x);
}

template <typename T>
void AVLTree<T>::remove(AVLNode<T>* &x, const T & data){
	if(x == nullptr)	return;
	if(x->data > data){
		remove(x->left, data);	//全是当成参数传递！！其实根本没有改变x！！因为x就相当于本身，修改太危险！也就只适用于递归的情况了。 
	}
	else if(x->data < data){
		remove(x->right, data);
	}
	else{	//可以remove！这时分两种情况：1.待删节点只有一个儿子或者没有儿子   2.待删节点两个儿子全都有
		if(x->left != nullptr && x->right != nullptr){
			//这种情况比较棘手。不能直接删除，要伪删除。应该把待删节点的左子树中的最大data值点max覆盖掉待删节点data，然后删掉最大data值那个点而不是x。
			//由于左子树最大data值点已经是左边最大，因此max->right必为nullptr。因此可以递归，但是还是不太好2333，迭代吧。
			//这样的话x指针根本不需要改动，因为直接把值覆盖掉，所以x还是root。 
			AVLNode<T>* behindLeftMax = x;
			AVLNode<T>* leftMax = x->left;
			while(leftMax->right != nullptr){
				behindLeftMax = leftMax;	//追上 
				leftMax = leftMax->right;	//前进 
			} 
			if(behindLeftMax != x){	//说明x->left有右子树。说明while进行了多次才找到maxLeft。 
				x->data = leftMax->data; //覆盖data
				behindLeftMax->right = leftMax->left;
				delete leftMax; 
			}
			else{	//说明x->left->right == nullptr.这样不能使用上边的算法，要单列出来. 
				x->data = leftMax->data; //覆盖data
				behindLeftMax->left = leftMax->left;	//这里有些许不同。见图。 
				delete leftMax;
			}
		} 
		else{
			AVLNode<T>* oldNode = x;
			x = (x->left == nullptr) ? x->right : x->left;	//x是正统方向上的，因此直接修改就好。整个链表方向就改变了，而BST中temp只是一个旁路，修改也只修改旁路。。。但是正统不会变化。 
			delete oldNode;	
		}
		
	}
		
	balance(x);	//被删除的点及其上方所有需要更新。而下方无需更新。 注意：要写在最外边！！ 

} 

template <typename T>
void AVLTree<T>::inOrderTraversal(AVLNode<T>* x){
	if(x != nullptr){
		inOrderTraversal(x->left);
		std::cout << x->data << " -> height: " << x->height << std::endl;
		inOrderTraversal(x->right);
	}	 
}



int main()
{
	AVLTree<int> avl;
	avl.insert(3);
	avl.insert(5);
	avl.insert(8);
	avl.insert(4);
	avl.inOrderTraversal();
//	avl.remove(8);
//	cout << endl;
//	avl.inOrderTraversal();
	avl.remove(4);
	cout << endl;
	avl.inOrderTraversal();
	
}
