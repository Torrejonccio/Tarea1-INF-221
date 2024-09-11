// https://www.geeksforgeeks.org/cpp-program-for-merge-sort/

#include <iostream>
#include <vector>

using namespace std;

// Une dos sub-arreglos
// El primer sub-arreglo es vec[left..mid]
// El segundo sub-arreglo es vec[mid+1..right]
void merge(vector<int>& vec, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crea vectores temporales
    vector<int> leftVec(n1), rightVec(n2);

    // Copia los datos de los vectores temporales
    for (i = 0; i < n1; i++)
        leftVec[i] = vec[left + i];
    for (j = 0; j < n2; j++)
        rightVec[j] = vec[mid + 1 + j];

    // Une los vectores temporales en vec[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftVec[i] <= rightVec[j]) {
            vec[k] = leftVec[i];
            i++;
        } else {
            vec[k] = rightVec[j];
            j++;
        }
        k++;
    }

    // Copia los elementos restantes de leftVec[], si es que hay
    while (i < n1) {
        vec[k] = leftVec[i];
        i++;
        k++;
    }

    // Copia los elementos restantes de rightVec[], si es que hay
    while (j < n2) {
        vec[k] = rightVec[j];
        j++;
        k++;
    }
}

// El sub-arreglo que será ordenado está en el rango de indice [left..right]
void mergeSort(vector<int>& vec, int left, int right) {
    if (left < right) {
      
        // Calcula el punto medio
        int mid = left + (right - left) / 2;

        // Ordena la primera y segunda mitad
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        // Une las mitades ordenadas
        merge(vec, left, mid, right);
    }
}

int main() {
    vector<int> vec = {12, 11, 13, 5, 6, 7};
    int n = vec.size();

    // Ordenamiento de vector usando mergeSort
    mergeSort(vec, 0, n - 1);

    for (auto i: vec)
        cout << i << " ";
    return 0;
}
