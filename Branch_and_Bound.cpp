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
}//s1과 s2의 hamming distance를 계산하는 함수


string random_string(int len, vector <char> v_c) {
	srand(time(0));
	int k = v_c.size();
	string s;
	for (int i = 0; i < len; i++) {
		char ch = v_c[rand() % k];
		s += ch;
	}
	return s;
}//input.txt의 문장들에서 사용된 문자 종류들만을 이용해 random하게 배열된 string을 만드는 함수



void thirty_timer() {
	Sleep(1800000);
	b = true;
	//30분동안 sleep 했다가 30분이 지났다를 나타내는 bool b를 true로 바꿔준다.
}

void main() {
	thread t1(thirty_timer);//30분 쓰레드 타이머 시작

	ifstream f;
	f.open("input.txt", std::ios::in);//파일 열기

	ofstream f_out;//출력파일
	vector <string> v;
	string s;
	vector<char> v_c;//input 문장에 쓰인 문자종류를 저장하는 벡터

	if (f.is_open()) {
		f >> s;
		while (!f.eof() && b==false) {//파일 입력받기
			//30분 내일때만 파일입력을 계속하도록 한다. 
			if (f.eof()) {
				break;//중복 체크
			}
			v.push_back(s);//입력파일의 string을 벡터에 저장
			for (int i = 0; i < s.length(); i++) {
				char ch = s[i];
				if (find(v_c.begin(), v_c.end(), ch) == v_c.end()) {
					v_c.push_back(ch);
				}
			}//input.txt의 문장들에서 사용된 문자 종류들을 벡터v_c에 저장

			f >> s;//다음 string 읽기
			if (b == true) {
				//파일읽기 도중 30분이 지나면 프로세스 종료
				t1.join();
				return;
			}
		}
	}

	int len = s.length();//문장의 길이
	int j = 0;
	int bound = 0;
	t = random_string(len,v_c);//최초 바운드 기준 string

	vector<string>t_v;//기준 문장이 중복되는지 확인하기 위한 벡터
	t_v.push_back(t);//이전의 기준 문장 저장
	
	while (j < v.size()&& b==false) {
		if (j != 0) {
			
			int tmp = hamming(t, v[j]);
			if (tmp > bound)
				bound = tmp;//현재까지 계산된 hamming distance보다 큰 값이 나오면 bound를 교체한다.
			if (b == true) {//bound를 구하는 과정에서 30분이 지나면 종료
				t1.join();
				return;
			}
		}
		j++;
	}//최초 bound 

	d_value = bound;//최초의 d_value

	f_out.open("output.txt");
	f_out << "string t : " << t << std::endl;//최초의 string을 우선 output파일에 입력
	f_out << "d_value : " << d_value << std::endl;//최초의 d_value을 우선 output파일에 입력

	int i = 1;
	
	while (b==false)
	{
		string s = random_string(len, v_c);
		
		if (find(t_v.begin(), t_v.end(), s) != t_v.end()) {//이전 기준문장과 중복되면
			string s = random_string(len, v_c);
			while (find(t_v.begin(), t_v.end(), s) != t_v.end()) {
				// 이전 기준문장과 중복되지 않도록 random 배열 반복
				s = random_string(len, v_c);
				if (b == true) {//랜덤배열하는 과정에서 30분이 지나면 종료
					t1.join();//하지만 93^len의 경우의 수에서 중복이 연속해서 나오기는 힘들다고 생각된다.
					return;
				}
			}
		}

		t_v.push_back(s);//기준문장 벡터 저장

		int j = 0;
		int bound=0;//bound 초기화

		while (j < v.size()&& b==false) {
			int tmp = hamming(s, v[j]);
			
			if (tmp > d_value) {
				break;
			}//현재의 optimal distance보다 큰 distance가 계산되면 더이상 distance 계산 X
			//worst case에는 더이상 branch를 뻗지 않는다.
			if (tmp > bound)
				bound = tmp;//최근의 최대 hamming distance보다 큰 값으로 계산되면 bound를 갱신한다.
			j++;//다음 string으로 넘어가기
		}

		if (d_value > bound) {//string을 하나 계산했을 때 더 optimal한 bound가 나온다면 d_value를 이때의 bound로 바꿔준다.
			d_value = bound;
			t = s;
			f_out.open("output.txt");
			f_out << "string t : " << t << endl;//optimal solution이 갱신되었으므로 출력파일의 내용도 바꿔준다.
			//30분 내 최선의 결과가 출력되어야하므로 optimal이 갱신될 때마다 다시 출력하는 것으로 설정
			f_out << "d_value : " << d_value << endl;
		}

		if (b == true) {//loop 내에서 30분이 지나면 코드 종료
			t1.join();
			return;
		}
	}

	if (b == true) {//30분 지나면 코드 종료
		t1.join();
		return;
	}

}

