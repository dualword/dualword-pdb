/*  Dualword-pdb http://github.com/dualword/dualword-pdb
 *	Dualword-pdb is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Dualword-pdb is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Dualword-pdb. If not, see <http://www.gnu.org/licenses/>.
 *
*/

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui>
#include "ui_MainWindow.h"

namespace chemkit{
class PolymerFile;
class GraphicsPymolSurfaceItem;
class GraphicsProteinItem;
class GraphicsNucleicAcidItem;
}
class ProteinPocket;
class Pdb;

class MainWindow : public QMainWindow, private Ui::MainWindowForm {
  Q_OBJECT

public:
	MainWindow(QWidget *p = 0, Qt::WindowFlags f = 0);
	virtual ~MainWindow();
	QPlainTextEdit* con() {return console;};

public slots:
	void showAbout();
	void openPdb();
	void getPdb();
	void reset();
	void opacityChanged(int);
	void modeChanged (int);
	void modePocket (int);
	void showPDB(const Pdb&);
	void showPocket(const QString&);
	void showText();
	void newPdb(const QString&);

private:
	void createRow(const QString&, const QString&, bool = false);

    QScopedPointer<chemkit::PolymerFile> pFile;
    QScopedPointer<chemkit::GraphicsPymolSurfaceItem> item, item2;
	QScopedPointer<ProteinPocket> pocket;
	QLineEdit* edit;

};

#endif /* MAINWINDOW_H_ */
