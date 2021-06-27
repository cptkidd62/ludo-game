#include "SimpleAI.hpp"

SimpleAIPlayer::SimpleAIPlayer()
{
    name = L"Robot";
    finished = false;
}

void SimpleAIPlayer::makeMove(std::vector<int> &positions, int id, int delta)
{
    // move ranks
    int ranks[4] = {6, 6, 6, 6};
    // check players pieces
    for (int i = 0; i < 4; i++)
    {
        // is in holder
        if (positions[id * 4 + i] == -1)
        {
            // dice 6
            if (delta == 6)
            {
                // own pieces on position 0
                if (positions[id * 4] == 0 || positions[id * 4 + 1] == 0 || positions[id * 4 + 2] == 0 || positions[id * 4 + 3] == 0)
                {
                    ranks[i] = 0;
                }
                else
                {
                    ranks[i] = 4;
                }
            }
            else
            {
                ranks[i] = 0;
            }
        }
        // after move beyond board
        else if (positions[id * 4 + i] + delta > 43)
        {
            ranks[i] = 0;
        }
        else
        {
            // move from 0 position
            if (positions[id * 4 + i] == 0)
            {
                ranks[i] = 2;
            }
            // collision with other pieces
            for (int j = 0; j < 16; j++)
            {
                // not in holder and home
                if (positions[j] != -1 && positions[j] < 40 && positions[id * 4 + i] < 40 && (positions[id * 4 + i] + delta + id * 10) % 40 == (positions[j] + (j / 4) * 10) % 40)
                {
                    // own piece
                    if (j / 4 == id)
                    {
                        ranks[i] = 0;
                        break;
                    }
                    // other player's piece
                    else
                    {
                        ranks[i] = 4;
                        break;
                    }
                }
                // own collision in home
                else if (j / 4 == id && positions[id * 4 + i] + delta == positions[j])
                {
                    ranks[i] = 0;
                }
            }
        }
    }
    int move = 0;
    // choose best
    for (int i = 1; i < 4; i++)
    {
        if (ranks[move] < ranks[i])
            move = i;
    }
    // move
    if (positions[id * 4 + move] == -1)
    {
        for (int i = 0; i < 16; i++)
        {
            if (i / 4 != id && positions[i] != -1 && positions[i] < 40 && (positions[i] + (i / 4) * 10) % 40 == (id * 10) % 40)
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
            if (positions[i] != -1 && positions[i] < 40 && positions[id * 4 + move] + delta < 40 && (positions[id * 4 + move] + delta + id * 10) % 40 == (positions[i] + (i / 4) * 10) % 40)
            {
                positions[i] = -1;
                break;
            }
        }
        positions[id * 4 + move] += delta;
    }
}