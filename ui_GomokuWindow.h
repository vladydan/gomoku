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
#include <QtWidgets/QLineEdit>
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
    QWidget *gameForm;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_5;
    QLabel *cinqCassableLabel;
    QLineEdit *playerOneNameLineEdit;
    QLabel *playerTwoNameLabel;
    QCheckBox *cinqCassableCheckBox;
    QLineEdit *playerTwoNameLineEdit;
    QLabel *playerOneNameLabel;
    QCheckBox *leDoubleTroisCheckBox;
    QLabel *leDoubleTroisLabel;
    QPushButton *startButton;
    QPushButton *backtoMenu;
    QWidget *gameRoom;
    QGridLayout *_2;
    QFrame *sfmlFrame;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QMenu *menuGame;

    void setupUi(QMainWindow *GomokuWindow)
    {
        if (GomokuWindow->objectName().isEmpty())
            GomokuWindow->setObjectName(QStringLiteral("GomokuWindow"));
        GomokuWindow->resize(800, 600);
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
        gameForm = new QWidget();
        gameForm->setObjectName(QStringLiteral("gameForm"));
        horizontalLayout_2 = new QHBoxLayout(gameForm);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setHorizontalSpacing(12);
        gridLayout_5->setVerticalSpacing(0);
        gridLayout_5->setContentsMargins(-1, -1, 127, 20);
        cinqCassableLabel = new QLabel(gameForm);
        cinqCassableLabel->setObjectName(QStringLiteral("cinqCassableLabel"));

        gridLayout_5->addWidget(cinqCassableLabel, 3, 0, 1, 1);

        playerOneNameLineEdit = new QLineEdit(gameForm);
        playerOneNameLineEdit->setObjectName(QStringLiteral("playerOneNameLineEdit"));

        gridLayout_5->addWidget(playerOneNameLineEdit, 0, 1, 1, 1);

        playerTwoNameLabel = new QLabel(gameForm);
        playerTwoNameLabel->setObjectName(QStringLiteral("playerTwoNameLabel"));

        gridLayout_5->addWidget(playerTwoNameLabel, 1, 0, 1, 1);

        cinqCassableCheckBox = new QCheckBox(gameForm);
        cinqCassableCheckBox->setObjectName(QStringLiteral("cinqCassableCheckBox"));

        gridLayout_5->addWidget(cinqCassableCheckBox, 3, 1, 1, 1);

        playerTwoNameLineEdit = new QLineEdit(gameForm);
        playerTwoNameLineEdit->setObjectName(QStringLiteral("playerTwoNameLineEdit"));

        gridLayout_5->addWidget(playerTwoNameLineEdit, 1, 1, 1, 1);

        playerOneNameLabel = new QLabel(gameForm);
        playerOneNameLabel->setObjectName(QStringLiteral("playerOneNameLabel"));

        gridLayout_5->addWidget(playerOneNameLabel, 0, 0, 1, 1);

        leDoubleTroisCheckBox = new QCheckBox(gameForm);
        leDoubleTroisCheckBox->setObjectName(QStringLiteral("leDoubleTroisCheckBox"));

        gridLayout_5->addWidget(leDoubleTroisCheckBox, 2, 1, 1, 1);

        leDoubleTroisLabel = new QLabel(gameForm);
        leDoubleTroisLabel->setObjectName(QStringLiteral("leDoubleTroisLabel"));

        gridLayout_5->addWidget(leDoubleTroisLabel, 2, 0, 1, 1);

        startButton = new QPushButton(gameForm);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setLayoutDirection(Qt::LeftToRight);

        gridLayout_5->addWidget(startButton, 5, 1, 1, 1);

        backtoMenu = new QPushButton(gameForm);
        backtoMenu->setObjectName(QStringLiteral("backtoMenu"));

        gridLayout_5->addWidget(backtoMenu, 4, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_5);

        stackedWidget->addWidget(gameForm);
        gameRoom = new QWidget();
        gameRoom->setObjectName(QStringLiteral("gameRoom"));
        _2 = new QGridLayout(gameRoom);
        _2->setSpacing(6);
        _2->setContentsMargins(11, 11, 11, 11);
        _2->setObjectName(QStringLiteral("_2"));
        sfmlFrame = new QFrame(gameRoom);
        sfmlFrame->setObjectName(QStringLiteral("sfmlFrame"));
        sfmlFrame->setFrameShape(QFrame::StyledPanel);
        sfmlFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(sfmlFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        _2->addWidget(sfmlFrame, 1, 2, 1, 1);

        stackedWidget->addWidget(gameRoom);

        gridLayout->addWidget(stackedWidget, 2, 0, 1, 1);

        GomokuWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GomokuWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 26));
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
        cinqCassableLabel->setText(QApplication::translate("GomokuWindow", "Cinq Cassable", 0));
        playerTwoNameLabel->setText(QApplication::translate("GomokuWindow", "Player Two Name", 0));
        playerOneNameLabel->setText(QApplication::translate("GomokuWindow", "Player One Name", 0));
        leDoubleTroisLabel->setText(QApplication::translate("GomokuWindow", "Le Double Trois", 0));
        startButton->setText(QApplication::translate("GomokuWindow", "Start", 0));
        backtoMenu->setText(QApplication::translate("GomokuWindow", "Back to the menu", 0));
        menuGame->setTitle(QApplication::translate("GomokuWindow", "Game", 0));
    } // retranslateUi

};

namespace Ui {
    class GomokuWindow: public Ui_GomokuWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOMOKUWINDOW_H
