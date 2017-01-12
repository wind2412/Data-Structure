#ifndef _BINOMIAL_HEAP_IMPL_H_
#define _BINOMIAL_HEAP_IMPL_H_
#include "BinomialHeap.hpp"

template <typename T, typename Comp>
using TreeNode = typename BinomialHeap<T, Comp>::TreeNode;

template <typename T, typename Comp>
BinomialHeap<T, Comp>::BinomialHeap(T const & x): forest(1), currentSize(1){
	forest[0] = new TreeNode(x);
}

template <typename T, typename Comp>
typename BinomialHeap<T, Comp>::TreeNode* BinomialHeap<T, Comp>::combineTrees(TreeNode* t1, TreeNode* t2){
	if(comp(t2->data, t1->data)){
		return combineTrees(t2, t1);
	}
	t2->nextSibling = t1->leftChild;
	t1->leftChild = t2;
	return t1;
}

template <typename T, typename Comp>
bool BinomialHeap<T, Comp>::isEmpty(){
	return currentSize == 0;
}

template <typename T, typename Comp>
int BinomialHeap<T, Comp>::capacity(){
	return 1<<forest.size() - 1;	//2^size() - 1  //2^0+2^1 = 2^2-1
}

template <typename T, typename Comp>
void BinomialHeap<T, Comp>::merge(BinomialHeap & rhs){
	if(this == &rhs)	return;	//�����������
	
	//���½������ 
	currentSize += rhs.currentSize;
	rhs.currentSize = 0;
	
	//�������ݣ�������
	if(currentSize > this->capacity()){
		int oldSize = forest.size();	//����ԭ�ȵ�size 
		int newSize = max(forest.size(), rhs.forest.size()) + 1;	//��������Ϊ����forest��size���ֵ+1 
		forest.resize(newSize);	//resize 
		while(oldSize < newSize){	//���ڴ�forest����������Ĳ���ȫ���nullptr 
			forest[oldSize++] = nullptr;
		}
	} 
	
	//�ϲ��㷨	�����µ�carryָ���ݴ��ºϲ�����
	TreeNode* carry = nullptr;	//���븳ֵΪnullptr����Ϊ�����Ҫ�жϡ��������ֵ����!=nullptr�ĺ������û�Թ� 
	//Ư������Ϊ���2^n���õ���currentSizeʱ����currentSize������2^nʱ���ͻᷢ�����һ������forest�ϲ����carry�޷��浽this->forest.
	//ʹ�����µ��ֶΣ�������һ������Ϊ���ۣ�������������࣡������ѭ����߶����ж��ˣ�
	for(int i = 0, j = 1; j <= currentSize; ++i, j *= 2){
		TreeNode* t1 = this->forest[i];	//��ȡ��ָ�뱣�����������������Ϳ��Զ�forest�����޸��ˣ��� 
		TreeNode* t2 = i < rhs.forest.size() ? rhs.forest[i] : nullptr;	//��Ϊʹ��this->currentSize��Ϊ��������ȷ��rhs�Ƿ�������Ư����
		
		//�±ߵ��㷨����Linux chmod chown���ַ�����2^1 2^2 2^3�Ȳ��ظ���ʽ��������ӣ�������ȫ���ظ�Ϊǰ�ᣡ��
		int whichCase =    	t1==nullptr ? 0 : 1;
		whichCase    +=    	t2==nullptr ? 0 : 2;
		whichCase    +=  carry==nullptr ? 0 : 4; 
		
		switch(whichCase){
			case 0:	//����
			case 1: //ֻ��this
				break;
			case 2: //ֻ��rhs
				this->forest[i] = t2;
				rhs.forest[i] = nullptr;
				break;
			case 3: //��this��rhs �����浽carry��
				carry = combineTrees(t1, t2);
				this->forest[i] = rhs.forest[i] = nullptr;
				break;
			case 4:	//ֻ��carry
				this->forest[i] = carry;
				carry = nullptr;
				break;
			case 5:	//��this��carry 
			 	carry = combineTrees(t1, carry);
			 	this->forest[i] = nullptr;
			 	break;
			case 6:	//��rhs��carry
				carry = combineTrees(t2, carry);
				rhs.forest[i] = nullptr;
				break; 
			case 7: //��this��rhs��carry 
				this->forest[i] = carry;	//carry�ŵ�this��
				carry = combineTrees(t1, t2);
				rhs.forest[i] = nullptr;
				break; 
		}
		
		for(auto & tree : rhs.forest){
			tree = nullptr;
		}
	} 
}

template <typename T, typename Comp>
int BinomialHeap<T, Comp>::findMinIndex(){
	int i;
	for(i = 0; forest[i] == nullptr; i ++);
	int min = i;
	for(; i < forest.size(); i ++){
		if(forest[i] != nullptr && comp(forest[i]->data, forest[min]->data))	min = i; 	//�����ж�nullptr�� 
	}
	return min;
}

template <typename T, typename Comp>
void BinomialHeap<T, Comp>::insert(T const & x){
	BinomialHeap b(x);
	merge(b);	//����ֱ������߽���������Ϊmerge������&���͡���ֵ�ǲ�����ȡ���õġ� 
}

template <typename T, typename Comp>
T BinomialHeap<T, Comp>::getMin(){
	return forest[findMinIndex()]->data;
}

template <typename T, typename Comp>
void BinomialHeap<T, Comp>::deleteMin(){
	if(isEmpty())	return;
	int minIndex = findMinIndex();
	
	//ɾ�����ڵ㣬���ұ����������Ԫ�ء� 
	TreeNode* oldTree = forest[minIndex];
	TreeNode* remainTree = oldTree->leftChild;
	delete oldTree; 
	
	//����H''
	BinomialHeap remainForest;
	remainForest.forest.resize(minIndex + 1);	//�������±�+1������ ��0��ʼ!
	remainForest.currentSize = (1 << minIndex) - 1;
	for(int j = minIndex - 1; j >= 0; --j){
		remainForest.forest[j] = remainTree;	//��������ж����� 
		remainTree = remainTree->nextSibling;	//��һ�������ֵܻ��֡� 
		remainForest.forest[j]->nextSibling = nullptr;	//�ж����ֵܡ��Ժ�����ر������е�����ӡ�  
	} 
	
	//����H' 
	forest[minIndex] = nullptr;
	currentSize -= remainForest.currentSize + 1;	//�б�Ҫ�ȶ��ȥ���еķ����ȥ��remainTree��currentSize����Ϊmerge֮�󻹻�ӻ��������� 
	
	merge(remainForest);
	 
}

#endif

int main()
{
	BinomialHeap<int> bh(3);
	bh.insert(5);
	bh.insert(7);
	bh.insert(1);
	for(int i = 0; i < 4; i ++){
		cout << "Min value: " << bh.getMin() << endl;
		bh.deleteMin();
	}
}