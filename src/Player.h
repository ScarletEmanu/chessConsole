#ifndef __PLAYER_H__
#define __PLAYER_H__

/**
 * \enum ColorPiece
 * @brief Enumerazione che contiene i possibili colori per i giocatori e per i pezzi
 * 
 */
enum ColorPiece {
    WHITE = 0,
    BLACK
};

#include "Piece.h"
#include "Tile.h"
#include <vector>
#include <string>

class Board;
class Tile;
class Piece;
class King;

/**
 * \brief    Questa classe contiene tutto ciò che serve per definire un giocatore, come il colore, il nome e i suoi pezzi
 */
class Player
{
public:

    /**
     * @brief Costruttore parametrizzato
     * 
     * @param c colore del gicatore e di tutti i pezzi
     * @param n nome del giocatore
     */
    Player(ColorPiece c, const std::string& n = "");

    /**
     * @brief Distruttore
     * 
     */
    ~Player();

    /**
     * @brief Accede al colore del giocatore
     * 
     * @return ColorPiece 
     */
    ColorPiece getColor() const { return color;}

    /**
     * @brief Accede al nome del giocatore
     * 
     * @return const std::string& 
     */
    const std::string& getName() const { return name;}

    /**
     * @brief Modifica il nome del giocatore
     * 
     * @param n nuovo nome
     */
    void setName(const std::string& n = "");

    /**
     * @brief Modifica tutte le posizioni dei pezzi del giocatore
     * 
     * @param pos Vettore di puntatori a Tile che rappresentano le nuove case di destinazione dei pezzi
     */
    void setPosPieces(std::vector<Tile*> pos);

    /**
     * @brief Accede alle posizioni dei pezzi del giocatore
     * 
     * @return std::vector<Tile*> 
     */
    std::vector<Tile*> getPosPieces() const;

    /**
     * @brief Accede al re del giocatore
     * 
     * @return Piece* 
     */
    Piece* getKing() const {return setPiece[0];}

    /**
     * @brief Questa funzione controlla se il re di questo giocatore può muoversi in altre case senza che sia di nuovo sotto rischio di cattura
     * 
     * @param opposing Giocatore avversario
     * @return true se il re può muoversi in libertà
     * @return false se il re può muoversi in libertà
     */
    bool kingCanMove(const Player& opposing) const;

    /**
     * @brief Questa funzione controlla quali pezzi possono catturare quello passato come parametro
     * 
     * @param piece pezzo da controllare
     * @param v vettore che conterra alla fine della funzione tutti i pezzi che possono catturare piece
     */
    void canCapturePiece(Piece* piece, std::vector<Piece*>& v) const;

    /**
     * @brief Questa funzione serve a controllare se si possono inserire altri pezzi tra un proprio pezzo e uno avversario
     * 
     * @param piece Puntatore ad un proprio pezzo
     * @param pieceOpp Puntatore ad un pezzo avversario
     * @return true se è possibile inserire pezzi tra piece e pieceOpp
     * @return false se non è possibile inserire pezzi tra piece e pieceOpp
     */
    bool canInsertPiece(Piece* piece, Piece* pieceOpp) const;
private:
    std::string name; ///< Il nome del giocatore
    ColorPiece color; ///< Il colore del giocatore e quindi dei suoi pezzi. Può essere Bianco e Nero
    const static unsigned int N_PIECES = 16; ///< Numero di pezzi che spettano ad un giocatore
    std::vector<Piece*> setPiece; ///< Un vettore che contiene tutti i puntatori ai pezzi del giocatore
    Board* playingBoard; ///< Puntatore alla scacchiera in cui si sta giocando
};

#endif // __PLAYER_H__
