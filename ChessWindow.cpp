#include "ChessWindow.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

#include <iostream>


ChessWindow::ChessWindow(QWidget* parent): QMainWindow(parent)
{
    generateWindow();
}

void ChessWindow::generateWindow()
{
    auto widgetPrincipal = new QWidget(this);

	setWindowTitle("Échecs");

	QGridLayout* grid = new QGridLayout(widgetPrincipal);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QLabel* label = new QLabel();
            label->setFixedSize(50, 50);
            if ((row + col) % 2 == 0) {
                label->setStyleSheet("background-color: rgb(255, 206, 158)");
            }
            else {
                label->setStyleSheet("background-color: rgb(209, 139, 71)");
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
