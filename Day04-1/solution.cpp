
#include <array>
#include <cassert>
#include <iostream>
#include <sstream>
#include <ranges>
#include <unordered_map>
#include <vector>


class BingoBoard {
public:
    static constexpr int WIDTH {5};
    static constexpr int HEIGHT {5};

    friend std::istream& operator>>(std::istream& in, BingoBoard& board);

    /* Returns true one BINGO! */    
    bool update(int new_num) {
        if (!num_to_location.contains(new_num))
            return false;

        auto [x, y] = num_to_location[new_num];
        num_to_location.erase(new_num);

        column_counts[x]++;
        row_counts[y]++;
        return column_counts[x] == HEIGHT || row_counts[y] == WIDTH;
    }

    int get_score(int called_num) {
        int score {0};
        for (auto [unconvered_num, pair] : num_to_location) {
            score += unconvered_num;
        }

        return score * called_num;
    }


private:
    std::unordered_map<int, std::pair<int, int>> num_to_location {};
    std::array<int, WIDTH> column_counts {};
    std::array<int, HEIGHT> row_counts {};
};

std::istream& operator>>(std::istream& in, BingoBoard& board) {
    board = {}; // Reset the board variable!

    for (int x {0}; x < BingoBoard::WIDTH; x++) {
        for (int y {0}; y < BingoBoard::HEIGHT; y++) {
            int num {};
            in >> num;
            board.num_to_location[num] = {x, y};
        }
    }

    return in;
}

/* Returns the score of the winning board */
int run_bingo(const std::vector<int>& called_numbers, std::vector<BingoBoard>& boards) {
    for (int new_num : called_numbers) {
        for (BingoBoard& board : boards) {
            if (board.update(new_num)) {
                return board.get_score(new_num);
            }
        }    
    }

    assert(false);
}

int main() {
    std::string first_line {};
    std::cin >> first_line;
    std::istringstream sstream {first_line};

    std::vector<int> called_numbers {};
    while (sstream) {
        int num {};
        sstream >> num;
        called_numbers.push_back(num);

        char _;
        sstream >> _;
    }
    
    std::vector<BingoBoard> boards {};
    BingoBoard nextBoard {};
    while (std::cin >> nextBoard) {
        boards.push_back(nextBoard);
    }

    std::cout << run_bingo(called_numbers, boards) << "\n";

    return 0;
}