#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>

using namespace std;


// Mescla dois subarrays de arr [].
// O primeiro subarray é arr [l..m]
// O segundo subarray é arr [m + 1..r]
void merge(std::vector<int> &arr, int l, int m, int r) {
    int n1 = m - l + 1; // primeira metade
    int n2 = r - m;     // segunda metade

    // Create temp arrays
    std::vector<int> L(n1), R(n2);

// Copiar dados para matrizes temporárias L [] e R []
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        //moedaExtra.push_back(coins[i]);
        R[j] = arr[m + 1 + j];

    // Mesclar as matrizes temporárias de volta em arr [l..r]

    // Índice inicial do primeiro subarray
    int i = 0;

    // Índice inicial do segundo subarray
    int j = 0;

    // Índice inicial do subarray mesclado
    int k = l;

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

// Copie os elementos restantes de
    // L [], se houver algum
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int> &arr, int l, int r) {
    if (l > = r) {
        return;
    }
    int m = (l +r )/ 2;

    mergeSort(arr, l, m);        //2T(n/2)
    mergeSort(arr, m + 1, r); //2T(n/2)
    merge(arr, l, m, r); // O(n)
}


template<class T>
void printVector(std::vector<T> &v) {
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::cout << *i << " | ";
    }
    std::cout << endl;
}


void printArray(int A[], int size) {
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
}

std::vector<int> inicializaVector(int n) {
    std::vector<int> v;
    //  int tam = sizeof(v)/sizeof(int);
    for (int i = 1; i < n + 1; i++) {
        v.push_back(i);
    }
    printVector(v);
    return v;
}

std::vector<int> inicializaVectorRandom(int t) {
    unsigned seed = time(0);
    srand(seed);
    vector<int> nums;

    for (int i = 0; i < t; i++) {
        nums.push_back(1 + rand() % 1000);
    }
    return nums;
}


int main() {
    ///11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
    //----------------------------------------- MergeSort --------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------

    int n = 20;
    cout << "Tamanho do Vetor: " << n << endl;
    std::vector<int> arr = inicializaVectorRandom(n); // O(n)

    cout << "O array: \n";
    printVector(arr);


    mergeSort(arr, 0, arr.size() - 1);

    cout << "Array ordenado: \n";
    printVector(arr);
    return 0;
}
