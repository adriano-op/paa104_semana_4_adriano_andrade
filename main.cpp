#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <random>
#include<stdio.h>

using namespace std;

//utilizada para int
class node {
public:
    int elemnto;
    node *left;
    node *right;
};

// utilizada para strings
class Tree {
public:
    string elemnto;
    Tree *left;
    Tree *right;
};
/*
  A busca começa examinando o nó raiz. Se a árvore está vazia, o valor procurado não pode existir na árvore.
  Caso contrário, se o valor é igual a raiz, a busca foi bem sucedida.
  Se o valor é menor do que a raiz, a busca segue pela subárvore esquerda, se não, pela direita.

  Esse processo é repetido até o valor ser encontrado ou a subárvore ser nula (vazia).
  Se o valor não for encontrado até a busca chegar na subárvore nula, então o valor não deve estar presente na árvore.
 */
//caso médio: O(log n)	 pior caso: O(n).

node *busca(node *t, int x) {
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
void preorder(Tree *node) {
    if (node == NULL)
        return;
    cout << node->elemnto << " ";
    preorder(node->left);
    preorder(node->right);
}

/* Na travessia pós-ordem, a raiz é visitada depois de visitar as subárvores esquerda e direita (nessa ordem) */
void postorder(Tree *node) {
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
void inorder(Tree *root) {
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
//struct Node {
//    int data;
//    struct Node *left, *right;
//
//    Node(int data) {
//        this->data = data;
//        left = right = NULL;
//    }
//};



//Inserção		caso médio: O(log n)	 pior caso: O(n)
// A função recebe uma árvore de busca r
// e uma folha avulsa novo e insere a folha
// na árvore de modo que a árvore continue
// sendo de busca. A função devolve a raiz
// da árvore resultante.

node *insert(int elemento, node *t) {
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

Tree *insertString(string elemento, Tree *t) {
    if (t == NULL) // se a arvore é vazia
    {
        t = new Tree; // cria um nó e insere. se não
        t->elemnto = elemento;
        t->left = t->right = NULL;
    } else if (elemento < t->elemnto) // faz as comparações
        t->left = insertString(elemento, t->left);
    else if (elemento > t->elemnto)
        t->right = insertString(elemento, t->right);
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


//void printArray(int A[][n], int n) {
//    printf("\nMatriz gerada\n");
//    for(int i=0;i<n;i++)
//    {
//        for(int j=0;j<n;j++)
//        {
//            printf("%d\t", A[i][j]);
//        }
//    }
//}

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

const int N = 2;


double insert() {
    unsigned seed = time(0);
    srand(seed);
    double x[N][N];
    double val;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            val = 1 + rand() % 100;
            x[i][j] = val;
        }
    }
    cout << "\nMatriz gerada\n";
    for (int linha = 0; linha < N; linha++) {
        for (int coluna = 0; coluna < N; coluna++) {
            cout << x[linha][coluna] << " ";
        }
        cout << "\n";
    }
}

double m1(double a[N][N], double b[N][N]) {
    double o = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
//    cout << o << " ";
    return o;
}

double m2(double a[N][N], double b[N][N]) {
    double o = ((a[1][0] + a[1][1]) * b[0][0]);
    //  cout << o << " ";
    return o;

}

double m3(double a[N][N], double b[N][N]) {
    double o = (a[0][0] * (b[0][1] - b[1][1]));
//    cout << o << " ";
    return o;
}

int m4(double a[N][N], double b[N][N]) {
    double o = (a[1][1] * (b[1][0] - b[0][0]));
    //  cout << o << " ";
    return o;
}

double m5(double a[N][N], double b[N][N]) {
    double o = ((a[0][0] + a[0][1]) * b[1][1]);
    //   cout << o << " ";
    return o;
}

double m6(double a[N][N], double b[N][N]) {
    double o = ((a[1][0] - a[0][0]) * (b[0][0] + b[0][1]));
    //  cout << o << " ";
    return o;
}

double m7(double a[N][N], double b[N][N]) {
    double o = ((a[0][1] - a[1][1]) * (b[1][0] + b[1][1]));
    //  cout << o << " ";
    return o;
}


void printmatriz(vector<vector<int>> &permutacao) {
    for (std::vector<int> p: permutacao) {
        for (int el: p) {
            std::cout << el << endl;
        }

    }
}

void strassen() {
    double a00, a10, a11, a01, a[N][N], b[N][N];
    cout << "Exibindo o conteúdo da matriz declarada e inicializada:" << endl;
    cout << "Matriz A: ";
    unsigned seed = time(0);
    srand(seed);


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = 1 + rand() % 100;;
        }
    }

    cout << "\n";
    for (int linha = 0; linha < N; linha++) {
        for (int coluna = 0; coluna < N; coluna++) {
            cout << a[linha][coluna] << " ";
        }
        cout << "\n";
    }

    cout << "\n Matriz B: ";
    seed = time(0);
    srand(seed);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            b[i][j] = 10 + rand() % 100;
        }
    }
    cout << " \n";
    for (int linha = 0; linha < N; linha++) {
        for (int coluna = 0; coluna < N; coluna++) {
            cout << b[linha][coluna] << " ";
        }
        cout << "\n";
    };


    a00 = m1(a, b) + m4(a, b) - m5(a, b) + m7(a, b);
    a10 = m2(a, b) + m4(a, b);
    a01 = m3(a, b) + m5(a, b);
    a11 = m1(a, b) + m3(a, b) - m2(a, b) + m6(a, b);
    cout << "\n";

    cout << "Matriz Final";
    cout << "\n" << a00 << " " << a01;
    cout << "\n" << a10 << " " << a11;
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
//    int v[]={6,2,3,4,5,6,7,8,30,1};
//    cout << "Inserção: " << endl;
//    for(int a :v){
//        root = insert(a, root);
//        cout << a <<  " ";
//    }
//    cout << endl;
//
//    cout << "Árvore inorder" << endl;
//    inorder( root);
//    cout << endl;
//
//    cout << "Busca: " ;
//    root = busca(root, 30);
//    cout << root->elemnto;

    //10-----------------------------------------------------------------10---------------------------------------------
    //----------------------------------------------------  BST - height------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------

   // Implemente um algoritmo recursivo que encontre o tamanho de uma  ́arvore bin ́aria.

//    node *root = NULL;
//    cout << "Inserção: " << endl;
//    int v[] = {6, 2, 3, 4, 5, 6, 7, 8, 30, 1};
//    cout << "Inserção: " << endl;
//    for (int a :v) {
//        root = insert(a, root);
//        cout << a << " ";
//    }
//    cout << endl;
//    cout << "Árvore inorder" << endl;
//
//    cout << endl << "Altura da árvore :" << height(root) << endl;


    //12-----------------------------------------------------------------12---------------------------------------------
    //----------------------------------------------------  BST - Caminhos------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------
    //Implemente os caminhamentospreorder,postordereinorderpara  ́arvores bin ́arias

//    Tree *root = NULL;
//    cout << "Inserção: " << endl;
//
//    string v[] = {"d", "g", "b", "e", "a", "f", "c"};
//    cout << "Inserção: " << endl;
//    for (string a : v) {
//        root = insertString(a, root);
//        cout << a << " ";
//    }
//    cout << endl;
//    cout << "Árvore " << endl;
//
//
//    cout << "Inorder: ";
//    inorder(root);//d, g, b, e, a, f, c
//
//    cout << "\nPreorder: "; //a, b, d, g, e, c, f
//    preorder(root);
//
//    cout << "\nPostorder: ";
//    postorder(root); //g, d, e, b, f, c, a

    //13-----------------------------------------------------------------13---------------------------------------------
    //----------------------------------------------------  Strassen ---------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------

       strassen();
}
