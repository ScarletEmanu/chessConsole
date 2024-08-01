/**
 * @file King.cpp
 * @author Emanuele Vita
 * @brief 
 * @version 0.1
 * @date 2022-01-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "King.h"
#include <cmath>

King::King(ColorPiece c, Tile* p) : Piece(c, p)
{
    symbol = 'K';
}

bool King::isLegalMove(const Tile& posDest, const Board& b) const
{
    //considero prima la distanza, in valore assoluta, tra la posizione attuale del pezzo e quella di arrivo
    unsigned short deltaRank = std::abs(this->pos->getRank() - posDest.getRank());
    unsigned short deltaFile = std::abs(this->pos->getFile() - posDest.getFile());
    
    if ((deltaRank == 0 || deltaRank == 1) && (deltaFile == 0 || deltaFile == 1))
    {
        //constrollo inoltre se la casella di destinazione sia vuota o ci sia un pezzo avversario
        if (!b(posDest.getFile(), posDest.getRank())->isOccupedBySamePlayer(*this))
            return false;

        return true;
    }

    return false;

}

void King::canMove(std::vector<Tile*>& vecPossibleMove, const Board& b) const
{
    vecPossibleMove.clear();

    //scorro le celle intorno a quella attuale, sapendo che se sforo la matrice della scacchiera avro Tile* = NULL
    checkMembershipTile(vecPossibleMove, b(pos->getFile() - 1, pos->getRank()));
    checkMembershipTile(vecPossibleMove, b(pos->getFile() - 1, pos->getRank() - 1));
    checkMembershipTile(vecPossibleMove, b(pos->getFile(), pos->getRank() - 1));
    checkMembershipTile(vecPossibleMove, b(pos->getFile() + 1, pos->getRank() - 1));
    checkMembershipTile(vecPossibleMove, b(pos->getFile() + 1, pos->getRank()));
    checkMembershipTile(vecPossibleMove, b(pos->getFile() + 1, pos->getRank() + 1));
    checkMembershipTile(vecPossibleMove, b(pos->getFile(), pos->getRank() + 1));
    checkMembershipTile(vecPossibleMove, b(pos->getFile() - 1, pos->getRank() + 1));
}

