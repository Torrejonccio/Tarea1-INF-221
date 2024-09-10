#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int CROSSOVER_POINT = 90;

// Función para separar la matriz
void split(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, int row, int col, int d){
    for (int i1 = 0, i2 = row; i1 < d; i1++, i2++){
        for (int j1 = 0, j2 = col; j1 < d; j1++, j2++){
            B[i1][j1] = A[i2][j2];
        }
    }
}

// Función que une las matrices separadas
void join(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, int row, int col, int d){
    for (int i1 = 0, i2 = row; i1 < d; i1++, i2++){
        for (int j1 = 0, j2 = col; j1 < d; j1++, j2++){
        	B[i2][j2] = A[i1][j1];
        }
    }
}

// Función que suma dos matrices 
void add(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &C, int d){
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Función que resta dos matrices 
void subtract(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &C, int d) {
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Función que multiplica dos matrices de forma tradicional
void multiply(std::vector< std::vector<int> > &A, std::vector< std::vector<int> > &B, std::vector< std::vector<int> > &C, int d){
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            for (int k = 0; k < d; k++){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
}

// Algoritmo de Strassen
void strassen(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &C, int d){
    if(d <= CROSSOVER_POINT){
        multiply(A, B, C, d);
        return;
    }
    else{

    int new_d = d/2;
    
    std::vector<int> inside(new_d);

    std::vector< std::vector<int> > A11 (new_d, inside);
    std::vector< std::vector<int> > A12 (new_d, inside);
    std::vector< std::vector<int> > A21 (new_d, inside);
    std::vector< std::vector<int> > A22 (new_d, inside);
    std::vector< std::vector<int> > B11 (new_d, inside);
    std::vector< std::vector<int> > B12 (new_d, inside);
    std::vector< std::vector<int> > B21 (new_d, inside);
    std::vector< std::vector<int> > B22 (new_d, inside);
    std::vector< std::vector<int> > C11 (new_d, inside);
    std::vector< std::vector<int> > C12 (new_d, inside);
    std::vector< std::vector<int> > C21 (new_d, inside);
    std::vector< std::vector<int> > C22 (new_d, inside);

    split(A, A11, 0 , 0, new_d);
    split(A, A12, 0 , new_d, new_d);
    split(A, A21, new_d, 0, new_d);
    split(A, A22, new_d, new_d, new_d);
    split(B, B11, 0 , 0, new_d);
    split(B, B12, 0 , new_d, new_d);
    split(B, B21, new_d, 0, new_d);
    split(B, B22, new_d, new_d, new_d);

    std::vector< std::vector<int> > result1 (new_d, inside);
    std::vector< std::vector<int> > result2 (new_d, inside);


    /************************************************
    *** 	M1 = (A11 + A22)(B11 + B22)
    *** 	M2 = (A21 + A22) B11
    *** 	M3 = A11 (B12 - B22)
    *** 	M4 = A22 (B21 - B11)
    *** 	M5 = (A11 + A12) B22
    *** 	M6 = (A21 - A11) (B11 + B12)
    *** 	M7 = (A12 - A22) (B21 + B22)
    ************************************************/

    // Calcula M1
    add(A11, A22, result1, new_d);
    add(B11, B22, result2, new_d);
    std::vector< std::vector<int> > M1 (new_d, inside);
    strassen(result1, result2, M1, new_d);
    
    // Calcula M2
    add(A21, A22, result1, new_d);
    std::vector< std::vector<int> > M2 (new_d, inside);
    strassen(result1, B11, M2, new_d);

    // Calcula M3
    subtract(B12, B22, result2, new_d);
    std::vector< std::vector<int> > M3 (new_d, inside);
    strassen(A11, result2, M3, new_d);

    // Calcula M4
    subtract(B21, B11, result2, new_d);
    std::vector< std::vector<int> > M4 (new_d, inside);
    strassen(A22, result2, M4, new_d);

    // Calcula M5
    add(A11, A12, result1, new_d);
    std::vector< std::vector<int> > M5 (new_d, inside);
    strassen(result1, B22, M5, new_d);

    // Calcula M6
    subtract(A21, A11, result1, new_d);
    add(B11, B12, result2, new_d);
    std::vector< std::vector<int> > M6 (new_d, inside);
    strassen(result1, result2, M6, new_d);

    // Calcula M7
    subtract(A12, A22, result1, new_d);
    add(B21, B22, result2, new_d);
    std::vector< std::vector<int> > M7 (new_d, inside);
    strassen(result1, result2, M7, new_d);

    /**********************************************
    ***      C11 = M1 + M4 - M5 + M7
    ***      C12 = M3 + M5
    ***      C21 = M2 + M4
    ***      C22 = M1 - M2 + M3 + M6
    **********************************************/

    // Calcula C11
    add(M1, M4, result1, new_d);
    add(result1, M7, result2, new_d);
    subtract(result2, M5, C11, new_d);

    // Calcula C12
    add(M3, M5, C12, new_d);

    // Calcula C21
    add(M2, M4, C21, new_d);

    // Calcula C22
    subtract(M1, M2, result1, new_d);
    add(M3, M6, result2, new_d);
    add(result1, result2, C22, new_d);



    // Une el resultado de las matrices en una sola
    join(C11, C, 0 , 0, new_d);
    join(C12, C, 0 , new_d, new_d);
    join(C21, C, new_d, 0, new_d);
    join(C22, C, new_d, new_d, new_d);  
    }
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
    ofstream outputfile("dataset_matrix_RANDOM 1024x1024 OUTPUT STRASSEN.txt"); // ***
    if(!inputfile || !outputfile){
        cerr << "NO SE PUDO ABRIR ARCHIVO DE ENTRADA O SALIDA" << endl;
        return 1;
    }
    string line;
    auto strassen_total = milliseconds(0);
    int count = 0;
    int lines = 1024; // ***
    int matrix_count = 0;

    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;

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
            vector<int> inside(lines);
            vector<vector<int>> rslt_matrix(lines, inside);

            auto strassen_start = high_resolution_clock::now();
            strassen(matrix1, matrix2, rslt_matrix, lines);
            auto strassen_stop = high_resolution_clock::now();
            auto strassen_dur = duration_cast<milliseconds>(strassen_stop - strassen_start);
            cout << strassen_dur.count() << endl;
            strassen_total += strassen_dur;

            genOutput(rslt_matrix, outputfile);

            matrix1.clear();
            matrix2.clear();
            matrix_count = 0;
        } 
    }   

    cout << "Tiempo demora Strassen: " << strassen_total.count() << " ms";

    return 0;
}
