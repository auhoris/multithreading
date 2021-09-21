#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#define SIZE 30
#define MATRIX std::vector<std::vector<int> >

std::mutex push;
void time(int start, int end) {
    std::cout << "[" << end - start << "] ticks && "
              << "[" << ((float)end - start) / CLOCKS_PER_SEC << "]"
              << " sec.\n";
}
void parallel_matrix_sum(std::vector<int> mat1, std::vector<int> mat2, std::vector<int>& result) {
    for (size_t i = 0; i < mat1.size(); i++) {
        result.push_back(mat1[i] + mat2[i]);
    }
}

void matrix_sum(MATRIX first, MATRIX second, MATRIX& result) {
    size_t size = first.size();
    std::vector<int> buffer;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            buffer.push_back(first[i][j] + second[i][j]);
        };
        result.push_back(buffer);
        buffer.clear();
    }
}

void show_matrix(MATRIX& matrix) {
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
    MATRIX results(SIZE);
    std::vector<int> res_buffer;
    int start;
    int end;
    srand(time(0));

    for (size_t i = 0; i < SIZE; i++) {
        matrix1.push_back(std::vector<int>(SIZE, rand() % 50));
        matrix2.push_back(std::vector<int>(SIZE, rand() % 30));
    }
    size_t size = matrix1.size();
    results.reserve(size);

    std::vector<std::thread> threads(size);
    start = clock();
    for (size_t i = 0; i < size; i++) {
        threads[i] = std::thread(parallel_matrix_sum, matrix1[i], matrix2[i], std::ref(results[i]));
    }
    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));
    end = clock();
    std::cout << "parallel_matrix_sum timing: " << "\n";
    time(start, end);

    MATRIX results2;
    start = clock();
    matrix_sum(matrix1, matrix2, results2);
    end = clock();
    std::cout << "matrix_sum timing: " << "\n";
    time(start, end);
    return 0;
}
