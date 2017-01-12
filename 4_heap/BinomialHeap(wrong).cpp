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
	if(this == &rhs)	return;	//避免别名问题
	
	//更新结点总数 
	currentSize += rhs.currentSize;
	rhs.currentSize = 0;
	
	//如需扩容，则扩容
	if(currentSize > this->capacity()){
		int oldSize = forest.size();	//保留原先的size 
		int newSize = max(forest.size(), rhs.forest.size()) + 1;	//容量扩充为两个forest的size最大值+1 
		forest.resize(newSize);	//resize 
		while(oldSize < newSize){	//对于此forest，把新扩充的部分全变成nullptr 
			forest[oldSize++] = nullptr;
		}
	} 
	
	//合并算法	引入新的carry指针暂存新合并的树
	TreeNode* carry = nullptr;	//必须赋值为nullptr，因为后边需要判断。如果不赋值会有!=nullptr的后果？？没试过 
	//漂亮！因为如果2^n正好等于currentSize时，即currentSize正好是2^n时，就会发生最后一次两个forest合并完的carry无法存到this->forest.
	//使用如下的手段，以新增一个变量为代价，换来代码的整洁！不用在循环外边额外判断了！
	for(int i = 0, j = 1; j <= currentSize; ++i, j *= 2){
		TreeNode* t1 = this->forest[i];	//先取出指针保存下来！保存下来就可以对forest任意修改了！！ 
		TreeNode* t2 = i < rhs.forest.size() ? rhs.forest[i] : nullptr;	//因为使用this->currentSize作为变量，不确定rhs是否会溢出！漂亮！
		
		//下边的算法类似Linux chmod chown的手法！以2^1 2^2 2^3等不重复的式子任意相加，得数会全不重复为前提！！
		int whichCase =    	t1==nullptr ? 0 : 1;
		whichCase    +=    	t2==nullptr ? 0 : 2;
		whichCase    +=  carry==nullptr ? 0 : 4; 
		
		switch(whichCase){
			case 0:	//无树
			case 1: //只有this
				break;
			case 2: //只有rhs
				this->forest[i] = t2;
				rhs.forest[i] = nullptr;
				break;
			case 3: //有this和rhs 即保存到carry中
				carry = combineTrees(t1, t2);
				this->forest[i] = rhs.forest[i] = nullptr;
				break;
			case 4:	//只有carry
				this->forest[i] = carry;
				carry = nullptr;
				break;
			case 5:	//有this和carry 
			 	carry = combineTrees(t1, carry);
			 	this->forest[i] = nullptr;
			 	break;
			case 6:	//有rhs和carry
				carry = combineTrees(t2, carry);
				rhs.forest[i] = nullptr;
				break; 
			case 7: //有this和rhs和carry 
				this->forest[i] = carry;	//carry放到this中
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
		if(forest[i] != nullptr && comp(forest[i]->data, forest[min]->data))	min = i; 	//勿忘判断nullptr。 
	}
	return min;
}

template <typename T, typename Comp>
void BinomialHeap<T, Comp>::insert(T const & x){
	BinomialHeap b(x);
	merge(b);	//不能直接在里边建立对象。因为merge参数是&类型。右值是不可以取引用的。 
}

template <typename T, typename Comp>
T BinomialHeap<T, Comp>::getMin(){
	return forest[findMinIndex()]->data;
}

template <typename T, typename Comp>
void BinomialHeap<T, Comp>::deleteMin(){
	if(isEmpty())	return;
	int minIndex = findMinIndex();
	
	//删除根节点，并且保存根下所有元素。 
	TreeNode* oldTree = forest[minIndex];
	TreeNode* remainTree = oldTree->leftChild;
	delete oldTree; 
	
	//构建H''
	BinomialHeap remainForest;
	remainForest.forest.resize(minIndex + 1);	//数量是下标+1别忘了 从0开始!
	remainForest.currentSize = (1 << minIndex) - 1;
	for(int j = minIndex - 1; j >= 0; --j){
		remainForest.forest[j] = remainTree;	//左儿子所有都保存 
		remainTree = remainTree->nextSibling;	//下一次拿右兄弟划分。 
		remainForest.forest[j]->nextSibling = nullptr;	//切断右兄弟。以后迭代地保留所有的左儿子。  
	} 
	
	//构建H' 
	forest[minIndex] = nullptr;
	currentSize -= remainForest.currentSize + 1;	//有必要先多减去所有的分离出去的remainTree的currentSize。因为merge之后还会加回来。。。 
	
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