/**
 * @file Queen.cpp
 * @author Emanuele Vita
 * @brief 
 * @version 0.1
 * @date 24-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Queen.h"

Queen::Queen(ColorPiece c, Tile* p) : Piece(c, p)
{
    symbol = 'Q';
}

bool Queen::isLegalMove(const Tile& posDest, const Board& b) const
{
    //per la Regina utilizzo le funzioni isValidMove della Torre e dell'alfiere,
    //in quanto la regina si muove sia come una torre che come un Alfiere
    //considero il caso che mi voglia muovere lungo lo stesso File
    if (pos->getFile() == posDest.getFile())
    {
        //controllo che i tutti Tile tra la posizione attuale e quella di arrivo non siano occupati
        int offset = (posDest.getRank() - pos->getRank() > 0) ? 1 : -1;
        for (int checkTile = pos->getRank() + offset; checkTile != pos->getRank(); checkTile += offset)
            if (!b(pos->getFile(), checkTile)->isOccuped())
                return false;

        //constrollo inoltre che la casella di destinazione sia vuota o ci sia un pezzo avversario
        if (!b(posDest.getFile(), posDest.getRank())->isOccupedBySamePlayer(*this))
            return false;

        return true;
    }
    else if (pos->getRank() == posDest.getRank())
    {
        //controllo che i tutti Tile tra la posizione attuale e quella di arrivo non siano occupati
        int offset = (posDest.getFile() - pos->getFile() > 0) ? 1 : -1;
        for (int checkTile = pos->getFile() + offset; checkTile != pos->getFile(); checkTile += offset)
            if (!b(checkTile, pos->getRank())->isOccuped())
                return false;

        //constrollo inoltre che la casella di destinazione sia vuota o ci sia un pezzo avversario
        if (!b(posDest.getFile(), posDest.getRank())->isOccupedBySamePlayer(*this))
            return false;
        
        return true;
    }

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
            if (!b(checkFile, checkRank)->isOccuped())
                return false;
        
        //constrollo inoltre che la casella di destinazione sia vuota o ci sia un pezzo avversario
        if (!b(posDest.getFile(), posDest.getRank())->isOccupedBySamePlayer(*this))
            return false;

        return true;
    }

    return false;
}

void Queen::tilesBetween(std::vector<Tile*>& vec, const Tile& posDest, const Board& b) const
{
    vec.clear();

    //questa variabile mi dice se sono arrivato fuori la scacchiera oppure ho incontrato un pezzo
    bool endLine = false;

    for (int i = 0; endLine == false; i++)
    {
        //se arrivo alla casa finale esco dalla funzione
        if (b(pos->getFile() + i, pos->getRank()) == &posDest)
            return;
        else if (b(pos->getFile() + i, pos->getRank()) == 0 || b(pos->getFile() + i, pos->getRank())->isOccuped() == true)
            endLine = true;
        else
            vec.push_back(b(pos->getFile() + i, pos->getRank()));
    }

    vec.clear();

    endLine = false;

    for (int i = 0; endLine == false; i++)
    {
        //se arrivo alla casa finale esco dalla funzione
        if (b(pos->getFile() - i, pos->getRank()) == &posDest)
            return;
        else if (b(pos->getFile() - i, pos->getRank()) == 0 || b(pos->getFile() - i, pos->getRank())->isOccuped() == true)
            endLine = true;
        else
            vec.push_back(b(pos->getFile() - i, pos->getRank()));
    }

    vec.clear();

    endLine = false;

    for (int i = 0; endLine == false; i++)
    {
        //se arrivo alla casa finale esco dalla funzione
        if (b(pos->getFile(), pos->getRank() + 1) == &posDest)
            return;
        else if (b(pos->getFile(), pos->getRank() + 1) == 0 || b(pos->getFile(), pos->getRank() + 1)->isOccuped() == true)
            endLine = true;
        else
            vec.push_back(b(pos->getFile(), pos->getRank() + 1));
    }

    vec.clear();

    endLine = false;

    for (int i = 0; endLine == false; i++)
    {
        //se arrivo alla casa finale esco dalla funzione
        if (b(pos->getFile(), pos->getRank() - 1) == &posDest)
            return;
        else if (b(pos->getFile(), pos->getRank() - 1) == 0 || b(pos->getFile(), pos->getRank() - 1)->isOccuped() == true)
            endLine = true;
        else
            vec.push_back(b(pos->getFile(), pos->getRank() - 1));
    }

    vec.clear();

    endLine = false;

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