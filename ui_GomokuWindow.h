/********************************************************************************
** Form generated from reading UI file 'GomokuWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOMOKUWINDOW_H
#define UI_GOMOKUWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GomokuWindow
{
public:
    QAction *actionReplay;
    QAction *actionBack_to_the_menu;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *menu;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *menuTitle;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_2;
    QPushButton *exitButton;
    QPushButton *IAButton;
    QPushButton *pvpButton;
    QSpacerItem *horizontalSpacer_2;
    QWidget *gameRoom;
    QGridLayout *_2;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *playerTurn;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QCheckBox *doubleTrois;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QCheckBox *cinqCassble;
    QLabel *time;
    QLabel *turn;
    QLabel *whiteScore;
    QLabel *blackScore;
    QFrame *sfmlFrame;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QMenu *menuGame;

    void setupUi(QMainWindow *GomokuWindow)
    {
        if (GomokuWindow->objectName().isEmpty())
            GomokuWindow->setObjectName(QStringLiteral("GomokuWindow"));
        GomokuWindow->resize(1081, 850);
        actionReplay = new QAction(GomokuWindow);
        actionReplay->setObjectName(QStringLiteral("actionReplay"));
        actionBack_to_the_menu = new QAction(GomokuWindow);
        actionBack_to_the_menu->setObjectName(QStringLiteral("actionBack_to_the_menu"));
        actionExit = new QAction(GomokuWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(GomokuWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        menu = new QWidget();
        menu->setObjectName(QStringLiteral("menu"));
        gridLayout_3 = new QGridLayout(menu);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        menuTitle = new QLabel(menu);
        menuTitle->setObjectName(QStringLiteral("menuTitle"));
        QFont font;
        font.setFamily(QStringLiteral("Bandal"));
        font.setPointSize(44);
        font.setBold(false);
        font.setUnderline(false);
        font.setWeight(50);
        menuTitle->setFont(font);
        menuTitle->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        menuTitle->setMargin(25);

        verticalLayout_2->addWidget(menuTitle);


        gridLayout_3->addLayout(verticalLayout_2, 1, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        exitButton = new QPushButton(menu);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        gridLayout_2->addWidget(exitButton, 2, 0, 1, 1);

        IAButton = new QPushButton(menu);
        IAButton->setObjectName(QStringLiteral("IAButton"));

        gridLayout_2->addWidget(IAButton, 1, 0, 1, 1);

        pvpButton = new QPushButton(menu);
        pvpButton->setObjectName(QStringLiteral("pvpButton"));
        pvpButton->setMinimumSize(QSize(0, 0));
        pvpButton->setIconSize(QSize(16, 16));

        gridLayout_2->addWidget(pvpButton, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 5);
        horizontalLayout->setStretch(2, 1);

        gridLayout_3->addLayout(horizontalLayout, 4, 0, 3, 2);

        stackedWidget->addWidget(menu);
        gameRoom = new QWidget();
        gameRoom->setObjectName(QStringLiteral("gameRoom"));
        _2 = new QGridLayout(gameRoom);
        _2->setSpacing(0);
        _2->setContentsMargins(11, 11, 11, 11);
        _2->setObjectName(QStringLiteral("_2"));
        _2->setContentsMargins(-1, 0, 36, 0);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout_4->setContentsMargins(-1, -1, -1, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, 107, 0, 120);
        playerTurn = new QLabel(gameRoom);
        playerTurn->setObjectName(QStringLiteral("playerTurn"));
        QFont font1;
        font1.setFamily(QStringLiteral("Bandal"));
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        font1.setKerning(false);
        playerTurn->setFont(font1);

        verticalLayout_4->addWidget(playerTurn);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(gameRoom);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        doubleTrois = new QCheckBox(gameRoom);
        doubleTrois->setObjectName(QStringLiteral("doubleTrois"));
        doubleTrois->setChecked(true);

        horizontalLayout_3->addWidget(doubleTrois);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(gameRoom);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        cinqCassble = new QCheckBox(gameRoom);
        cinqCassble->setObjectName(QStringLiteral("cinqCassble"));
        cinqCassble->setChecked(true);
        cinqCassble->setTristate(false);

        horizontalLayout_4->addWidget(cinqCassble);


        verticalLayout_4->addLayout(horizontalLayout_4);

        time = new QLabel(gameRoom);
        time->setObjectName(QStringLiteral("time"));

        verticalLayout_4->addWidget(time);

        turn = new QLabel(gameRoom);
        turn->setObjectName(QStringLiteral("turn"));

        verticalLayout_4->addWidget(turn);

        whiteScore = new QLabel(gameRoom);
        whiteScore->setObjectName(QStringLiteral("whiteScore"));

        verticalLayout_4->addWidget(whiteScore);

        blackScore = new QLabel(gameRoom);
        blackScore->setObjectName(QStringLiteral("blackScore"));

        verticalLayout_4->addWidget(blackScore);


        gridLayout_4->addLayout(verticalLayout_4, 0, 0, 1, 1);

        sfmlFrame = new QFrame(gameRoom);
        sfmlFrame->setObjectName(QStringLiteral("sfmlFrame"));
        sfmlFrame->setFrameShape(QFrame::StyledPanel);
        sfmlFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(sfmlFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        gridLayout_4->addWidget(sfmlFrame, 0, 1, 1, 1);

        gridLayout_4->setColumnStretch(0, 2);
        gridLayout_4->setColumnStretch(1, 10);

        _2->addLayout(gridLayout_4, 1, 3, 1, 1);

        stackedWidget->addWidget(gameRoom);

        gridLayout->addWidget(stackedWidget, 2, 0, 1, 1);

        GomokuWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GomokuWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1081, 19));
        menuBar->setNativeMenuBar(true);
        menuGame = new QMenu(menuBar);
        menuGame->setObjectName(QStringLiteral("menuGame"));
        GomokuWindow->setMenuBar(menuBar);

        menuBar->addAction(menuGame->menuAction());
        menuGame->addAction(actionReplay);
        menuGame->addAction(actionBack_to_the_menu);
        menuGame->addAction(actionExit);

        retranslateUi(GomokuWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GomokuWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GomokuWindow)
    {
        GomokuWindow->setWindowTitle(QApplication::translate("GomokuWindow", "Gomoku", 0));
        actionReplay->setText(QApplication::translate("GomokuWindow", "Replay", 0));
        actionBack_to_the_menu->setText(QApplication::translate("GomokuWindow", "Back to the menu", 0));
        actionExit->setText(QApplication::translate("GomokuWindow", "Exit", 0));
        menuTitle->setText(QApplication::translate("GomokuWindow", "Gomoku", 0));
        exitButton->setText(QApplication::translate("GomokuWindow", "Exit", 0));
        IAButton->setText(QApplication::translate("GomokuWindow", "Player vs IA", 0));
        pvpButton->setText(QApplication::translate("GomokuWindow", "Player vs Player", 0));
        playerTurn->setText(QApplication::translate("GomokuWindow", "White Turn", 0));
        label->setText(QApplication::translate("GomokuWindow", "Double Trois", 0));
        doubleTrois->setText(QString());
        label_2->setText(QApplication::translate("GomokuWindow", "Cinq Cassable", 0));
        cinqCassble->setText(QString());
        time->setText(QApplication::translate("GomokuWindow", "Time : 0", 0));
        turn->setText(QApplication::translate("GomokuWindow", "Turn : 0", 0));
        whiteScore->setText(QApplication::translate("GomokuWindow", "White : ", 0));
        blackScore->setText(QApplication::translate("GomokuWindow", "Black : ", 0));
        menuGame->setTitle(QApplication::translate("GomokuWindow", "Game", 0));
    } // retranslateUi

};

namespace Ui {
    class GomokuWindow: public Ui_GomokuWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOMOKUWINDOW_H
