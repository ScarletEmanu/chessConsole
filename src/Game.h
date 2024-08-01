#ifndef __Game_H__
#define __Game_H__

/**
 * @file Game.h
 * @author Emanuele Vita
 * @brief 
 * @version 0.1
 * @date 26-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Engine.h"
#include <iostream>
#include <string>

/**
 * @brief Questa classe si occupa dell'interfaccia dell'applicazione
 * 
 */
class Game
{
public:
    /**
     * @brief Costruttore
     * 
     */
    Game();

    /**
     * @brief Distruttore
     * 
     */
    ~Game() {}

    /**
     * @brief Questa funzione si occupa della gestione dell'interfaccia dell'applicazione
     * 
     */
    void run();
    
private:
    Engine* engChess; ///< Puntatore ad un oggetto della classe Engine, che rapperenta il motore del gioco
    std::string colTileDark; ///< Stringa che grazie ai codici ANSI permette di colorare lo sfondo di un carattere del terminale di Grigio
    std::string colTileLight; ///< Stringa che grazie ai codici ANSI permette di colorare lo sfondo di un carattere del terminale di Verde
    std::string codeReset; ///< Stringa che grazie ai codici ANSI permette di resettare tutte le proprietà del terminale
    std::string textRed; ///< Stringa che grazie ai codici ANSI permette di colorare un carattere del terminale di Rosso
    std::string boldText; ///< Stringa che grazie ai codici ANSI permette di rendere un carattere del terminale in grassetto
    const static unsigned short CELL = 7; ///< Costante che regola la grandezza di una casa della scacchiera
    
    /**
     * @brief Questa funzione si occupa di gestire la parte dell'interfaccia che riguarda il menu' iniziale
     * 
     */
    void printInitMenu() const;

    /**
     * @brief Questa funzione si occupa di gestire la parte dell'interfaccia che riguarda la visualizzazione della scacchiera
     * 
     */
    void printChessBoard(Board* b) const;

    /**
     * @brief Questa funzione si occupa di gestire la parte dell'interfaccia che riguarda la visualizzazione di una sola riga della scacchiera
     * 
     */
    void printLineBoard(unsigned short n_line, std::string firstColor, std::string secondColor, Board* b) const;

    /**
     * @brief Questa funzione si occupa di gestire la parte dell'interfaccia che riguarda la visualizzazione del titolo del gioco
     * 
     */
    void printTitle() const;

    /**
     * @brief Questa funzione si occupa di gestire la parte dell'interfaccia che riguarda il caricamento di una partita da file
     * 
     */
    void printLoadGame() const;

    /**
     * @brief Questa funzione si occupa di gestire la parte dell'interfaccia che riguarda il salvataggio di una partita su file
     * 
     */
    void printSaveGame() const;

    /**
     * @brief Stampo a schermo la situazione del giocatore corrente, ovvero se è sotto scacco, sotto scacco matto oppure nessuno dei due
     * 
     * @return true se il giocatore corrente è sotto scacco oppure 
     * @return false se il giocatore corrente è sotto scacco matto
     */
    bool printStateMatch() const;

    /**
     * @brief Questa funzione si occupa di gestire la parte dell'interfaccia che riguarda la vera e propria partita
     * 
     */
    void loopMatch() const;
};

#endif // __Game_H__