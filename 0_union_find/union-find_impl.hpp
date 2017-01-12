#ifndef _UNION_FIND_IMPL_H_
#define _UNION_FIND_IMPL_H_

/***************���캯��*****************/ 
UnionFind::UnionFind(int num):root(num), size(num, 1){		//size ȫ����Ϊ1 
	for(size_t i = 0; i < num; i ++){ 						//root �±�Ϊ��ֵΪ�� 
		root[i] = i;
	}
}

/***************��Ҫ����*****************/ 
int UnionFind::find(int k){	//k����ţ�ͬʱҲ���±ꡣ 
	while(k != root[k]){	//ע�⣬����·��ѹ�����ֻ��һ�㣬���뻹��Ч��������������Ĺ涨��root[a]=a�Ļ�����a�Ǹ���������һ��Ľ������a�� 
		root[k] = root[root[k]];	//·��ѹ���������ƶ�һ�㡣
		k = root[k];				//��k��ֵΪ��ǰ�㣨��Ϊ�ƶ�������ֵ�� 
	}
	return k;
}

void UnionFind::Union(int m, int n){	//��С��������������ϣ� 
	int rootM = find(m);
	int rootN = find(n);
	//�������ͬ�������Ͳ���Ҫ���顣 
	if(rootM == rootN)	return; 
	if(size[rootM] > size[rootN]){
		root[rootN] = rootM;
		size[rootM] += size[rootN];
	} 
	else {	//����Ƚ�С���ߵ��ڣ���Ĭ�Ͻӵ��ұߵ������ˡ� 
		root[rootM] = rootN;
		size[rootN] += size[rootM];
	}
}

bool UnionFind::connected(int m, int n){
	return find(m) == find(n);
}

/***************��������*****************/ 
void UnionFind::print(){
	cout << "��ţ�" << endl;
	for(int i = 0; i < root.size(); i ++){
		cout << i << " ";
	}
	cout << endl << "���ף�" << endl;
	for(int i = 0; i < root.size(); i ++){
		cout << root[i] << " ";
	}
	cout << endl << "��С��" << endl;
	for(int i = 0; i < root.size(); i ++){
		cout << size[i] << " ";
	}
	cout << endl;
}

#endif
