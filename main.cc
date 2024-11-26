#include <iostream>
#include <algorithm>
#include <vector>
#include "board.h"
#include "subject.h"
#include "player.h"
#include "textObserver.h"
#include "unit.h"
#include "link.h"
#include "data.h"
#include "virus.h"
#include "serverports.h"

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
        std::cout << "Set " << n << std::endl;
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
                Virus* virus = new Virus(targetRow, col, strength + 1, n, false, false, false, false);
                player->links.push_back(virus);
                board->units.push_back(virus);
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
                Data* data = new Data(targetRow, col, strength + 1, n, false, false, false, false);
                player->links.push_back(data);
                board->units.push_back(data);
                std::cout << "Successfully set Data " << set << ".\n";
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
    if (startRow == 0) {
        Serverports* serverports1 = new Serverports {0, 3, 0, 'S', false, false, false, false} ;
        Serverports* serverports2 = new Serverports {0, 4, 0, 'S', false, false, false, false} ;
        board->units.push_back(serverports1);
        board->units.push_back(serverports2);
    } else if (startRow == 7) {
        Serverports* serverports1 = new Serverports {7, 3, 0, 'S', false, false, false, false} ; 
        Serverports* serverports2 = new Serverports {7, 4, 0, 'S', false, false, false, false} ;
        board->units.push_back(serverports1);
        board->units.push_back(serverports2);
    }
    std::cout << playerName << " has finished setting their links.\n";
}

void battle (Unit *l1, Unit *l2, Player *p1,Player *p2, Board *board) {
    if (l1->getStrength() >= l2->getStrength()) {
        if (dynamic_cast<Data*>(l2)) {
            p1->setdownloadD(p1->getdownloadD() + 1);
            std::cout << "You download a data.\n";
            l2->setDownloaded(true);
        } else if (dynamic_cast<Virus*>(l2)) {
            p1->setdownloadV(p1->getdownloadV()+1);
            std::cout << "You download a virus.\n";
            l2->setDownloaded(true);
        }
    } else {
        if (dynamic_cast<Data*>(l1)) {
            p2->setdownloadD(p2->getdownloadD() + 1);
            std::cout << "Your data is downloaded by opponent.\n";
            l1->setDownloaded(true);
        } else if (dynamic_cast<Virus*>(l1)) {
            p2->setdownloadV(p2->getdownloadV() + 1);
            std::cout << "Your virus is downloaded by opponent.\n";
            l1->setDownloaded(true);
        } 
    }
} 

void check_s(Board* board, Unit* l1, Player* player1, Player* player2, Player* owner) {
    if ((player2 == owner && l1->getRow() == 7 && l1->getCol() == 3) 
        ||(player2 == owner && l1->getRow() == 7 && l1->getCol() == 4)) {
        if (dynamic_cast<Data*>(l1)) {
            int n = player2->getdownloadD();
            n++;
            player2->setdownloadD(n);
            l1->setDownloaded(true);
            std::cout << "Player2 has downloaded your Data.\n";
        } else if (dynamic_cast<Virus*>(l1)) {
            int n = player2->getdownloadV();
            n++;
            player2->setdownloadV(n);
            l1->setDownloaded(true);
            std::cout << "Player2 has downloaded your Virus.\n";
        }
    } else if ((player1 == owner && l1->getRow() == 0 && l1->getCol() == 3) 
        ||(player1 == owner && l1->getRow() == 0 && l1->getCol() == 4)) {
        if (dynamic_cast<Data*>(l1)) {
            int n = player1->getdownloadD();
            n++;
            player1->setdownloadD(n);
            l1->setDownloaded(true);
            std::cout << "Player1 has downloaded your Data.\n";
        } else if (dynamic_cast<Virus*>(l1)) {
            int n = player1->getdownloadV();
            n++;
            player1->setdownloadV(n);
            l1->setDownloaded(true);
            std::cout << "Player1 has downloaded your Virus.\n";
        }
    }
}

void check_battle_s(Board* board, Unit* l1, Player* player1, Player* player2) {
    Player* owner;
    Player* other;
    if (std::find(player1->links.begin(), player1->links.end(), l1) == player1->links.end()) {
        owner = player1;
        other = player2;
    } else {
        owner = player2;
        other = player1;
    }
    Unit* l2 = board->getAnotherUnit(l1->getRow(), l1->getCol(), l1, owner);
    if (!l2) {
        check_s(board, l1, player1, player2, owner);
        return;
    }
    if (dynamic_cast<Data*>(l2) || dynamic_cast<Virus*>(l2)) {
        battle(l1, l2, owner, other, board);
        return;
    }
}

void moveit(Player* player, const std::string& playername, Board* board, Player* player1, Player* player2) {
    bool moving = true;

    while (moving) {
        bool getlink = false;
        bool getdir = false;
        std::string movelink;
        std::string dir;
        Unit* movel = nullptr;

        std::cout << playername << " please choose the link you move. Use format a, A, b, B, etc.\n";
        while (!getlink) {
            std::cin >> movelink;
            if (movelink.length() != 1 || !isalpha(movelink[0])) {
                std::cout << "Invalid link format. Use a single character (e.g., a, A).\n";
                continue;
            }

            movel = board->find_unit(movelink[0]);
            if (!movel) {
                std::cout << "Link not found on board. Choose another one.\n";
                continue;
            }

            if (movel->getDownloaded()) {
                std::cout << "Link is already downloaded. Choose another one.\n";
                continue;
            }

            // 检查链接是否属于玩家
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
            }

            getdir = true;
        }

        if (player->move(board, movel, dir)) {
            std::cout << "Successful move.\n";
            check_battle_s(board, movel, player1, player2);
            moving = false;
        } else {
            std::cout << "Moving failed. Choose again.\n";
            getlink = false;
            getdir = false;
            continue;
        }
    }
}

bool check_win(Player* player1, Player* player2) {
    if ((player1->getdownloadD() == 4) || (player2->getdownloadV() == 4)) {
        std::cout << "Player1 wins.\n";
        return true;
    } else if ((player1->getdownloadV() == 4) || (player2->getdownloadD() == 4)) {
        std::cout << "Player2 wins.\n";
        return true;
    }
    return false;
}

void setability(Player * player) {
    std::cout << "Please select your abilities. You can pick 5 abilities, up to two for each. "
              << "Below are the optional abilities (please respond with the number, separated by a carriage return):\n"
              << "1. Link Boost: Allows a link to move one additional square per turn, enabling it to jump over obstacles.\n"
              << "2. Firewall: \n"
              << "3. Download: Instantly downloads an opponent's targeted link without requiring it to be revealed.\n"
              << "4. Polarize: Converts a targeted data link to a virus or a virus to data, maintaining the same strength.\n"
              << "5. Scan: Reveals the type and strength of any targeted link on the field, excluding the player's own links.\n"
              << "6. Negate: Cancels the opponent's current ability usage.\n"
              << "7. Combat Lock: Prevents a specific link from being downloaded by any method other than combat.\n"
              << "8. Enhance: Increases the strength of a specific link by 1.\n";
    bool abilityset[8][2]= {{false, false}, {false, false}, {false, false}, {false, false}, {false, false}, {false, false}, {false, false}, {false, false}};
    int a;
    int n = 0;
    while (n < 5) {
        if (!(std::cin >> a)) { // 检查输入是否有效
            std::cout << "Invalid input, please enter a number between 1 and 8.\n";
            std::cin.clear();   // 清除错误状态
            std::cin.ignore(); // 丢弃当前行的输入
            continue;
        }
        if (a > 8 || a < 0) {
            std::cout << "Invalid number, choose another one.\n";
            continue;
        } else {
            a--;
            if (abilityset[a][1]) {
                std::cout << "You have choosed this ability twice. Choose another one.\n";
                continue;
            } else if (abilityset[a][0]) {
                player->addAbilityNum(a);
                abilityset[a][1] = true;
                std::cout << "Successfully choose.\n";
                n++;
            } else {
                player->addAbilityNum(a);
                abilityset[a][0] = true;
                std::cout << "Successfully choose.\n";
                n++;
            }
        }
    }
    player->setabilityNum(5);
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
    // Initial setup
    Board* board = new Board;
    Subject subject{board};
    Player* player1 = new Player();
    Player* player2 = new Player();
    TextObserver* observer = new TextObserver(&subject, player1, player2);

    // Player 1 setup (a-h)
    print_blank();
    setupPlayer(board, player1, 0, "Player 1", 'a');
    setability(player1);

    // Player 2 setup (A-H)
    print_blank();
    setupPlayer(board, player2, 7, "Player 2", 'A');
    setability(player2);

    // Set new decorated board
    subject.setBoard(new Board{board->units}); // Use setBoard to properly assign the new decorated board

    bool win = false;
    while (!win) {
        // Player1 move
        
        subject.notifyObservers();
        moveit(player1, "Player1", subject.getBoard(), player1, player2);
        win = check_win(player1, player2);
        
        if (win) break;
        player1->changeturn(false);

        // Player2 move
        subject.notifyObservers();
        moveit(player2, "Player2", subject.getBoard(), player1, player2);
        win = check_win(player1, player2);
        player1->changeturn(true);
        
    }

    // Cleanup
    for (auto unit : subject.getBoard()->units) {
        delete unit;
    }
    delete board;
    delete observer;  // Detach and delete observer
    delete player1;
    delete player2;
}
