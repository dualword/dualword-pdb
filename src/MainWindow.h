/*
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

class MainWindow : public QMainWindow, private Ui::MainWindowForm {
  Q_OBJECT

public:
	MainWindow(QWidget *p = 0, Qt::WindowFlags f = 0);
	virtual ~MainWindow();

public slots:
	void showAbout();
	void openPdb();
	void opacityChanged(int);
	void modeChanged (int);

private:
    QScopedPointer<chemkit::PolymerFile> pFile;
    QScopedPointer<chemkit::GraphicsPymolSurfaceItem> surfaceItem;

};

#endif /* MAINWINDOW_H_ */
