#include "ASFMLCanvas.hpp"
#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif
#include <iostream>
#include <QResizeEvent>

QSFMLCanvas::QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime) : QWidget(Parent),
myInitialized (false)
{
  setAttribute(Qt::WA_PaintOnScreen);
  setAttribute(Qt::WA_OpaquePaintEvent);
  setAttribute(Qt::WA_NoSystemBackground);
  setFocusPolicy(Qt::StrongFocus);
  move(Position);
  resize(Size);
  myTimer.setInterval(FrameTime);
}
QSFMLCanvas::~QSFMLCanvas() {}

void QSFMLCanvas::showEvent(QShowEvent*)
{
  if (!myInitialized)
  {
    #ifdef Q_WS_X11
    //XFlush(QX11Info::display());
    #endif
    sf::RenderWindow::create((sf::WindowHandle) winId());
    OnInit();
    //OnInit();
    connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    myTimer.start();
    myInitialized = true;
  }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
  return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
  OnUpdate();
  RenderWindow::display();
}

void QSFMLCanvas::resizeEvent(QResizeEvent *event)
{
  setSize(sf::Vector2u(event->size().width(),event->size().height()));
}

void QSFMLCanvas::OnInit() {}
void QSFMLCanvas::OnUpdate() {}
