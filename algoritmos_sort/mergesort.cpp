#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función auxiliar MergeSort
void merge(vector<int>& arr, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
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

// Función MergeSort
void mergeSort(vector<int>& arr, int left, int right){
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main(){
    // Se cambió la entrada/salida a través del código en las
    // líneas seleccionadas con "***"
    ifstream inputfile("dataset_sort_DESORDENADAS S.txt"); // ***
    ofstream outputfile("dataset_sort_DESORDENADAS S OUTPUT MERGESORT.txt"); // ***
    if(!inputfile || !outputfile){
        cerr << "NO SE PUDO ABRIR ARCHIVO DE ENTRADA O SALIDA" << endl;
        return 1;
    }
    string line;
    auto merge_total = milliseconds(0);

    while(getline(inputfile, line)){
        istringstream lineStream(line);
        vector<int> list;
        int num;

        while(lineStream >> num){
            list.push_back(num);
        }
        int n = list.size();

        auto merge_start = high_resolution_clock::now();
        mergeSort(list, 0, n-1);
        auto merge_stop = high_resolution_clock::now();
        auto merge_dur = duration_cast<milliseconds>(merge_stop - merge_start);
        cout << merge_dur.count() << endl;
        merge_total += merge_dur;

        for(int i : list){
            outputfile << i << " ";
        }
        outputfile << endl;
    }

    cout << "Tiempo demora Mergesort: " << merge_total.count() << " ms";

    return 0;
}