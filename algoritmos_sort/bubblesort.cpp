#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// BubbleSort optimizado (si no hay swap, detiene el loop)
vector<int> bubblesort(vector<int> list, int n){
    int i, j;
    bool swapped;

    for(i = 0; i < n-1; i++){
        swapped = false;
        for(j = 0; j < n-i-1; j++){
            if(list[j] > list[j+1]){
                swap(list[j], list[j+1]);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
    }
    return list;
}

int main(){
    // Se cambió la entrada/salida a través del código en las
    // líneas seleccionadas con "***"
    ifstream inputfile("dataset_sort_DESORDENADAS S.txt"); // ***
    ofstream outputfile("dataset_sort_DESORDENADAS S OUTPUT BUBBLESORT.txt"); // ***
    if(!inputfile || !outputfile){
        cerr << "NO SE PUDO ABRIR ARCHIVO DE ENTRADA O SALIDA" << endl;
        return 1;
    }
    string line;
    auto bubble_total = milliseconds(0);

    while(getline(inputfile, line)){
        istringstream lineStream(line);
        vector<int> list;
        int num;

        while(lineStream >> num){
            list.push_back(num);
        }
        int n = list.size();

        auto bubble_start = high_resolution_clock::now();
        list = bubblesort(list, n);
        auto bubble_stop = high_resolution_clock::now();
        auto bubble_dur = duration_cast<milliseconds>(bubble_stop - bubble_start);
        bubble_total += bubble_dur;

        for(int i : list){
            outputfile << i << " ";
        }
        outputfile << endl;
    }

    cout << "Tiempo demora bubblesort: " << bubble_total.count() << " ms";

    inputfile.close();
    outputfile.close();

    return 0;
}