#include "ASFMLCanvas.hpp"
#include <iostream>

class Game;

class SFMLCanvas : public QSFMLCanvas
{
public :

    SFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size){};

    void setGame(Game *game);

    void    addPiece(const std::string &color, unsigned int x, unsigned int y);
    void    removePiece(unsigned int x, unsigned int y);
    void    setWinner(const std::string &color);
    void    setCurrentPlayer(const std::string &color);
    void    updateStat(const std::string &turn, const std::string &black, const std::string &white);

private :

    void    OnInit();
    void    OnUpdate();
    void    handleEvent();
    void    drawState();
    void    drawPiece(unsigned int x, unsigned int y, sf::Sprite & piece);
    void    setPiece(unsigned int x, unsigned int y, char color);
    void    drawWinner(char winner);
    void    trySetPiece(unsigned int x, unsigned int y);
    sf::Vector2i    screenToGamePos(sf::Vector2f &pos);

    int         pieces[19][19];
    char        winner;
    char        currentPlayer;

    sf::Vector2f    coefAff;

    sf::Texture backgroundTexture;
    sf::Texture blackWinTexture;
    sf::Texture whiteWinTexture;
    sf::Texture invalidPieceTexture;
    sf::Texture whitePieceTexture;
    sf::Texture blackPieceTexture;
    sf::Texture whitePlayerTexture;
    sf::Texture blackPlayerTexture;
    sf::Sprite  background;
    sf::Sprite  whitePiece;
    sf::Sprite  blackPiece;
    sf::Sprite  invalidPiece;
    sf::Sprite  whiteWin;
    sf::Sprite  blackWin;
    sf::Sprite  whitePlayer;
    sf::Sprite  blackPlayer;

    sf::Clock   myClock;
    Game      *currentGame;
};
