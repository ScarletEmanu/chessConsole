/**
 * @file Tile.cpp
 * @author Emanuele Vita
 * @brief 
 * @version 0.1
 * @date 2022-01-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Tile.h"

Tile::Tile() : file(0), rank(0)
{
    occupant = 0;

    colSymbolWhite = "\033[38;2;225;225;225m";

    colSymbolBlack = "\033[38;2;0;0;0m";
}

Tile::Tile(int f, int r) : file(f + 'A') , rank(r)
{
    occupant = 0;

    colSymbolWhite = "\033[38;2;225;225;225m";

    colSymbolBlack = "\033[38;2;0;0;0m";
}

void Tile::setOccupant(Piece* newOccupant) 
{
    occupant = newOccupant;
}

std::string Tile::toString() const
{
    return occupant != 0 ? (occupant->getColor() == WHITE ? colSymbolWhite : colSymbolBlack) + occupant->getSymbol() : " ";
}

bool Tile::isOccupedBySamePlayer(const Piece& p) const
{
    return !isOccuped() || p.getColor() == getOccupant()->getColor();
}

bool Tile::isOccupedBySamePlayer(Player* p) const
{
    return !isOccuped() || p->getColor() == getOccupant()->getColor();
}

void Tile::moveOccupant(Tile& dstTile) 
{
    dstTile.occupant = occupant;

    occupant->movePiece(&dstTile);

    occupant = 0;
}

void Tile::capturePiece() 
{
    //prima elimino il pezzo su questa casa dalla scacchiera
    if (isOccuped())
        occupant->movePiece(0);
    
    occupant = 0;
}

