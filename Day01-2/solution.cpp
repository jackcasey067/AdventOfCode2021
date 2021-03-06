
#include <iostream>
#include <fstream>

/*
 * Let k be the size of each sum (here k = 3)
 * For an additional challenge:
 * - parameterize your code with respect to K
 * - Have O(n) time complexity (not O(n * K))
 * - Have O(1) space complexity (not O(K))
 */

constexpr int K = 3;

int main(int argc, char *argv[]) {
    std::string file_name {"input.txt"};

    if (argc >= 2) {
        file_name = argv[1];
    }

    /* input_1 runs ahead, input_2 runs k behind. */
    std::fstream input_1 = std::fstream(file_name);
    std::fstream input_2 = std::fstream(file_name);

    /* Move input_1 ahead. */
    int last_sum {};
    for (int i {0}; i < K; i++) {
        int in {};
        input_1 >> in;
        last_sum += in;
    }

    int new_num {};
    int count {0};
    while (input_1 >> new_num) {
        int lost_num {};
        input_2 >> lost_num;
        
        int next_sum{};
        next_sum = last_sum + new_num - lost_num;

        if (next_sum > last_sum)
            count++;

        last_sum = next_sum;
    }

    std::cout << count << "\n";

    return 0;
}

// ./solution input.txt