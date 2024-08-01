/**
 * @file Pawn.cpp
 * @author Emanuele Vita
 * @brief 
 * @version 0.1
 * @date 25-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include"Pawn.h"

Pawn::Pawn(ColorPiece c, Tile* p) : Piece(c, p)
{
    symbol = 'P';
}

bool Pawn::isLegalMove(const Tile& posDest, const Board& b) const
{
    //innanzitutto considero il colore del pedone, in quanto quelli bianchi si muovono in una direzione e qulli neri in un altra
    short pawnDir = (color == WHITE) ? 1 : -1;

    //il Pedone si può muovere in avanti di una casella solo se la casella di destinazione è vuota
    if (!posDest.isOccuped())
        if (posDest.getFile() == pos->getFile() && posDest.getRank() == pos->getRank() + pawnDir)
            return true;
    //si può muovere in diagonale se è presente un pezzo avversario
    else if (!posDest.isOccupedBySamePlayer(*this))
        if ((posDest.getFile() == pos->getFile() + 1 || posDest.getFile() == pos->getFile() - 1) &&
            posDest.getRank() == pos->getRank() + pawnDir)
            return true;

    return false;
}
