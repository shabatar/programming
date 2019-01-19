#include <iostream>
using namespace std;

int int_search(int *A, int N, int X) {
	int left = 0;
	int right = N-1;
	int mid;
	while(A[left] < X && X < A[right]) {
		mid = left + (X - A[left]) * (right - left) / (A[right] - A[left]);
		if (A[mid] < X) left = mid + 1;
		else if (A[mid] > X)
			right = mid - 1;
		else return mid;
	}
	if (A[left] == X) return left;
	else if (A[right] == X) return right;
	else return -1;
}

int main() {
	int N;
	cout << "Enter number of elements in sorted array: ";
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
	cout << "Enter the number to search: ";
	int n;
	cin >> n;
	if (int_search(A,N,n) == -1) {
		cout << "Can't find your number." << endl;
		return 0;
	}
	cout << "The index of your number is " << int_search(A, N, n) + 1 << "." << endl;
	return 0;
}