
#include <iostream>
#include <omp.h>
using namespace std;

// Bubble Sort Function
void bubbleSort(int arr[], int n) {
    #pragma omp parallel for
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Merge Function
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort Function
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, l, m);

            #pragma omp section
            mergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

// Print Array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Main Function with Switch Case
int main() {
    int n, choice;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];

    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "\nChoose Sorting Algorithm:" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Merge Sort" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            bubbleSort(arr, n);
            cout << "\nSorted Array using Bubble Sort:\n";
            printArray(arr, n);
            break;

        case 2:
            mergeSort(arr, 0, n - 1);
            cout << "\nSorted Array using Merge Sort:\n";
            printArray(arr, n);
            break;

        default:
            cout << "Invalid Choice!" << endl;
    }

    return 0;
}
