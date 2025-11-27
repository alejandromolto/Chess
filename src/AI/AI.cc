#include "AI.h"
#include <vector>
#include <utility>

AI::AI(const Board* board, int searchDepth)
{
    this->board = const_cast<Board*>(board); //AI should not modify the board directly
    this->searchDepth = searchDepth;
}

void AI::AIPawnPromotion()
{
    T_Coordinates pawnCoords{-1, -1};
    int (*b)[8] = board->getboard();

    if (board->getMovementCount() % 2 == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            if (b[0][i] % 10 == 1)
            {
                pawnCoords.row = 0;
                pawnCoords.col = i;
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            if (b[7][i] % 10 == 1)
            {
                pawnCoords.row = 7;
                pawnCoords.col = i;
                break;
            }
        }
    }

    b[pawnCoords.row][pawnCoords.col] = ((b[pawnCoords.row][pawnCoords.col] / 10) * 10 + 3);
}

int AI::evaluate()
{
    int evaluation = 0;
    int materialEvaluationSum = 0;
    int (*b)[8] = board->getboard();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (b[i][j] / 10 == 1)
            {
                if (b[i][j] % 10 == 1)
                {
                    materialEvaluationSum += 1;
                }
                else if (b[i][j] % 10 == 6)
                {
                    materialEvaluationSum += 3;
                }
                else if (b[i][j] % 10 == 3)
                {
                    materialEvaluationSum += 3;
                }
                else if (b[i][j] % 10 == 4)
                {
                    materialEvaluationSum += 5;
                }
                else if (b[i][j] % 10 == 5)
                {
                    materialEvaluationSum += 9;
                }
            }
            else if (b[i][j] / 10 == 0 && !(b[i][j] == 0))
            {
                if (b[i][j] % 10 == 1)
                {
                    materialEvaluationSum -= 1;
                }
                else if (b[i][j] % 10 == 6)
                {
                    materialEvaluationSum -= 3;
                }
                else if (b[i][j] % 10 == 3)
                {
                    materialEvaluationSum -= 3;
                }
                else if (b[i][j] % 10 == 4)
                {
                    materialEvaluationSum -= 5;
                }
                else if (b[i][j] % 10 == 5)
                {
                    materialEvaluationSum -= 9;
                }
            }
        }
    }

    int mobilityEvaluationSum;
    Board boardEnemy = Board(board->getboard(), board->getMovementCount() + 1);

    if (board->getMovementCount() % 2 == 0)
    {
        mobilityEvaluationSum = board->generateAllLegalMoves().size() - boardEnemy.generateAllLegalMoves().size();
    }
    else
    {
        mobilityEvaluationSum = boardEnemy.generateAllLegalMoves().size() - board->generateAllLegalMoves().size();
    }

    int centerEvaluationSum = 0;
    for (int i = 3; i < 5; i++)
    {
        for (int j = 3; j < 5; j++)
        {
            if (b[i][j] / 10 == 1)
            {
                if (b[i][j] % 10 == 1)
                {
                    centerEvaluationSum += 1;
                }
                else if (b[i][j] % 10 == 6)
                {
                    centerEvaluationSum += 3;
                }
                else if (b[i][j] % 10 == 3)
                {
                    centerEvaluationSum += 3;
                }
                else if (b[i][j] % 10 == 4)
                {
                    centerEvaluationSum += 5;
                }
                else if (b[i][j] % 10 == 5)
                {
                    centerEvaluationSum += 9;
                }
            }
            else if (b[i][j] / 10 == 0 && !(b[i][j] == 0))
            {
                if (b[i][j] % 10 == 1)
                {
                    centerEvaluationSum -= 1;
                }
                else if (b[i][j] % 10 == 6)
                {
                    centerEvaluationSum -= 3;
                }
                else if (b[i][j] % 10 == 3)
                {
                    centerEvaluationSum -= 3;
                }
                else if (b[i][j] % 10 == 4)
                {
                    centerEvaluationSum -= 5;
                }
                else if (b[i][j] % 10 == 5)
                {
                    centerEvaluationSum -= 9;
                }
            }
        }
    }

    int outercenterEvaluationSum = 0;
    for (int i = 2; i < 6; i++)
    {
        for (int j = 2; j < 6; j++)
        {
            if (b[i][j] / 10 == 1)
            {
                if (b[i][j] % 10 == 1)
                {
                    outercenterEvaluationSum += 1;
                }
                else if (b[i][j] % 10 == 6)
                {
                    outercenterEvaluationSum += 3;
                }
                else if (b[i][j] % 10 == 3)
                {
                    outercenterEvaluationSum += 3;
                }
                else if (b[i][j] % 10 == 4)
                {
                    outercenterEvaluationSum += 5;
                }
                else if (b[i][j] % 10 == 5)
                {
                    outercenterEvaluationSum += 9;
                }
            }
            else if (b[i][j] / 10 == 0 && !(b[i][j] == 0))
            {
                if (b[i][j] % 10 == 1)
                {
                    outercenterEvaluationSum -= 1;
                }
                else if (b[i][j] % 10 == 6)
                {
                    outercenterEvaluationSum -= 3;
                }
                else if (b[i][j] % 10 == 3)
                {
                    outercenterEvaluationSum -= 3;
                }
                else if (b[i][j] % 10 == 4)
                {
                    outercenterEvaluationSum -= 5;
                }
                else if (b[i][j] % 10 == 5)
                {
                    outercenterEvaluationSum -= 9;
                }
            }
        }
    }

    outercenterEvaluationSum = outercenterEvaluationSum - centerEvaluationSum;

    evaluation = materialEvaluationSum * 2 + mobilityEvaluationSum + centerEvaluationSum + outercenterEvaluationSum;

    if (boardEnemy.isTheKingCheckMated())
    {
        if (board->getMovementCount() % 2 == 0)
        {
            evaluation = 1000;
        }
        else
        {
            evaluation = -1000;
        }
    }

    return evaluation;
}

std::pair<T_Coordinates, T_Coordinates> AI::bestMoveWithMinimax(int alpha, int beta)
{
    std::vector<std::pair<T_Coordinates, T_Coordinates>> legalMoves = board->generateAllLegalMoves();
    std::pair<T_Coordinates, T_Coordinates> bestMove;
    int bestScore;

    if (board->getMovementCount() % 2 == 0)
    {
        bestScore = -2147483647;

        for (int i = 0; i < static_cast<int>(legalMoves.size()); i++)
        {
            Board boardCopy(board->getboard(), board->getMovementCount());
            boardCopy.updateboard(legalMoves[i].first, legalMoves[i].second);
            boardCopy.setMovementCount(boardCopy.getMovementCount() + 1);
            AI enemyAI(&boardCopy, searchDepth-1);
            int score = enemyAI.mini(searchDepth - 1, alpha, beta);

            if (score > bestScore)
            {
                bestScore = score;
                bestMove = legalMoves[i];
            }

            if (bestScore > alpha)
            {
                alpha = bestScore;
            }

            if (alpha >= beta)
            {
                break;
            }
        }
    }
    else
    {
        bestScore = 2147483647;

        for (int i = 0; i < static_cast<int>(legalMoves.size()); i++)
        {
            Board boardCopy(board->getboard(), board->getMovementCount());
            boardCopy.updateboard(legalMoves[i].first, legalMoves[i].second);
            boardCopy.setMovementCount(boardCopy.getMovementCount() + 1);
            AI enemyAI(&boardCopy, searchDepth-1);
            int score = enemyAI.maxi(searchDepth - 1, alpha, beta);

            if (score < bestScore)
            {
                bestScore = score;
                bestMove = legalMoves[i];
            }

            if (bestScore < beta)
            {
                beta = bestScore;
            }

            if (alpha >= beta)
            {
                break;
            }
        }
    }

    return bestMove;
}

int AI::maxi(int depth, int alpha, int beta)
{
    if (depth == 0)
    {
        return evaluate();
    }

    int maximum = -2147483647;
    std::vector<std::pair<T_Coordinates, T_Coordinates>> legalMoves = board->generateAllLegalMoves();

    for (int i = 0; i < static_cast<int>(legalMoves.size()); i++)
    {
        Board boardCopy(board->getboard(), board->getMovementCount());
        boardCopy.updateboard(legalMoves[i].first, legalMoves[i].second);
        boardCopy.setMovementCount(boardCopy.getMovementCount() + 1);
        AI enemyAI(&boardCopy, searchDepth-1);
        int score = enemyAI.mini(searchDepth - 1, alpha, beta);
        if (score > maximum)
        {
            maximum = score;
        }
        if (maximum > alpha)
        {
            alpha = maximum;
        }
        if (alpha >= beta)
        {
            break;
        }
    }
    return maximum;
}

int AI::mini(int depth, int alpha, int beta)
{
    if (depth == 0)
    {
        return evaluate();
    }

    int minimum = 2147483647;
    std::vector<std::pair<T_Coordinates, T_Coordinates>> legalMoves = board->generateAllLegalMoves();

    for (int i = 0; i < static_cast<int>(legalMoves.size()); i++)
    {
        Board boardCopy(board->getboard(), board->getMovementCount());
        boardCopy.updateboard(legalMoves[i].first, legalMoves[i].second);
        boardCopy.setMovementCount(boardCopy.getMovementCount() + 1);
        AI enemyAI(&boardCopy, searchDepth-1);
        int score = enemyAI.maxi(searchDepth - 1, alpha, beta);
        if (score < minimum)
        {
            minimum = score;
        }
        if (minimum < beta)
        {
            beta = minimum;
        }
        if (alpha >= beta)
        {
            break;
        }
    }
    return minimum;
}
