#include <iostream>
#include <memory>
#include "board.h"
#include "blank.h"
#include "subject.h"
#include "player.h"
#include "textObserver.h"
#include "unit.h"
#include "link.h"
#include "data.h"
#include "virus.h"
#include "decorator.h"
#include "datadecorator.h"
#include "virusdecorator.h"
#include <vector>

void print_rule() {
    std::cout << "RAIInet is a two-player strategy game played on an 8×8 grid.\n"
              << "Each player controls 8 hidden links (4 data and 4 viruses) with strengths from 1 to 4.\n"
              << "The goal is to download 4 data links to win, or make your opponent download 4 viruses to cause their loss.\n"
              << "Players take turns.\n"
              << "Each turn involves optionally using one ability card and moving one link in a cardinal direction (north, south, east, or west).\n"
              << "If a link moves onto an opponent's link, a battle occurs: the stronger link wins, and the losing link is downloaded.\n"
              << "Ties are won by the initiating player.\n"
              << "Abilities allow strategic actions like boosting link movement or revealing hidden information.\n"
              << "Each player has 5 ability cards, which can only be used once per game.\n"
              << "The game ends when either player downloads 4 data (winning) or 4 viruses (losing).\n"
              << "Hidden information and clever use of abilities are key to success.\n";
}

void print_blank() {
    std::cout << "========\n" 
              << "abcSSfgh\n"
              << "...de...\n"
              << "........\n"
              << "........\n"
              << "........\n"
              << "........\n"
              << "...DE...\n"
              << "ABCSSFGH\n"
              << "========\n";
}

void setupPlayer(Board* board, Player* player, int startRow, const std::string& playerName, char startChar) {
    std::cout << playerName << ", please set your links (" << startChar
              << "-" << static_cast<char>(startChar + 7)
              << "). Use format v1, d2, etc.\n";

    char n = startChar;
    int col = 0;
    bool vSet[4] = {false, false, false, false};
    bool dSet[4] = {false, false, false, false};

    while (n <= startChar + 7) {
        std::string set;
        std::cin >> set;

        int strength = 0;
        if (set[0] == 'v' && set[1] >= '1' && set[1] <= '4') {
            strength = set[1] - '1';
            if (!vSet[strength]) {
                vSet[strength] = true;

                int targetRow = ((n - startChar == 3) || (n - startChar == 4))
                                    ? (startRow == 0 ? 1 : 6)
                                    : startRow;
                auto virus = std::make_unique<Virus>(targetRow, col, n, 'v', strength + 1, player);

                board->units.push_back(std::move(virus));
                std::cout << "Successfully set Virus " << set << std::endl;
            } else {
                std::cout << "You have already set " << set << ".\n";
            }
        } else if (set[0] == 'd' && set[1] >= '1' && set[1] <= '4') {
            strength = set[1] - '1';
            if (!dSet[strength]) {
                dSet[strength] = true;

                int targetRow = ((n - startChar == 3) || (n - startChar == 4))
                                    ? (startRow == 0 ? 1 : 6)
                                    : startRow;
                auto data = std::make_unique<Data>(targetRow, col, n, 'd', strength + 1, player);

                board->units.push_back(std::move(data));
                std::cout << "Successfully set Data " << set << std::endl;
            } else {
                std::cout << "You have already set " << set << ".\n";
            }
        } else {
            std::cout << "Invalid input. Please use format v1, d2, etc.\n";
            continue;
        }
        n++;
        col++;
    }
    std::cout << playerName << " has finished setting their links.\n";
}

int main() {
    std::cout << "Welcome to the game: RAIInet\n";
    std::cout << "Do you need the rulebook for RAIInet? Reply Y or N.\n";
    std::string command;
    std::cin >> command;

    bool rule = true;
    while (rule) {
        if (command == "Y") {
            print_rule();
        } else if (command != "N") {
            std::cout << "Please reply Y or N.\n";
        } else {
            rule = false;
        }
    }

    Board* board = new Blank;
    std::unique_ptr<Player> player1 = std::make_unique<Player>();
    std::unique_ptr<Player> player2 = std::make_unique<Player>();

    print_blank();
    // Player 1 setup (a-h)
    setupPlayer(board, player1.get(), 0, "Player 1", 'a');

    print_blank();
    // Player 2 setup (A-H)
    setupPlayer(board, player2.get(), 0, "Player 2", 'A');


    return 0;
}
