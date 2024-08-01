
#include "Knight.h"

Knight::Knight(ColorPiece c, Tile* p) : Piece(c, p)
{
    symbol = 'N';
}

bool Knight::isLegalMove(const Tile& posDest, const Board& b) const
{
    if ((std::abs(pos->getFile() - posDest.getFile()) == 1 && std::abs(pos->getRank() - posDest.getRank()) == 2) ||
        (std::abs(pos->getFile() - posDest.getFile()) == 2 && std::abs(pos->getRank() - posDest.getRank()) == 1))
        {
            //non serve controllare se ci siano o no pezzi d'intralcio, in quanto il cavallo sala tutti i pezzi,
            //l'unica cosa che bisogna controllare è se la casella di destinazione sia vuota o ci sia un pezzo avversario
            if (!b(posDest.getFile(), posDest.getRank())->isOccupedBySamePlayer(*this))
                return false;
            
            return true;
        }

    return false;
}

void Knight::canMove(std::vector<Tile*>& vecPossibleMove, const Board& b) const
{
    checkMembershipTile(vecPossibleMove, b(pos->getFile() + 2, pos->getRank() + 1));
    checkMembershipTile(vecPossibleMove, b(pos->getFile() + 2, pos->getRank() - 1));
    checkMembershipTile(vecPossibleMove, b(pos->getFile() - 2, pos->getRank() + 1));
    checkMembershipTile(vecPossibleMove, b(pos->getFile() - 2, pos->getRank() - 1));

    checkMembershipTile(vecPossibleMove, b(pos->getFile() + 1, pos->getRank() + 2));
    checkMembershipTile(vecPossibleMove, b(pos->getFile() + 1, pos->getRank() - 2));
    checkMembershipTile(vecPossibleMove, b(pos->getFile() - 1, pos->getRank() + 2));
    checkMembershipTile(vecPossibleMove, b(pos->getFile() - 1, pos->getRank() - 2));
}
