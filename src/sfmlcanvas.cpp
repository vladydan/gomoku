#include "SFMLCanvas.hh"


void SFMLCanvas::setGame(Game *game)
{
  currentGame = game;
}

void SFMLCanvas::OnInit()
{
    this->winner = -1;for (int i = 0; i < 19; i++)
    {
        for (int e = 0; e < 19; e++)
        {
           pieces[i][e] = 0;
        }
    }
    this->currentPlayer = 'w';
    this->backgroundTexture.loadFromFile("ressources/back.jpg");
    this->whitePieceTexture.loadFromFile("ressources/white.png");
    this->blackPieceTexture.loadFromFile("ressources/black.png");
    this->whiteWinTexture.loadFromFile("ressources/whiteWin.png");
    this->blackWinTexture.loadFromFile("ressources/blackWin.png");
    this->invalidPieceTexture.loadFromFile("ressources/invalid.png");
    this->whitePlayerTexture.loadFromFile("ressources/whiteTurn.png");
    this->blackPlayerTexture.loadFromFile("ressources/blackTurn.png");

    this->background.setTexture(this->backgroundTexture);
    this->background.scale(RenderWindow::getView().getSize() / 600.f);
    this->background.setOrigin(this->background.getScale() / 2.f);
    this->whitePiece.setTexture(this->whitePieceTexture);
    this->whitePiece.setScale(RenderWindow::getView().getSize() / 1800.f);
    this->blackPiece.setTexture(this->blackPieceTexture);
    this->blackPiece.setScale(RenderWindow::getView().getSize() / 1800.f);
    this->invalidPiece.setTexture(this->invalidPieceTexture);
    this->invalidPiece.setScale(RenderWindow::getView().getSize() / 1800.f);

    this->whiteWin.setTexture(this->whiteWinTexture);
    this->blackWin.setTexture(this->blackWinTexture);
    this->whitePlayer.setTexture(this->whitePlayerTexture);
    this->blackPlayer.setTexture(this->blackPlayerTexture);
    this->blackPlayer.setPosition(170, 0);
    this->whitePlayer.setPosition(170,0);
    this->whiteWin.setPosition(120, 150);
    this->blackWin.setPosition(120, 150);

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

    if (currentPlayer == 'b')
        RenderWindow::draw(this->blackPlayer);
    else if (currentPlayer == 'w')
        RenderWindow::draw(this->whitePlayer);
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
    if (winner != -1)
        drawWinner(winner);
}

void    SFMLCanvas::drawPiece(unsigned int x, unsigned int y, sf::Sprite & piece)
{
    piece.setPosition(x*18.3+70,y*18.5+70);
    RenderWindow::draw(piece);
}

void    SFMLCanvas::setPiece(unsigned int x, unsigned int y, char color)
{
    this->pieces[x][y] = color;
}

sf::Vector2i    SFMLCanvas::screenToGamePos(sf::Vector2f &pos)
{
    sf::Vector2i    gamePos;

    gamePos.x  = round((pos.x - 70) / 18.3);
    gamePos.y  = round((pos.y - 70) / 18.5);
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

