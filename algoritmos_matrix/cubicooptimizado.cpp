#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Dimensiones de las matrices:
#define R1 1024
#define C1 1024
#define R2 1024
#define C2 1024

// Función para transponer una matriz
void transposeMatrix(const vector<vector<int>>& mat, vector<vector<int>>& mat_transpose) {
    int rows = mat.size();
    int cols = rows; // Al ser matrices cuadradas rows == cols
    mat_transpose.resize(cols, vector<int>(rows));
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j) {
            mat_transpose[j][i] = mat[i][j];
        }
    }
}

// Función para multiplicar dos matrices con la segunda matriz transpuesta
vector<vector<int>> mulMatOptimized(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2_t) {
    vector<vector<int>> rslt(R1, vector<int>(C2, 0)); 
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            for (int k = 0; k < C1; k++) {
                rslt[i][j] += mat1[i][k] * mat2_t[j][k];
            }
        }
    }
    return rslt;
}

// Función para exportar salida en un archivo .txt
void genOutput(const vector<vector<int>> &rslt, ofstream &outputfile){
    for(const auto &row : rslt){
        for(int num : row){
            outputfile << num << " ";
        }
        outputfile << endl;
    }
}

int main(){
    // Se cambió la entrada/salida y las dimensiones manualmente 
    // a través del código en las líneas seleccionadas con "***"
    ifstream inputfile("dataset_matrix_RANDOM 1024x1024.txt"); // ***
    ofstream outputfile("dataset_matrix_RANDOM 1024x1024 OUTPUT CUBICOOPTIMIZADO.txt"); // ***
    if(!inputfile || !outputfile){
        cerr << "NO SE PUDO ABRIR ARCHIVO DE ENTRADA O SALIDA" << endl;
        return 1;
    }
    string line;
    auto cubicooptimizada_total = milliseconds(0);
    int count = 0;
    int lines = 1024; // ***
    int matrix_count = 0;

    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;
    vector<vector<int>> matrix2_t;

    while(getline(inputfile, line)){
        istringstream lineStream(line);
        vector<int> row;
        int num;
        while(lineStream >> num){
            row.push_back(num);
        }
        if(matrix_count == 1){
            matrix2.push_back(row);
        }
        else{
            matrix1.push_back(row);
        }
        count += 1;
        if(count == lines){          
            count = 0;
            matrix_count += 1;
        }
        if (matrix_count == 2){
            transposeMatrix(matrix2, matrix2_t);
            auto cubico_start = high_resolution_clock::now();
            vector<vector<int>> rslt = mulMatOptimized(matrix1, matrix2_t);
            auto cubico_stop = high_resolution_clock::now();
            auto cubico_dur = duration_cast<milliseconds>(cubico_stop - cubico_start);
            cout << cubico_dur.count() << endl;
            cubicooptimizada_total += cubico_dur;

            genOutput(rslt, outputfile);

            matrix1.clear();
            matrix2.clear();
            matrix2_t.clear();
            matrix_count = 0;
        } 
    }   

    cout << "Tiempo demora multiplicación cúbica optimizada: " << cubicooptimizada_total.count() << " ms";

    return 0;
}
