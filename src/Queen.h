#ifndef __QUEEN_H__
#define __QUEEN_H__

/**
 * @file Queen.h
 * @author Emanuele Vita
 * @brief 
 * @version 0.1
 * @date 24-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Piece.h"
#include "Board.h"

/**
 * @brief Questa classe implementa tutte le azioni definite dalla classe Piece e le adatta al tipo di pezzo
 * 
 */
class Queen : public Piece
{
public:
    /**
     * @brief Costruttore parametrizzato
     * 
     * @param c colore del pezzo
     * @param p posizione che occupa durante la partita, di default punta a NULL
     */
    Queen(ColorPiece c, Tile* p = 0);

    /**
     * @brief Distruttore
     * 
     */
    ~Queen() {}

    /**
     * @brief Serve a capire se il pezzo può muoversi in una determinata casa partendo da quella attuale
     * 
     * @param posDest casa
     * @param b scacchiera su cui è presente il pezzo
     * @return true se può muoversi in quella casa
     * @return false se non può muoversi in quella casa
     */
    bool isLegalMove(const Tile& posDest, const Board& b) const;

    /**
     * @brief Inserisce in un vettore dei puntatori a tutte le possibili case su cui il pezzo si può muovere
     * 
     * @param vecPossibleMove vettore che contiene tutte le case
     * @param b scacchiera su cui è presente il pezzo
     */
    void canMove(std::vector<Tile*>& vecPossibleMove, const Board& b) const {}

    /**
     * @brief Inserisce in un vettore dei puntatori a tutte le case comprese tra la posizione attuale del pezzo e la casa di destinazione
     * 
     * @param vec vettore che conterrà i puntatori
     * @param posDest casa di destinazione
     * @param b scacchiera su cui è presente il pezzo
     */
    void tilesBetween(std::vector<Tile*>& vec, const Tile& posDest, const Board& b) const;
    
private:

};

#endif // __QUEEN_H__