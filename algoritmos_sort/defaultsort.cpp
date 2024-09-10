#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Función por defecto a utilizar: std::sort()
int main(){
    // Se cambió la entrada/salida a través del código en las
    // líneas seleccionadas con "***"
    ifstream inputfile("dataset_sort_DESORDENADAS S.txt"); // ***
    ofstream outputfile("dataset_sort_DESORDENADAS S OUTPUT SORT().txt"); // ***
    if(!inputfile || !outputfile){
        cerr << "NO SE PUDO ABRIR ARCHIVO DE ENTRADA O SALIDA" << endl;
        return 1;
    }
    string line;
    auto sort_total = milliseconds(0);

    while(getline(inputfile, line)){
        istringstream lineStream(line);
        vector<int> list;
        int num;

        while(lineStream >> num){
            list.push_back(num);
        }
        auto sort_start = high_resolution_clock::now();
        std::sort(list.begin(), list.end());
        auto sort_stop = high_resolution_clock::now();
        auto sort_dur = duration_cast<milliseconds>(sort_stop - sort_start);
        cout << sort_dur.count() << endl;
        sort_total += sort_dur;
        for(int i : list){
            outputfile << i << " ";
        }
        outputfile << endl;
    }

    cout << "Tiempo demora sort(): " << sort_total.count() << " ms";

    return 0;
}
