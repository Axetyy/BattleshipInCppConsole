void rules()
{
    /**

    ///////////////////////////////////////////////////////
    Welcome to the game Battleship! Alpha version 0.2.0
    Patch Notes 0.2.0
    - Improved AI decision making
    - Improved visibility
    - Fixed a bug where the enemy Destroyer wouldnt show up

    Patch Notes 0.1.1 ALPHA RELEASE 1:
    - The game works now
    - Fixed bugs related to AI
    - Fixed Positioning Indices
    - Debug mode for Testers

    Patch Notes 0.1.0 BETA:
    - Intelligent Algorithm now in place.
    - Memory optimisations
    - Interactive Loading of the Elements;
    - Easier to read code
    - Bug Fixes

    Patch Notes 0.0.2 PRE-BETA:
    - Added better explanations
    - Fixed bugs related to Ship Placement
    - Allowed for more free placement of ships
    - More error messages
    **/
}
#include <stdlib.h>
#include <utility>
#include <chrono>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <set>
#include <thread>

using namespace std;

vector<string> v = {"Destroyer", "Submarine", "Cruiser", "Battleship", "Carrier"};
int matP1Ocean[10][10], matP2Ocean[10][10], matP1Target[10][10], matP2Target[10][10];
/// 1-Destroyer(2) 2-Submarine(3) 3-Cruiser(3) 4 -Battleship(4) 5-Carrier(5)

class Ship
{
public:
    vector<string> v = {"Destroyer", "Submarine", "Cruiser", "Battleship", "Carrier"};
    int typeShip;
    bool isAI = false;
    bool okShip = true;
    int healthPoints;
    bool dirHV;
    int pozI, pozJ;
    bool dirLR;
    Ship(int Type, int pozi, int pozj, bool dirVO, bool DirLR)
    {
        typeShip = Type;
        pozJ = pozj, pozI = pozi, dirHV = dirVO, dirLR = DirLR;
    }
    void setType(int Type)
    {

        switch (Type)
        {
        case 1:
            this->healthPoints = 2;
            break;
        case 2:
            this->healthPoints = 3;
            break;
        case 3:
            this->healthPoints = 3;
            break;
        case 4:
            this->healthPoints = 4;
            break;
        case 5:
            this->healthPoints = 5;
            break;
        }
    }
    void Placement(int mat[10][10])
    {
        this->okShip = true;
        if (pozI > 7 || pozJ >= 8)
        {
            if (!this->isAI)
                cout << "\n\n  ! Invalid positioning ! \n"
                     << "Cause:Coordinates incorrect \n\n The ship causing the error is " << this->v[typeShip - 1] << "\n\n";
            this->okShip = false;
        }
        else
        {

            if (this->dirHV == 1)
            {
                if (this->dirLR == 1)
                {
                    if (pozI + this->healthPoints > 8)
                    {
                        if (!this->isAI)
                            cout << "\n\n  ! Invalid positioning ! \n"
                                 << "Cause:Out of bounds\n\n The ship causing the error is " << this->v[typeShip - 1] << "\n\n";
                        this->okShip = false;
                    }
                    else
                    {
                        bool ok = true;
                        for (int i = pozI; i < pozI + this->healthPoints; i++)
                        {
                            if (mat[i][pozJ] != 0)
                                ok = false;
                        }
                        if (ok)
                        {
                            for (int i = pozI; i < pozI + this->healthPoints; i++)
                            {
                                mat[i][pozJ] = this->typeShip;
                            }
                        }
                        else
                        {
                            if (!this->isAI)
                                cout << "\n\n  ! Invalid positioning ! \n"
                                     << "Cause:Overlapping\n\n The ship causing the error is " << this->v[typeShip - 1] << "\n\n";
                            this->okShip = false;
                        }
                    }
                }
                else
                {
                    if (pozI - this->healthPoints < 0)
                    {
                        if (!this->isAI)
                            cout << "\n\n  ! Invalid positioning ! \n"
                                 << "Cause:Out of bounds\n\n The ship causing the error is " << this->v[typeShip - 1] << "\n\n";
                        this->okShip = false;
                    }
                    else
                    {
                        bool ok = true;
                        for (int i = pozI; i > pozI - this->healthPoints; i--)
                        {
                            if (mat[i][pozJ] != 0)
                                ok = false;
                        }
                        if (ok)
                        {
                            for (int i = pozI; i > pozI - this->healthPoints; i--)
                                mat[i][pozJ] = this->typeShip;
                        }
                        else
                        {
                            if (!this->isAI)
                                cout << "\n\n  ozI-this->health_Pozit! Invalid positioning ! \n"
                                     << "Cause:Overlapping\n\n The ship causing the error is " << this->v[typeShip - 1] << "\n\n";
                            this->okShip = false;
                        }
                    }
                }
            }
            else
            {
                if (this->dirLR == 0)
                {
                    if (pozJ + this->healthPoints > 9)
                    {
                        if (!this->isAI)
                            cout << "\n\n  ! Invalid positioning ! \n"
                                 << "Cause:Out of bounds\n\n The ship causing the error is " << this->v[typeShip - 1] << "\n\n";
                        this->okShip = false;
                    }
                    else
                    {
                        bool ok = true;
                        for (int j = pozJ; j < pozJ + this->healthPoints; j++)
                        {
                            if (mat[pozI][j] != 0)
                                ok = false;
                        }
                        if (ok)
                        {
                            for (int j = pozJ; j < pozJ + this->healthPoints; j++)
                            {
                                mat[pozI][j] = this->typeShip;
                            }
                        }
                        else
                        {
                            if (!this->isAI)
                                cout << "\n\n ! Invalid positioning ! \n"
                                     << "Cause:Overlapping\n\n The ship causing the error is " << this->v[typeShip - 1] << "\n\n";
                            this->okShip = false;
                        }
                    }
                }
                else
                {
                    if (pozJ - this->healthPoints < 0)
                    {
                        if (!this->isAI)
                            cout << "\n\n ! Invalid positioning ! \n"
                                 << "Cause:Out of bounds\n\n The ship causing the error is " << this->v[typeShip - 1] << "\n\n";
                        this->okShip = false;
                    }
                    else
                    {
                        bool ok = true;
                        for (int j = pozJ; j > pozJ - this->healthPoints; j--)
                        {
                            if (mat[pozI][j] != 0)
                                ok = false;
                        }
                        if (ok)
                        {
                            for (int j = pozJ; j > pozJ - this->healthPoints; j--)
                                mat[pozI][j] = this->typeShip;
                        }
                        else
                        {
                            if (!this->isAI)
                                cout << "\n\n ! Invalid positioning ! \n"
                                     << "Cause:Overlapping\n\n The ship causing the error is " << this->v[typeShip - 1] << "\n\n";
                            this->okShip = false;
                        }
                    }
                }
            }
        }
        return;
    }
    void gotHit(int x, int y, int mat[10][10])
    {
        mat[x][y] = -1 * mat[x][y];
        this->healthPoints--;
    }
    ~Ship() = default;
};
void genMat(int mat[10][10])
{
    for (int i = 0; i < 8; i++)
        mat[i][0] = i, mat[0][i] = i;
    mat[0][8] = 8;
}
void afisareMat(int mat[10][10])
{
    bool negative = false;
    for (int i = 1; i < 8; i++)
    {
        for (int j = 1; j < 9; j++)
        {
            if (mat[i][j] == -1)
                negative = true;
        }
    }
    cout << '\n';
    if (negative)
    {
        for (int i = 0; i < 8; i++)
        {

            for (int j = 0; j < 9; j++)
            {

                if (j == 0)
                {
                    cout << (char)(mat[i][j] - 1 + 'A') << "    ";
                }
                else if (i == 0 && j == 0)
                    cout << "  ";
                else
                {
                    if (mat[i][j] == -9)
                    {
                        cout << 'M' << " ";
                    }
                    else
                        cout << mat[i][j] << " ";
                }
            }
            if (i == 0)
                cout << "\n";
            cout << '\n';
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {

            for (int j = 0; j < 9; j++)
            {

                if (j == 0)
                {
                    cout << (char)(mat[i][j] - 1 + 'A') << "    ";
                }
                else if (i == 0 && j == 0)
                    cout << "  ";
                else
                {
                    if (mat[i][j] == -9)
                    {
                        cout << 'M' << " ";
                    }
                    else
                        cout << mat[i][j] << " ";
                }
            }
            if (i == 0)
                cout << "\n";
            cout << '\n';
        }
    }
    cout << "\n";
}
void missTable(int i, int j, int mat[10][10], int mat2[10][10], bool Miss)
{
    if (Miss == 1)
        mat[i][j] = -9;
    else
        mat[i][j] = mat2[i][j];
}
void sleep(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
void Question()
{
    cout << "\n Ocean Table \n";
    afisareMat(matP1Ocean);
    cout << "\n";
    cout << " Target Table \n";
    afisareMat(matP1Target);
    cout << "\n\n";
}

void genRandomShip(Ship *ptr)
{
    ptr->isAI = true;
    int pozI = rand() % 7 + 1, pozJ = rand() % 8 + 1, ok1 = rand() % 2, ok2 = rand() % 2;
    Ship *ptr1 = new Ship(ptr->typeShip, pozI, pozJ, ok1, ok2);
    ptr1->setType(ptr->typeShip);
    ptr1->isAI = true;
    ptr1->Placement(matP2Ocean);
    while (ptr1->okShip == false)
    {
        delete ptr1;
        int pozI = rand() % 7 + 1, pozJ = rand() % 8 + 1, ok1 = rand() % 2, ok2 = rand() % 2;
        Ship *ptr1 = new Ship(ptr->typeShip, pozI, pozJ, ok1, ok2);
        ptr1->isAI = true;
        ptr1->setType(ptr->typeShip);
        ptr1->Placement(matP2Ocean);
    }
    ptr = ptr1;
    delete ptr1;
}
bool inMat(int i, int j)
{
    return (i > 0 && i < 8 && j > 0 && j < 9);
}
int randomCoords()
{
    int pozI = rand() % 7 + 1;
    int pozJ = rand() % 8 + 1;
    return (pozI * 10) + pozJ;
}
int randomBoundcoords(int Bound, int I, int J)
{
    int p, pozI, pozJ, k, put, ok;
    if (Bound != 0)
    {
        ok = rand() % 2;
        k = rand() % 10 + 1;
        put = pow(-1, k);
        pozI = I + ok * (put * ((rand() % Bound) + 1));
        ok = rand() % 2;
        p = rand() % 10;
        put = pow(-1, p);
        pozJ = J + ok * (put * ((rand() % Bound) + 1));
        while (pozI <= 0 || pozI > 7)
        {
            ok = rand() % 2;
            k = rand() % 10 + 1;
            put = pow(-1, k);
            pozI = I + ok * (put * ((rand() % Bound) + 1));
            ;
        }
        while (pozJ <= 0 || pozJ > 8)
        {
            ok = rand() % 2;
            p = rand() % 10;
            put = pow(-1, p);
            pozJ = J + ok * (put * ((rand() % Bound) + 1));
        }
        return pozI * 10 + pozJ;
    }
    else
        return I * 10 + J;
}
Ship *ships[10];
int cntAI = 5, cntPlayer = 5, type;
deque<int> nextHits;
int condensedCoords = 0;
bool succesfullVec = true;
const int di[] = {1, -1, 0, 0};
const int dj[] = {0, 0, -1, 1};
int matTemp[11][11];
void generateShips(int type)
{
    for (int i = 1; i < 8; i++)
    {
        for (int j = 1; j < 9; j++)
        {
            if (matP1Ocean[i][j] == type || matP1Ocean[i][j] == -1 * type)
                matTemp[i][j] = matP1Ocean[i][j];
            else
                matTemp[i][j] = 0;
        }
    }
}
set<int> neighbors;

void genHit(int pozI, int pozJ, int type, int AIlevel, int roundNumber)
{
    int iv = pozI, jv = pozJ;
    for (int k = 0; k < 4; k++)
    {
        int I = iv + di[k], J = jv + dj[k];
        if ((matTemp[I][J] == type || matTemp[I][J] == -1 * type) && inMat(I, J) && matTemp != 0)
        {
            matTemp[I][J] = 0;
            genHit(I, J, type, AIlevel, roundNumber);
            if (matP2Target[I][J] != type)
            {
                float Formula = AIlevel + (roundNumber / 10);
                bool Opportunity = (Formula >= rand() % 20 + 1);
                if (Opportunity)
                    neighbors.insert(I * 10 + J);
            }
        }
    }
}
void AIChooseHits(int &AIlevel, int roundNumber)
{
    neighbors.clear();
    int pozI, pozJ;
    if (nextHits.empty() && roundNumber > 1)
    {
        condensedCoords = randomCoords();
        pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
        while (matP2Target[pozI][pozJ] != 0)
        {
            condensedCoords = randomCoords();
            pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
        }
        nextHits.push_back(condensedCoords);
    }
    if (roundNumber % 7 == 0 && AIlevel < 20)
        AIlevel++;
    float Formula = AIlevel + (roundNumber / 10);
    bool Opportunity;
    if (Formula >= rand() % 20 + 1)
        Opportunity = true;
    else
        Opportunity = false;
    if (roundNumber == 1)
    {
        condensedCoords = randomCoords();
        pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
        while (matP2Target[pozI][pozJ] != 0)
        {
            condensedCoords = randomCoords();
            pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
        }
        nextHits.push_back(condensedCoords);
    }
    else
    {
        condensedCoords = nextHits.front();
    }
    pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
    type = matP1Ocean[pozI][pozJ];
    if (Opportunity == false)
    {

        if (type > 0)
        {
            pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
            missTable(pozI, pozJ, matP2Target, matP1Ocean, 0);
            if (ships[type]->healthPoints > 0)
                ships[type]->gotHit(pozI, pozJ, matP1Ocean);
            if (ships[type]->healthPoints == 0)
            {
                cntPlayer--;
                cout << "\n You lost the " << v[type - 1] << " to the opponent!\n";
            }
            condensedCoords = randomBoundcoords(1, pozI, pozJ);
            pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
            while (matP2Target[pozI][pozJ] != 0)
            {
                condensedCoords = randomBoundcoords(1, pozI, pozJ);
                pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
            }
            nextHits.push_back(condensedCoords);
        }
        else
        {
            pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
            missTable(pozI, pozJ, matP2Target, matP1Ocean, 1);
            missTable(pozI, pozJ, matP1Ocean, matP2Target, 1);
            condensedCoords = randomCoords();
            pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
            while (matP2Target[pozI][pozJ] != 0)
            {
                condensedCoords = randomCoords();
                pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
            }
            nextHits.push_back(condensedCoords);
        }
    }
    else
    {
        if (type > 0)
        {
            pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
            missTable(pozI, pozJ, matP2Target, matP1Ocean, 0);
            ships[type]->gotHit(pozI, pozJ, matP1Ocean);
            if (ships[type]->healthPoints == 0)
            {
                cntPlayer--;
                cout << "\n You lost the " << v[type - 1] << " to the opponent!\n";
            }
            generateShips(type);
            genHit(pozI, pozJ, type, AIlevel, roundNumber);
            if (neighbors.empty() != true)
            {
                for (auto x : neighbors)
                {
                    if (matP1Ocean[x / 10][x % 10] > 0)
                        nextHits.push_back(x);
                }
            }
            else
            {
                condensedCoords = randomBoundcoords(2, pozI, pozJ);
                pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
                while (matP2Target[pozI][pozJ] != 0)
                {
                    condensedCoords = randomBoundcoords(2, pozI, pozJ);
                    pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
                }
                nextHits.push_back(condensedCoords);
            }
        }
        else
        {
            pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
            missTable(pozI, pozJ, matP2Target, matP1Ocean, 1);
            missTable(pozI, pozJ, matP1Ocean, matP2Target, 1);
            condensedCoords = randomBoundcoords(2, pozI, pozJ);
            pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
            while (matP2Target[pozI][pozJ] != 0)
            {
                condensedCoords = randomBoundcoords(2, pozI, pozJ);
                pozI = condensedCoords / 10, pozJ = condensedCoords % 10;
            }
            nextHits.push_back(condensedCoords);
        }
    }
}
int main()
{
    nextHits.clear();
    genMat(matP1Ocean);
    genMat(matP2Ocean);
    genMat(matP1Target);
    genMat(matP2Target);
    srand(time(NULL));
    int pozi, pozj, ok1, ok2;
    string input;
    cout << "Loading ships...\n";
    ifstream fin("input.in");
    int frcv[10] = {0};
    int n = 5;
    for (int i = 1; i <= n; i++)
    {
        fin >> type >> input >> ok1 >> ok2;
        fin.get();
        pozi = (toupper(input[0]) - 'A') + 1;
        pozj = (input[1] - '0');
        sleep(rand() % 3 + 1 - 1 / 2);
        frcv[type]++;
        if (frcv[type] > 1)
        {
            cout << "\nDon't cheat! You cant have more than one ship of each type!! \n";
            return 0;
        }
        else
            ships[i] = new Ship(type, pozi, pozj, ok1, ok2);
        ships[i]->setType(ships[i]->typeShip);
        ships[i]->Placement(matP1Ocean);
        ships[i]->isAI = false;
        if (ships[i]->okShip == 0)
        {
            return 0;
        }
        cout << "\n Your " << v[ships[i]->typeShip - 1] << " has been initialized! \n";
    }
    cout << "\n All ships loaded successfully! \n";
    system("cls");
    Question();
    Ship *AiShips[10];
    for (int i = 0; i <= n; i++)
    {
        AiShips[i] = new Ship(i + 1, 1, 1, 1, 1);
        genRandomShip(AiShips[i]);
    }
    char rasp;
    int temp[1001];
    int AILevel = 0;
    sleep(rand() % 3);
    cout << "\n /////////////////\nInput an difficulty level from 1-20,\n 1 being the lowest and 20 being the highest\nThis will determine how hard the game will be\n////////////////////\n";
    cin >> AILevel;
    sleep(1);
    cout << "\nInitializing...\n";
    sleep(rand() % 6);
    system("cls");
    cout << "\nDo you wish to start the game? (Y/N) \n";
    cin >> rasp;
    rasp = toupper(rasp);
    if (rasp == 'N')
    {
        afisareMat(matP2Ocean);
        cout << "\nThanks for playing!\n";
        return 0;
    }
    if (rasp == 'D')
    {

        cout << "\n\n Debugging mode enabled \n\n";
        sleep(1);
        cout << " beep booping...\n";
        sleep(2);
    }
    int roundCnt = 1;
    while (cntAI && cntPlayer)
    {

        cout << "Type in the square you wish to attack ";
        cin >> input;
        system("cls");
        pozi = (toupper(input[0]) - 'A') + 1;
        pozj = (input[1] - '0');
        while (matP1Target[pozi][pozj] != 0)
        {
            cout << " You can't hit the same place twice !\n Enter a new position: ";
            cin >> input;
            pozi = (toupper(input[0]) - 'A') + 1;
            pozj = (input[1] - '0');
        }
        type = matP2Ocean[pozi][pozj];
        if (type > 0)
        {
            missTable(pozi, pozj, matP1Target, matP2Ocean, 0);
            AiShips[type]->gotHit(pozi, pozj, matP2Ocean);
            cout << input << " Hit." << "Enemy " << v[type - 1] << "\n\n";
            if (AiShips[type]->healthPoints == 0)
            {
                cout << " Downed enemy " << v[type - 1] << "\n\n";
                cntAI--;
            }
        }
        else
        {
            missTable(pozi, pozj, matP1Target, matP2Ocean, 1);
            cout << "Miss. Noting position where you missed\n\n";
        }
        while (!nextHits.empty() && matP1Ocean[nextHits.front() / 10][nextHits.front() % 10] < 0)
            nextHits.pop_front();
        AIChooseHits(AILevel, roundCnt);
        cout << " Ai chose " << (char)(nextHits.front() / 10 - 1 + 'A') << nextHits.front() % 10 << "\n";
        nextHits.pop_front();
        Question();
        roundCnt++;
    }
    system("cls");
    sleep(3);
    if (cntAI == 0)
        cout << "!!YOU WON ON DIFFICULTY LEVEL  " << AILevel << " YOU DESERVE A COOKIE!! ";
    else if (cntPlayer == 0)
        cout << "YOU LOST. GAME OVER";
    for (int i = 1; i <= 5; i++)
        delete ships[i], delete AiShips[i];
    return 0;
}
