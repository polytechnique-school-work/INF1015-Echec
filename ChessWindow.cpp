﻿#include "ChessWindow.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsBlurEffect>
#include <QtGui/QPixmap>
#include <algorithm>
#include "Game.hpp"
#include <QPushButton>
#include <QCheckBox>
#include <algorithm>
#include <QStackedLayout>
#include <chrono>
#include <QComboBox>
#include "VueGame.hpp"

#include <iostream>
#include "Board.hpp"



#include "Utils.hpp"

constexpr int WHITE_BOARD[3] = { 197, 198, 200 };
constexpr int BLACK_BOARD[3] = { 70, 162, 159 };

using namespace model;
using namespace vue;

ChessWindow::ChessWindow(QWidget* parent): QMainWindow(parent)
{
    Board& board = Board::getInstance();
    generateWindow();
    refreshWindow();
}

void ChessWindow::generateWindow()
{
    auto widgetPrincipal = new QWidget(this);
	setWindowTitle("Jeu d'échecs - Gabriel Landry & Thomas Petrie");
    QVBoxLayout* qvboxLayout = new QVBoxLayout(widgetPrincipal);

    auto chessWidget = new QWidget();
	grid = new QGridLayout(chessWidget);

    QPushButton* button = new QPushButton("Retour en arrière", widgetPrincipal);
    connect(button, &QPushButton::clicked, this, [this]() {rollback(); });

    QPushButton* buttonSave = new QPushButton("Sauvegarder l'échéquier", widgetPrincipal);
    connect(buttonSave, &QPushButton::clicked, this, [this]() {saveBoard(); });

    QCheckBox* showDangerousMoves = new QCheckBox("Afficher les positions attaquées", widgetPrincipal);
    connect(showDangerousMoves, &QCheckBox::stateChanged, [this]() {changeCheckBox(); });


    QComboBox* selectMenu = new QComboBox();



    QString selected[4] = { "Début habituel", "Milieu de partie", "Première fin de partie", "Deuxième fin de partie" };
    int i = 0;
    for (QString text : selected) {
        selectMenu->addItem(text);
        selectMenu->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
        i++;
    }

    connect(selectMenu, &QComboBox::currentIndexChanged, [this](int i) { changeBoard(i); });

   
    text = new QLabel();

    text->setText("Équipe: ");

    qvboxLayout->addWidget(chessWidget);
    qvboxLayout->addWidget(text);
    qvboxLayout->addWidget(showDangerousMoves);
    qvboxLayout->addWidget(button);
    qvboxLayout->addWidget(selectMenu);
    qvboxLayout->addWidget(buttonSave);
    
    Board& board = Board::getInstance();
    model::Team team = model::Game::getInstance().getTurn();

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            ClickableLabel* label = new ClickableLabel();
            label->setFixedSize(50, 50);
            const int* values = nullptr;

            if ((row + col) % 2 == 0) {
                values = WHITE_BOARD;
            }
            else {
                values = BLACK_BOARD;
            }

            std::string background = "background-color: rgb(";
            background += std::to_string(values[0]);
            background += ", "; 
            background += std::to_string(values[1]);
            background += ", ";
            background += std::to_string(values[2]);
            background += ")";

            label->setStyleSheet(QString::fromStdString(background));

            connect(label, &ClickableLabel::clicked, this, [this, col, row]() {onClickChess({ col, row }); });

            grid->setSpacing(0);
            grid->addWidget(label, row, col);
        }
    }

    setCentralWidget(widgetPrincipal);
}

void ChessWindow::changeBoard(int i) {
    model::Board& board = model::Board::getInstance();
    std::string boardSelected;
    switch (i)
    {
    case 0: /* Default */
        boardSelected = "BRBCBFBQBKBFBCBRBPBPBPBPBPBPBPBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWPWPWPWPWPWPWPWPWRWCWFWQWKWFWCWR";
        break;
    case 1: /* Avancé */
        boardSelected = "BRXXXXXXBKBFXXBRBPBPBPXXXXBPBPBPXXXXBCBPXXXXXXXXXXXXXXXXBPXXWCXXXXXXXXXXWPXXXXXXXXWPXXWPWPXXXXWPWPXXWPXXXXXXWPXXWRWCXXXXWKXXXXWR";
        break;
    case 2: /* Fin de jeu 1 */
        boardSelected = "XXXXXXBKXXBRXXXXBPXXXXXXXXXXBPXXXXXXXXXXXXXXXXBPXXBPXXXXWRXXXXXXXXXXXXBPXXXXWPXXWPWPXXXXXXXXXXWPXXXXXXXXXXXXXXXXXXXXWRXXWKXXXXXX";
        break;
    case 3: /* Fin de jeu 2 */
        boardSelected = "XXXXXXXXXXXXXXXXBPBPXXXXXXBKBPBPXXXXXXBPXXXXXXXXXXXXXXXXXXBFWPXXXXXXWPXXXXXXXXXXXXXXXXXXXXXXXXXXWPXXXXXXXXBFWPWPXXXXXXWKXXXXXXXX";
        break;
    default:
        boardSelected = "BRBCBFBQBKBFBCBRBPBPBPBPBPBPBPBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWPWPWPWPWPWPWPWPWRWCWFWQWKWFWCWR";
        break;
    }


    board.generateBoard(boardSelected);
    model::Game& game = model::Game::getInstance();
    refreshWindow();
}

void ChessWindow::rollback() {
    Board& board = Board::getInstance();
    board.rollback();
    refreshWindow();
}

void ChessWindow::refreshTeam()
{
    model::Board& board = model::Board::getInstance();
    model::Team team = model::Game::getInstance().getTurn();
    std::string tour = "C'est au tour de: ";
    auto&& teamStr = [](Team& team) {return (team == model::Team::WHITE ? "♖ (blancs)" : "♜ (noirs)"); };
    tour += teamStr(team);
    if (board.isEchec(team))
        tour += "\n⚠️ votre roi est en échec";
    if (isMat) {
        Team winner = team == Team::WHITE ? Team::BLACK : Team::WHITE;
        tour += "\n❌ la partie est terminée, les ";
        tour += teamStr(winner);
        tour += " ont gagnés.";
    }
    text->setText(tour.c_str());
}

void ChessWindow::saveBoard()
{
    Board& board = Board::getInstance();
    std::cout << board.saveBoard() << std::endl;
}

void ChessWindow::refreshWindow()
{
    vue::Game& vueGame = vue::Game::getInstance();
    Board& board = Board::getInstance();
    model::LocationContainer possibleLocations = {};

    if (vueGame.getSelected().has_value()) {
        possibleLocations = board.possibleMoves(*vueGame.getSelected());
    }
    model::Team team = model::Game::getInstance().getTurn();

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {

            QLabel* label = dynamic_cast<QLabel*>(grid->itemAtPosition(row, col)->widget());
            PieceContainer& pieceCtr = board.getPiece({ col, row });
            if (pieceCtr.has_value()) {
                auto map = QPixmap(getImage(**pieceCtr).c_str());
                label->setPixmap(map);
                label->setScaledContents(true);
            }
            else {
                label->clear();
            }

           if (!board.isSafeMove({ col, row }, team) && this->showDangerousMoves) {
                setLabelUnsafe(label);
            }

            auto it = std::find(possibleLocations.begin(), possibleLocations.end(), Location(col, row));
            QPainter qpainter = QPainter();
            if (it != possibleLocations.end()) {
                setLabelSelected(label);
            }
            
        }
    }

    refreshTeam();
}

void ChessWindow::setLabelUnsafe(QLabel* label)
{
    int width = label->width();
    int height = label->height();
    QPixmap pixmap(width, height);
    QImage image = label->pixmap().toImage();

    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    if (!image.isNull()) {
        image = image.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QRect rect(image.rect());
        QRect devRect(0, 0, painter.device()->width(), painter.device()->height());
        rect.moveCenter(devRect.center());
        painter.drawImage(rect.topLeft(), image);
    }
    QColor color;
    color.setRgb(102, 252, 241);
    color.setAlpha(255);
    QPen pen(color, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    painter.drawLine(0, 0, width, height);
    painter.drawLine(width, 0, 0, height);

    label->setPixmap(pixmap);
    label->setScaledContents(true);
}

void ChessWindow::changeCheckBox()
{
    showDangerousMoves = !showDangerousMoves;
    refreshWindow();
}


void ChessWindow::setLabelSelected(QLabel* label)
{
    int width = label->width();
    int height = label->height();
    QPixmap pixmap(width, height);
    QImage image = label->pixmap().toImage();
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    // Perte de qualité sur l'image, à cause du resize, je sais pas comment le fix.
    if(!image.isNull()) {
        image = image.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QRect rect(image.rect());
        QRect devRect(0,0, painter.device()->width(), painter.device()->height());
        rect.moveCenter(devRect.center());
        painter.drawImage(rect.topLeft(), image);
    }


    int x = width / 2;
    int y = height / 2;
    QColor color;
    color.setRgb(102, 252, 241);
    color.setAlpha(155);
    painter.setBrush(color);
    painter.setPen(QPen(Qt::black, 0));
    int radius = qMin(x, y) - 30;
    painter.drawEllipse(QPoint(x, y), radius, radius);
    label->setPixmap(pixmap);
    label->setScaledContents(true);
}

std::string ChessWindow::getImage(model::Piece& piece)
{
    std::string str = "";
    str.append((piece.getTeam() == Team::WHITE ? "white" : "black"));
    str.append("_");
    str.append(piece.getName());
    return str;
}

void ChessWindow::onClickChess(model::Location loc)
{

    if (isMat) return;
    model::Board& board = model::Board::getInstance();
    vue::Game& vueGame = vue::Game::getInstance();
    model::Game& modelGame = model::Game::getInstance();
    

    PieceContainer& pieceCtr = board.getPiece(loc);

    // Déplacement d'une pièce
    if (vueGame.getSelected().has_value() && board.isMovePossible(*vueGame.getSelected(), loc))
    {
        this->movePiece(*vueGame.getSelected(), loc);
    }
    // Click dans un emplacement sans pièce
    else if (!pieceCtr.has_value()) {
        resetSelect();
    }

    // Sélection d'une pièce
    else {
        Team& team = modelGame.getTurn();
        Piece& piece = **pieceCtr;
        if (piece.getTeam() == team) {
            selectPiece(loc);
        }
        else {
            resetSelect();
        }

    }
    refreshWindow();
}

void ChessWindow::selectPiece(model::Location loc)
{
    //std::cout << "Select: " << loc << std::endl;
    vue::Game& vueGame = vue::Game::getInstance();
    vueGame.setSelected(loc);
}

void ChessWindow::movePiece(model::Location src, model::Location dst)
{
    //std::cout << "MovePiece: \n" << "\tSrc: " << src << "\n" << "\tDst: " << dst <<std::endl;
    model::Board& board = model::Board::getInstance();
    board.movePiece(src, dst);
    Team team = model::Game::getInstance().getTurn();
    isMat = board.isMat(team);
    resetSelect();
}

void ChessWindow::resetSelect()
{
    //std::cout << "Reset selection" << std::endl;
    vue::Game& vueGame = vue::Game::getInstance();
    vueGame.setSelected({});

}
ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f) : QLabel(parent)
{
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}

