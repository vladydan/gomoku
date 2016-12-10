#pragma once

#include "Player.hpp"
#include "ASFMLCanvas.hpp"
class GomokuWindow;
#include <iostream>

class Game;

class SFMLCanvas : public QSFMLCanvas
{
public :

    SFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, GomokuWindow *qt) :
    QSFMLCanvas(Parent, Position, Size){
      this->qt = qt;
    };

    ~SFMLCanvas()
    {

    }

    void setGame(Game *game);

    void    addPiece(const std::string &color, unsigned int x, unsigned int y);
    void    removePiece(unsigned int x, unsigned int y);
    void    setWinner(const std::string &color);
    void    setCurrentPlayer(const std::string &color);
    void    updateStat(const std::string &turn, const std::string &black, const std::string &white);
    void    setIa(bool);
    void    trySetPiece(unsigned int x, unsigned int y);
    void    drawState();

private :

    void    OnInit();
    void    OnUpdate();
    void    handleEvent();
    void    drawPiece(unsigned int x, unsigned int y, sf::Sprite & piece);
    void    setPiece(unsigned int x, unsigned int y, char color);
    void    drawWinner(char winner);
    sf::Vector2i    screenToGamePos(sf::Vector2f &pos);
    void        drawTips();
    int         pieces[19][19];
    char        winner;
    char        currentPlayer;

    sf::Vector2f    coefAff;

    sf::Texture backgroundTexture;
    sf::Texture invalidPieceTexture;
    sf::Texture whitePieceTexture;
    sf::Texture blackPieceTexture;
    sf::Texture whitePlayerTexture;
    sf::Texture blackPlayerTexture;
    sf::Texture pieceText;
    sf::Texture whiteTransp;
    sf::Sprite  transWhitePiece;
    sf::Sprite  piece;
    sf::Sprite  background;
    sf::Sprite  whitePiece;
    sf::Sprite  blackPiece;
    sf::Sprite  invalidPiece;
    sf::Sprite  whitePlayer;
    sf::Sprite  blackPlayer;

    bool ia;
    bool iaPlayed;
    sf::Clock   myClock;
    Game      *currentGame;
    GomokuWindow   *qt;
};
