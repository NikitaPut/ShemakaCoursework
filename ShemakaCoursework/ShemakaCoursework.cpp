#include <iostream>
#include <string>
#include <chrono>
#include "CrossRefs.h"

static void check() {
    CrossRefs cr2;
    auto start_time = std::chrono::high_resolution_clock::now();
    cr2.createTable("big_text.txt");
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Big text processing time: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()
        << " microseconds\n";

    CrossRefs cr1;
    start_time = std::chrono::high_resolution_clock::now();
    cr1.createTable("test.txt");
    end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Test text processing time: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count()
        << " microseconds\n";
}

int main() {
    try {
        CrossRefs cr;
        cr.createTable("test.txt");
        cr.readFile(std::cout, "test.txt");
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

    try {
        CrossRefs cr1;
        cr1.createTable("big_text.txt");
        cr1.readFile(std::cout, "big_text.txt");
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}