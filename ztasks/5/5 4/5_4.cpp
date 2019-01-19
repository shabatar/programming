#include <iostream>
using namespace std;

void ShellSort(int *A, int N) 
{
	int tmp;
	int k, j, i;
	for(k = N/2; k>0; k/=2) 
		for (i = k; i < N; ++i) {
			tmp = A[i];
			for (j = i; j >= k; j = j-k) {
				if(tmp < A[j-k]) A[j] = A[j-k];
				else break;
			}
			A[j] = tmp;
		}
}


int main() {
	int N;
	cout << "Enter number of elements in array: ";
	cin >> N;
	int *A = new int[N];
	cout << "Enter elements one by one: " << endl;
	int i;
	for(i = 0; i < N; ++i) {
		cin >> A[i];
	}
	cout << "You've entered: ";
    for(i = 0; i < N; ++i) {
		cout << A[i] << " ";
	}
	cout << endl;
	ShellSort(A,N);
	cout << "Sorted array: ";
    for(i = 0; i < N; ++i) {
		cout << A[i] << " ";
	}
	cout << endl;
} 