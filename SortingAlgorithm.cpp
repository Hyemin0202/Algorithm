#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <sstream>

void Selection_sort(std::vector<std::string> &inputList);
void Bubble_sort(std::vector<std::string> &inputList);
void Insertion_sort(std::vector<std::string> &inputList);
void Merge_sort(std::vector<std::string> &inputList, int start, int end);
void Merge(std::vector<std::string> &inputList, int start, int mid, int end);
void Quick_sort(std::vector<std::string>& inputList, int start, int end);
void Merge_sort_sequential(std::vector<std::string>& inputList);
void Quick_sort_sequential(std::vector<std::string>& inputList, int start, int end);
void Heap_sort(std::vector<std::string>& inputList);

int min(int i, int j) {
	//최솟값 반환 함수
	if (i <= j)
		return i;
	else
		return j;
}

bool is_digit(std::string str) {
	//입력이 integer인지 string인지 판단
	return atoi(str.c_str()) != 0 || str.compare("0") == 0; 
}

int main() {
	
	std::vector<std::string> inputList;//데이터 입력받을 벡터

	std::ifstream file; //input.txt 
	file.open("input.txt", std::ios::in);//input.txt 오픈 & 읽기만 허용
	std::ofstream output_file;//output.txt
	output_file.open("output.txt");//output.txt 오픈 

	std::string str;
	if (file.is_open()) {
		//파일 오픈에 에러가 없다면
		file >> str;
		while (!file.eof()) {
			if (file.eof())
				break;// 중복 체크
			inputList.push_back(str);
			file >> str;
		}//공백으로 구분된 데이터이기 때문에 file >>str 사용 , push_back이용해 리스트에 append
	}

	else {
		std::cout << "File Open Error" << std::endl;
	}//파일오픈 에러가 있는 경우 에러메세지 반환

	if (inputList.empty()) {
		std::cerr << "inputList does not have data" << std::endl;
	}//inputList가 비어있는지 확인

	//어떤 알고리즘을 선택할지에 대한 안내문
	std::cout << "--------Choose Sorting Algorithm--------" << std::endl;
	std::cout << "1. Selection sort" << std::endl;
	std::cout << "2. Bubble sort" << std::endl;
	std::cout << "3. Insertion sort" << std::endl;
	std::cout << "4. Merge sort" << std::endl;
	std::cout << "5. Sequential Merge sort" << std::endl;
	std::cout << "6. Quick sort" << std::endl;
	std::cout << "7. Sequential Quick sort" << std::endl;
	std::cout << "8. Heap sort" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Number : ";

	int num;
	std::cin >> num;// 선택 알고리즘의 넘버
	clock_t start, end;//알고리즘의 runnung time을 정확히 알 수 있도록 colock_t 사용

	switch (num) {//number에 해당하는 알고리즘 작동
	case 1:
		start = clock();
		Selection_sort(inputList);//selection sorting
		end = clock();
		break;
	case 2:
		start = clock();
		Bubble_sort(inputList);//Bubble sorting
		end = clock();
		break;
	case 3:
		start = clock();
		Insertion_sort(inputList);//insertion sorting
		end = clock();
		break;
	case 4:
		start = clock();
		Merge_sort(inputList, 0, inputList.size() - 1);//merge sorting
		end = clock();
		break;
	case 5:
		start = clock();
		Merge_sort_sequential(inputList);//sequential merge sorting
		end = clock();
		break;
	case 6:
		start = clock();
		Quick_sort(inputList, 0, inputList.size() - 1);//quick sorting
		end = clock();
		break;
	case 7:
		start = clock();
		Quick_sort_sequential(inputList,0,inputList.size()-1);//sequential quick sorting
		end = clock();
		break;
	case 8:
		start = clock();
		Heap_sort(inputList);//heap sorting
		end = clock();		
		break;
	default:
		std::cerr << "Wrong Number" << std::endl;
		break;
	}

	for (int i = 0; i < inputList.size(); i++){
			output_file << inputList[i] << " ";//sorting 결과를 output.txt에 입력
	}

	std::cout << "Running time : " << (double)(end - start) << std::endl;//runningtime 출력

	file.close();
	output_file.close();
}

void Selection_sort(std::vector<std::string> &inputList) {
	int length = inputList.size()-1;

	if (is_digit(inputList[0]) == 1)//if input is integer
	{
		while (length > 0) {
			int max = 0;
			for (int j = 1; j <= length; j++) {
				if (atoi(inputList[j].c_str()) > atoi(inputList[max].c_str()))
					max = j;
			}
			inputList[length].swap(inputList[max]);
			length--;
		}
	
	}

	else {
		while (length > 0) {
			int max = 0;
			for (int j = 1; j <= length; j++) {
				if (inputList[j].compare(inputList[max]) >0)
					max = j;
			}
			inputList[length].swap(inputList[max]);
			length--;
		}
	}

}

void Bubble_sort(std::vector<std::string> &inputList) {
	int length = inputList.size() - 1;

	if (is_digit(inputList[0]) == 1) {
		for (int i = length; i > 0; i--)
			for (int j = 0; j < i; j++) {
				if (atoi(inputList[j].c_str()) > atoi(inputList[j + 1].c_str()))
					inputList[j].swap(inputList[j + 1]);
			}
	}

	else {
		for (int i = length; i > 0; i--)
			for (int j = 0; j < i; j++) {
				if (inputList[j] > inputList[j + 1])
					inputList[j].swap(inputList[j + 1]);
			}
	}

}

void Insertion_sort(std::vector<std::string> &inputList) {
	int length = inputList.size() ;
	
	if (is_digit(inputList[0]) == 1) {
		for (int j = 1; j < length; j++) {
			int key = atoi(inputList[j].c_str());
			int i = j - 1;
			while (i >= 0 && atoi(inputList[i].c_str()) > key) {
				inputList[i].swap(inputList[i + 1]);
				i--;
			}

			std::string tmp = std::to_string(key);//change int to string
			inputList[i + 1] = tmp;
		}
	}

	else {
		for (int j = 1; j < length; j++) {
			std::string key;
			key = inputList[j];
			int i = j - 1;

			while (i >= 0 && inputList[i] > key) {
				inputList[i].swap(inputList[i + 1]);
				i--;
			}

			inputList[i + 1] = key;
		}
	}
}

void Merge_sort(std::vector<std::string> &inputList, int start, int end) {
	if (start < end){
		int mid = (start+end) / 2;
		Merge_sort(inputList,start, mid);
		Merge_sort(inputList, mid+1, end);
		Merge(inputList, start, mid, end);
	}
}

void Merge(std::vector<std::string> &inputList, int start, int mid, int end) {
	int i = start;
	int j = mid + 1;
	
	std::vector<std::string> sortedList;

	if (is_digit(inputList[0]) == 1) {
		while (i <= mid && j <= end) {
			if (atoi(inputList[i].c_str()) <= atoi(inputList[j].c_str()))
				sortedList.push_back(inputList[i++]);

			else
				sortedList.push_back(inputList[j++]);
		}

		if (i > mid) {
			while (j <= end)
				sortedList.push_back(inputList[j++]);

		}
		else {
			while (i <= mid)
				sortedList.push_back(inputList[i++]);
		}

		int length = sortedList.size() - 1;//index for indicating last index of sortedList

		for (int k = end; k >= start; k--) {
			inputList[k] = sortedList[length--];//to use pop_back(), insert changed element from end to start
			sortedList.pop_back();//by using pop_back(), delete last element in vector
		}
	}

	else {
		while (i <= mid && j <= end) {
			if (inputList[i] <= inputList[j])
				sortedList.push_back(inputList[i++]);

			else
				sortedList.push_back(inputList[j++]);
		}

		if (i > mid) {
			while (j <= end)
				sortedList.push_back(inputList[j++]);

		}
		else {
			while (i <= mid)
				sortedList.push_back(inputList[i++]);
		}

		int length = sortedList.size() - 1;//index for indicating last index of sortedList

		for (int k = end; k >= start; k--) {
			inputList[k] = sortedList[length--];//to use pop_back(), insert changed element from end to start
			sortedList.pop_back();//by using pop_back(), delete last element in vector
		}
	}
}

int partition(std::vector<std::string> &inputList, int start, int end) {

	int i = start - 1;
	
	if (is_digit(inputList[0]) == 1) {
		int piv_int = atoi(inputList[end].c_str());

		for (int j = start; j < end; j++) {
			if (atoi(inputList[j].c_str()) <= piv_int) {
				i++;
				inputList[i].swap(inputList[j]);
			}
		}

		inputList[i + 1].swap(inputList[end]);
	}

	else {
		std::string piv_str = inputList[end];

		for (int j = start; j < end; j++) {
			if (inputList[j] <= piv_str) {
				i++;
				inputList[i].swap(inputList[j]);
			}
		}

		inputList[i + 1].swap(inputList[end]);
	}
	return i + 1;
}

void Quick_sort(std::vector<std::string> &inputList, int start, int end) {

	if (start < end){
		int piv = partition(inputList, start, end);
		Quick_sort(inputList, start, piv - 1);
		Quick_sort(inputList, piv + 1,end);
	}
}

void Merge_sort_sequential(std::vector<std::string>& inputList) {
	int size = inputList.size();

	for (int sub_size = 1; sub_size < size; sub_size = 2 * sub_size) {
		for (int start = 0; start < size - 1; start += 2 * sub_size) {
			int mid = min(start + sub_size - 1, size - 1);
			int end = min(start + 2 * sub_size - 1, size - 1);
			Merge(inputList, start, mid, end);
		}
	}

}

void Quick_sort_sequential(std::vector<std::string> &inputList, int start, int end) {
	
	if (start < end) {
		int* indexStack = new int[end - start + 1];
		int top = -1;
		indexStack[++top] = start;
		indexStack[++top] = end;

		while (top>=0) {
			int r = indexStack[top--];
			int l = indexStack[top--];

			int piv = partition(inputList, l, r);

			if (piv - 1 > l) {
				indexStack[++top] = l;
				indexStack[++top] = piv - 1;
			}

			if (piv + 1 < r) {
				indexStack[++top] = piv + 1;
				indexStack[++top] = r;
			}
		}

		delete[] indexStack;
	}
	
}

int left(int parent) {
	return 2 * parent;
}

int right(int parent) {
	return 2 * parent + 1;
}

void Max_Heapify(std::vector<std::string>& inputList, int i,int heap_size) {
	int l_child = left(i);
	int r_child = right(i);
	int largest;

	if (is_digit(inputList[0]) == 1) {
		if (l_child < heap_size && atoi(inputList[l_child].c_str()) > atoi(inputList[i].c_str()))
			largest = l_child;
		else
			largest = i;

		if (r_child < heap_size && atoi(inputList[r_child].c_str()) > atoi(inputList[largest].c_str()))
			largest = r_child;

		if (largest != i) {
			inputList[i].swap(inputList[largest]);
			Max_Heapify(inputList, largest, heap_size);
		}
	}
	else {
		if (l_child < heap_size && inputList[l_child] > inputList[i])
			largest = l_child;
		else
			largest = i;

		if (r_child < heap_size && inputList[r_child]>inputList[largest])
			largest = r_child;

		if (largest != i) {
			inputList[i].swap(inputList[largest]);
			Max_Heapify(inputList, largest, heap_size);
		}
	}
	
}

void Build_Max_Heap(std::vector<std::string>& inputList) {
	int length = inputList.size() - 1;
	int i = length / 2;
	int heap_size = inputList.size();
	for(i=length/2;i >= 0;i--){
		Max_Heapify(inputList, i,heap_size);
	}
}

void Heap_sort(std::vector<std::string>& inputList) {
	double total=0;

	Build_Max_Heap(inputList);

	int heap_size = inputList.size();
	for (int i = inputList.size() - 1; i > 0; i--) {
		inputList[0].swap(inputList[i]);
		heap_size--;
		Max_Heapify(inputList, 0, heap_size);
	}

}


















