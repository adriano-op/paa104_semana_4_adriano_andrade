#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <random>

using namespace std;

/* C implementation QuickSort */
#include<stdio.h>

// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* Esta função pega o último elemento como pivô, coloca
    o elemento pivô em sua posição correta na classificação
     array, e coloca todos menores (menores que pivô)
    à esquerda do pivô e todos os elementos maiores à direita
    de pivô */
template<class T>
int partition (std::vector<T> &arr, int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/*
 * quicksort ou ordenação por troca de partições
-ideia básica: dividir e conquistar.
-um elemento é escolhido como pivo.
-"particionar": os dados são rearranjados (valores menores do que o pivô são colocados antes dele e os maiores, depois).
-Recursivamente ordena as 2 partições.

"performance"
- melhor caso: O(n log n)
-Pior caso(raro): O(n²)
-Estável: não altera a ordem de dados iguais
-Desvantagens: como escolher o pivô?
*/
template<class T>
void quickSort(std::vector<T> &arr, int low, int high)
{
    if (low < high)
    {
        /* pi é o índice de particionamento, arr[p] agora é    no lugar certo */
        int pi = partition(arr, low, high);

        // Classifique os elementos separadamente antes
        // partição e depois da partição
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void printArray(int A[], int n) {
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << "\n";
}

template<class T>
int posicaoMaioreMenorElemento(std::vector<T> &arr, int begin, int end, int max, int min) {
    int max1  , min1 ;
    if (begin == end) {
        min = arr[begin];
        max = arr[begin];
        max1 =arr[begin];
        min1 =arr[begin];
    }
    else if( (begin == end - 1)) {
        if(arr[begin] < arr[end] ){
            max=arr[end];
            min=arr[begin];
        } else{
            max=arr[begin];
            min=arr[end];
        }
    } else{
        int m= (begin + end)/2;
        posicaoMaioreMenorElemento(arr,begin,m, max1,min1);
        posicaoMaioreMenorElemento(arr,m+1,end, max,min);
        if(max1 < max){
            max=max1;
        }
        if(min1 > min){
            min=min1;
        }
        cout << "Max: " << max << " Min: " << min << endl;
    }

//    int max1, min1;
//    if (begin == end) {
//        min = arr[begin];
//        max = arr[begin];
//        max1 = arr[begin];
//        min1 = arr[begin];
//    } else if ((end - begin) == 1) {
//        if (arr[begin] <= arr[end]) {
//            min = arr[end];
//            max = arr[end];
//        } else {
//            min = arr[end];
//            max = arr[begin];
//        }
//    } else if ((end - begin) > 1) {
//        int m = (begin + end) / 2;
//        posicaoMaioreMenorElemento(arr, 0, m, max, min);
//        posicaoMaioreMenorElemento(arr, m + 1, end, max1, min1);
//        if (max1 > max) {
//            max = max1;
//        }
//        if (min1 < min) {
//            min = min1;
//        }
//        cout << "max: " << max << "   Min " << min << endl;
//    }
}

template<class T>
int posicaoMaiorElemento(std::vector<T> &arr, int begin, int end) {
    if (begin == end) {
        return begin;
    }
    int m = ((begin + end) / 2);

    int p1 = posicaoMaiorElemento(arr, begin, m);        //2T(n/2) -> divide em subproblemas
    int p2 = posicaoMaiorElemento(arr, m + 1, end); //2T(n/2)

    if (arr[p1] >= arr[p2]) {
//            cout << "arr[p1] " << arr[p1]  << endl;
        return p1;
    } else {
        //          cout << "arr[p2] " << arr[p2]  << endl;
        return p2;
    }

}


// Mescla dois subarrays de arr [].
// O primeiro subarray é arr [l..m]
// O segundo subarray é arr [m + 1..r]
template<class T>
void merge(std::vector<T> &arr, int l, int m, int r) {
    int x = m - l + 1; // primeira metade
    int y = r - m;     // segunda metade

    // Create temp arrays
    std::vector<T> B(x), C(y);

// Copiar dados para matrizes temporárias B [] e C []
    for (int i = 0; i < x; i++)
        B[i] = arr[l + i];
    for (int j = 0; j < y; j++)
        C[j] = arr[m + 1 + j];

    // Mesclar as matrizes temporárias de volta em arr [l..r]

    // Índice inicial do primeiro subarray
    int i = 0;

    // Índice inicial do segundo subarray
    int j = 0;

    // Índice inicial do subarray mesclado
    int k = l;

    while (i < x && j < y) {
        if (B[i] <= C[j]) {
            arr[k] = B[i];
            i++;
        } else {
            arr[k] = C[j];
            j++;
        }
        k++;
    }

// Copie os elementos restantes de  B[], se houver algum
    while (i < x) {
        arr[k] = B[i];
        i++;
        k++;
    }

    // Copie os elementos restantes de  C[], se houver algum
    while (j < y) {
        arr[k] = C[j];
        j++;
        k++;
    }
}

template<class T>
void mergeSort(std::vector<T> &arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int m = (l + r) / 2;

    mergeSort(arr, l, m);        //2T(n/2) -> divide em subproblemas
    mergeSort(arr, m + 1, r); //2T(n/2)
    merge(arr, l, m, r); // O(n) -> intercala os arrays
}


template<class T>
void printVector(std::vector<T> &v) {
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::cout << *i << " | ";
    }
    std::cout << endl;
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

//    int n = 20;
//    cout << "Tamanho do Vetor: " << n << endl;
//    std::vector<int> arr = inicializaVectorRandom(n); // O(n)
//
//    cout << "O array: \n";
//    printVector(arr);
//
//
//    mergeSort(arr, 0, arr.size() - 1);
//
//    cout << "Array ordenado: \n";
//    printVector(arr);

    ///22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222
    //----------------------------------------- MergeSort ----- String--------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------

//    std::vector<string> arr = {"E", "X", "A","M", "P", "L", "E"};//inicializaVectorRandom(n); // O(n)
//    cout << "Tamanho do Vetor: " <<arr.size() << endl;
//
//    cout << "O array: \n";
//    printVector(arr);
//    mergeSort(arr, 0, arr.size() - 1);
//
//    cout << "Array ordenado: \n";
//    printVector(arr);


    ///33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333
    //----------------------------------------- resposta no  pdf --------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------



    ///44444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444
    //----------------------------------------- posicaoMaiorElemento  --------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------

//    int n = 10;
//
//    std::vector<int> arr = inicializaVectorRandom(n); // O(n)
//
//    arr.push_back(984);
//    arr.push_back(984);
//    arr.push_back(984);
//
//    cout << "Tamanho do Vetor: " << arr.size() << endl;
//    cout << "O array: " << endl;
//
//    printVector(arr);
//
//
//    int p = posicaoMaiorElemento(arr, 0, arr.size() - 1);
//    cout << "arr[p1] " << arr[p] << " na posição: " << p << endl;


    ///55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555
    //----------------------------------------- posicaoMaioreMenorElemento  --------------------------------------------
    //------------------------------------------------------------------------------------------------------------------


//    int n = 10;
//
//    std::vector<int> arr = {97, 494, 564, 909, 542, 124, 8, 605, 540, 884};//inicializaVectorRandom(n); // O(n)
//
////    arr.push_back(984);
////    arr.push_back(984);
////    arr.push_back(984);
//
//    cout << "Tamanho do Vetor: " << arr.size() << endl;
//    cout << "O array: " << endl;
//
//    printVector(arr);
//
//
//    posicaoMaioreMenorElemento(arr, 0, arr.size() , 0, 0);


    //666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666
    //----------------------------------------------- quickSort  -------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------


    int n = 20;
    cout << "Tamanho do Vetor: " << n << endl;
    std::vector<int> arr = inicializaVectorRandom(n); // O(n)

    cout << "O array: \n";
    printVector(arr);


    quickSort(arr, 0, arr.size() - 1);

    cout << "Array ordenado: \n";
    printVector(arr);


    return 0;
}
