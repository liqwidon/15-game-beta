//implementation of the core of this game
#include "core.h"

Game15Core::Game15Core () //constructor where we initialise board, ckeck if it is solvable and make it solvable)
{
    int array[16], n, i, buffer, k = 0;
    bool flag = false ;

    srand(time(nullptr));

    for (n = 0; n < 16; )
    {
        flag = false;
        buffer =  rand() % 16;
        for (i = 0; i < n; i++)
        {
            if (array[i] == buffer)
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            array[n] = buffer;
            n++;
        }
    }
    for (n = 0; n < 4; n++)
        for (i = 0; i < 4; i++)
        {
            board[n][i] = array[k];
            k++;
        }
    for (n = 0; n < 4; n++)
        for (i = 0; i < 4; i++)
        {
            if (board[n][i] == 0)
            {
                buffer = board[3][3];
                board[3][3] = 0;
                board[n][i] = buffer;
                break;
            }
        }
    //это было создание рандомного поля 4 на 4
    for (i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            conf[board[i][j]] = i*4 + j; //заполнение массива с номером от 0 до 15 позиции цифры в поле
        }

    if(!is_Solvable())
    {
        buffer = board[0][0];
        board[0][0] = board[0][1];
        board[0][1] = buffer;

        buffer = conf[board[0][0]];
        conf[board[0][0]] = conf[board[0][1]];
        conf[board[0][1]] = buffer;
    }

    return;
}

bool  Game15Core::is_Solvable() const // пока не знаю, как работает...
{
    int pairs = 0;
    for (int i = 1; i < 16; ++i) {
        for (int k = i + 1; k < 16; ++k) {
            if (conf[i] < conf[k]) ++pairs;
        }
    }
    return (pairs + conf[0] / 4) % 2 == 0;
}

string Game15Core::create_Line() const
{
    string str;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (int(board[i][j] / 10) == 0)
                str += board[i][j] + '0';
            else
            {
                str += int(board[i][j] / 10) + '0';
                str += board[i][j] % 10 + '0';
            }
            str += ' ';
        }
    }
    return str;
}

bool Game15Core::is_Solved()
{
    bool f = true;
    int k = 1;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if(i == 3 && j == 3)
            {
                if(board[i][j] != 0)
                {
                    f = false;
                    break;
                }
            }
            else if(board[i][j] != k)
            {
                f = false;
                break;
            }
            k++;
        }
    if(f == true) return true;
    return false;
}

void Game15Core::auto_Win() //test functional
{
    int l = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = l;
            l++;
        }
    }
    board[3][3] = 0;
}

int Game15Core::get_Number(int i, int j) const
{
    return board[i][j];
}

// functions for movement of '0' element(the feature of movement)
void Game15Core::up()
{
    int i_0 = ((conf[0] - conf[0]%4) / 4);
    int j_0 = conf[0]%4;

    conf[0] -= 4;

    int i_new = ((conf[0] - conf[0]%4) / 4);
    int j_new = conf[0]%4;

    conf[get_Number(i_new, j_new)] += 4;

    board[i_0][j_0] = get_Number(i_new, j_new) ;
    board[i_new][j_new] = 0;
}
void Game15Core::down()
{
    int i_0 = ((conf[0] - conf[0]%4) / 4);
    int j_0 = conf[0]%4;
    conf[0] += 4;
    int i_new = ((conf[0] - conf[0]%4) / 4);
    int j_new = conf[0]%4;
    conf[get_Number(i_new, j_new)] -= 4;
    board[i_0][j_0] = get_Number(i_new, j_new) ;
    board[i_new][j_new] = 0;
}
void Game15Core::left()
{
    int i_0 = ((conf[0] - conf[0]%4) / 4);
    int j_0 = conf[0]%4;
    conf[0] -= 1;
    int i_new = ((conf[0] - conf[0]%4) / 4);
    int j_new = conf[0]%4;
    conf[get_Number(i_new, j_new)] += 1;
    board[i_0][j_0] = get_Number(i_new, j_new) ;
    board[i_new][j_new] = 0;
}
void Game15Core::right()
{
    int i_0 = ((conf[0] - conf[0]%4) / 4);
    int j_0 = conf[0]%4;
    conf[0] += 1;
    int i_new = ((conf[0] - conf[0]%4) / 4);
    int j_new = conf[0]%4;
    conf[get_Number(i_new, j_new)] -= 1;
    board[i_0][j_0] = get_Number(i_new, j_new) ;
    board[i_new][j_new] = 0;
}
