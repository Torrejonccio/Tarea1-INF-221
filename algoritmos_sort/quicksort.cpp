#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función que genera la partición
int partition(vector<int> &vec, int low, int high) {
    int randomPivotIndex = low + rand() % (high - low);
    swap(vec[randomPivotIndex], vec[high]); 

    int pivot = vec[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return (i + 1);
}

// Función QuickSort
void quickSort(vector<int> &vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);

        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

int main(){
    // Se cambió la entrada/salida a través del código en las
    // líneas seleccionadas con "***"
    ifstream inputfile("dataset_sort_DESORDENADAS S.txt"); // ***
    ofstream outputfile("dataset_sort_DESORDENADAS S OUTPUT QUICKSORT.txt"); // ***
    if(!inputfile || !outputfile){
        cerr << "NO SE PUDO ABRIR ARCHIVO DE ENTRADA O SALIDA" << endl;
        return 1;
    }
    string line;
    auto quick_total = milliseconds(0);

    while(getline(inputfile, line)){
        istringstream lineStream(line);
        vector<int> list;
        int num;

        while(lineStream >> num){
            list.push_back(num);
        }
        int n = list.size();

        auto quick_start = high_resolution_clock::now();
        quickSort(list, 0, n-1);
        auto quick_stop = high_resolution_clock::now();
        auto quick_dur = duration_cast<milliseconds>(quick_stop - quick_start);
        cout << quick_dur.count() << endl;
        quick_total += quick_dur;
        
        for(int i : list){
            outputfile << i << " ";
        }
        outputfile << endl;
    }

    cout << "Tiempo demora Quicksort: " << quick_total.count() << " ms";

    return 0;
}







