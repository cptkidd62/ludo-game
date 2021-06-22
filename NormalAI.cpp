#include "NormalAI.hpp"

NormalAIPlayer::NormalAIPlayer()
{
    name = L"Robot";
    finished = false;
}

void NormalAIPlayer::makeMove(std::vector<int> &positions, int id, int delta)
{
    int ranks[4] = {4};
    for (int i = 0; i < 4; i++)
    {
        if (positions[id * 4 + i] == -1)
        {
            if (delta == 6)
            {
                if (positions[id * 4] == 0 || positions[id * 4 + 1] == 0 || positions[id * 4 + 2] == 0 || positions[id * 4 + 3] == 0)
                {
                    ranks[i] = 0;
                }
                else
                {
                    ranks[i] = 6;
                }
            }
            else
            {
                ranks[i] = 0;
            }
        }
        else if (positions[id * 4 + i] + delta > 43)
        {
            ranks[i] = 0;
        }
        else
        {
            for (int j = 0; j < 16; j++)
            {
                if (positions[j] != -1 && positions[j] < 40 && (positions[id * 4 + i] + delta + id * 10) % 40 == (positions[j] + (j / 4) * 10) % 40)
                {
                    if (j / 4 == id)
                    {
                        ranks[i] = 0;
                        break;
                    }
                    else
                    {
                        ranks[i] = 10;
                        break;
                    }
                }
                else if (j / 4 == id && positions[id * 4 + i] == positions[j])
                {
                    ranks[i] = 0;
                }
            }
        }
    }
    int move = 0;
    for (int i = 1; i < 4; i++)
    {
        if (ranks[move] < ranks[i])
            move = i;
    }
    if (positions[id * 4 + move] == -1)
    {
        for (int i = 0; i < 16; i++)
        {
            if (positions[i] != -1 && positions[i] < 40 && (positions[i] + (i / 4) * 10) % 40 == (id * 10) % 40)
            {
                positions[i] = -1;
                break;
            }
        }
        positions[id * 4 + move] = 0;
    }
    else
    {
        for (int i = 0; i < 16; i++)
        {
            if (positions[i] != -1 && positions[i] < 40 && (positions[id * 4 + move] + delta + id * 10) % 40 == (positions[i] + (i / 4) * 10) % 40)
            {
                positions[i] = -1;
                break;
            }
        }
        positions[id * 4 + move] += delta;
    }
}