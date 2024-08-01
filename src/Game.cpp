/**
 * @file Game.cpp
 * @author Emanuele Vita
 * @brief 
 * @version 0.1
 * @date 29-01-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Game.h"

#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR_SCREEN system("cls")
#elif defined(__unix__) || defined(__unix) || defined(__linux__) || defined(__APPLE__)
    #define CLEAR_SCREEN system("clear")
#else
    std::cout << "Sistema operativo non riconosciuto" << std::endl;
#endif

Game::Game() 
{
    //inizializzo l'oggetto engChess
    engChess = new Engine();

    //inizializzo le variabili per i vari colori del terminale
    colTileDark = "\033[48;2;128;128;128m";
    colTileLight = "\033[48;2;0;100;0m";
    codeReset = "\033[0m";
    textRed = "\033[31m";
    boldText = "\033[1m";
}

void Game::run() 
{
    printInitMenu();
    CLEAR_SCREEN;

    printChessBoard(engChess->getPlayingBoard());

    char choices;

    std::cout << "Scegliere di nuovo quale azione si vuole compiere:\n";
    std::cout << "1) (N)uova Partita;\n";
    std::cout << "2) (C)aricare partita da file.\n";
    std::cout << "Fai la tua scelta: ";
    choices = std::cin.get();

    while(toupper(choices) != 'N' && toupper(choices) != 'C')
    {
        std::cout << "\n\nInput errato!!!\n";
        std::cout << "Scegliere di nuovo quale azione si vuole compiere:\n";
        std::cout << "1) (N)uova Partita;\n";
        std::cout << "2) (C)aricare partita da file.\n";
        std::cout << "Fai la tua scelta: ";
        choices = std::cin.get();
    }

    toupper(choices) == 'C' ? printLoadGame() : engChess->newGame();
    
    CLEAR_SCREEN;

    loopMatch();
    
}

void Game::printInitMenu() const
{
    //parte in cui si spiegano le regole dell'applicazione specifica
    std::cout << "Questa applicazione permette di giocare al gioco degli scacchi tra due umani da terminale e attraverso la tastiera.\n";
    std::cout << "Questa e' una schermata che riepiloga le regole del gioco. Una volta lasciata questa schermata si puo' scegliere se iniziare una nuova partita, ";
    std::cout << "premendo la lettera N da tastiera, oppure caricare una partita gia' iniziata da file, premendo la lettera C da tastiera, e in quest'ultimo caso bisogna anche in seguito specificare il file da cui si desidera scaricare il file.\n";
    std::cout << "Una volta effettuate queste operazioni si puo' incominciare a giocare, specificando di volta in volta le coordinate del pezzo che si vuole spostare e le coordinate della casa di destinazione, separate da un trattino. ";
    std::cout << "Una volta iniziato il gioco vero e proprio, in qualunque turno, si puo' uscire dal gioco premendo U, oppure salvare la partita su un file, premendo S, e anche in quest'ultimo caso devo in seguito specificare il file in cui si desidera salvare la partita. ";
    std::cout << "Per ogni passaggio il carattere da specificare per le varie azioni, comprese per le mosse, puo' essere sia maiuscolo che minuscolo. ";
    std::cout << "Il gioco durante la partita provvede a specificare chi e' il giocatore che deve giocare nel turno specifico e se esso e' sotto scacco da parte dell'avversario o e' sotto scacco matto e in quest'ultimo caso chiude la partita.\n";
    std::cout << "Premere il tasto Invio per passare alla prossima schermata: ";
    char ch = std::cin.get();

    //parte in cui si spiega le regole degli scacchi
    std::cout << "Nel gioco degli scacchi sono presenti due giocatori, che si pongono ai due lati opposti della scacchiera e sono contraddistinti da un colore (di solito Bianco e Nero). ";
    std::cout << "Ogni giocatore ha a disposizione 16 pezzi: 1 Re, 1 Regina, 2 Alfieri, 2 Cavalli, 2 Torri, 8 Pedoni. L'obiettivo del gioco e' quello di dare scacco matto al re avversario. ";
    std::cout << "Si ha lo scacco matto quando il re avversario viene messo nella condizione di essere inevitabilmente catturato (ovvero si trova \"sotto scacco\") ed in cui, anche muovendo, gli sarebbe comunque impossibile sfuggire alla cattura. ";
    std::cout << "Il giocatore con i pezzi bianchi muove sempre per primo. Per questo motivo in genere i giocatori tirano a sorte per chi terra' il Bianco. A questo punto, il Bianco fara' la sua mossa, seguita da quella de Nero: muovera' poi di nuovo il Bianco e poi ancora il Nero... e cosi via fino alia fine della partita. ";
    std::cout << "Ogni casa ha il proprio nome, che e' formato dalle sue coordinate, cioe' una lettera e un numero, quindi per indicare con precisione ogni singola casa della scacchiera e il movimento di tutti i pezzi. Ciascuno dei 6 diversi tipi di pezzi muove diversamente. ";
    std::cout << "In generale, i pezzi non possono passare 'attraverso' gli altri pezzi (benche' il cavallo possa saltarli), ne' possono occupare una casa gia' occupata da un altro pezzo del proprio stesso colore. Tuttavia possono prendere il posto di un pezzo avversario, che in questo caso viene catturato.";
    std::cout << "\n\nRE:\n";
    std::cout << "Il Re e' il pezzo piu' importante, ma e' anche il pezzo piu' debole ed ha bisogno di attenta protezione. Contro di lui, infatti, si rivolgono gli attacchi dell'avversario e la sua \"cattura\" determina la fine della partita. ";
    std::cout << "Puo' muoversi solo di una casa alla volta, nelle 8 direzioni - avanti, indietro, ai 2 lati e in obliquo.";
    std::cout << "\n\nDONNA:\n";
    std::cout << "La Donna e' il pezzo piu' potente. Puo' muoversi in qualsiasi direzione - in avanti, indietro (colonna), a destra e a sinistra (traversa) o lungo le diagonali - seguendo una linea retta e di quante case vuole, ma solo fino a che non incontra un pezzo del proprio schieramento (dato che non puo' passarci attraverso).";
    std::cout << "\n\nTORRE:\n";
    std::cout << "La Torre puo' muoversi di quante case vuole, ma solo lungo le colonne e le traverse (in avanti, indietro e di lato a destra o a sinistra).";
    std::cout << "\n\nALFIERE:\n";
    std::cout << "L'Alfiere puo' muoversi di quante case vuole, avanti e indietro, ma solo in diagonale. Ciascun alfiere comincia su una casa di colore diverso (bianco o nero), e rimare sempre sulle case di quel colore.";
    std::cout << "\n\nCAVALLO:\n";
    std::cout << "I Cavalli si muovono in modo molto diverso dagli altri pezzi. Il movimento del Cavallo si puo' spiegare ricorrendo alla figura della “L” infatti il Cavallo si muove di 2 case lungo una traversa o colonna (in avanti, indietro e di lato a destra o a sinistra) e poi si muove di un'altra casa in direzione perpendicolare. I cavalli sono gli unici pezzi che possono scavalcare tutti gli altri;";
    std::cout << "\n\nPEDONI:\n";
    std::cout << "I Pedoni hanno la particolarita' di muoversi e di catturare in due modi diversi: si muovono in avanti, ma catturano in diagonale. I pedoni possono solo avanzare e di una sola casa per volta. Quando un pedone si muove per la prima volta puo' pero' avanzare anche di due case. I pedoni catturano solo sulle case poste immediatamente davanti a loro in diagonale. Non possono mai indietreggiare ne' catturare all'indietro.\n";
    std::cout << "Premere il tasto Invio per entrare nel vivo del gioco:";
    ch = std::cin.get();
}


void Game::printChessBoard(Board* b) const
{
    std::cout << "   A      B      C      D      E      F      G      H\n\n";

    for (int i = 8; i > 0; i--)
    {
        if (i % 2 == 1)
            printLineBoard(i, colTileLight, colTileDark, b);
        else
            printLineBoard(i, colTileDark, colTileLight, b);
    }
}

void Game::printLineBoard(unsigned short n_line, std::string firstColor, std::string secondColor, Board* b) const
{
    for (int i = 0; i < CELL / 2; i++)
    {
        //ogni linea della scacchiera e' formata da 8 celle che pero' possono essere raggruppate in 4 gruppi di 2 celle di colori alterni
        for (int j = 0; j < 4; j++)
        {
            //prima casa della coppia
            for (int z = 0; z < CELL; z++)
            {
                std::cout << firstColor;

                if (i == 1 && z == 3)
                {
                    //std::cerr << std::boolalpha << "{oper: " << (*b)(n_line, j * 2 + 1)->isOccuped() << "}";
                    std::cout << (*b)(j * 2 + 1, n_line)->toString();
                }
                else
                    std::cout << " ";
            }

            //seconda casa della coppia
            for (int z = 0; z < CELL; z++)
            {
                std::cout << secondColor;

                if (i == 1 && z == 3)
                    std::cout << (*b)(j * 2 + 2, n_line)->toString();
                else
                    std::cout << " ";
            }
        }

        //riporto il colore alla normalita'
        std::cout << codeReset;

        if (i == 1)
            std::cout << "   " << n_line;
        
        std::cout << "\n";  
    }     
}

void Game::printTitle() const
{
    std::cout << textRed;
    std::cout << "    ======================================\n";
    std::cout << "       _____ _    _ ______  _____ _____\n";
    std::cout << "      / ____| |  | |  ____|/ ____/ ____|\n";
    std::cout << "     | |    | |__| | |__  | (___| (___ \n";
    std::cout << "     | |    |  __  |  __|  \\___ \\\\___ \\ \n";
    std::cout << "     | |____| |  | | |____ ____) |___) |\n";
    std::cout << "      \\_____|_|  |_|______|_____/_____/\n\n";
    std::cout << "    ======================================\n\n";
    std::cout << codeReset;
}

void Game::printLoadGame() const
{
    std::string fileName;

    std::cout << "\nScrivere il nome del file da cui si vuole caricare la partita: ";
    std::cin.ignore();
    std::getline(std::cin, fileName);

    while(!engChess->loadGame(fileName))
    {
        std::cout << "\nErrore nell'apertura del file o nel formato del file stesso.\n";
        std::cout << "Riscrivere il nome del file da cui si vuole caricare la partita: ";
        std::cin.ignore();
        std::getline(std::cin, fileName);
    }
}

void Game::printSaveGame() const
{
    std::string fileName;

    std::cout << "\nScrivere il nome del file in cui si vuole salvare la partita: ";
    std::cin.ignore();
    std::getline(std::cin, fileName);
    
    while(!engChess->saveGame(fileName))
    {
        std::cout << "\nErrore nell'apertura del file.\n";
        std::cout << "Ricrivere il nome del file in cui si vuole salvare la partita: ";
        std::cin.ignore();
        std::getline(std::cin, fileName);
    }
}

bool Game::printStateMatch() const
{
    StateMatch StateMatch = engChess->stateplayer();

    if(StateMatch == NONE)
        return false;
    else if(StateMatch == CHECK)
    {
        std::cout << "\n" << engChess->getcurrentPlayer()->getName() << " sei sotto scacco!!!!\n";

        return false;
    }
    //se il giocatore e' sotto scacco matto cancello tutto sullo schermo e visualizzo una frase
    else
    {
        CLEAR_SCREEN;

        std::cout << "\n\n\n";

        printChessBoard(engChess->getPlayingBoard());

        std::cout << "\n\n\n" << textRed << engChess->getOpposingplayer()->getName() << " HAI VINTO!";

        return true;
    }
}

void Game::loopMatch() const
{
    while(true)
    {
        printTitle();

        printChessBoard(engChess->getPlayingBoard());

        bool statePlayer;
        if (statePlayer = printStateMatch())
        {
            
        }

        std::string choice;

        std::cout << "\n" << engChess->getcurrentPlayer()->getName() << " e' il tuo turno. Puoi decidere di effettuare una mossa o di salvare la partita, premendo S, o di uscire dal gioco premendo U." << "\n";
        std::cout << "Fai la tua mossa: ";
        std::cin.ignore();
        std::getline(std::cin, choice);

        while(toupper(choice[0]) != 'U' && toupper(choice[0]) != 'S' && !engChess->turn(choice))
        {
            std::cout << "\n\nInput errato!!!!!!!!\n";
            std::cout << engChess->getcurrentPlayer()->getName() << " e' il tuo turno. Puoi decidere di effettuare una mossa o di salvare la partita, premendo S, o di uscire dal gioco premendo U." << "\n";
            std::cout << "Fai la tua mossa: ";
            std::cin.ignore();
            std::getline(std::cin, choice);
        }

        if (toupper(choice[0]) == 'U')
            break;
        else if (toupper(choice[0]) == 'S')
            printSaveGame();

        CLEAR_SCREEN;
    }
}

