#ifndef __TILE_H__
#define __TILE_H__

/**
 * @file Tile.h
 * @author Emanuele Vita
 * @brief 
 * @version 0.1
 * @date 2022-01-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Piece.h"
#include "Player.h"
#include <string>

class Piece;
class Player;

/** 
 * @brief Questa classe gestisce il funzionamento di una singola casa sulla scacchiera
 * 
 */
class Tile
{
public:
    /**
     * @brief Costruttore
     * 
     */
    Tile();

    /**
     * @brief Costruttore parametrizzato
     * 
     * @param f è la colonna che occupa questa casa
     * @param r è la riga che occupa questa casa
     */
    Tile(int f, int r);

    /**
     * @brief Distruttore
     * 
     */
    ~Tile() {}

    /**
     * @brief Questa funzione serve ad accedere all'attributo Occupant
     * 
     * @return Puntatore al pezzo che occupa questa casa
     * @return NULL se non c'è nessun pezzo su questa casa
     */
    Piece* getOccupant() const { return occupant;}

    /**
     * @brief Modifica l'attributo Occupant
     * 
     * @param newOccupant nuovo pezzo che va inserito in questa casa
     */
    void setOccupant(Piece* newOccupant);

    /**
     * @brief Questa funzione serve ad accedere al simbolo della casa, che corrisponde al simbolo del pezzo posizionato su di essa o alla string " "
     * 
     * @return Simbolo del pezzo posizionato sopra questa casa preceduta dalla stringa in ANSI che permette di modificare il colore della scritta sul terminale
     * @return " " se sopra questa casa non è presente nessun pezzo
     */
    std::string toString() const;

    /**
     * @brief Questa funzione indica se nella casa c'è un pezzo
     * 
     * @return true se c'è un pezzo su questa casa
     * @return false se non c'è nessun pezzo su questa casa
     */
    bool isOccuped() const {return occupant;}

    /**
     * @brief Controlla se in questa casa c'è un pezzo che appartiene allo stesso giocatore di P
     * 
     * @param p 
     * @return true 
     * @return false se 
     */
    bool isOccupedBySamePlayer(const Piece& p) const;

    /**
     * @brief Controlla se in questa casa c'è un pezzo che appartiene al giocatore P
     * 
     * @param p puntatore a giocatore di riferimento
     * @return true se il pezzo su questa casa è del giocatore p 
     * @return false se il pezzo su questa casa non è del giocatore p 
     */
    bool isOccupedBySamePlayer(Player* p) const;

    /**
     * @brief Questa funzione serve ad accedere alla riga che occupa questa casa
     * 
     * @return int 
     */
    int getRank() const { return rank;}

    /**
     * @brief Questa funzione serve ad accedere alla colonna che occupa questa casa
     * 
     * @return int 
     */
    char getFile() const { return file;}

    /**
     * @brief Questa funzione provvede a spostare il pezzo posto su questa casa su un'altra casa
     * 
     * @param dstTile casa di destinazione del pezzo
     */
    void moveOccupant(Tile& dstTile);
    
    /**
     * @brief Questa funzione provvede a catturare il pezzo, togliendolo da questa casa
     * 
     */
    void capturePiece();

private:
    const char file;     ///< Indica la colonna della casa
    const int rank;     ///< Indica la riga della casa
    Piece* occupant;    ///< Puntatore al pezzo che occupa questa casa

    std::string colSymbolWhite; ///< Stringa che grazie ai codici ANSI permette di colorare un carattere del terminale di bianco
    std::string colSymbolBlack; ///< Stringa che grazie ai codici ANSI permette di colorare un carattere del terminale di nero
};

#endif // __TILE_H__