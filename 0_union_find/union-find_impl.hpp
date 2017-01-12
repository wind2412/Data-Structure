#ifndef _UNION_FIND_IMPL_H_
#define _UNION_FIND_IMPL_H_

/***************构造函数*****************/ 
UnionFind::UnionFind(int num):root(num), size(num, 1){		//size 全部设为1 
	for(size_t i = 0; i < num; i ++){ 						//root 下标为几值为几 
		root[i] = i;
	}
}

/***************重要函数*****************/ 
int UnionFind::find(int k){	//k是序号，同时也是下标。 
	while(k != root[k]){	//注意，这里路径压缩如果只有一层，代码还有效，这是由于这里的规定：root[a]=a的话代表a是根。所以下一句的结果还是a。 
		root[k] = root[root[k]];	//路径压缩，向上移动一层。
		k = root[k];				//把k赋值为当前层（已为移动过）的值。 
	}
	return k;
}

void UnionFind::Union(int m, int n){	//把小的树并到大的树上！ 
	int rootM = find(m);
	int rootN = find(n);
	//如果根相同，根本就不需要并查。 
	if(rootM == rootN)	return; 
	if(size[rootM] > size[rootN]){
		root[rootN] = rootM;
		size[rootM] += size[rootN];
	} 
	else {	//如果比较小或者等于，就默认接到右边的树上了。 
		root[rootM] = rootN;
		size[rootN] += size[rootM];
	}
}

bool UnionFind::connected(int m, int n){
	return find(m) == find(n);
}

/***************其他函数*****************/ 
void UnionFind::print(){
	cout << "序号：" << endl;
	for(int i = 0; i < root.size(); i ++){
		cout << i << " ";
	}
	cout << endl << "父亲：" << endl;
	for(int i = 0; i < root.size(); i ++){
		cout << root[i] << " ";
	}
	cout << endl << "大小：" << endl;
	for(int i = 0; i < root.size(); i ++){
		cout << size[i] << " ";
	}
	cout << endl;
}

#endif
