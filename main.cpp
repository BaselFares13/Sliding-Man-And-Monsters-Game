// باسل اشريتح
// ملك قواسمة
#include <iostream>
#include <windows.h>

const int X = 4, Y = 4;
double y = 0.6;
bool isThereSliding = true;

int enviroment[X][Y] = {{1, 0, 0, 0},
                        {0, 2, 0, 0},
                        {0, 0, 2, 3},
                        {0, 0, 0, 0}};

int rewardMatrix[X * Y][4];
double qMatrix[X * Y][4];

void createRewardsMatrix();

void train(int iterationNumber);

int getStateNumber(int a, int b);

double Max(int state);

int indexOf(int state, double actionReward);

bool move(int actionIndex, int &a, int &b);

void printEnviroment();

void getPersonCordinates(int &a, int &b);

void getGoalCordinates(int &a, int &b);

void slide(int action, int &a, int &b);

int getRandomPositiveNumber(int greatestNumber);

using namespace std;
int main()
{
    srand(time(0));
    createRewardsMatrix();
    train(50000);

    int lose = false;
    int a = 0, b = 0, goala = 0, goalb = 0;

    getPersonCordinates(a, b);
    getGoalCordinates(goala, goalb);

    system("cls");
    printEnviroment();
    Sleep(1000);

    // for (int i = 0; i < X * Y; i++)
    // {
    //     cout << i << " => " << " ";
    //         for (int j = 0; j < 4; j++) {
    //             cout << rewardMatrix[i][j] << "         ";
    //         }

    //         cout << "\n";
    // }

    // Q Matrix
    // for (int i = 0; i < X * Y; i++)
    // {
    //     cout << i << " => " << " ";
    //     for (int j = 0; j < 4; j++) {
    //         cout << qMatrix[i][j] << "         ";
    //     }

    //     cout << "\n";
    // }

    while (!(a == goala && b == goalb))
    {
        system("cls");
        int state = getStateNumber(a, b);
        if (!move(indexOf(state, Max(state)), a, b))
        {
            printEnviroment();
            Sleep(1000);
            lose = true;
            cout << "Game Over !" << endl;
            break;
        }
        printEnviroment();
        Sleep(1000);
    }

    if (!lose)
    {
        cout << "The Person Won :)" << endl;
    }

    return 0;
}

void getPersonCordinates(int &a, int &b)
{
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            if (enviroment[i][j] == 1)
            {
                a = i;
                b = j;
            }
        }
    }
}

void getGoalCordinates(int &a, int &b)
{
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            if (enviroment[i][j] == 3)
            {
                a = i;
                b = j;
            }
        }
    }
}

void printEnviroment()
{
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            cout << enviroment[i][j] << "    ";
        }
        cout << "\n\n";
    }
}

int setReward(int value)
{
    switch (value)
    {
    case 0:
        return 0;
    case 2:
        return -100;
    case 3:
        return 100;
    }

    return -100;
}

bool isInside(int i, int j)
{
    return (i >= 0 && i < X) && (j >= 0 && j < Y);
}

void setRewardsForState(int i, int j, int state)
{
    if (isInside(i - 1, j)) // up
    {
        rewardMatrix[state][0] = setReward(enviroment[i - 1][j]);
    }
    else
        rewardMatrix[state][0] = -100;

    if (isInside(i, j + 1)) // right
    {
        rewardMatrix[state][1] = setReward(enviroment[i][j + 1]);
    }
    else
        rewardMatrix[state][1] = -100;

    if (isInside(i + 1, j)) // down
    {
        rewardMatrix[state][2] = setReward(enviroment[i + 1][j]);
    }
    else
        rewardMatrix[state][2] = -100;

    if (isInside(i, j - 1)) // left
    {
        rewardMatrix[state][3] = setReward(enviroment[i][j - 1]);
    }
    else
        rewardMatrix[state][3] = -100;
}

void createRewardsMatrix()
{
    int r = 0;
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            setRewardsForState(i, j, r);
            r++;
        }
    }
}

void setStateCordinates(int state, int &a, int &b)
{
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            if (state == 0)
            {
                a = i;
                b = j;
                return;
            }
            state--;
        }
    }
}

void setNextStateCordinates(int &a, int &b, int action)
{
    switch (action)
    {
    case 0:
        a--;
        return;
    case 1:
        b++;
        return;
    case 2:
        a++;
        return;
    case 3:
        b--;
    }
}

bool move(int action, int &a, int &b)
{
    bool success = true;

    enviroment[a][b] = 0;
    setNextStateCordinates(a, b, action);
    if (enviroment[a][b] == 2)
    {
        success = false;
    }
    enviroment[a][b] = 1;

    return success;
}

void slide(int action, int &a, int &b)
{
    int a1 = a, b1 = b;
    if (isThereSliding && getRandomPositiveNumber(10) < 5)
    {
        setNextStateCordinates(a, b, action);
        if (!isInside(a, b))
        {
            a = a1;
            b = b1;
        }
    }
}

int getStateNumber(int a, int b)
{
    int counter = 0;
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            if (i == a && j == b)
            {
                return counter;
            }
            else
                counter++;
        }
    }
    return counter;
}

int getNextState(int state, int action)
{
    int a, b;
    setStateCordinates(state, a, b);
    setNextStateCordinates(a, b, action);
    if (!isInside(a, b))
        return state;
    else
        slide(action, a, b);
    return getStateNumber(a, b);
}

double Max(int state)
{
    double greaterValue = qMatrix[state][0];

    for (int i = 1; i < 4; i++)
    {
        if (qMatrix[state][i] > greaterValue)
        {
            greaterValue = qMatrix[state][i];
        }
    }

    return greaterValue;
}

int indexOf(int state, double actionReward)
{
    int action = 0;
    for (int i = 0; i < 4; i++)
    {
        if (qMatrix[state][i] == actionReward)
        {
            action = i;
            break;
        }
    }

    return action;
}

bool isReachedTheGoal(int state)
{
    int i, j;
    setStateCordinates(state, i, j);
    return enviroment[i][j] == 3;
}

int getRandomPositiveNumber(int greatestNumber)
{
    return rand() % greatestNumber;
}

void train(int iterationNumber)
{
    for (int i = 0; i < iterationNumber; i++)
    {
        int state = getRandomPositiveNumber(X * Y);

        while (!isReachedTheGoal(state))
        {
            int action = getRandomPositiveNumber(4);
            int nextState = getNextState(state, action);
            qMatrix[state][action] = rewardMatrix[state][action] + y * Max(nextState);
            state = nextState;
        }

        int action = getRandomPositiveNumber(4);
        int nextState = getNextState(state, action);
        qMatrix[state][action] = rewardMatrix[state][action] + y * Max(nextState);
    }
}