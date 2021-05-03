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

#include "MainWindow.h"
#include "ProteinPocket.h"
#include "ProteinVolume.h"
#include "LoaderPDB.h"
#include "global.h"

#include <BALL/FORMAT/PDBInfo.h>
#include <BALL/KERNEL/system.h>
#include <BALL/FORMAT/PDBFile.h>
using namespace BALL;

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
	qRegisterMetaType<Pdb>("Pdb");
	setWindowTitle(qApp->applicationName());
	tbl->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	actionOpenPdb->setIcon(style()->standardIcon(QStyle::SP_FileDialogStart, 0, this));
    connect(actionOpenPdb,SIGNAL(triggered()), SLOT(openPdb()));
	actionGetPdb->setIcon(style()->standardIcon(QStyle::SP_DriveNetIcon, 0, this));
    connect(actionGetPdb,SIGNAL(triggered()), SLOT(getPdb()));
	actionConsole->setIcon(style()->standardIcon(QStyle::SP_FileDialogContentsView, 0, this));
	console->setVisible(false);
	actionDelete->setIcon(style()->standardIcon(QStyle::SP_TrashIcon, 0, this));
	actionFirst->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward, 0, this));
	actionBack->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward, 0, this));
	edit = new QLineEdit();
	edit->setMaximumWidth(100);
	toolBar->insertWidget(actionNext, edit);
	actionNext->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward, 0, this));
	actionLast->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward, 0, this));
	connect(actionFirst,SIGNAL(triggered()), mainDb, SLOT(first()));
	connect(actionBack,SIGNAL(triggered()), mainDb, SLOT(back()));
	connect(actionNext,SIGNAL(triggered()), mainDb, SLOT(next()));
	connect(actionLast,SIGNAL(triggered()), mainDb, SLOT(last()));
	connect(mainDb,SIGNAL(newPdb(const Pdb&)), SLOT(showPDB(const Pdb&)));
    connect(actionConsole,SIGNAL(toggled(bool)), console, SLOT(setVisible(bool)));
	actionAbout->setIcon(style()->standardIcon(QStyle::SP_FileDialogInfoView, 0, this));
    connect(actionAbout,SIGNAL(triggered()), SLOT(showAbout()));
    connect(sliderOpacity, SIGNAL(valueChanged(int)), SLOT(opacityChanged(int)));
    connect(checkMode, SIGNAL(stateChanged(int)), SLOT(modeChanged(int)));
    connect(checkPocket, SIGNAL(stateChanged(int)), SLOT(modePocket(int)));
	connect(actionShowPDB,SIGNAL(triggered()), SLOT(showText()));
    reset();

}

MainWindow::~MainWindow() {}

void MainWindow::reset() {
	tbl->clearContents();
	tbl->setRowCount(0);
	view->removeItem(item.data());
	view->removeItem(item2.data());
    item.reset(new chemkit::GraphicsPymolSurfaceItem());
    view->addItem(item.data());
    item2.reset(new chemkit::GraphicsPymolSurfaceItem());
    view->addItem(item2.data());
    opacityChanged(sliderOpacity->value());
    modeChanged(checkMode->checkState());
    modePocket(checkPocket->checkState());
}

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

	pocket.reset(new ProteinPocket(f));
	connect(pocket.data(), SIGNAL(newPdb(const QString&)), SLOT(newPdb(const QString&)));
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

void MainWindow::modePocket (int i){
	if(Qt::Unchecked == i){
		item2->setVisible(false);
	}else if((Qt::Checked == i)){
		item2->setVisible(true);
	}
    view->update();
}

void MainWindow::showPDB(const Pdb& buf){
    reset();
	std::istringstream is(buf.getText().toStdString());
    pFile.reset(new chemkit::PolymerFile);
    pFile->read(is, "pdb");
	const boost::shared_ptr<chemkit::Polymer> &polymer = pFile->polymer();
	item->setMolecule(polymer.get());
	view->camera()->lookAt(polymer->center().cast<float>());

	std::istringstream is2(buf.getPocket().toStdString());
    pFile.reset(new chemkit::PolymerFile);
    pFile->read(is2, "pdb");
    const boost::shared_ptr<chemkit::Polymer> &p = pFile->polymer();
    item2->setMolecule(p.get());

	view->update();
	createRow("Atoms",QString::number(buf.getAtoms()));
	createRow("Molecular Weight",QString::number(buf.getWeight(),'f'));
}

void MainWindow::showPocket(const QString& buf) {
	std::istringstream is(buf.toStdString());
    pFile.reset(new chemkit::PolymerFile);
    pFile->read(is, "pdb");
    const boost::shared_ptr<chemkit::Polymer> &p = pFile->polymer();
    item2->setMolecule(p.get());
    view->update();
}

void MainWindow::getPdb(){
	LoaderPDB pdb;
	pdb.exec();
}

void MainWindow::createRow(const QString& p, const QString& v, bool c){
	tbl->insertRow(tbl->rowCount());
	int row = tbl->rowCount()-1;
	QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(p));
	if (c) item->setBackground(QBrush(QColor(153,255,255)));
	tbl->setItem(row, 0, item);
	item = new QTableWidgetItem(tr("%1").arg(v));
	if (c) item->setBackground(QBrush(QColor(153,255,255)));
	tbl->setItem(row, 1, item);
}

void MainWindow::showText(){
	if(mainDb->size() > 0){
		QMessageBox::about(this, tr("About"), mainDb->pdb()->getText() );
	}
}

void MainWindow::newPdb(const QString& id){
	listId->addItem(id);
}
