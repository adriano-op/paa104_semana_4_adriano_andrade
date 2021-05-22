#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <random>
#include<stdio.h>
#include<math.h>
#include <bits/stdc++.h>

using namespace std;


struct Point {
    double x, y;
};

#define Ponto pair<int, int>
set<Ponto> casca;
int orientacao(Ponto p1, Ponto p2, Ponto p) {
    int res = (p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first);

    if (res == 0) { return 0; }
    else if (res > 0) { return 1; }
    else { return 2; }
}

// p1 e p2 são os pontos finais da linha
void qHull(pair<int, int> *a, int n, Ponto p1, Ponto p2, int lado) {
    int ind = -1;
    int max_dist = 0;

    // encontrar o ponto com distância máxima da linha.
    for (int i = 0; i < n; i++) {
        Ponto p = a[i];
        //distancia entre os dois pontos p1 e p2
        int dis = (p.second - p1.second) * (p2.first - p1.first) -
                  (p2.second - p1.second) * (p.first - p1.first);
        int temp = abs(dis);
        int aux;

        if (dis > 0) {
            aux = 1;
        } else {
            aux = -1; //Retorna o lado do ponto p em relação à linha que une os pontos p1 e p2.
        }

        if (aux == lado && temp > max_dist) {
            ind = i;
            max_dist = temp;
        }
    }
    if (ind == -1) { // Se nenhum ponto for encontrado adicione os pontos finais na casca convexa.
        casca.insert(p1);
        casca.insert(p2);
        return;
    }
    // Recorre para as duas partes divididas por um [ind]
    qHull(a, n, a[ind], p1, -orientacao(a[ind], p1, p2));
    qHull(a, n, a[ind], p2, -orientacao(a[ind], p2, p1));
}

void imprimeCasca(pair<int, int> *p, int n) {
    //Encontra o ponto com p coordenada x mínima e máxima
    int minX = 0, maxX = 0;
    for (int i = 1; i < n; i++) {
        if (p[i].first < p[minX].first)
            minX = i;
        if (p[i].first > p[maxX].first)
            maxX = i;
    }
    qHull(p, n, p[minX], p[maxX], 1); // sentido horario
    qHull(p, n, p[minX], p[maxX], -1); // sentido anti-horario

    cout << "Pontos que pertence ao quick hull: " << endl;

    for (auto it1 = casca.begin(); it1 != casca.end(); it1++) {
        cout << "(" << it1->first << ", " << it1->second << ") ";
    }

}


// Resultado: distância euclidiana entre o par de pontos mais próximo
double distancia(Point a, Point b) {
    double z = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    return sqrt(z);
};

//T(1) = 1
//T(n)= 2T(n/2) + f(n)
//Semelhante ao QuickSort, tem complexidade O(n log n) para entradas favoráveis. Porém, no pior caso, tem complexidade O(n²)
//Quickhull é um método de calcular o casco convexo de um casca finito de pontos no espaço n-dimensional.
// Ele usa uma abordagem de dividir para conquistar semelhante à de quicksort, da qual seu nome deriva.
//A idéia principal do QuickHull é descartar rapidamente pontos que obviamente estão no interior do fecho
double efficientClosestPair(Point p[], Point q[], int n) {
    int meio = (n / 2), num = 0;
    double dl, dr, d, dminsq;
    Point pl[n], pr[n], ql[n], qr[n], s[n];

    // Deve haver pelo menos 3 pontos
    // Quando n == 3, encontre diretamente a distância mínima
    if (n == 2) {
        //  cout << "Calculado a distância entre os pontos " << endl;
        return distancia(p[0], p[1]); // calculada por força bruta
    }
// retorna a distância mínima encontrada pelo algoritmo de força bruta
    else if (n == 3) {
        //  cout << "Calculado a distância entre os pontos " << endl;
        return std::min(distancia(p[0], p[1]), distancia(p[1], p[2]));
    } else {
        for (int i = 0; i < meio; i++) {
            // Copia os primeiros [n/2] pontos de p para pl, de q para ql
            pl[i] = p[i];
            ql[i] = q[i];
            // Copie os [n/2] pontos restantes de p para pr, de q para qr
            pr[i] = p[i + meio];
            qr[i] = q[i + meio];
        }

        // Atribuir a distância mínima em pl, ql a dl
        dl = efficientClosestPair(pl, ql, meio);
        // Atribuir a distância mínima em pr, qr a dr
        dr = efficientClosestPair(pr, qr, n - meio);

        // Atribuir a menor distância entre os dois para d
        d = std::min(dl, dr);

        int index = (ceil(n / 2) - 1); // metade de baixo

        int m = p[index].x;
        // Copia todos os pontos de | x-m | <d em q para a array s[0..num-1]
        for (int i = 0; i < n; i++) {
            if (fabs(q[i].x - m) < d) {
                s[num++] = q[i];
            }
        }
        // Defina a distância mínima dminsq para d * d
        dminsq = d * d;
        // Julgue o valor de cada dois pontos na matriz s, se for menor que dminsq, atribua o comprimento desses dois pontos a dminsq
        for (int i = 0; i < num - 2; i++) {
            int k = i + 1;
            while (k <= num - 1 && (s[k].y - s[i].y) * (s[k].y - s[i].y) < dminsq) {
                dminsq = min((s[k].x - s[i].x) * (s[k].x - s[i].x) + (s[k].y - s[i].y) * (s[k].y - s[i].y), dminsq);
                k++;
            }
        }
    }
    // Retorna a distância mínima
    return sqrt(dminsq);


}


//utilizada para int
//BST de busca; obedece as regras de dois filhos por nós e filho menores que o pai, lado esquerdo e maior, lado direto
//arvore binaria obedece a regra de dois filhos por nós
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

//10
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


//exercicio 5> da lista
/**
 * @see Descrição do problema:
 *  Dado um array A[] de tamanho n, encontre os elementos máximo e mínimo presentes no array.
 *  O algoritmo deve fazer o número mínimo de comparações.

 * @tparam T
 * @param arr
 * @param l
 * @param r
 * @return
 */

template<class T>
std::vector<T> posicaoMaioreMenorElemento(std::vector<T> &arr, int l, int r) {
    T max;
    T min;

    if (l == r) { //Se N == 1, retorne o elemento como máximo e mínimo
        max = arr[l];
        min = arr[l];
    } else if (l + 1 == r) {//segunda metade
        if (arr[l] < arr[r]) {
            max = arr[r];
            min = arr[l];
        } else {
            max = arr[l];
            min = arr[r];
        }
    } else {
        int m = (l + r) / 2;
        std::vector<T> left = posicaoMaioreMenorElemento(arr, l,
                                                         m); //Calcule recursivamente o máximo e o mínimo para as partes esquerda e direita
        std::vector<T> right = posicaoMaioreMenorElemento(arr, m + 1, r);
        if (left[0] > right[0]) //Encontre o máximo e o mínimo com 2 comparações
            max = left[0];
        else
            max = right[0];
        if (left[1] < right[1])
            min = left[1];
        else
            min = right[1];
    }
    std::vector<int> res = {max, min};
    return res;
}


template<class T>
std::vector<T> posicaoMaioreMenorElementoForcaBruta(std::vector<T> &arr) {
    T max = arr[0];
    T min = arr[0];

    std::vector<T> res;
//    if (arr.size() == 1) {
//        res.push_back(max);
//        res.push_back(min);
//        return res;
//    //} else {
    //
    for (int i = 1; i < arr.size(); i++) { //  Analise de complexidade: 2*(n-1) = 2n - 2
        if (arr[i] > max) {   // 2 iteraçãoes no pior caso
            max = arr[i];
        } else if (arr[i] < min) {
            min = arr[i];
        }
    }
    //  }
    res.push_back(max);
    res.push_back(min);
    return res;
}


template<class T>
std::vector<T> posicaoMaioreMenorElementoPair(std::vector<T> &arr) {
    T max, min;
    int i, n = arr.size();
    //se é impar, inicializa min e max com o primeiro elemento do array
    if (n % 2 == 1) // 3 * (n-1) / 2
    {
        max = arr[0];
        min = arr[0];
        i = 1;
    }
        // se não, compare os elementos e defina min para o valor menor e max para o valor maior
    else //1 + 3*(n-2)/2 = 3n/2-2
    {
        if (arr[0] < arr[1]) {
            max = arr[1];
            min = arr[0];
        } else {
            max = arr[0];
            min = arr[1];
        }
        i = 2;
    }
    // Para cada par, compare os dois elementos e, em seguida,
    // Compare o elemento maior com o máximo, atualize o máximo se necessário.
    // Compare o elemento menor com min, atualize min se necessário.
    while (i < n) {
        if (arr[i] < arr[i + 1]) {
            if (arr[i] < min)
                min = arr[i];
            if (arr[i + 1] > max)
                max = arr[i + 1];
        } else {
            if (arr[i] > max)
                max = arr[i];
            if (arr[i + 1] < min)
                min = arr[i + 1];
        }
        i = i + 2;
    }
    std::vector<T> res = {max, min};
    return res;
}

//encontrar a posição do maior elemento em um array e retorne a sua posição
//C(N) = 2C(N/2) + 1, C(1)=0
//     =n−1
template<class T>
int posicaoMaiorElemento(std::vector<T> &arr, int begin, int end) {
    if (begin == end) {        // T(N)=0
        return begin; // retorno nao é operação básica
    }
    int m = ((begin + end) / 2);

    int p1 = posicaoMaiorElemento(arr, begin, m);        //2T(n/2) -> divide em subproblemas
    int p2 = posicaoMaiorElemento(arr, m + 1, end);      //2T(n/2)

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
            a[i][j] = 1 + rand() % 100;
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
//    std::vector<int> arr = {97, 494, 564, 909, 542, 124, 8, 605, 540, 884};
//    printVector(arr);
////    std::vector<int> arDC =  posicaoMaioreMenorElemento(arr, 0, arr.size()-1);
////    cout << "MaxDC: " << arDC[0] << endl;
////    cout << "MinDC: " << arDC[1] << endl;
//
//    //// Força Bruta
//    std::vector<int> arFB =  posicaoMaioreMenorElementoForcaBruta(arr);
//    cout << "MaxFB: " << arFB[0] << endl;
//    cout << "MinFB: " << arFB[1] << endl;


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
    //Implemente os caminhamentos preorder,postordereinorderpara  ́arvores bin ́arias

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

    //   strassen();

    //14-----------------------------------------------------------------14---------------------------------------------
    //----------------------------------------------------  QuickHull---------------------------------------------------
    //------------------------------------------------------------------------------------------------------------------


    Point p[] = {{16, 3},
                 {12, 17},
                 {0,  6},
                 {-4, -6},
                 {16, 6},
                 {16, -7},
                 {16, -3},
                 {17, -4},
                 {5,  19},
                 {19, -8},
                 {3,  16},
                 {12, 13},
                 {3,  -4},
                 {17, 5},
                 {-3, 15},
                 {-3, -9},
                 {0,  11},
                 {-9, -3},
                 {-4, -2},
                 {12, 10}};
    Point q[] = {{16, 3},
                 {12, 17},
                 {0,  6},
                 {-4, -6},
                 {16, 6},
                 {16, -7},
                 {16, -3},
                 {17, -4},
                 {5,  19},
                 {19, -8},
                 {3,  16},
                 {12, 13},
                 {3,  -4},
                 {17, 5},
                 {-3, 15},
                 {-3, -9},
                 {0,  11},
                 {-9, -3},
                 {-4, -2},
                 {12, 10}};

    //  int tam = sizeof(p) / sizeof(p[0]);
    // cout << "A distância mínima é： " << efficientClosestPair(p, q, tam);

    Ponto a[] = {{0, 3},
                 {1, 1},
                 {2, 2},
                 {4, 4},
                 {0, 0},
                 {1, 2},
                 {3, 1},
                 {3, 3}};
    int n = sizeof(a) / sizeof(a[0]);
    imprimeCasca(a, n);
}
