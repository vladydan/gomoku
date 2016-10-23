#include "qsfmlcanvas.h"

class SFMLCanvas : public QSFMLCanvas
{
public :

    SFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size)
    {

    }

private :

    void OnInit()
    {
        // Load the image
        myImage.loadFromFile("/home/danilo_d/Epitech-Projects/Semestre5/gomoku/gomoku.jpg");

        // Setup the sprite
        mySprite.setTexture(myImage);
        mySprite.setOrigin(mySprite.getScale() / 2.f);
    }

    void OnUpdate()
    {
        RenderWindow::clear(sf::Color(0, 128, 0));
        // Rotate the sprite
        mySprite.rotate(myClock.getElapsedTime().asSeconds() * 100.f);

        // Draw it
        RenderWindow::draw(mySprite);
        myClock.restart();
    }

    sf::Texture  myImage;
    sf::Sprite mySprite;
    sf::Clock myClock;

};
