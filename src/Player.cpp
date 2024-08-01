#include "Player.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Rook.h"

Player::Player(ColorPiece c, const std::string& n) 
{
    color = c;

    setName(n);

    setPiece.resize(N_PIECES);

    //crei i pezzi del giocatore e li posiziono fuori dalla scacchiera
    setPiece[0] = new King(c);
    setPiece[1] = new Queen(c);
    setPiece[2] = new Bishop(c);
    setPiece[3] = new Bishop(c);
    setPiece[4] = new Knight(c);
    setPiece[5] = new Knight(c);
    setPiece[6] = new Rook(c);
    setPiece[7] = new Rook(c);
    setPiece[8] = new Pawn(c);
    setPiece[9] = new Pawn(c);
    setPiece[10] = new Pawn(c);
    setPiece[11] = new Pawn(c);
    setPiece[12] = new Pawn(c);
    setPiece[13] = new Pawn(c);
    setPiece[14] = new Pawn(c);
    setPiece[15] = new Pawn(c);
}

Player::~Player()
{
    for (auto p : setPiece)
        delete p;
}

void Player::setName(const std::string& n) 
{
    name = n;

    //se n era vuoto dò come nomi Bianco o Nero, in base al colore del giocatore
    if(name == "")
        name = color == WHITE ? "Bianco" : "Nero";
}

void Player::setPosPieces(std::vector<Tile*> pos) 
{
    for (int i = 0; i < setPiece.size(); i++)
    {
        setPiece[i]->movePiece(pos[i]);
        pos[i]->setOccupant(setPiece[i]);
    }
}

bool Player::kingCanMove(const Player& opposing) const
{
    //innanzitutto vedo se il re si può muovere
    std::vector<Tile*> possMove;

    getKing()->canMove(possMove, *playingBoard);

    if (possMove.size() == 0)
    {
        return false;
    }

    //se il re può muoversi, controllo se facendo queste mosse comunque il re va sotto scacco

    Tile* actualPosKing = getKing()->getOccupingTile();
    std::vector<Piece*> tempVec;

    for (auto t : possMove)
    {
        //sposto il re nelle celle possibili
        getKing()->movePiece(t);
        
        opposing.canCapturePiece(getKing(), tempVec);
        
        if (tempVec.size() != 0)
            return false;
    }

    //a questo punto il re ha a disposizione almeno una casella in cui spostarsi e non essere sotto attacco,
    //quindi riporto il re alla pos iniziale e ritorno dalla funzione true

    getKing()->movePiece(actualPosKing);

    return true;
}

std::vector<Tile*> Player::getPosPieces() const
{
    std::vector<Tile*> posPieces;

    for (auto p : setPiece)
        posPieces.push_back(p->getOccupingTile());

    return posPieces;
}

void Player::canCapturePiece(Piece* piece, std::vector<Piece*>& v) const
{
    v.clear();

    for(auto p: setPiece)
    {
        if (p->isLegalMove(*(piece->getOccupingTile()), *playingBoard))
            v.push_back(piece);
    }

    return;
}

bool Player::canInsertPiece(Piece* piece, Piece* pieceOpp) const
{
    //se piece è un Pedone allora non posso interporre nessun pezzo tra i due pezzi,
    //in quanto il pedone sarà nelle immediate vicinanze del pezzo avversario
    if (piece->getSymbol() == 'P')
        return false;

    std::vector<Tile*> tilesBetween;
    piece->tilesBetween(tilesBetween, *(pieceOpp->getOccupingTile()), *playingBoard);

    //scorro tutte le celle trovate e vedo se ci sono dei pezziche possono spostarsi sulla casa
    for (auto t : tilesBetween)
        for (auto p : setPiece)
        {
            if (p->isLegalMove(*t, *playingBoard))
                return true;
        }
    
    return false;
}

