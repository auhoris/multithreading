#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#define SIZE 40
#define MATRIX std::vector<std::vector<int> >

std::mutex msg;

void time(int start, int end) {
    std::cout << "[" << end - start << "] ticks && "
              << "[" << ((float)end - start) / CLOCKS_PER_SEC << "]"
              << " sec.\n";
}

void parallel_matrix_mul(const MATRIX& matrix1, const MATRIX& matrix2,
                         MATRIX& result, size_t i) {
    size_t tmp = 0;
    std::vector<int> buffer;

    for (size_t k = 0; k < matrix1.size(); k++) {
        for (size_t j = 0; j < matrix1[k].size(); j++) {
            tmp += matrix1[i][j] * matrix2[j][k];
        };
        buffer.push_back(tmp);
        tmp = 0;
    }
    result[i] = buffer;
}

void matrix_mul(const MATRIX& matrix1, const MATRIX& matrix2, MATRIX& result) {
    size_t tmp = 0;
    std::vector<int> buffer;

    for (size_t i = 0; i < matrix1.size(); i++) {
        for (size_t k = 0; k < matrix1.size(); k++) {
            for (size_t j = 0; j < matrix1[k].size(); j++) {
                tmp += matrix1[i][j] * matrix2[j][k];
            };
            buffer.push_back(tmp);
            tmp = 0;
        };
        result[i] = buffer;
        buffer.clear();
    }
}

void show_matrix(const std::string& name, MATRIX& matrix) {
    std::cout << name << ": ==============================\n";
    size_t size = matrix.size();
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << " ";
        };
        std::cout << "\n";
    }
}

int main(void) {
    MATRIX matrix1;
    MATRIX matrix2;
    MATRIX results;
    std::vector<int> res_buffer;
    int start;
    int end;
    srand(time(0));

    for (size_t i = 0; i < SIZE; i++) {
        matrix1.push_back(std::vector<int>(SIZE, rand() % 10));
        matrix2.push_back(std::vector<int>(SIZE, rand() % 10));
    }
    size_t size = matrix1.size();
    results.resize(size);

    start = clock();
    std::vector<std::thread> threads(size);
    for (size_t i = 0; i < size; i++) {
        threads[i] = std::thread(parallel_matrix_mul, std::ref(matrix1),
                                 std::ref(matrix2), std::ref(results), i);
    }
    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));
    end = clock();
    time(start, end);

    MATRIX results2;
    results2.resize(size);
    start = clock();
    matrix_mul(matrix1, matrix2, results2);
    end = clock();
    time(start, end);
    return 0;
}
