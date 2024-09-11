// https://www.geeksforgeeks.org/bubble-sort-algorithm/

#include <bits/stdc++.h>
using namespace std;

// Versión optimizada del Bubblesort
void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // Si ningún elemento fue intercambiado
        // en el primer loop, ejecuta break
        if (swapped == false)
            break;
    }
}

// Función para imprimir un arreglo
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << " " << arr[i];
}

// Programa de prueba para probar funciones
int main()
{
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int N = sizeof(arr) / sizeof(arr[0]);
    bubbleSort(arr, N);
    cout << "Sorted array: \n";
    printArray(arr, N);
    return 0;
}
// Este código fue creado por shivanisinghss2110
