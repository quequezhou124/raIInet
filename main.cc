#include <iostream>
#include <algorithm>
#include <vector>
#include "board.h"
#include "subject.h"
#include "player.h"
#include "textObserver.h"
#include "graphicObserver.h"
#include "unit.h"
#include "link.h"
#include "data.h"
#include "virus.h"
#include "serverports.h"
#include "linkboostAbility.h"
#include "downloadAbility.h"
#include "polarizeAbility.h"
#include "scanAbility.h"
#include "enhanceAbility.h"
#include "lockedAbility.h"
#include "wall.h"
#include <thread>
#include <chrono>

void sleep(int n) {
#ifndef NO_SLEEP
    std::this_thread::sleep_for(std::chrono::seconds(n));
#endif
}

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
    sleep(1);
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
    sleep(1);
}

void check_player(int n) {
    bool check = false;
    std::string s;
    sleep(1);
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "It should be Player " << n << ". Are you player " << n << "? Please reply Y if you are.\n";
    while (!check) {
        std::cin >> s;
        if (s == "Y") {
            check = true;
        } else {
            std::cout << "Please let Player " << n << " reply Y.\n";
            sleep(1);
            continue;
        }
    }
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
        sleep(1);
        std::cout << "Set " << n << std::endl;
        std::string set;
        std::cin >> set;

        int strength = 0;
        if (set.length() == 2 && set[0] == 'v' && set[1] >= '1' && set[1] <= '4') {
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
                continue;
            }
        } else if (set.length() == 2 && set[0] == 'd' && set[1] >= '1' && set[1] <= '4') {
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
                continue;
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
    sleep(1);
}

void battle (Unit *l1, Unit *l2, Player *p1,Player *p2, Board *board) {
    if (l1->getStrength() >= l2->getStrength()) {
        if (dynamic_cast<Data*>(l2)) {
            p2->setdownloadD(p2->getdownloadD() + 1);
            std::cout << "You download a data.\n";
            sleep(1);
            l2->setDownloaded(true);
        } else if (dynamic_cast<Virus*>(l2)) {
            p2->setdownloadV(p2->getdownloadV()+1);
            std::cout << "You download a virus.\n";
            sleep(1);
            l2->setDownloaded(true);
        }
    } else {
        if (dynamic_cast<Data*>(l1)) {
            p1->setdownloadD(p1->getdownloadD() + 1);
            std::cout << "Your data is downloaded by opponent.\n";
            sleep(1);
            l1->setDownloaded(true);
        } else if (dynamic_cast<Virus*>(l1)) {
            p1->setdownloadV(p1->getdownloadV() + 1);
            std::cout << "Your virus is downloaded by opponent.\n";
            sleep(1);
            l1->setDownloaded(true);
        } 
    }
} 

void check_s(Board* board, Unit* l1, Player* player1, Player* player2, Player* owner) {
    if ((player2 == owner && l1->getRow() == 7 && l1->getCol() == 3 && !l1->getLocked()) 
        ||(player2 == owner && l1->getRow() == 7 && l1->getCol() == 4 && !l1->getLocked())) {
        if (dynamic_cast<Data*>(l1)) {
            int n = player2->getdownloadD();
            n++;
            player2->setdownloadD(n);
            l1->setDownloaded(true);
            std::cout << "Player2 has downloaded your Data.\n";
            sleep(1);
        } else if (dynamic_cast<Virus*>(l1)) {
            int n = player2->getdownloadV();
            n++;
            player2->setdownloadV(n);
            l1->setDownloaded(true);
            std::cout << "Player2 has downloaded your Virus.\n";
            sleep(1);
        }
    } else if ((player1 == owner && l1->getRow() == 0 && l1->getCol() == 3 && !l1->getLocked()) 
        ||(player1 == owner && l1->getRow() == 0 && l1->getCol() == 4) && !l1->getLocked()) {
        if (dynamic_cast<Data*>(l1)) {
            int n = player1->getdownloadD();
            n++;
            player1->setdownloadD(n);
            l1->setDownloaded(true);
            std::cout << "Player1 has downloaded your Data.\n";
            sleep(1);
        } else if (dynamic_cast<Virus*>(l1)) {
            int n = player1->getdownloadV();
            n++;
            player1->setdownloadV(n);
            l1->setDownloaded(true);
            std::cout << "Player1 has downloaded your Virus.\n";
            sleep(1);
        }
    }
}

bool check_f (Board* board, Unit* l1, Player* owner, Player* other) {
    Unit *f = board->getFirewall(l1->getRow(), l1->getCol(), owner);
    if (f) {
        if (dynamic_cast<Virus*>(l1)) {
            int n = owner->getdownloadV();
            n++;
            owner->setdownloadV(n);
            l1->setDownloaded(true);
            std::cout << "Your virus move to others' firewall, so you have download it.\n";
            sleep(1);
            return true;
        } else {
            l1->setDisplayed(true);
        }
    }
    return false;
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
    if (check_f (board, l1, owner, other)) {
        return;
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
                sleep(1);
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
                sleep(1);
                continue;
            }

            getlink = true;
        }
        std::cout << "Get link.\n";
        sleep(1);
        std::cout << "Please choose the direction you move. Use format u, d, l, r.\n";
        while (!getdir) {
            std::cin >> dir;

            if ((dir.length() != 1) || ((dir != "u") && (dir != "d") && (dir != "l") && (dir != "r"))) {
                std::cout << "Invalid direction. Choose another one.\n";
                sleep(1);
                continue;
            }

            getdir = true;
        }

        if (player->move(board, movel, dir)) {
            std::cout << "Successful move.\n";
            sleep(1);
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
        sleep(1);
        return true;
    } else if ((player1->getdownloadV() == 4) || (player2->getdownloadD() == 4)) {
        std::cout << "Player2 wins.\n";
        sleep(1);
        return true;
    }
    return false;
}

void setability(Player * player) {
    std::cout << "Please select your abilities. You can pick 5 abilities, up to two for each. "
              << "Below are the optional abilities (please respond with the number, separated by a carriage return).\n"
              << "1. Link Boost: Allows a link to move one additional square per turn, enabling it to jump over obstacles.\n"
              << "2. Firewall: is played targeting any empty square on the board other than the server ports. When passing through this square, opponent links are revealed and, if they are viruses, immediately downloaded by their owner. A square with a firewall with it is usually printed to the display with an “m” for a firewall by player 1 and a “w” for a firewall by player 2. If a link is placed on a firewall, print the link rather than the firewall. Links owned by the player who placed firewall are unaffected by this ability. If an opponent attempts to battle a player’s link which is stationed on the player’s firewall: the firewall effect applies prior to the battle taking place.\n"
              << "3. Download: Instantly downloads an opponent's targeted link without requiring it to be revealed.\n"
              << "4. Polarize: Converts a targeted data link to a virus or a virus to data, maintaining the same strength.\n"
              << "5. Scan: Reveals the type and strength of any targeted link on the field, excluding the player's own links.\n"
              << "6. Enhance:Increases the strength of a specific link by 1.\n"
              << "7. Combat Lock: Prevents a specific link from being downloaded by any method other than combat.\n"
              << "8. Negate: Cancels the opponent's current ability usage.\n";
    sleep(1);
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
        if (a > 8 || a <= 0) {
            std::cout << "Invalid number, choose another one.\n";
            continue;
        } else {
            a--;
            if (abilityset[a][1]) {
                std::cout << "You have choosed this ability twice. Choose another one.\n";
                continue;
            } else if (abilityset[a][0]) {
                player->addAbility(a+1);
                abilityset[a][1] = true;
                std::cout << "Successfully choose.\n";
                n++;
            } else {
                player->addAbility(a+1);
                abilityset[a][0] = true;
                std::cout << "Successfully choose.\n";
                n++;
            }
        }
    }
    player->setabilityNum(5);
}

bool check_negate(Player * owner, Subject* subject, Player * other, std::string operate, int oth) {
    sleep(1);
    if (!(other->findAbility(8))) {
        std::cout << "Your opponent doesn't have the ability to Negate.\n";
        sleep(1);
        return false;
    } else {
        std::cout << "Your opponent have the ability to Negate.\nPlease let your opponent decide whether to use it.";
        sleep(1);
        std::cout << "\n\n\n\n\n\n\n\n\n\n";
        owner->changeturn(0);
        other->changeturn(0);
        subject->notifyObservers();
        check_player(oth);
        owner->changeturn(oth);
        other->changeturn(oth);
        subject->notifyObservers();
        if (oth == 1) {
            other->changeturn(1);
            owner->changeturn(1);
        } else {
            other->changeturn(2);
            owner->changeturn(2);
        }
        subject->notifyObservers();
        if (oth == 2) {
            other->changeturn(1);
            owner->changeturn(1);
        } else {
            other->changeturn(2);
            owner->changeturn(2);
        }
        std::cout << "The other player is going to:\n" << operate << "\nDo you want to use negate? Please reply Y/N.";
        bool decide = false;
        while (!decide) {
            string ans;
            std::cin >> ans;
            if (ans == "Y") {
                std::cout << "Negate used successfully.\n";
                sleep(1);
                return true;
            } else if (ans == "N") {
                return false;
            } else {
                std::cout << "Please reply Y or N.\n";
                sleep(1);
                continue;
            }
        }
    }
}

void UseAbility(Board* board, Player* owner, Player* other, int cur, Subject *subject) {
    int oth;
    if (cur == 1) {
        oth = 2;
    } else {
        oth = 1;
    }
    if (owner->getabilityNum() < 1) {
        std::cout << "You have used all your abilities.\n";
        sleep(1);
        return;
    }
    std::cout << "1.Link Boost 2.Firewall 3.Download 4.Polarize 5.Scan 6.Enhance 7.Combat Lock 8.Negate\n";
    sleep(1);
    std::cout << "The following is what abilities you have: "; owner->printAbility();
    std::cout<< "Do you want to use your ability? Reply Y or N.\n";
    std::string s;
    bool decide = false;
    int a;
    while (!decide) {
        std::cin >> s;
        if (s == "N") {
            return;
        } else if (s != "Y") {
            std::cout << "Invalid input. Please reply Y/N.\n";
            sleep(1);
            continue;
        } else {
            std::cout << "Please reply the number of the ability you want to use.\nReply 0 if you do not want to use any ability.\n";
            bool find = false;
            bool use = false;
            while (!find) {
                if (!(std::cin >> a)){
                    std::cout << "Invalid input, please enter a number between 1 and 8.\n";
                    sleep(1);
                    std::cin.clear();   // 清除错误状态
                    std::cin.ignore(); // 丢弃当前行的输入
                    continue;
                } else if ((a < 0) || (a > 7)) {
                    std::cout << "Invalid input, please enter a number of the ability you have.\n";
                } else if (a == 0) {
                    return;
                } else if (a == 8) {
                    std::cout << "You can not use it right now, please choose another one.\n";
                    continue;
                } else if (!(owner->findAbility(a))) {
                    std::cout << "You do not have the ability, please choose another one.\n";
                    continue;
                } else {
                    find = true;
                }
            }
            std::cout << "Get ability number.\n";
            sleep(1);
            int n = 2;
            while (!use) {
                std::cout << "If you want to use another ability, reply 0.\n"
                << "If you want to stop using any ability, reply 1.\n"
                << "If you want to continue, reply 2.\n";
                if (!(std::cin >> n)){
                    std::cout << "Invalid input, please enter a number.\n";
                    sleep(1);
                    std::cin.clear();   // 清除错误状态
                    std::cin.ignore(); // 丢弃当前行的输入
                    continue;
                }
                if (n == 1) {
                    return;
                } else if (n == 0) {
                    std::cout << "1.Link Boost 2.Firewall 3.Download 4.Polarize 5.Scan 6.Enhance 7.Combat Lock 8.Negate\n";
                    sleep(1);
                    std::cout << "The following is what abilities you have: "; owner->printAbility();
                    std::cout<< "Do you want to use your ability? Reply Y or N.\n";
                    break;
                } else if (a == 1) {
                    std::cout << "If you want to use Link Boost, please reply the link you want to boost, like a, A.\n";
                    char link;
                    if (!(std::cin >> link)){
                        std::cout << "Invalid input, please enter a link, like a, A.\n";
                        std::cin.clear();   // 清除错误状态
                        std::cin.ignore(); // 丢弃当前行的输入
                        continue;
                    } else {
                        Unit* l = board->find_unit(link);
                        if (!l) {
                            std::cout << "Link is not found. Choose another one.\n";
                            continue;
                        } else {
                            char name = l->getName();
                            std::string str(1, name);
                            std::string operate = "Use Link Boost on " + str;
                            bool useNegate = check_negate(owner, subject, other, operate, oth);
                            owner->changeturn(0);
                            other->changeturn(0);
                            subject->notifyObservers();
                            check_player(cur);
                            owner->changeturn(cur);
                            other->changeturn(cur);
                            linkboostAbility func{};
                            subject->notifyObservers();
                            if (func.useAbility(owner, link, board, useNegate)) {
                                std::cout << "Used successfully.\n";
                                sleep(1);
                                if (useNegate) {
                                    other->deleteAbility(8);
                                }
                                owner->deleteAbility(1);
                                decide = true;
                                return;
                            } else {
                                std::cout << "Failed using, try again.\n";
                                continue;
                            }
                        }
                    }
                }
                if (a == 2) {
                    std::cout << "If you want to use Fire Wall, please reply the location you want to use. (Left and up is smaller.)\n";
                    int row,col;
                    bool r = false;
                    bool c = false;
                    std::cout << "Please reply the row, number 0-7.\n";
                    while (!r) {
                        if (!(std::cin >> row)){
                            std::cout << "Invalid input, please enter a number.\n";
                            sleep(1);
                            std::cin.clear();   // 清除错误状态
                            std::cin.ignore(); // 丢弃当前行的输入
                            continue;
                        } else if ((row < 0) || (row > 7)) {
                            std::cout << "Invalid number, it should between 0-7. Try again.\n";
                            continue;
                        } else {
                            std::cout << "Get row.\n";
                            r = true;
                        }
                    }
                    sleep(1);
                    std::cout << "Please reply the col, number 0-7.\n";
                    while (!c) {
                        if (!(std::cin >> col)){
                            std::cout << "Invalid input, please enter a number.\n";
                            sleep(1);
                            std::cin.clear();   // 清除错误状态
                            std::cin.ignore(); // 丢弃当前行的输入
                            continue;
                        } else if ((col < 0) || (col > 7)) {
                            std::cout << "Invalid number, it should between 0-7. Try again.\n";
                            continue;
                        } else {
                            std::cout << "Get col.\n";
                            c = true;
                        }
                    }
                    std::string operate = "Set Firewall on (" + std::to_string(row) + "," + std::to_string(col) + ")";
                    bool useNegate = check_negate(owner, subject, other, operate, oth);
                    owner->changeturn(0);
                    other->changeturn(0);
                    subject->notifyObservers();
                    check_player(cur);
                    owner->changeturn(cur);
                    other->changeturn(cur);
                    subject->notifyObservers();
                    if (board->setFirewall(board, owner, row, col, useNegate)) {
                        std::cout << "Used successfully.\n";
                        sleep(1);
                        if (useNegate) {
                            other->deleteAbility(8);
                        }
                        owner->deleteAbility(2);
                        decide = true;
                        return;
                    } else {
                        std::cout << "Failed using, try again.\n";
                        continue;
                    }
                }
                if (a == 3) {
                    std::cout << "If you want to use Download, please reply the link you want to download, like a, A.\n";
                    char link;
                    if (!(std::cin >> link)){
                        std::cout << "Invalid input, please enter a link, like a, A.\n";
                        std::cin.clear();   // 清除错误状态
                        std::cin.ignore(); // 丢弃当前行的输入
                        continue;
                    } else {
                        Unit* l = board->find_unit(link);
                        if (!l) {
                            std::cout << "Link is not found. Choose another one.\n";
                            continue;
                        } else {
                            char name = l->getName();
                            std::string str(1, name);
                            std::string operate = "Use Download on " + str;
                            bool useNegate = check_negate(owner, subject, other, operate, oth);
                            owner->changeturn(0);
                            other->changeturn(0);
                            subject->notifyObservers();
                            check_player(cur);
                            owner->changeturn(cur);
                            other->changeturn(cur);
                            subject->notifyObservers();
                                    downloadAbility func{};
                            if (func.useAbility(owner, other, link, board, useNegate)) {
                                if (useNegate) {
                                    other->deleteAbility(8);
                                }
                                if (owner->deleteAbility(3)) std::cout << "Successfully used.\n"; 
                                sleep(1);
                                decide = true;
                                return;
                            } else {
                                std::cout << "Failed using, try again.\n";
                                continue;
                            }
                        }
                    }
                }
                if (a == 4) {
                    std::cout << "If you want to use Polarize, please reply the link, like a, A.\n";
                    char link;
                    if (!(std::cin >> link)){
                        std::cout << "Invalid input, please enter a link, like a, A.\n";
                        sleep(1);
                        std::cin.clear();   // 清除错误状态
                        std::cin.ignore(); // 丢弃当前行的输入
                        continue;
                    } else {
                        Unit* l = board->find_unit(link);
                        if (!l) {
                            std::cout << "Link is not found. Choose another one.\n";
                            continue;
                        } else {
                            char name = l->getName();
                            std::string str(1, name);
                            std::string operate = "Use Polarize on " + str;
                            bool useNegate = check_negate(owner, subject, other, operate, oth);
                            owner->changeturn(0);
                            other->changeturn(0);
                            subject->notifyObservers();
                            check_player(cur);
                            owner->changeturn(cur);
                            other->changeturn(cur);
                            subject->notifyObservers();
                            polarizeAbility func{};
                            if (func.useAbility(link, board, useNegate)) {
                                std::cout << "Used successfully.\n";
                                sleep(1);
                                if (useNegate) {
                                    other->deleteAbility(8);
                                }
                                owner->deleteAbility(4);
                                decide = true;
                                return;
                            } else {
                                std::cout << "Failed using, try again.\n";
                                continue;
                            }
                        }
                    }
                }
                if (a == 5) {
                    std::cout << "If you want to use Scan, please reply the link you want to scan, like a, A.\n";
                    char link;
                    if (!(std::cin >> link)){
                        std::cout << "Invalid input, please enter a link, like a, A.\n";
                        sleep(1);
                        std::cin.clear();   // 清除错误状态
                        std::cin.ignore(); // 丢弃当前行的输入
                        continue;
                    } else {
                        Unit* l = board->find_unit(link);
                        if (!l) {
                            std::cout << "Link is not found. Choose another one.\n";
                            continue;
                        } else {
                            char name = l->getName();
                            std::string str(1, name);
                            std::string operate = "Use Scan on " + str;
                            bool useNegate = check_negate(owner, subject, other, operate, oth);
                            owner->changeturn(0);
                            other->changeturn(0);
                            subject->notifyObservers();
                            check_player(cur);
                            owner->changeturn(cur);
                            other->changeturn(cur);
                            subject->notifyObservers();
                            scanAbility func{};
                            if (func.useAbility(owner, other, link, board, useNegate)) {
                                std::cout << "Used successfully.\n";
                                sleep(1);
                                if (useNegate) {
                                    other->deleteAbility(8);
                                }
                                owner->deleteAbility(5);
                                decide = true;
                                return;
                            } else {
                                std::cout << "Failed using, try again.\n";
                                continue;
                            }
                        }
                    }
                }
                if (a == 6) {
                    std::cout << "If you want to use Enhance, please reply the link you want to enhance, like a, A.\n";
                    char link;
                    if (!(std::cin >> link)){
                        std::cout << "Invalid input, please enter a link, like a, A.\n";
                        sleep(1);
                        std::cin.clear();   // 清除错误状态
                        std::cin.ignore(); // 丢弃当前行的输入
                        continue;
                    } else {
                        Unit* l = board->find_unit(link);
                        if (!l) {
                            std::cout << "Link is not found. Choose another one.\n";
                            continue;
                        } else {
                            char name = l->getName();
                            std::string str(1, name);
                            std::string operate = "Use Enhance on " + str;
                            bool useNegate = check_negate(owner, subject, other, operate, oth);
                            owner->changeturn(0);
                            other->changeturn(0);
                            subject->notifyObservers();
                            check_player(cur);
                            owner->changeturn(cur);
                            other->changeturn(cur);
                            subject->notifyObservers();
                            enhanceAbility func{};
                            if (func.useAbility(owner, link, board, useNegate)) {
                                std::cout << "Used successfully.\n";
                                sleep(1);
                                if (useNegate) {
                                    other->deleteAbility(8);
                                }
                                owner->deleteAbility(6);
                                decide = true;
                                return;
                            } else {
                                std::cout << "Failed using, try again.\n";
                                continue;
                            }
                        }
                    }
                }
                if (a == 7) {
                    std::cout << "If you want to use CombatLock, please reply the link you want to look, like a, A.\n";
                    char link;
                    if (!(std::cin >> link)){
                        std::cout << "Invalid input, please enter a link, like a, A.\n";
                        sleep(1);
                        std::cin.clear();   // 清除错误状态
                        std::cin.ignore(); // 丢弃当前行的输入
                        continue;
                    } else {
                        Unit* l = board->find_unit(link);
                        if (!l) {
                            std::cout << "Link is not found. Choose another one.\n";
                            continue;
                        } else {
                            char name = l->getName();
                            std::string str(1, name);
                            std::string operate = "Use CombatLock on " + str;
                            bool useNegate = check_negate(owner, subject, other, operate, oth);
                            owner->changeturn(0);
                            other->changeturn(0);
                            subject->notifyObservers();
                            check_player(cur);
                            owner->changeturn(cur);
                            other->changeturn(cur);
                            subject->notifyObservers();
                            lockedAbility func{};
                            if (func.useAbility(owner, other, link, board, useNegate)) {
                                std::cout << "Used successfully.\n";
                                sleep(1);
                                if (useNegate) {
                                    other->deleteAbility(8);
                                }
                                owner->deleteAbility(7);
                                decide = true;
                                return;
                            } else {
                                std::cout << "Failed using, try again.\n";
                                continue;
                            }
                        }
                    }
                }
            }
            if (n == 0) {
                continue;
                std::cout << "1.Link Boost 2.Firewall 3.Download 4.Polarize 5.Scan 6.Enhance 7.Combat Lock 8.Negate\n";
                sleep(1);
                std::cout << "The following is what abilities you have: "; owner->printAbility();
                std::cout<< "Do you want to use your ability? Reply Y or N.\n";
            }
        }
    }
}

int main() {
    std::cout << "Welcome to the game: RAIInet\n";
    sleep(1);
    std::cout << "Do you need the rulebook for RAIInet? Reply Y or N.\n";
    std::string command;

    bool rule = true;
    while (rule) {
        std::cin >> command;
        if (command == "Y") {
            print_rule();
            sleep(1);
            rule = false;
        } else if (command != "N") {
            std::cout << "Please reply Y or N.\n";
            sleep(1);
            continue;
        } else {
            rule = false;
            sleep(1);
        }
    }
    // Initial setup
    Board* board = new Board;
    Subject subject{board};
    Player* player1 = new Player();
    Player* player2 = new Player();
    TextObserver* textobserver = new TextObserver(&subject, player1, player2);
    GraphicObserver* graphicobserver = new GraphicObserver(&subject, player1, player2);
    // Player 1 setup (a-h)
    sleep(1);
    check_player(1);
    print_blank();
    sleep(1);
    setupPlayer(board, player1, 0, "Player 1", 'a');
    sleep(1);
    setability(player1);

    // Player 2 setup (A-H)
    sleep(1);
    check_player(2);
    print_blank();
    sleep(1);
    setupPlayer(board, player2, 7, "Player 2", 'A');
    sleep(1);
    setability(player2);

    // Set new decorated board
    subject.setBoard(new Board{board->units}); // Use setBoard to properly assign the new decorated board

    bool win = false;
    while (!win) {
        // Player1 move
        player1->changeturn(0);
        player2->changeturn(0);
        subject.notifyObservers();
        sleep(1);
        check_player(1);
        player1->changeturn(1);
        player2->changeturn(1);
        subject.notifyObservers();
        sleep(1);
        UseAbility(subject.getBoard(), player1, player2, 1, &subject);
        player1->changeturn(1);
        player2->changeturn(1);
        subject.notifyObservers();
        sleep(1);
        moveit(player1, "Player1", subject.getBoard(), player1, player2);
        win = check_win(player1, player2);
        
        if (win) break;
        player1->changeturn(0);
        player2->changeturn(0);
        subject.notifyObservers();
        // Player2 move
        sleep(1);
        check_player(2);
        player1->changeturn(2);
        player2->changeturn(2);
        subject.notifyObservers();
        sleep(1);
        UseAbility(subject.getBoard(), player2, player1, 2, &subject);
        player1->changeturn(2);
        player2->changeturn(2);
        subject.notifyObservers();
        sleep(1);
        moveit(player2, "Player2", subject.getBoard(), player1, player2);
        win = check_win(player1, player2);
        
    }

    // Cleanup
    for (auto unit : subject.getBoard()->units) {
        delete unit;
    }
    delete textobserver;  // Detach and delete observer
    delete graphicobserver; 
}
