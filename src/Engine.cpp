/**
 * @file Engine.cpp
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

#pragma warning(disable : 4996)

Engine::Engine()
{
    //
    players[0] = new Player(WHITE);
    players[1] = new Player(BLACK);

    currPlayer = 0;

    playingBoard = new Board();
}

Engine::~Engine()
{
    delete players[0];
    delete players[1];

    delete playingBoard;
}

Player *Engine::getOpposingplayer() const
{
    if (currPlayer == 0)
        return 0;

    return (currPlayer == players[0]) ? players[1] : players[0];
}

void Engine::newGame()
{
    // per iniziare un nuova partita mi riconduco ad usare la funzione loadGame passandogli il nome del file con le posizioni iniziali
    loadGame("file/InitGame.txt");
}

bool Engine::loadGame(const std::string &fileName)
{
    std::ifstream fin;

    fin.open(fileName);

    if (!fin)
    {
        std::cerr << "ERRORE::LOADGAME\n";
        return false;
    }

    for (int i = 0; i < N_PLAYERS; i++)
    {
        std::vector<Tile *> vecTemp;

        // acquisisco la prima riga del file e la trasformo in un vettore di puntatori a Tile
        line2vec(fin, vecTemp, (char *)"-");

        //
        players[i]->setPosPieces(vecTemp);
    }

    // analizzo l'ultima riga del file per capire quale è il giocatore che deve giocare il prossimo turno
    std::string strTemp;

    getline(fin, strTemp);

    // a questo punto posso già chiudere il file
    fin.close();

    if (strTemp == "WHITE")
        currPlayer = players[0];
    else if (strTemp == "BLACK")
        currPlayer = players[1];
    else
        return false;

    return true;
}

bool Engine::saveGame(const std::string &fileName)
{
    std::ofstream fout;

    fout.open(fileName, std::ios::out | std::ios::app);

    if (!fout)
    {
        std::cerr << "ERRORE::SAVEGAME\n";
        return false;
    }

    for (int i = 0; i < N_PLAYERS; i++)
    {
        // acquisisco il vettore con i puntatori ai tasselli occupati dai pezzi del giocatore
        std::vector<Tile *> posPieces = players[i]->getPosPieces();

        for (int j = 0; j < posPieces.size() - 1; j++)
            fout << posPieces[j]->getFile() << posPieces[j]->getRank() << "-";

        fout << posPieces[posPieces.size()]->getFile() << posPieces[posPieces.size()]->getRank() << "\n";
    }

    // nell'ultima riga inserisco la sigla del giocatore che dovrebbe fare il prossimo turno
    fout << (currPlayer->getColor() == WHITE) ? "WHITE" : "BLACK";

    return true;
}

bool Engine::turn(const std::string &moveStr)
{
    // innanzitutto verifico che la stringa sia della lunghezza giusta, 5 caratteri e nel formato corretto,
    // ovvero A5-b6 per esempio. Le lettere possono essere maiuscole o minuscole
    if (moveStr.size() == 5)
    {
        if (isalpha(moveStr[0]) && isdigit(moveStr[1]) && moveStr[2] == '-' && isalpha(moveStr[3]) && isdigit(moveStr[4]))
        {
            // adesso controllo che la casa indicata dalle prime due lettere di moveStr sia del giocatore corrente
            if ((*playingBoard)(moveStr.substr(0, 2).c_str())->isOccupedBySamePlayer(currPlayer))
            {
                if (playingBoard->movePiece(moveStr))
                {
                    // arrivato qui
                    nextTurn();

                    return true;
                }
            }
        }
    }

    return false;
}

StateMatch Engine::stateplayer() const
{
    // innanzitutto vedo se il re del giocatore corrente è sotto scacco
    std::vector<Piece *> pieceCapturedKing;

    getOpposingplayer()->canCapturePiece(getcurrentPlayer()->getKing(), pieceCapturedKing);

    if (pieceCapturedKing.size() == 0)
        return NONE;

    // a questo punto vedo se il re per levarsi dallo scacco puù muoversi
    if (getcurrentPlayer()->kingCanMove(*getOpposingplayer()))
        return CHECK;

    // se il numero di pezzi che possono catturare il re è uno, a questo punto posso pensare di catturarlo o di interporvi un pezzo del giocatore corrente
    if (pieceCapturedKing.size() == 1)
    {
        // utilizzo un vettore temporaneo la funzione canCapturePiece
        std::vector<Piece *> vecTemp;

        // acquisisco in vecTemp tutti i Pezzi che possono catturare pieceCapturedKing[0]
        getcurrentPlayer()->canCapturePiece(pieceCapturedKing[0], vecTemp);

        if (vecTemp.size() != 0)
            return CHECK;

        // se il pezzo che ha sotto scacco il re è un cavallo è inutile fare ciò
        if (pieceCapturedKing[0]->getSymbol() == 'N')
            return CHECKMATE;

        // adesso riutilizzo vecTemp per capire se posso interporre un pezzo tra il re e quello che lo vuole catturare
        if (currPlayer->canInsertPiece(currPlayer->getKing(), pieceCapturedKing[0]))
            return CHECK;

        return CHECKMATE;
    }

    // se il numero di pezzi che possono catturare il re sono più di uno, allora se anche ne catturassi uno o interponessi un altro pezzo tra i due,
    // avrei comunque un altro pezzo che potrebbe tranquillamente fare scaccomatto
    return CHECKMATE;
}

void Engine::line2vec(std::ifstream &in, std::vector<Tile *> &v, char *delim)
{
    char str[MAX_LINE], c, *tok;
    // Estrazione della linea dallo stream
    in.getline(str, MAX_LINE);

    // Si controlla che non sia vuota
    if (strlen(str) == 0)
        return;

    // Estrazione dei valori dalla linea
    tok = strtok(str, delim);

    strcmp(tok, "00") == 0 ? v.push_back(0) : v.push_back((*playingBoard)(tok));

    while (tok = strtok(0, delim))
        strcmp(tok, "00") == 0 ? v.push_back(0) : v.push_back((*playingBoard)(tok));

    return;
}
