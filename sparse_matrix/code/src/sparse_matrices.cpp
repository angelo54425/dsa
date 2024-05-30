#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <limits>

using namespace std;

// Define a type for a sparse matrix
using SparseMatrix = vector<tuple<int, int, double>>;

// Function to load a sparse matrix from a file
SparseMatrix loadSparseMatrix(ifstream &infile) {
    int rows, cols;
    infile >> rows >> cols;

    SparseMatrix matrix;
    int row, col;
    double value;
    while (infile >> row >> col >> value) {
        matrix.emplace_back(row, col, value);
    }
    return matrix;
}

// Function to add two sparse matrices
SparseMatrix addSparseMatrices(const SparseMatrix &matrix1, const SparseMatrix &matrix2) {
    unordered_map<pair<int, int>, double, hash<pair<int, int>>> result_map;

    for (const auto& [row, col, value] : matrix1) {
        result_map[{row, col}] += value;
    }

    for (const auto& [row, col, value] : matrix2) {
        result_map[{row, col}] += value;
    }

    SparseMatrix result;
    for (const auto& [key, value] : result_map) {
        if (value != 0) {
            result.emplace_back(key.first, key.second, value);
        }
    }

    return result;
}

// Function to subtract the second sparse matrix from the first
SparseMatrix subtractSparseMatrices(const SparseMatrix &matrix1, const SparseMatrix &matrix2) {
    unordered_map<pair<int, int>, double, hash<pair<int, int>>> result_map;

    for (const auto& [row, col, value] : matrix1) {
        result_map[{row, col}] += value;
    }

    for (const auto& [row, col, value] : matrix2) {
        result_map[{row, col}] -= value;
    }

    SparseMatrix result;
    for (const auto& [key, value] : result_map) {
        if (value != 0) {
            result.emplace_back(key.first, key.second, value);
        }
    }

    return result;
}

// Function to multiply two sparse matrices
SparseMatrix multiplySparseMatrices(const SparseMatrix &matrix1, const SparseMatrix &matrix2, int rows1, int cols1, int cols2) {
    unordered_map<int, unordered_map<int, double>> result_map;

    for (const auto& [row1, col1, value1] : matrix1) {
        for (const auto& [row2, col2, value2] : matrix2) {
            if (col1 == row2) {
                result_map[row1][col2] += value1 * value2;
            }
        }
    }

    SparseMatrix result;
    for (const auto& row_pair : result_map) {
        int row = row_pair.first;
        for (const auto& col_pair : row_pair.second) {
            int col = col_pair.first;
            double value = col_pair.second;
            if (value != 0) {
                result.emplace_back(row, col, value);
            }
        }
    }

    return result;
}

int main() {
    string filepath = "C:\\dsa\\sparse_matrix\\sample_inputs\\xfile";
    ifstream infile(filepath);

    if (!infile) {
        cerr << "Error opening file: " << filepath << endl;
        return 1;
    }

    // Load the first sparse matrix
    SparseMatrix matrix1 = loadSparseMatrix(infile);

    // Skip any extra lines or delimiters between matrices & clear any error flags
    infile.clear();
    infile.ignore(numeric_limits<streamsize>::max(), '\n'); // skip to the next line

    // Load the second sparse matrix
    SparseMatrix matrix2 = loadSparseMatrix(infile);

    // Close the file
    infile.close();

    // Perform addition, subtraction and multiplication
    SparseMatrix sum = addSparseMatrices(matrix1, matrix2);

    SparseMatrix difference = subtractSparseMatrices(matrix1, matrix2);

    SparseMatrix product = multiplySparseMatrices(matrix1, matrix2, 3, 3, 3); // assuming 3x3 matrices for example

    // Output the results
    cout << "Sum:" << endl;
    for (const auto& [row, col, value] : sum) {
        cout << row << " " << col << " " << value << endl;
    }

    cout << "Difference:" << endl;
    for (const auto& [row, col, value] : difference) {
        cout << row << " " << col << " " << value << endl;
    }

    cout << "Product:" << endl;
    for (const auto& [row, col, value] : product) {
        cout << row << " " << col << " " << value << endl;
    }

    return 0;
}
