#ifndef __ENGINE_H__
#define __ENGINE_H__

/**
 * @file Engine.h
 * @author Emanuele Vita
 * @brief
 * @version 0.1
 * @date 26-01-2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Player.h"
#include "Board.h"
#include <string>
#include <cstring>
#include <fstream>

/**
 * @brief enumerazione utile per definire all'inizio la situazione del giocatore,
 *        ovvero se è sotto scacco, sotto scacco matto oppure nessuno dei due
 *
 */
enum StateMatch
{
    NONE = 0,
    CHECK,
    CHECKMATE
};

/**
 * @brief Questa funzione implementa il motore vero e proprio del gioco
 *
 */
class Engine
{
public:
    /**
     * @brief Costruttore
     *
     */
    Engine();

    /**
     * @brief Distruttore
     *
     */
    ~Engine();

    /**
     * @brief Questa funzione serve ad accedere al giocatore corrente, ovvero il giocatore che sta effettuando il turno
     *
     * @return Puntatore al giocatore corrente
     */
    Player *getcurrentPlayer() const { return currPlayer; }

    /**
     * @brief Questa funzione serve ad accedere al giocatore avversario
     *
     * @return Puntatore al giocatore avversario
     */
    Player *getOpposingplayer() const;

    /**
     * @brief Questa funzione serve ad accedere alla scacchiera su cui si sta giocando
     *
     * @return Board&
     */
    Board *getPlayingBoard() const { return playingBoard; }

    /**
     * @brief Questa funzione provvede a iniziare una nuova partita, provvedendo a posizionare in modo corretto i pezzi sulla scacchiera
     *
     */
    void newGame();

    /**
     * @brief Questa funzione provvede a caricare lo stato di una partita da file e quindi continuarla
     *
     * @param fileName nome del file da cui si vuole caricare una partita
     * @return true se l processo va a buon fine
     * @return false se il prosesso termina in modo sbagliato
     */
    bool loadGame(const std::string &fileName);

    /**
     * @brief Questa funzione provvede a salvare lo stato della partita in corso su file
     *
     * @param fileName nome del file su cui si vuole caricare la partita
     * @return true se l processo va a buon fine
     * @return false se il prosesso termina in modo sbagliato
     */
    bool saveGame(const std::string &fileName);

    /**
     * @brief Questa funzione si occupa di effettuare la mossa espessa nella stringa passata come parametro
     *
     * @param moveStr stringa che corrisponde alla mossa che il giocatore vuole fare
     */
    bool turn(const std::string &moveStr);

    /**
     * @brief Restituisce in che condizione è il giocatore corrente ovverso se è sotto scacco, sotto scacco matto oppure nessuno dei due
     *
     * @return StateMatch
     */
    StateMatch stateplayer() const;

private:
    const static unsigned short N_PLAYERS = 2U; ///< numero di giocatori in una partita
    Player *players[N_PLAYERS];                 ///< Vettore che contiene i giocatori coinvolti nella partita
    Player *currPlayer;                         ///< Puntatore al giocatore corrente
    Board *playingBoard;                        ///< Puntatore all'oggetto Board che rappresenta la scacchiera su cui avviene la partita

    /**
     * @brief Funzione privata ausiliaria che permette di trasformare una stringa in un vettore di puntatori a Tile
     *
     * @param in Stream da cui si vuole leggere la linea
     * @param v vettore di Tile
     * @param delim Delimitatore
     */
    void line2vec(std::ifstream &in, std::vector<Tile *> &v, char *delim);
    const static unsigned int MAX_LINE = 100; ///< Constante

    /**
     * @brief Imposta il giocatore avversario del turno corrente come giocatore corrente per il prossimo turno
     *
     */
    void nextTurn() { currPlayer = getOpposingplayer(); }
};

#endif // __ENGINE_H__