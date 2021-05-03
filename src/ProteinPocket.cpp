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

#include "global.h"
#include "ProteinPocket.h"
#include "ProteinVolume.h"

#include "lcs.h"

ProteinPocket::ProteinPocket(const QString& f, const QString& t, QObject *p) :
	QThread(), fname(f), txt(t)  {

}

ProteinPocket::~ProteinPocket() {

}

void ProteinPocket::run() {
	try{
		Pdb pdb;
		QTemporaryFile file;
		if(txt.length() > 0){
			if (file.open()) {
				file.write(txt.toUtf8());
			}
			pdb.setPdb(txt);
			pdb.setName(fname.toUpper());
			fname = file.fileName();

			QFile f(file.fileName());
			f.open(QIODevice::ReadOnly | QIODevice::Text);
			qDebug() << f.readAll();
			file.close();

		}else{
		    QFile file(fname);
		    file.open(QIODevice::ReadOnly | QIODevice::Text);
		    pdb.setPdb(file.readAll());
		    file.close();
		    pdb.setName(fname.mid(fname.lastIndexOf("/")+1,
		    		(fname.lastIndexOf(".") - fname.lastIndexOf("/"))-1).toUpper());
		}

		lcs o;
		o.runLigsite(fname.toStdString());
		pdb.setPocket(o.buf);

		ProteinVolume vol;
		vol.calculate(fname, &pdb);

		mainDb->savePdb(pdb);
		emit newPdb(pdb.getName());
	}catch (...) {
		//
	}
}
