#pragma once
#include <string>
using namespace std;

	struct skill
	{
		string name;	//��������
		int totaltime;		//�����ۼ�ʱ��
		string stringtotaltime;//������ӡʱ��

	};
	//������
	struct Node
	{
		skill val;
		Node* next;
		Node(skill x) :val(x), next(NULL) {
		}
	};

	class skilllist
	{
	public:

		//���캯��
		skilllist();
		//��ʼ��
		void init();
		//������
		void Insert(string name);
		//ɾ�����
		void Remove(string name);
		//�õ�������
		int Length();
		//���ҽ��λ��
		int Find(string name);
		//��ӡ����
		bool Print();
		//��ȡ�б�ĵڼ�������
		skill getskill(int);
		//��ȡ��ӡʱ��
		void getstringtime(skill& s);
		//���ü���ʱ��
		void settitaltime(skill s,int t);
		//��������
		~skilllist();
	private:
		Node* head;
		int length;
	};


