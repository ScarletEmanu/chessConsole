#ifndef __PIECE_H__
#define __PIECE_H__
/**
 * @file Piece.h
 * @author Emanuele
 * @brief 
 * @version 0.1
 * @date 2022-01-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Player.h"
#include <string>
#include <vector>


class Tile;
class Board;

/**
 * @brief Questa classe implementa il comportamento generale dei pezzi
 * 
 */
class Piece
{
public:
    /**
     * @brief Costruttore parametrizzato
     *
     * @param c colore del pezzo
     * @param p posizione che occupa durante la partita, di default punta a NULL
     */
    Piece(ColorPiece c, Tile* p = 0);

    /**
     * @brief Distruttore
     * 
     */
    virtual ~Piece() {}

    /**
     * @brief Questa funzione serve ad accedere all'attributo privato color
     * 
     * @return ColorPiece colore del pezzo
     */
    ColorPiece getColor() const { return color;}

    /**
     * @brief Serve a capire se il pezzo può muoversi in una determinata casa partendo da quella attuale
     * 
     * @param posDest casa
     * @param b scacchiera su cui è presente il pezzo
     * @return true se può muoversi in quella casa
     * @return false se non può muoversi in quella casa
     */
    virtual bool isLegalMove(const Tile& posDest, const Board& b) const = 0;

    /**
     * @brief Inserisce in un vettore dei puntatori a tutte le possibili case su cui il pezzo si può muovere
     * 
     * @param vecPossibleMove vettore che contiene tutte le case
     * @param b scacchiera su cui è presente il pezzo
     */
    virtual void canMove(std::vector<Tile*>& vecPossibleMove, const Board& b) const = 0;

    /**
     * @brief Inserisce in un vettore dei puntatori a tutte le case comprese tra la posizione attuale del pezzo e la casa di destinazione
     * 
     * @param vec vettore che conterrà i puntatori
     * @param posDest casa di destinazione
     * @param b scacchiera su cui è presente il pezzo
     */
    virtual void tilesBetween(std::vector<Tile*>& vec, const Tile& posDest, const Board& b) const = 0;

    /**
     * @brief Questa funzione serve ad accedere all'attributo privato symbol
     * 
     * @return char carattere che identifica il tipo di pezzo
     */
    char getSymbol() const { return symbol;}

    /**
     * @brief Inserisce in un vettore dei puntatori a tutte le case comprese tra la posizione attuale del pezzo e la casa di destinazione
     * 
     * @param vec vettore che conterrà i puntatori
     * @param posDest casa di destinazione
     * @param b scacchiera su cui è presente il pezzo
     */
    void movePiece(Tile* posDest) { pos = posDest;}

    /**
     * @brief Questa funzione serve ad accedere all'attributo privato pos
     * 
     * @return Tile* puntatore alla casa su cui è presente il pezzo
     * @return NULL se il pezzo è fuori la scacchiera
     */
    Tile* getOccupingTile() const { return pos;}

protected:
    ColorPiece color; ///< Indica il colore del pezzo e, quindi, a quale giocatore appartiene
    char symbol; ///< Identifica univocamente il tipo di pezzo
    Tile* pos; ///< Puntatore alla casa occupata dal

    /**
     * @brief Questa funzione aggiunge un puntatore ad una casa a vec se la casa non è occupata o è presente un pezzo avversario  
     * 
     * @param vec 
     * @param tile
     */
    void checkMembershipTile(std::vector<Tile*>& vec, Tile* tile) const;
};

#endif // __PIECE_H__