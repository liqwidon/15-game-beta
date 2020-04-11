//implementation of the core of this game
#include "core.h"
// доделать с убранным conf, переделать движение и структуру ядра!!!
void Game15Core::set_random()
{
    const int max = Board::board_size * Board::board_size;
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    vector<int> res(max);

    for (size_t i = 0; i < res.size(); ++i)
        res[i] = int(i);

    shuffle(res.begin(), res.end(), default_random_engine{seed});

    for (int i = 0; i < Board::board_size ; ++i)
    {
        for (int j = 0; j < Board::board_size ; ++j)
        {
            board(i, j) = res[size_t(i * Board::board_size + j)];
        }
    }

    for (int i = 0; i < Board::board_size ; i++)
        for (int j = 0; j < Board::board_size ; j++)
        {
            if (board(i, j) == 0)
            {
                std::swap(board(3, 3), board(i, j));
                break;
            }
        }
    for (int i = 0; i < Board::board_size; i++)
        for (int j = 0; j < Board::board_size; j++)
        {
            conf[board(i, j)] = i*Board::board_size + j; //заполнение массива с номером от 0 до 15 позиции цифры в поле
        }

    if(!is_Solvable())
    {
        swap(board(0, 0), board(0 ,1));
        swap(conf[board(0, 0)],conf[board(0, 1)]);
    }
}

Game15Core::Game15Core () //constructor where we initialise board, ckeck if it is solvable and make it solvable)
{
    set_random();
    return;
}

void Game15Core::restart()
{
    set_random();
    counter = 0;

}

bool  Game15Core::is_Solvable() const
{
    int pairs = 0;
    for (int i = 1; i < Board::board_size * Board::board_size; ++i) {
        for (int k = i + 1; k < Board::board_size * Board::board_size; ++k)
        {
            if (conf[i] < conf[k]) ++pairs;
        }
    }
    return (pairs + conf[0] / Board::board_size) % 2 == 0;
}

bool Game15Core::is_Solved()
{
    int k = 1;
    for(int i = 0; i < Board::board_size; i++)
        for(int j = 0; j < Board::board_size; j++)
        {
            if(i == 3 && j == 3)
            {
                if(board(i, j) != 0)
                {
                    return false;
                }
            }
            else if(board(i, j) != k)
            {
                return false;
            }
            k++;
        }
    return true;
}

int Game15Core::get_Number(int i, int j) const
{
    return board(i, j);
}

// functions for movement of '0' element(the feature of movement)
void Game15Core::up()
{
    int i_0 = ((conf[0] - conf[0] % Board::board_size) / Board::board_size);
    int j_0 = conf[0] % Board::board_size;

    conf[0] -= Board::board_size;

    int i_new = ((conf[0] - conf[0] % Board::board_size) / Board::board_size);
    int j_new = conf[0] % Board::board_size;

    conf[get_Number(i_new, j_new)] += Board::board_size;

    board(i_0, j_0) = get_Number(i_new, j_new) ;
    board(i_new, j_new) = 0;
    counter++;
}
void Game15Core::down()
{
    int i_0 = ((conf[0] - conf[0] % Board::board_size) / Board::board_size);
    int j_0 = conf[0] % Board::board_size;

    conf[0] += Board::board_size;

    int i_new = ((conf[0] - conf[0] % Board::board_size) / Board::board_size);
    int j_new = conf[0] % Board::board_size;

    conf[get_Number(i_new, j_new)] -= Board::board_size;

    board(i_0, j_0) = get_Number(i_new, j_new) ;
    board(i_new, j_new) = 0;
        counter++;
}
void Game15Core::left()
{
    int i_0 = ((conf[0] - conf[0] % Board::board_size) / Board::board_size);
    int j_0 = conf[0] % Board::board_size;

    conf[0] -= 1;

    int i_new = ((conf[0] - conf[0]%Board::board_size) / Board::board_size);
    int j_new = conf[0] % Board::board_size;

    conf[get_Number(i_new, j_new)] += 1;

    board(i_0, j_0) = get_Number(i_new, j_new) ;
    board(i_new, j_new) = 0;
        counter++;
}
void Game15Core::right()
{
    int i_0 = ((conf[0] - conf[0] % Board::board_size) / Board::board_size);
    int j_0 = conf[0] % Board::board_size;

    conf[0] += 1;

    int i_new = ((conf[0] - conf[0] % Board::board_size) / Board::board_size);
    int j_new = conf[0] % Board::board_size;

    conf[get_Number(i_new, j_new)] -= 1;

    board(i_0, j_0) = get_Number(i_new, j_new) ;
    board(i_new, j_new) = 0;
        counter++;
}
