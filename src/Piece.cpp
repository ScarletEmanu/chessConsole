#include "Piece.h"
#include <iostream>

Piece::Piece(ColorPiece c, Tile* p)
{
    color = c;

    pos = p;
}

void Piece::checkMembershipTile(std::vector<Tile*>& vec, Tile* tile) const
{
    if (tile != 0 && !tile->isOccupedBySamePlayer(*this))
        vec.push_back(tile);
}

