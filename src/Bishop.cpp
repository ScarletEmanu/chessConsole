/**
 * @file Bishop.cpp
 * @author Emanuele Vita
 * @brief 
 * @version 0.1
 * @date 25-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Bishop.h"

Bishop::Bishop(ColorPiece c, Tile* p) : Piece(c, p)
{
    symbol = 'B';

}

bool Bishop::isLegalMove(const Tile& posDest, const Board& b) const
{
    unsigned short deltaRank = posDest.getRank() - pos->getRank();
    unsigned short deltaFile = posDest.getFile() - pos->getFile();
    if (std::abs(deltaRank) == std::abs(deltaFile))
    {
        //adesso controllo che tra la posizione attuale e la posizione di arrivo non ci siano altri pezzi
        unsigned short offsetRank = (posDest.getRank() - pos->getRank() > 0) ? 1 : -1;
        unsigned short offsetFile = (posDest.getFile() - pos->getFile() > 0) ? 1 : -1;
        for (unsigned short checkFile = pos->getFile() + offsetFile, checkRank = pos->getRank() + offsetRank;
            checkRank != posDest.getRank();
            checkFile += offsetFile, checkRank += offsetRank)
            if (!b(int(checkFile), int(checkRank))->isOccuped())
                return false;

        //controllo inoltre che la casella di destinazione sia vuota o ci sia un pezzo avversario
        if (!b(posDest.getFile(), posDest.getRank())->isOccupedBySamePlayer(*this))
            return false;

        return true;
    }

    return false;
}

void Bishop::tilesBetween(std::vector<Tile*>& vec, const Tile& posDest, const Board& b) const
{
    vec.clear();

    //questa variabile mi dice se sono arrivato fuori la scacchiera oppure ho incontrato un pezzo
    bool endLine = false;

    for (int i = 0; endLine == false; i++)
    {
        //se arrivo alla casa finale esco dalla funzione
        if (b(pos->getFile() + i, pos->getRank() + i) == &posDest)
            return;
        else if (b(pos->getFile() + i, pos->getRank() + i) == 0 || b(pos->getFile() + i, pos->getRank() + i)->isOccuped() == true)
            endLine = true;
        else
            vec.push_back(b(pos->getFile() + i, pos->getRank() + i));
    }

    vec.clear();

    endLine = false;

    for (int i = 0; endLine == false; i++)
    {
        //se arrivo alla casa finale esco dalla funzione
        if (b(pos->getFile() - i, pos->getRank() - i) == &posDest)
            return;
        else if (b(pos->getFile() - i, pos->getRank() - i) == 0 || b(pos->getFile() - i, pos->getRank() - i)->isOccuped() == true)
            endLine = true;
        else
            vec.push_back(b(pos->getFile() - i, pos->getRank() - i));
    }

    vec.clear();

    endLine = false;

    for (int i = 0; endLine == false; i++)
    {
        //se arrivo alla casa finale esco dalla funzione
        if (b(pos->getFile() - i, pos->getRank() + i) == &posDest)
            return;
        else if (b(pos->getFile() - i, pos->getRank() + i) == 0 || b(pos->getFile() - i, pos->getRank() + i)->isOccuped() == true)
            endLine = true;
        else
            vec.push_back(b(pos->getFile() - i, pos->getRank() + i));
    }

    vec.clear();

    endLine = false;

    for (int i = 0; endLine == false; i++)
    {
        //se arrivo alla casa finale esco dalla funzione
        if (b(pos->getFile() + i, pos->getRank() - i) == &posDest)
            return;
        else if (b(pos->getFile() + i, pos->getRank() - i) == 0 || b(pos->getFile() + i, pos->getRank() - i)->isOccuped() == true)
            endLine = true;
        else
            vec.push_back(b(pos->getFile() + i, pos->getRank() - i));
    }
}

