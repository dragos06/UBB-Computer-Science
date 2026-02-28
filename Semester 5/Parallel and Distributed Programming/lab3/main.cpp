#include <iostream>
#include <vector>
#include <random>
#include <thread>

using namespace std;

int rows1 = 500;
int common12 = 500;
int cols2 = 500;

int NUM_THREADS = 10;

vector<vector<int>> matrix1(rows1, vector<int>(common12));
vector<vector<int>> matrix2(common12, vector<int>(cols2));
vector<vector<int>> matrix3(rows1, vector<int>(cols2));

void generate() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution dist(1, 100);

    for(int i = 0; i < rows1; i++) {
        for(int j = 0; j < common12; j++) {
            matrix1[i][j] = dist(gen);
        }
    }

    for(int i = 0; i < common12; i++) {
        for(int j = 0; j < cols2; j++) {
            matrix2[i][j] = dist(gen);
        }
    }
}

int computeElem(int i, int j) {
    int elem = 0;
    for(int k = 0; k < common12; k++) {
        elem += matrix1[i][k] * matrix2[k][j];
    }
    return elem;
}

void completeRows(int threadNum) {
    int nrElemsPerThread = (rows1 * cols2) / NUM_THREADS;

    int n = threadNum * nrElemsPerThread;
    
    int startRow = n / cols2;
    int startCol = n % cols2;

    if (threadNum == NUM_THREADS - 1) {
        nrElemsPerThread += (rows1 * cols2) % NUM_THREADS;
    }

    while(nrElemsPerThread) {
        this_thread::sleep_for(std::chrono::milliseconds(rand() % 10));
        cout << threadNum << " - (" << startRow << ", " << startCol << ") " << endl;

        matrix3[startRow][startCol] = computeElem(startRow, startCol);
        
        if (startCol == cols2 - 1) {
            startRow++;
            startCol = 0;
        } else {
            startCol++;
        }

        nrElemsPerThread--;
    }
}

void completeColumns(int threadNum) {
    int nrElemsPerThread = (rows1 * cols2) / NUM_THREADS;

    int n = threadNum * nrElemsPerThread;

    int startCol = n / rows1;
    int startRow = n % rows1;

    if (threadNum == NUM_THREADS - 1) {
        nrElemsPerThread += (rows1 * cols2) % NUM_THREADS;
    }

    while(nrElemsPerThread) {
        this_thread::sleep_for(std::chrono::milliseconds(rand() % 10));
        cout << threadNum << " - (" << startRow << ", " << startCol << ") " << endl;

        matrix3[startRow][startCol] = computeElem(startRow, startCol);
        
        if (startRow == rows1 - 1) {
            startCol++;
            startRow = 0;
        } else {
            startRow++;
        }

        nrElemsPerThread--;
    }
}

void completeK(int threadNum) {
    int totalElems = rows1 * cols2;

    for(int i = threadNum; i < totalElems; i += NUM_THREADS) {
        int row = i / cols2;
        int col = i % cols2;

        matrix3[row][col] = computeElem(row, col);

        this_thread::sleep_for(std::chrono::milliseconds(rand() % 10));
        cout << threadNum << " - (" << row << ", " << col << ")" << endl;
    }
}

void verify() {
    for(int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            int elem = computeElem(i, j);
            if (matrix3[i][j] != elem) {
                cout << "Matrices do not match" << endl;
                return ;
            }
        }
    }

    cout << "Matrices match" << endl;
}

int main() {
    generate();
    vector<thread> threads;
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < NUM_THREADS; i++) {
        threads.emplace_back(completeRows, i);
    }

    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Duration: " << elapsed.count() << "s" << endl;

    verify();
    for(int i = 0; i < rows1; i++) {
        for(int j = 0; j < cols2; j++) {
            cout << matrix3[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
