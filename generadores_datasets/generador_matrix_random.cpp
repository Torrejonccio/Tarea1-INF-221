#include <iostream>
#include <random>
#include <fstream>

using namespace std;

int main(){
    // Se cambió la salida, dimensiones y rangos a través
    // del código en las líneas seleccionadas con "***"
    ofstream file("dataset_matrix_RANDOM 1024x1024.txt"); // ***
    if(!file){
        cerr << "NO SE PUDO ABRIR EL ARCHIVO PARA ESCRIBIR" << endl;
        return 1;
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> num_value(0, 1000); // ***
    int dimension = 1024; // ***
    int mult_amount = 100; // ***
    for(int j = 0; j < (dimension * 2) * mult_amount; j++){
        for(int i = 0; i <= dimension - 1; i++){
            int num = num_value(gen);
            file << num << " ";
        }    
        file << endl;
    }
    file.close();
    return 0;
}