#include <QMainWindow>
class ChessWindow: public QMainWindow {
	Q_OBJECT
public: 

	ChessWindow(QWidget* parent=nullptr);
	void generateWindow();
};