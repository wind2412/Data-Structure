#ifndef _TOPOLOGICAL_SORT_
#define _TOPOLOGICAL_SORT_
#include "Graph.hpp"
#include <queue> 

/**
 * ��������   ʹ���ڽӱ�ĸ��Ӷȣ�O(|E|+|V|) �����ҵĳ�������Ϊ��reverse()����˻������㷨������̫�ᣬ��Ҫѧϰ�� 
 * 1.����һ������q��
 * 2.����һ�Σ��ҵ��������Ϊ0�ĵ㣬˳��������q��
 * 3.����һ��ֵ��ɾ��һ�����==0�ĵ㣩�������������ֵ�����й�������ٽ�ֵ������ÿ���ڽ�ֵ�������ǵ���������һ������indegree����-1��
 * 4.�����˰Ѹղ��Ǹ�����ֵ�����������˳����¶���sorted�С��������һ���ڽ�ֵ����ȱ����0���Ǿͼ���˳������queue��ȥ�� 
 * 5.�ظ�3��4.  ֱ��û���κ����Ϊ0��ֵ������С�����q.empty()����.
 * 6.���sorted�����sorted.size() == V�����������нڵ������Ǿ����������!=���Ǿ�˵��һ���л�����Ϊ�������ʼ��!=0 ���������Զ�޷�����q����
 * 7.������л�ͼ�����������޷����������������Ļ���ֱ�����쳣�� 
 */ 
class Topological{
public:
	Topological() = delete;
	static deque<int> sort(Graph & g){
		deque<int> q, sorted; //q�������Ϊ0�Ķ����±ꡣsorted�洢q.push_front()֮����������С� 
		int indegree[g.getV()];	//����б� //�������������Ǹ���һ��һ�ּ������ʵ�ֵġ� 
		Graph && rev = g.reverse();	//���򡣰�����[����]ȫ��ת��Ϊ[���]�� 
		for(int i = 0; i < g.getV(); i ++){
			indegree[i] = rev.getDegree(i);	//������ȵ�ֵ��	//ΪʲôҪ�������ٿռ�����ֵ������ֱ��get list.size()�أ���Ϊ�����޸����ֵ��ÿ��-1�� 
			cout << i << "'s indegree is " << indegree[i] << endl;
			if(indegree[i] == 0){
				q.push_back(i);	//�����0���Ͱѽ��push��q�У� 
			}
		}	
		while(!q.empty()){	//�������һȦ����������ȶ�>0�����������ǺǺ��ˡ���Դ�������ء���ֱ�Ӷ����л����� 
			int v = q.front();q.pop_front();
			sorted.push_back(v);	//����sorted�У��Ѿ����� 
//			list<Edge> l = g.getAdj(v);	// ���Բۣ����μ�Graph.hpp������const��list<Edge>�����list����const�ģ����û������Edgeȴ��const�ģ��� 
			for(const Edge & e : g.getAdj(v)){
				if(--indegree[e.to] == 0){	//����ڽ�ֵ����ȼ�Ϊ0���Ǿͼ���q��ע���Ǵ�indegree[]�м�ȥ��������ļ�������ȡ� 
					q.push_back(e.to);
				}
			}
		}
		if(sorted.size() != g.getV()){
			cerr << "there is a circle in the graph!! topological sort failed! " << endl;
			return deque<int>{};	//����һ��ɶҲû�е�queue 
		}
		return sorted;
	}
};

#endif

int main()
{
	Graph g(5);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(0, 1);
	g.addEdge(1, 6);
	g.addEdge(1, 3);
	g.addEdge(4, 1);
	cout << "1's out_degree: "<<g.getDegree(1) << endl;
	g.print();
	g.reverse().print();
	
	deque<int> && sorted = Topological::sort(g);	//ʧ�󡣡�Ӧ����deque������queue���Ǳ�׼STL�����ṩ���������������� 
	for(int & i : sorted){
		cout << i << " ";
	}
	cout << endl;
}
