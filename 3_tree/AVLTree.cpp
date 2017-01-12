#include <iostream>
#include "AVLTree.hpp"
using namespace std;


//ע�⣺��AVL��ע�ͺͺ������Ǵ�ģ�һ��������left-left�ֲ�����ô���ڵ�rootҪ����right-rotation������ȫд���ˣ��� 
template <typename T>
int AVLTree<T>::height(AVLNode<T>* x) const{
	return x == nullptr ? 0 : x->height;
}

template <typename T>
void AVLTree<T>::insert(AVLNode<T>* &x, const T & data){
	if(x == nullptr)	x = new AVLNode<T>(data, nullptr, nullptr);
	else if(x->data == data){
		x->data = data;
		return; //��ʵ����Ҫbalance.������ôдҲֻ�ܼ���һ�ֵ�balance. 
	}
	else if(x->data > data)	insert(x->left, data);
	else insert(x->right, data);
	
	//ע�����ʱ������new��֮����������������ײ㣡 ���ö�����дheight��������ˣ���Ϊ��ײ���ӽڵ㲻��Ҫ���£� 
	balance(x);	 
}

//��תʱ��������߶ȡ� 
template <typename T>
void AVLTree<T>::balance(AVLNode<T>* &x){
	if(x == nullptr)	return;	//��ֹremoveʱ������� 
	//x�����height���ùܡ�ֻ��left��right��height.ע������insert֮�����ײ㣬�����ӽڵ�heightֵȫ����ȷ�ģ���˿���ֱ���жϡ�
	if(height(x->left) - height(x->right) > 1){	 //����һ��leftRotation 
		if(height(x->left->left) > height(x->left->right)){	//left-left-Rotation
			leftRotation(x);	//xһ���ᱻ�޸ġ� 
		} 
		else {	//�жϹ������if�����һ��insert��x->left->left����x->left->right�����������������height��ȵ������ 
			leftRightRotation(x);	//��һ���ǲ�����x->left->right. left-right-Rotation. 
		}
	}
	else if(height(x->right) - height(x->left) > 1){	//����һ��rightRotation 
		if(height(x->right->right) > height(x->right->left)){
			rightRotation(x);
		}	
		else{
			rightLeftRotation(x);
		}
	}
	
	//�������ifȫû��ִ�У������Ѿ����룬�͸���һ�½����ˡ�
	x->height = std::max(height(x->left), height(x->right)) + 1; 
} 

//��ʱ�����������ڵ�/����״���˺�����������������data insert��x->left->left�����3������/�ˡ�
//��������ֻ��Ҫ����x��x->left�����ڵ�ͺã�Ȼ���������䡣 ���������׹��x->left�±ߵ�����һ�ŵĶ��ӽ�㡣 
template <typename T>
void AVLTree<T>::leftRotation(AVLNode<T>* &x){	
	AVLNode<T>* temp = x->left;
	x->left = temp->right;
	temp->right = x;
	x->height = std::max(height(x->left), height(x->right)) + 1;	//����x���±ߣ��ӵ����ϸ��¸߶ȡ��ӽڵ㲻��Ҫ���£���Ϊû�б仯��
	temp->height = std::max(height(temp->left), height(temp->right)) + 1;
	x = temp;	//root����Ϊtemp�� ����xΪ���ã����ݣ���˿���ֱ���޸�x�� 
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
void AVLTree<T>::leftRightRotation(AVLNode<T>* &x){	//Ҫ�Ե�������ת���ʶ���rightRotation��leftRotation. 
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
		remove(x->left, data);	//ȫ�ǵ��ɲ������ݣ�����ʵ����û�иı�x������Ϊx���൱�ڱ����޸�̫Σ�գ�Ҳ��ֻ�����ڵݹ������ˡ� 
	}
	else if(x->data < data){
		remove(x->right, data);
	}
	else{	//����remove����ʱ�����������1.��ɾ�ڵ�ֻ��һ�����ӻ���û�ж���   2.��ɾ�ڵ���������ȫ����
		if(x->left != nullptr && x->right != nullptr){
			//��������Ƚϼ��֡�����ֱ��ɾ����Ҫαɾ����Ӧ�ðѴ�ɾ�ڵ���������е����dataֵ��max���ǵ���ɾ�ڵ�data��Ȼ��ɾ�����dataֵ�Ǹ��������x��
			//�������������dataֵ���Ѿ������������max->right��Ϊnullptr����˿��Եݹ飬���ǻ��ǲ�̫��2333�������ɡ�
			//�����Ļ�xָ���������Ҫ�Ķ�����Ϊֱ�Ӱ�ֵ���ǵ�������x����root�� 
			AVLNode<T>* behindLeftMax = x;
			AVLNode<T>* leftMax = x->left;
			while(leftMax->right != nullptr){
				behindLeftMax = leftMax;	//׷�� 
				leftMax = leftMax->right;	//ǰ�� 
			} 
			if(behindLeftMax != x){	//˵��x->left����������˵��while�����˶�β��ҵ�maxLeft�� 
				x->data = leftMax->data; //����data
				behindLeftMax->right = leftMax->left;
				delete leftMax; 
			}
			else{	//˵��x->left->right == nullptr.��������ʹ���ϱߵ��㷨��Ҫ���г���. 
				x->data = leftMax->data; //����data
				behindLeftMax->left = leftMax->left;	//������Щ��ͬ����ͼ�� 
				delete leftMax;
			}
		} 
		else{
			AVLNode<T>* oldNode = x;
			x = (x->left == nullptr) ? x->right : x->left;	//x����ͳ�����ϵģ����ֱ���޸ľͺá�����������͸ı��ˣ���BST��tempֻ��һ����·���޸�Ҳֻ�޸���·������������ͳ����仯�� 
			delete oldNode;	
		}
		
	}
		
	balance(x);	//��ɾ���ĵ㼰���Ϸ�������Ҫ���¡����·�������¡� ע�⣺Ҫд������ߣ��� 

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
