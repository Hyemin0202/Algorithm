#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <thread>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int d_value;
string t;
bool b = false;

int hamming(string s1, string s2) {
	int i = 0, count = 0;
	while (i != s1.length()) {
		if (s1.at(i) != s2.at(i))
			count++;
		i++;
	}
	return count;
}//s1�� s2�� hamming distance�� ����ϴ� �Լ�


string random_string(int len, vector <char> v_c) {
	srand(time(0));
	int k = v_c.size();
	string s;
	for (int i = 0; i < len; i++) {
		char ch = v_c[rand() % k];
		s += ch;
	}
	return s;
}//input.txt�� ����鿡�� ���� ���� �����鸸�� �̿��� random�ϰ� �迭�� string�� ����� �Լ�



void thirty_timer() {
	Sleep(1800000);
	b = true;
	//30�е��� sleep �ߴٰ� 30���� �����ٸ� ��Ÿ���� bool b�� true�� �ٲ��ش�.
}

void main() {
	thread t1(thirty_timer);//30�� ������ Ÿ�̸� ����

	ifstream f;
	f.open("input.txt", std::ios::in);//���� ����

	ofstream f_out;//�������
	vector <string> v;
	string s;
	vector<char> v_c;//input ���忡 ���� ���������� �����ϴ� ����

	if (f.is_open()) {
		f >> s;
		while (!f.eof() && b==false) {//���� �Է¹ޱ�
			//30�� ���϶��� �����Է��� ����ϵ��� �Ѵ�. 
			if (f.eof()) {
				break;//�ߺ� üũ
			}
			v.push_back(s);//�Է������� string�� ���Ϳ� ����
			for (int i = 0; i < s.length(); i++) {
				char ch = s[i];
				if (find(v_c.begin(), v_c.end(), ch) == v_c.end()) {
					v_c.push_back(ch);
				}
			}//input.txt�� ����鿡�� ���� ���� �������� ����v_c�� ����

			f >> s;//���� string �б�
			if (b == true) {
				//�����б� ���� 30���� ������ ���μ��� ����
				t1.join();
				return;
			}
		}
	}

	int len = s.length();//������ ����
	int j = 0;
	int bound = 0;
	t = random_string(len,v_c);//���� �ٿ�� ���� string

	vector<string>t_v;//���� ������ �ߺ��Ǵ��� Ȯ���ϱ� ���� ����
	t_v.push_back(t);//������ ���� ���� ����
	
	while (j < v.size()&& b==false) {
		if (j != 0) {
			
			int tmp = hamming(t, v[j]);
			if (tmp > bound)
				bound = tmp;//������� ���� hamming distance���� ū ���� ������ bound�� ��ü�Ѵ�.
			if (b == true) {//bound�� ���ϴ� �������� 30���� ������ ����
				t1.join();
				return;
			}
		}
		j++;
	}//���� bound 

	d_value = bound;//������ d_value

	f_out.open("output.txt");
	f_out << "string t : " << t << std::endl;//������ string�� �켱 output���Ͽ� �Է�
	f_out << "d_value : " << d_value << std::endl;//������ d_value�� �켱 output���Ͽ� �Է�

	int i = 1;
	
	while (b==false)
	{
		string s = random_string(len, v_c);
		
		if (find(t_v.begin(), t_v.end(), s) != t_v.end()) {//���� ���ع���� �ߺ��Ǹ�
			string s = random_string(len, v_c);
			while (find(t_v.begin(), t_v.end(), s) != t_v.end()) {
				// ���� ���ع���� �ߺ����� �ʵ��� random �迭 �ݺ�
				s = random_string(len, v_c);
				if (b == true) {//�����迭�ϴ� �������� 30���� ������ ����
					t1.join();//������ 93^len�� ����� ������ �ߺ��� �����ؼ� ������� ����ٰ� �����ȴ�.
					return;
				}
			}
		}

		t_v.push_back(s);//���ع��� ���� ����

		int j = 0;
		int bound=0;//bound �ʱ�ȭ

		while (j < v.size()&& b==false) {
			int tmp = hamming(s, v[j]);
			
			if (tmp > d_value) {
				break;
			}//������ optimal distance���� ū distance�� ���Ǹ� ���̻� distance ��� X
			//worst case���� ���̻� branch�� ���� �ʴ´�.
			if (tmp > bound)
				bound = tmp;//�ֱ��� �ִ� hamming distance���� ū ������ ���Ǹ� bound�� �����Ѵ�.
			j++;//���� string���� �Ѿ��
		}

		if (d_value > bound) {//string�� �ϳ� ������� �� �� optimal�� bound�� ���´ٸ� d_value�� �̶��� bound�� �ٲ��ش�.
			d_value = bound;
			t = s;
			f_out.open("output.txt");
			f_out << "string t : " << t << endl;//optimal solution�� ���ŵǾ����Ƿ� ��������� ���뵵 �ٲ��ش�.
			//30�� �� �ּ��� ����� ��µǾ���ϹǷ� optimal�� ���ŵ� ������ �ٽ� ����ϴ� ������ ����
			f_out << "d_value : " << d_value << endl;
		}

		if (b == true) {//loop ������ 30���� ������ �ڵ� ����
			t1.join();
			return;
		}
	}

	if (b == true) {//30�� ������ �ڵ� ����
		t1.join();
		return;
	}

}

