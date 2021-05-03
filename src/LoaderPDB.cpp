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

#include "LoaderPDB.h"
#include "ProteinPocket.h"
#include "global.h"

LoaderPDB::LoaderPDB(QWidget *p, Qt::WindowFlags f) : QInputDialog(p, f){
    connect(&mgr, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
    setLabelText("Enter PDB ID:");
}

LoaderPDB::~LoaderPDB() {

}

void LoaderPDB::done (int r){
	if(r) {
		QString pdb("http://files.rcsb.org/download/"+textValue().toUpper()+".pdb");
		QNetworkReply* reply = mgr.get(QNetworkRequest(QUrl(pdb)));
	}else {
		QDialog::done (0);
	}
}

void LoaderPDB::downloadFinished(QNetworkReply *reply){
	if (reply->error()) {
		mainApp->log(reply->errorString());
	}else{
		QString str(reply->readAll());
		ProteinPocket* t = new ProteinPocket(textValue().toUpper(), str, this);
		connect(t, SIGNAL(newPdb(const QString&)),mainWin, SLOT(newPdb(const QString&)));
		connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
		t->start();
	}
	reply->deleteLater();
	QDialog::done (0);
}
