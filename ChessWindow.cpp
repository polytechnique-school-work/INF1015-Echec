#include "ChessWindow.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsBlurEffect>
#include <QtGui/QPixmap>

#include <iostream>
#include "Board.hpp"

using namespace model;

ChessWindow::ChessWindow(QWidget* parent): QMainWindow(parent)
{

    Board& board = Board::getInstance();
    generateWindow();

   board.movePiece({ 0,1 }, { 0,2 });

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
            // ajouter code ici 

            connect(label, &ClickableLabel::clicked, this, [this, col, row]() {onClickChess({ col, row }); });
            

            Board& board = Board::getInstance();
            PieceContainer& pieceCtr = board.getPiece({ col, row });
            if (pieceCtr.has_value()) {
                auto map = QPixmap(getImage(**pieceCtr).c_str());
                label->setPixmap(map);
                label->setScaledContents(true);
            }

            grid->setSpacing(0);
            grid->addWidget(label, row, col);
        }
    }

    QLabel* label = new QLabel();
    label->setText("Test");
    grid->addWidget(label);
    
    setCentralWidget(widgetPrincipal);
}

void ChessWindow::refreshWindow()
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QLabel* label = dynamic_cast<QLabel*>(grid->itemAtPosition(row, col)->widget());
            Board& board = Board::getInstance();
            PieceContainer& pieceCtr = board.getPiece({ col, row });
            if (pieceCtr.has_value()) {
                auto map = QPixmap(getImage(**pieceCtr).c_str());
                label->setPixmap(map);
                label->setScaledContents(true);
            }
            else {
                label->clear();
            }
        }
    }
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
