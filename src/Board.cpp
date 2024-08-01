/**
 * @file Board.cpp
 * @author Emanuele Vita
 * @brief 
 * @version 0.1
 * @date 25-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Board.h"

Board::Board() 
{
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            board[i][j] = new Tile(i, j);

    //std::cerr << "Costruttore Board!!\n\n"; 
}

Board::~Board() 
{
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
             delete board[i][j];
}

Tile* Board::operator()(int file, int rank) const
{
    if (file > 0 && file <= 8 && rank > 0 && rank <= 8)
        return board[file - 1][rank - 1];
    else 
    {
        std::cerr << "ERRORE::OPERATOR(int, int)\n";
        return 0;
    }
}

Tile* Board::operator()(char file, int rank) const
{
    if (!isalpha(file))
    {
        std::cerr << "ERRORE::OPERATOR(char, int)\n";
        return 0;
    }

    return operator()(int(toupper(file) - 'A'), rank);

}

Tile* Board::operator()(const char* pos) const
{
    if (!isalpha(pos[0]) || !isdigit(pos[1]))
    {
        std::cerr << "ERRORE::OPERATOR(const char*)\n";
        return 0;
    }

    return operator()(int(toupper(pos[0]) - 'A') + 1, atoi(&pos[1]));
}

bool Board::movePiece(const std::string& moveStr) const
{
    Tile* srcTile = operator()(moveStr.substr(0, 2).c_str());
    Tile* dstTile = operator()(moveStr.substr(3, 2).c_str());
    
    //verifico se il pezzo si può muovere tra le due celle
    if (srcTile->getOccupant()->isLegalMove(*dstTile, *this))
    {
        dstTile->capturePiece();

        srcTile->moveOccupant(*dstTile);

        return true;
    }

    return false;
}


