
#include <iostream>
#include <math.h>

using namespace std;

const int SIZE = 8;
const int MAXSIZE = 16;

void translate(int a, int *A);
int retranslate(int *C);
void processor(int **first, int **second, int **result, int n);
void shift(int *A);
void sum(int *A, int *B);

int main()
{
	int i, pairs, j;
	cout << "Input number of pairs" << endl;
	cin >> pairs;
	int *first = new int[pairs];
	int *second = new int[pairs];

	cout << "Enter first vector" << endl;
	for (i = 0; i < pairs; i++) {
		cin >> first[i];
	}

	cout << "Enter second vector" << endl;
	for (i = 0; i < pairs; i++) {
		cin >> second[i];
	}

	int **A = new int*[pairs];
	for (i = 0; i < pairs; i++) {
		A[i] = new int[SIZE];
	}
	int **B = new int*[pairs];
	for (i = 0; i < pairs; i++) {
		B[i] = new int[SIZE];
	}
	int **C = new int*[pairs];
	for (i = 0; i < pairs; i++) {
		C[i] = new int[MAXSIZE];
	}

	for (i = 0; i < pairs; i++) {
		translate(first[i], A[i]);
		translate(second[i], B[i]);
	}
	for (i = 0; i < pairs; i++)
		for (j = 0; j < MAXSIZE; j++)
			C[i][j] = 0;


	cout << "Vector A:" << endl;
	for (i = 0; i < pairs; i++) {
		cout << i+1 << ":  ";
		if (i + 1 < 10) cout << " ";
		for (j = 0; j < SIZE; j++)
			cout << A[i][j];
		cout << endl;
	}
	cout << "Vector B:" << endl;
	for (i = 0; i < pairs; i++) {
		cout << i+1 << ":  ";
		if (i + 1 < 10) cout << " ";
		for (j = 0; j < SIZE; j++)
			cout << B[i][j];
		cout << endl;
	}

	cout << endl << "Tacts:      ";
	for (i = 0; i < SIZE; i++) {
		cout << "STEP " << i+1 << "              ";
		if (i < 10) cout << " ";
	}
	cout << endl;
	cout << "___________|";
	for (i = 0; i < SIZE-1; i++) cout << "____________________|";
	cout << "_________________";
	processor(A, B, C, pairs);
	cout << endl;
	cout << "RESULT:" << endl;
	for (i = 0; i < pairs; i++) {
		cout << i + 1 << ":  ";
		if (i + 1 < 10) cout << " ";
		for (j = 0; j < MAXSIZE; j++)
			cout << C[i][j];
		cout <<"("<<retranslate(C[i])<<")"<< endl;
	}

	for (i = 0; i < pairs; i++) {
		delete[]A[i];
	}

	for (i = 0; i < pairs; i++) {
		delete[]B[i];
	}

	for (i = 0; i < pairs; i++) {
		delete[]C[i];
	}

	delete []A;
	delete []B;
	delete []C;
	delete []first;
	delete []second;
	system("pause");

	return 0;
}

void processor(int **First, int **Second, int **Res, int kol)
{
	int i = 0, j = 0, work = 1, end = 0, ti=0, k=0;
	while (end<kol) {
		j++;
		ti++;
		cout << endl;
        cout << "TACT " << ti << ":    ";
		if (ti < 10) cout<<" ";
		for (i = 0; i < ti - kol; i++) cout << "                     ";
			for (i = 0 + end; i < work; i++) {
				if (Second[i][j - 1 - i + end] == 1) sum(First[i], Res[i]);
				if (j != 8 || i - end  != 0) shift(Res[i]);	
			}

		for (i = work - 1; i >= end; i--) {
			if (i != work - 1) cout << " ";
			for (k = 0; k < MAXSIZE; k++) cout << Res[i][k];
			cout << "    ";
		}

		cout << endl;
		cout << "___________|";
		for (i = 0; i < SIZE - 1; i++) cout << "____________________|";
		cout << "_________________";

		if (j == 8) {
			j--;
			end++;
		}
		if (work < kol) work++;
	}
}


void translate(int a, int *A) {
	int i;
	i = SIZE - 1;
	while (i >= 0) {
		if (a == 0) A[i] = 0;
		else {
			A[i] = a % 2;
			a = a / 2;
		}
		i--;
	}
}


void sum(int *A, int *C) {
	int i = 0;

	for (i = SIZE - 1; i >= 0; i--) {
		C[SIZE + i] = A[i] + C[SIZE + i];
	}


	for (i = MAXSIZE - 1; i>0; i--) {
		if (C[i] == 3) {
			C[i - 1] = C[i - 1] + 1;
			C[i] = 1;
		}
		if (C[i] == 2) {
			C[i - 1] = C[i - 1] + 1;
			C[i] = 0;
		}
	}
}

void shift(int *C)
{
	int i;
	for (i = 1; i<MAXSIZE; i++) {
		C[i - 1] = C[i];
	}
	C[MAXSIZE-1] = 0;


}

int retranslate(int *C)
{
	int i, a=0;
	for (i = 0; i < MAXSIZE; i++) {
		a += C[i] * pow(2, MAXSIZE-1-i);
	}
	return a;
}
