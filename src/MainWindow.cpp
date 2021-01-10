/*  Dualword-pdb http://github.com/dualword/dualword-pdb License:GNU GPL
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

#include "MainWindow.h"
#include "ProteinPocket.h"

#include <chemkit/polymerfile.h>
#include <chemkit/graphicsview.h>
#include <chemkit/graphicsproteinitem.h>
#include <chemkit/graphicsmoleculeitem.h>
#include <chemkit/graphicsnucleicaciditem.h>
#include <chemkit/graphicsmolecularsurfaceitem.h>
#include <chemkit/graphicspymolsurfaceitem.h>

#include <chemkit/molecule.h>
#include <chemkit/graphicsmoleculeitem.h>
#include <chemkit/moleculefile.h>

#include <chemkit/polymer.h>
#include <chemkit/bondpredictor.h>
#include <chemkit/graphicscamera.h>
#include <chemkit/graphicsnavigationtool.h>

MainWindow::MainWindow(QWidget *p, Qt::WindowFlags f) : QMainWindow(p, f){
	setupUi(this);
	setWindowTitle(qApp->applicationName());
	actionOpenPdb->setIcon(style()->standardIcon(QStyle::SP_FileDialogStart, 0, this));
    connect(actionOpenPdb,SIGNAL(triggered()), SLOT(openPdb()));
	actionAbout->setIcon(style()->standardIcon(QStyle::SP_FileDialogInfoView, 0, this));
    connect(actionAbout,SIGNAL(triggered()), SLOT(showAbout()));
    connect(sliderOpacity, SIGNAL(valueChanged(int)), SLOT(opacityChanged(int)));
    connect(checkMode, SIGNAL(stateChanged(int)), SLOT(modeChanged(int)));
    item.reset(new chemkit::GraphicsPymolSurfaceItem());
    view->addItem(item.data());
    item2.reset(new chemkit::GraphicsPymolSurfaceItem());
    view->addItem(item2.data());

}

MainWindow::~MainWindow() {}

void MainWindow::showAbout(){
	QString str;
	str.append(qApp->applicationName());
	str.append(" ").append(qApp->applicationVersion()).append("<br>");
	str.append("License: GPL v3 <br/>");
	str.append("&copy;2020 Alexander Busorgin <br/>");
	QMessageBox::about(this, tr("About"), str );
}

void MainWindow::openPdb(){
	QString f = QFileDialog::getOpenFileName( this, "Open file",
			".", "PDB File (*.pdb);;All Files (*.*)");
	if(f.isEmpty()) return;
    pFile.reset(new chemkit::PolymerFile);
    QByteArray format = QFileInfo(f).suffix().toAscii();
    bool ok = pFile->read(f.toAscii().constData(), format.constData());
    if(!ok){
        QMessageBox::critical(this, "Error:", pFile->errorString().c_str());
        return;
    }
	const boost::shared_ptr<chemkit::Polymer> &polymer = pFile->polymer();
	item->setMolecule(polymer.get());
	view->camera()->lookAt(polymer->center().cast<float>());
	view->update();
    pocket.reset(new ProteinPocket(f));
    connect(pocket.data(), SIGNAL(showPocket(const QString&)), SLOT(showPocket(const QString&)));
    pocket->start();

}

void MainWindow::opacityChanged(int value){
    float opacity = value / 100.0;
    item->setOpacity(opacity);
    view->update();
}

void MainWindow::modeChanged (int i){
	if(Qt::Unchecked == i){
		item->setColorMode(chemkit::GraphicsPymolSurfaceItem::AtomColor);
	}else if((Qt::Checked == i)){
		item->setColorMode(chemkit::GraphicsPymolSurfaceItem::SolidColor);
		item->setColor(QColor("green"));
	}
    view->update();
}

void MainWindow::showPocket(const QString& buf) {
	std::istringstream is(buf.toStdString());
    pFile.reset(new chemkit::PolymerFile);
    pFile->read(is, "pdb");
    const boost::shared_ptr<chemkit::Polymer> &p = pFile->polymer();
    item2->setMolecule(p.get());
}
