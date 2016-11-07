#include "SFMLCanvas.hh"
#include "Game.hpp"
#include <QLabel>

void SFMLCanvas::setGame(Game *game)
{
  currentGame = game;
}

void SFMLCanvas::OnInit()
{
    this->winner = -1;
    for (int i = 0; i < 19; i++)
    {
        for (int e = 0; e < 19; e++)
        {
           pieces[i][e] = 0;
        }
    }
    this->currentPlayer = 'b';
    this->backgroundTexture.loadFromFile("ressources/back.jpg");
    this->whitePieceTexture.loadFromFile("ressources/white.png");
    this->blackPieceTexture.loadFromFile("ressources/black.png");
    this->whiteWinTexture.loadFromFile("ressources/whiteWin.png");
    this->blackWinTexture.loadFromFile("ressources/blackWin.png");
    this->invalidPieceTexture.loadFromFile("ressources/invalid.png");
    this->whitePlayerTexture.loadFromFile("ressources/whiteTurn.png");
    this->blackPlayerTexture.loadFromFile("ressources/blackTurn.png");
    this->pieceText.loadFromFile("ressources/black_transp.png");

    this->background.setTexture(this->backgroundTexture);
    this->background.scale(RenderWindow::getView().getSize() / 600.f);
    this->background.setOrigin(this->background.getScale() / 2.f);
    this->whitePiece.setTexture(this->whitePieceTexture);
    this->whitePiece.setScale(RenderWindow::getView().getSize() / 1800.f);
    this->blackPiece.setTexture(this->blackPieceTexture);
    this->blackPiece.setScale(RenderWindow::getView().getSize() / 1800.f);
    this->invalidPiece.setTexture(this->invalidPieceTexture);
    this->invalidPiece.setScale(RenderWindow::getView().getSize() / 1800.f);
    this->piece.setTexture(this->pieceText);
    this->piece.setScale(RenderWindow::getView().getSize() / 1800.f);
    this->whiteWin.setTexture(this->whiteWinTexture);
    this->blackWin.setTexture(this->blackWinTexture);
    this->whitePlayer.setTexture(this->whitePlayerTexture);
    this->blackPlayer.setTexture(this->blackPlayerTexture);
    this->blackPlayer.setPosition(170, 0);
    this->whitePlayer.setPosition(170,0);
    this->whiteWin.setPosition(120, 150);
    this->blackWin.setPosition(120, 150);

    /*
    this->pieces[0][0] ='b';
    this->pieces[0][18] ='b';
    this->pieces[18][0] ='b';
    this->pieces[18][18] ='b';
    */
}

void SFMLCanvas::OnUpdate()
{
    this->handleEvent();
    this->drawState();
    myClock.restart();
}

void    SFMLCanvas::handleEvent()
{
    static bool wasPressed = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !wasPressed)
   {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this);
        sf::Vector2f screenPos = RenderWindow::mapPixelToCoords(mousePos);
        sf::Vector2i pionPos = screenToGamePos(screenPos);

        if (pionPos.x >= 0 && pionPos.x < 19 && pionPos.y >= 0 && pionPos.y < 19)
            this->trySetPiece(pionPos.x, pionPos.y);
        wasPressed = true;
    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && wasPressed)
        wasPressed = false;

}

void    SFMLCanvas::drawState()
{
    RenderWindow::clear(sf::Color(0, 128, 0));
    RenderWindow::draw(this->background);

    QLabel *label = this->qt->findChild<QLabel *>("playerTurn");
    if (currentPlayer == 'b')
      label->setText("White turn");
    else if (currentPlayer == 'w')
      label->setText("Black turn");
    for (int i = 0; i < 19; i++)
    {
        for (int e = 0; e < 19; e++)
        {
            if (this->pieces[i][e] == 'b')
                this->drawPiece(i,e, this->blackPiece);
            else if (this->pieces[i][e] == 'w')
                this->drawPiece(i, e, this->whitePiece);
            else if (this->pieces[i][e] < -1)
            {
                this->drawPiece(i, e, this->invalidPiece);
                this->pieces[i][e]++;
            }
        }
    }
    this->drawTips();
    if (winner != -1)
        drawWinner(winner);
}

void    SFMLCanvas::drawPiece(unsigned int x, unsigned int y, sf::Sprite & piece)
{
    sf::Vector2f   win_size;
    sf::Vector2f   coef;

    win_size = RenderWindow::getView().getSize();
    coef.x = win_size.x / 600.f;
    coef.y = win_size.y / 600.f;

    piece.setPosition(x*((win_size.x - (82.f*(coef.x)) * 2)/19.f )+ 84.f*(coef.x),
                      y*((win_size.y - (82.f*(coef.y)) * 2)/19.f )+ 84.f*(coef.y));
    RenderWindow::draw(piece);
}

void    SFMLCanvas::setPiece(unsigned int x, unsigned int y, char color)
{
    this->pieces[x][y] = color;
}

sf::Vector2i    SFMLCanvas::screenToGamePos(sf::Vector2f &pos)
{
    sf::Vector2i   gamePos;
    sf::Vector2f   win_size;
    sf::Vector2f   coef;

    win_size = RenderWindow::getView().getSize();
    coef.x = win_size.x / 600.f;
    coef.y = win_size.y / 600.f;

    gamePos.x  = nearbyint((pos.x - 84.f*coef.x) / ((win_size.x - (82.f*(coef.x)) * 2)/19.f ));
    gamePos.y  = nearbyint((pos.y - 84.f*coef.y) / ((win_size.y - (82.f*(coef.y)) * 2)/19.f ));
    return (gamePos);
}

void    SFMLCanvas::addPiece(const std::string &color, unsigned int x, unsigned int y)
{
    if (color.compare("black") == 0)
        this->setPiece(x, y, 'b');
    else if (color.compare("white") == 0)
        this->setPiece(x, y, 'w');
}

void    SFMLCanvas::drawWinner(char winner)
{
    if (winner == 'w')
        RenderWindow::draw(this->whiteWin);
    if (winner == 'b')
        RenderWindow::draw(this->blackWin);
}

void    SFMLCanvas::setWinner(const std::string &color)
{
    if (color.compare("black") == 0)
        this->winner = 'b';
    else if (color.compare("white") == 0)
        this->winner = 'w';
}

void    SFMLCanvas::trySetPiece(unsigned int x, unsigned int y)
{
    std::string     piece;
    piece = currentGame->play(x,y);
    // piece = Appel methode arbitre pour savoir si on peu poser le pion (retourne black, white ou invalid
    if (piece.compare("black") == 0)
        this->pieces[x][y] = 'b';
    else if (piece.compare("white") == 0)
        this->pieces[x][y] = 'w';
    else if (pieces[x][y] == 'b' || pieces[x][y] == 'w')
        {
        }
    else
       this->pieces[x][y] = -700;
}

void    SFMLCanvas::setCurrentPlayer(const std::string &color)
{
    if (color.compare("black") == 0)
        this->currentPlayer = 'b';
    else if (color.compare("white") == 0)
        this->currentPlayer = 'w';
}

 void    SFMLCanvas::updateStat(const std::string &turn, const std::string &black, const std::string &white)
{
   QLabel *label = this->qt->findChild<QLabel *>("turn");
   label->setText(turn.c_str());
   label = this->qt->findChild<QLabel *>("blackScore");
   label->setText(black.c_str());
   label = this->qt->findChild<QLabel *>("whiteScore");
   label->setText(white.c_str());
}

void    SFMLCanvas::removePiece(unsigned int x, unsigned int y)
{
    this->pieces[x][y] = -1;
}

void    SFMLCanvas::drawTips()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this);
    sf::Vector2f screenPos = RenderWindow::mapPixelToCoords(mousePos);
    sf::Vector2i pionPos = screenToGamePos(screenPos);

    if (pionPos.x >= 0 && pionPos.x < 19 && pionPos.y >= 0 && pionPos.y < 19)
        this->drawPiece(pionPos.x, pionPos.y, this->piece);
}
