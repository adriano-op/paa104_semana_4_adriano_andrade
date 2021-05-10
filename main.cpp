#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <random>
#include<stdio.h>

using namespace std;

class node {
public:
    char elemnto;
    node *left;
    node *right;
};
/*
  A busca começa examinando o nó raiz. Se a árvore está vazia, o valor procurado não pode existir na árvore.
  Caso contrário, se o valor é igual a raiz, a busca foi bem sucedida.
  Se o valor é menor do que a raiz, a busca segue pela subárvore esquerda, se não, pela direita.

  Esse processo é repetido até o valor ser encontrado ou a subárvore ser nula (vazia).
  Se o valor não for encontrado até a busca chegar na subárvore nula, então o valor não deve estar presente na árvore.
 */
//caso médio: O(log n)	 pior caso: O(n).

node *busca(node *t, char x) {
    if (t == NULL)
        return NULL;
    else if (x < t->elemnto)
        return busca(t->left, x);
    else if (x > t->elemnto)
        return busca(t->right, x);
    else
        return t;

}

// No percurso da pré-ordem, a raiz é visitada antes que as subárvores esquerda e direita sejam visitadas (nessa ordem).
void preorder(node *node) {
    if (node == NULL)
        return;
    cout << node->elemnto << " ";
    preorder(node->left);
    preorder(node->right);
}

/* Na travessia pós-ordem, a raiz é visitada depois de visitar as subárvores esquerda e direita (nessa ordem) */
void postorder(node *node) {
    if (node == NULL)
        return;
    postorder(node->left);
    postorder(node->right);
    cout << node->elemnto << " ";
}


//No caso de travessia em ordem, a raiz de cada subárvore é visitada depois que sua subárvore esquerda foi percorrida,
// mas antes que a travessia de sua subárvore direita comece.
// As etapas para percorrer uma árvore binária na travessia inorder são:
// 1- Visite a subárvore esquerda, usando inorder.
// 2- visitar a raiz
// 3- Visite a subárvore certa, usando inorder.
void inorder(node *root) {
    if (root == NULL)
        return;
    else {
        inorder(root->left);
        cout << root->elemnto << " ";
        inorder(root->right);
    }
}

/* Um nó de árvore binária possui dados, ponteiro para filho esquerdo
e um ponteiro para a criança direita */
struct Node {
    int data;
    struct Node *left, *right;

    Node(int data) {
        this->data = data;
        left = right = NULL;
    }
};



//Inserção		caso médio: O(log n)	 pior caso: O(n)
// A função recebe uma árvore de busca r
// e uma folha avulsa novo e insere a folha
// na árvore de modo que a árvore continue
// sendo de busca. A função devolve a raiz
// da árvore resultante.

node *insert(char elemento, node *t) {
    if (t == NULL) // se a arvore é vazia
    {
        t = new node; // cria um nó e insere. se não
        t->elemnto = elemento;
        t->left = t->right = NULL;
    } else if (elemento < t->elemnto) // faz as comparações
        t->left = insert(elemento, t->left);
    else if (elemento > t->elemnto)
        t->right = insert(elemento, t->right);
    return t;
}

//calcula a altura da arvore
int height(node *node) {
    if (node == NULL)
        return -1;
    else
        return max(height(node->left), height(node->right)) + 1;
}


/* Esta função pega o último elemento como pivô, coloca
    o elemento pivô em sua posição correta na classificação
     array, e coloca todos menores (menores que pivô)
    à esquerda do pivô e todos os elementos maiores à direita
    de pivô
    https://www.geeksforgeeks.org/quick-sort/*/
template<class T>
int partition(std::vector<T> &arr, int low, int high) {
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot) {
            i++;    // increment index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
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
void quickSort(std::vector<T> &arr, int low, int high) {
    if (low < high) {
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
std::vector<T> posicaoMaioreMenorElemento(std::vector<T> &arr, int l, int r) {
    T max;
    T min;
    if (l == r) {
        max = arr[l];
        min = arr[l];
    } else if (l + 1 == r) {
        if (arr[l] < arr[r]) {
            max = arr[r];
            min = arr[l];
        } else {
            max = arr[l];
            min = arr[r];
        }
    } else {
        int m = (l + r) / 2;
        std::vector<T> left = posicaoMaioreMenorElemento(arr, l, m);
        std::vector<T> right = posicaoMaioreMenorElemento(arr, m + 1, r);
        if (left[0] > right[0])
            max = left[0];
        else
            max = right[0];
        if (left[1] < right[1])
            min = left[1];
        else
            min = right[1];
    }
    std::vector<int> ans = {max, min};
    return ans;
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
//
//    int minval, maxval = 0;
//    std::vector<int> arr = {97, 494, 564, 909, 542, 124, 8, 605, 540, 884};
//    printVector(arr);
//    posicaoMaioreMenorElemento(arr, 0, arr.size()-1, &minval, &maxval);//Note that the address is passed here because the outside value needs to be changed through the function
//
//    cout << "  Max: " <<  maxval << "  Min: " << minval ;

//https://www.programmersought.com/article/59775787376/
//    int n = 10;
//    std::vector<int> arr = {97, 494, 564, 909, 542, 124, 8, 605, 540, 884};
//    printVector(arr);
//    std::vector<int> ar =  posicaoMaioreMenorElemento(arr, 0, arr.size()-1);//Note that the address is passed here because the outside value needs to be changed through the function
//
//
//    int p_max;
//    int p_min;
//    for (int i=0; i < arr.size(); i++){
//        if(arr[i]==ar[0]){
//            p_max=i;
//        }
//        if(arr[i]== ar[1]){
//            p_min=i;
//
//        }
//    }
//    cout << "Max: " <<  ar[0] ;
//    cout << " Elem max : " << p_max << endl;
//
//    cout << "Min: " << ar[1]  ;
//    cout << " Elem min : " << p_min << endl;
    //666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666
    //----------------------------------------------- quickSort  -------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------


//    int n = 20;
//    cout << "Tamanho do Vetor: " << n << endl;
//    std::vector<int> arr = inicializaVectorRandom(n); // O(n)
//
//    cout << "O array: \n";
//    printVector(arr);
//
//
//    quickSort(arr, 0, arr.size() - 1);
//
//    cout << "Array ordenado: \n";
//    printVector(arr);

    //999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
    //----------------------------------------------------  BST  -------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------
//    node *root = NULL;
//    cout << "Inserção: " << endl;
//
//    root = insert(6, root);
//    cout << 6 <<  " ";
//    insert(3, root);
//    cout <<  3 <<  " ";
//    insert(30, root);
//    cout << 30 <<  " ";
//    insert(7, root);
//    cout << 7 <<  " ";
//    insert(1, root);
//    cout << 1  <<  " ";
//    insert(5, root);
//    cout << 5 <<  " ";
//    insert(2, root);
//    cout << 2 <<  " ";
//    insert(20, root);
//    cout << 20 <<  " ";
//    insert(40, root);
//    cout <<  40 <<  " ";
//    insert(70, root);
//    cout << 70 <<  " ";
//    insert(60, root);
//    cout <<  60 <<  " ";
//    insert(80, root);
//    cout << 80 <<  endl;

//    cout << "Árvore " << endl;
//    inorder(root);
//    cout << endl;
//
//    cout << "Busca: " ;
//    root = busca(root, 30);
//    cout << root->elemnto;

    //10-----------------------------------------------------------------10---------------------------------------------
    //----------------------------------------------------  BST - height------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------
//    node *root = NULL;
//    cout << "Inserção: " << endl;
//
//    root = insert(6, root);
//    cout << 6 <<  " ";
//    insert(3, root);
//    cout <<  3 <<  " ";
//    insert(30, root);
//    cout << 30 <<  " ";
//    insert(7, root);
//    cout << 7 <<  " ";
//    insert(1, root);
//    cout << 1  <<  " ";
//    insert(5, root);
//    cout << 5 <<  " ";
//    insert(2, root);
//    cout << 2 <<  " ";
//    insert(20, root);
//    cout << 20 <<  " ";
//    insert(40, root);
//    cout <<  40 <<  " ";
//    insert(70, root);
//    cout << 70 <<  " ";
//    insert(60, root);
//    cout <<  60 <<  " ";
//    insert(80, root);
//    cout << 80 <<  endl;

//    cout << "Árvore " << endl;
//    inorder(root);
//    cout << endl;

//    cout << "Busca: " ;
//    root = busca(root, 30);
//    cout << root->elemnto;

    //   cout << endl << "Altura da árvore :" << height(root) << endl;

    //12-----------------------------------------------------------------12---------------------------------------------
    //----------------------------------------------------  BST - Caminhos------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------
    node *root = NULL;
    cout << "Árvore " << endl;
//d, g, b, e, a, f, c
    root = insert('d', root);
    cout << 'd' << " ";
    insert('g', root);
    cout << 'g' << " ";
    insert('b', root);
    cout << 'b' << " ";
    insert('a', root);
    cout << 'a' << " ";
    insert('f', root);
    cout << 'f' << " ";
    insert('c', root);
    cout << 'c' << " ";
    insert('g', root);
    cout << 'g' << endl;


    cout << "inorder: ";
    inorder(root);//d, g, b, e, a, f, c

    cout << "\nPreorder: "; //a, b, d, g, e, c, f
    preorder(root);

    cout << "\nPostorder: ";
    postorder(root); //g, d, e, b, f, c, a

    cout << " Falta fazer o 11: ";


}
