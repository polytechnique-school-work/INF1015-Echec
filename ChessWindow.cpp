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

#include "VueGame.hpp"

#include <iostream>
#include "Board.hpp"

using namespace model;

ChessWindow::ChessWindow(QWidget* parent): QMainWindow(parent)
{
    Board& board = Board::getInstance();
    generateWindow();
    // board.movePiece({0, 6}, {0, 5});
    refreshWindow();
}

void ChessWindow::generateWindow()
{
    auto widgetPrincipal = new QWidget(this);

	setWindowTitle("Échecs");

	grid = new QGridLayout(widgetPrincipal);

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

    text = new QLabel();
    text->setText("Équipe: ");
    grid->addWidget(text);
    
    setCentralWidget(widgetPrincipal);
}

void ChessWindow::refreshWindow()
{
  

    vue::Game& vueGame = vue::Game::getInstance();
    Board& board = Board::getInstance();
    std::list<model::Location> possibleLocations = {};
    if (vueGame.getSelected().has_value()) {
        model::PieceContainer& pieceCtr = board.getPiece(*vueGame.getSelected());
        model::Piece& piece = **board.getPiece(*vueGame.getSelected());
        possibleLocations = board.calculateKingSafePosition(piece, *vueGame.getSelected());
    }
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

            auto it = std::find(possibleLocations.begin(), possibleLocations.end(), Location(col, row));
            QPainter qpainter = QPainter();
            if (it != possibleLocations.end()) {
                setLabelSelected(label);
            }
            
        }
    }

  /*  model::Game& game = model::Game::getInstance();
    std::string teamName = (game.getTurn() == model::Team::WHITE ? "Blanc" : "Noir");
    std::string textTotal = "Équipe: " + teamName;
    text->setText(QString::fromStdString(textTotal));*/
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
    std::cout << loc << std::endl;
    model::Board& board = model::Board::getInstance();
    vue::Game& vueGame = vue::Game::getInstance();
    model::Game& modelGame = model::Game::getInstance();

    PieceContainer& pieceCtr = board.getPiece(loc);

    if (vueGame.getSelected().has_value() && board.isMovePossible(*vueGame.getSelected(), loc))
        this->movePiece(*vueGame.getSelected(), loc);

    else if (!pieceCtr.has_value()) {
        resetSelect();
    }

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
    std::cout << "Select: " << loc << std::endl;
    vue::Game& vueGame = vue::Game::getInstance();
    vueGame.setSelected(loc);
}

void ChessWindow::movePiece(model::Location src, model::Location dst)
{
    std::cout << "MovePiece: \n" << "\tSrc: " << src << "\n" << "\tDst: " << dst <<std::endl;
    model::Board& board = model::Board::getInstance();
    model::Game& modelGame = model::Game::getInstance();

    board.movePiece(src, dst);
    modelGame.nextTurn();
    resetSelect();
}

void ChessWindow::resetSelect()
{
    std::cout << "Reset selection" << std::endl;
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

