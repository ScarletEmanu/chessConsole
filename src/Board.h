#ifndef __BOARD_H__
#define __BOARD_H__

/**
 * @file Board.h
 * @author Emanuele Vita
 * @brief 
 * @version 0.1
 * @date 25-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Player.h"
#include "Tile.h"
#include <cctype>
#include <iostream>

class Tile;

/**
 * @brief Questa classe implementa le caratteristiche e le funzionalità della scacchiera
 * 
 */
class Board
{
public:
    /**
     * @brief Costruttore
     * 
     */
    Board();

    /**
     * @brief Distruttore
     * 
     */
    ~Board();

    /**
     * @brief Overloading dell'operatore ()
     * 
     * @param file Colonna della casa che si vuole trovare
     * @param rank Riga della casa che si vuole trovare
     * @return puntatore ad un oggetto Tile
     * @return NULL se i parametri passati non sono corretti
     */
    Tile* operator()(int file, int rank) const;

    /**
     * @brief Overloading dell'operatore ()
     * 
     * @param file Colonna della casa che si vuole trovare
     * @param rank riga della casa che si vuole trovare
     * @return puntatore ad un oggetto Tile
     * @return NULL se i parametri passati non sono corretti 
     */
    Tile* operator()(char file, int rank) const;

    /**
     * @brief Overloading dell'operatore ()
     * 
     * @param pos Stringa che contiene la riga e la colonna della casa che si vuole trovare
     * @return puntatore ad un oggetto Tile
     * @return NULL se il parametro passati non è corretto
     */
    Tile* operator()(const char* pos) const;

    /**
     * @brief Si occupa di verificare se è possibile effettuare la mossa e di consequenza, se è lecita, l'esegue
     * 
     * @param moveStr stringa che contiene la mossa
     * @return true se la mossa è lecita
     * @return false se la mossa non è lecita
     */
    bool movePiece(const std::string& moveStr) const;

    /**
     * @brief Questa funzione serve ad accedere alla dimensione della scacchiera
     * 
     * @return unsigned short 
     */
    unsigned short getDimBoard() const { return DIM;}

private:
    const static unsigned short DIM = 8; ///< Indica la dimensione della matrice
    Tile* board[DIM][DIM]; ///< Matrice di puntatori a Tile
};

#endif // __BOARD_H__