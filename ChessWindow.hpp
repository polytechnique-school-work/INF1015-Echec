﻿#include <QMainWindow>
#include "Piece.hpp"
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
namespace vue {

	class ChessWindow : public QMainWindow {
		Q_OBJECT
	public:

		ChessWindow(QWidget* parent = nullptr);
		void generateWindow();
		void refreshWindow();
		std::string getImage(model::Piece& piece);

	public slots:
		void onClickChess(model::Location loc);

	private:
		QGridLayout* grid;
		QLabel* text;
		bool isMat = false;
		void selectPiece(model::Location loc);
		void movePiece(model::Location src, model::Location dst);
		void resetSelect();
		void setLabelSelected(QLabel* label);
		void rollback();
		void refreshTeam();
		void saveBoard();
		void setLabelUnsafe(QLabel* label);
		void changeCheckBox();
		void changeBoard(int index);
		bool showDangerousMoves = false;
	};


	// Copie du wiki : https://wiki.qt.io/Clickable_QLabel
	class ClickableLabel : public QLabel {
		Q_OBJECT
	public:
		explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
		~ClickableLabel();

	signals:
		void clicked();
	protected:
		void mousePressEvent(QMouseEvent* event);
	};

}