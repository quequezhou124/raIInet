#include <iostream>
#include <memory>
#include <algorithm>
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
        std::cout << "Set " << n << endl;
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
                auto virusp = std::make_unique<Virus>(targetRow, col, strength + 1, n, false, false, false);
                auto virusb = std::make_unique<Virus>(targetRow, col, strength + 1, n, false, false, false);
                player->links.push_back(std::move(virusp));
                board->units.push_back(std::move(virusb));
                std::cout << "Successfully set Virus " << set << std::endl;
                n++;
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
                auto datap = std::make_unique<Data>(targetRow, col, strength + 1, n, false, false, false);
                auto datab = std::make_unique<Data>(targetRow, col, strength + 1, n, false, false, false);
                player->links.push_back(std::move(datap));
                board->units.push_back(std::move(datab));
                std::cout << "Successfully set Data " << set << std::endl;
                n++;
            } else {
                std::cout << "You have already set " << set << ".\n";
            }
        } else {
            std::cout << "Invalid input. Please use format v1, d2, etc.\n";
            continue;
        }
        col++;
    }
    std::cout << playerName << " has finished setting their links.\n";
}

bool operator==(const std::unique_ptr<Link> &lhs, const std::unique_ptr<Unit> &rhs) {
    return lhs->getName() == rhs->getName();
}

void moveit (Player * player, std::string playername, Board * b) {
    Board * board = b;
    bool moving = true;
    while (moving) {
        bool getlink = false;
        bool getdir = false;
        std::string movelink;
        std::string dir;
        std::cout << playername << " please choose the link you move. Use format a, A, b, B, etc.\n";
        std::unique_ptr<Unit> movel;
        while (!getlink) {
            std::cin >> movelink;
            if (movelink.length() != 1 || !isalpha(movelink[0])) {
                std::cout << "Invalid link format. Use a single character (e.g., a, A).\n";
                continue;
            }
            // 查找单元
            movel = board->find_unit(movelink[0]); // 假设 find_unit 返回 std::unique_ptr<Unit>
            if (!movel) {
                std::cout << "Link not found on board. Choose another one.\n";
                continue;
            }
            // 检查链接是否属于玩家
            Unit* rawUnit = movel.get(); // 获取底层原始指针
            if (std::find(player->links.begin(), player->links.end(), movel) == player->links.end()) {
                std::cout << "The link does not belong to you. Choose another one.\n";
                continue;
            }
            getlink = true;
        }
        std::cout << "Please choose the direction you move. Use format u, d, l, r.\n";
        while (!getdir) {
            std::cin >> dir;
            if ((dir.length() != 1) || ((dir != "u") && (dir != "d") && (dir != "l") && (dir != "r"))) {
                std::cout << "Invalid direction. Choose another one.\n";
                continue;
            } else {
                getdir = true;
            }
        }
        if (player->move(movel, dir)) {
            std::cout << "Successful move.\n";
            moving = false;
        } else {
            std::cout << "Moving failed. Choose again.\n";
            getlink = false;
            getdir = false;
            continue;
        }
    }
}

bool check_win (Player * player1, Player * player2) {
    if ((player1->getdownloadD() == 4) ||  (player2->getdownloadV() == 4)){
        std::cout << "Player1 wins.\n";
        return true;
    } else if ((player1->getdownloadV() == 4) || (player2->getdownloadD() == 4)) {
        std::cout << "Player2 wins.\n";
        return true;
    }
}

int main() {
    std::cout << "Welcome to the game: RAIInet\n";
    std::cout << "Do you need the rulebook for RAIInet? Reply Y or N.\n";
    std::string command;

    bool rule = true;
    while (rule) {
        std::cin >> command;
        if (command == "Y") {
            print_rule();
            rule = false;
        } else if (command != "N") {
            std::cout << "Please reply Y or N.\n";
            continue;
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
    
    bool win = false; 
    while (!win) {
        //Player1 move
        moveit(player1.get(), "player1", board);
        win = check_win(player1.get(), player2.get());
        //Player2 move
        moveit(player2.get(), "player2", board);
        win = check_win(player1.get(), player2.get());
    }
    
    return 0;
}
