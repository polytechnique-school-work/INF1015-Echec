#include "ChessWindow.hpp"
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

#include "VueGame.hpp"

#include <iostream>
#include "Board.hpp"

using namespace model;

ChessWindow::ChessWindow(QWidget* parent): QMainWindow(parent)
{
    Board& board = Board::getInstance();
    // board.generateBoard("XXXXXXXXXXBFXXXXXXBPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWKWPXXXXXXXXXXXXXXXXXXXXXXBCXXXXXXXXXXXXXXXXXXXXXXBRXXXXXXXXXXXXXXXXXXXXXX");
    // board.generateBoard("BRBCXXBQBKXXBCBRBPXXXXBPXXBPBPBPBFBPXXXXXXXXWPXXXXXXBPXXXXXXXXXXXXWPXXXXWPBPXXBFXXXXXXXXXXXXXXWPWPXXWPWPXXXXXXXXWRWCWFWQWKWFWCWR");
    generateWindow();

    // board.movePiece({0, 6}, {0, 5});
    refreshWindow();
}

void ChessWindow::generateWindow()
{

    // QVBoxLayout* qvBoxLayout = new QVBoxLayout(this);

    auto widgetPrincipal = new QWidget(this);
    // qvBoxLayout->addWidget(widgetPrincipal);

	setWindowTitle("Échecs");


    // Mettre le QVBoxLayout parent de widgetPrincipal
    QVBoxLayout* qvboxLayout = new QVBoxLayout(widgetPrincipal);

    // Contient le plateau
    auto chessWidget = new QWidget();
	grid = new QGridLayout(chessWidget);

    QPushButton* button = new QPushButton("Rollback", widgetPrincipal);
    connect(button, &QPushButton::clicked, this, [this]() {rollback(); });

    QPushButton* buttonSave = new QPushButton("Saveboard", widgetPrincipal);
    connect(buttonSave, &QPushButton::clicked, this, [this]() {saveBoard(); });

    text = new QLabel();
    text->setText("Équipe: ");

    qvboxLayout->addWidget(chessWidget);
    qvboxLayout->addWidget(text);
    qvboxLayout->addWidget(button);
    qvboxLayout->addWidget(buttonSave);
    
    Board& board = Board::getInstance();
    model::Team team = model::Game::getInstance().getTurn();


    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            ClickableLabel* label = new ClickableLabel();
            label->setFixedSize(50, 50);
            if ((row + col) % 2 == 0) {
                label->setStyleSheet("background-color: rgb(255, 206, 158)");
            }
            else {
                label->setStyleSheet("background-color: rgb(209, 139, 71)");
            }

            connect(label, &ClickableLabel::clicked, this, [this, col, row]() {onClickChess({ col, row }); });

            grid->setSpacing(0);
            grid->addWidget(label, row, col);
        }
    }


    setCentralWidget(widgetPrincipal);
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
    tour += team == model::Team::WHITE ? "blanc" : "noir";
    if (board.isEchec(team))
        tour += "\nLe roi est en échec!!!";
    text->setText(tour.c_str());
}

void ChessWindow::saveBoard()
{
    Board& board = Board::getInstance();
    board.saveBoard();
}

void ChessWindow::refreshWindow()
{
  
    // testDraw();
    vue::Game& vueGame = vue::Game::getInstance();
    Board& board = Board::getInstance();
    model::LocationContainer possibleLocations = {};
    if (vueGame.getSelected().has_value()) {
        possibleLocations = board.possibleMoves(*vueGame.getSelected());
    }
    model::Team team = model::Game::getInstance().getTurn();

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {

      

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

            if (!board.isSafeMove({ col, row }, team)) {
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
    color.setRgb(216, 76, 76);
    color.setAlpha(255);
    QPen pen(color, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    painter.drawLine(0, 0, width, height);
    painter.drawLine(width, 0, 0, height);

    label->setPixmap(pixmap);
    label->setScaledContents(true);
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
    color.setRgb(120, 120, 120);
    color.setAlpha(100);
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
    model::Board& board = model::Board::getInstance();
    vue::Game& vueGame = vue::Game::getInstance();
    model::Game& modelGame = model::Game::getInstance();

    PieceContainer& pieceCtr = board.getPiece(loc);

    // Déplacement d'une pièce
    if (vueGame.getSelected().has_value() && board.isMovePossible(*vueGame.getSelected(), loc))
    {
        std::cout << "1" << std::endl;
        this->movePiece(*vueGame.getSelected(), loc);
    }
    // Click dans un emplacement sans pièce
    else if (!pieceCtr.has_value()) {
        std::cout << "2" << std::endl;
        resetSelect();
    }

    // Sélection d'une pièce
    else {
        std::cout << "3" << std::endl;
        Team& team = modelGame.getTurn();
        Piece& piece = **pieceCtr;
        if (piece.getTeam() == team) {
            std::cout << "4" << std::endl;
            selectPiece(loc);
        }
        else {
            std::cout << "5" << std::endl;
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
    model::Game& modelGame = model::Game::getInstance();

    board.movePiece(src, dst);
    modelGame.nextTurn();
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

