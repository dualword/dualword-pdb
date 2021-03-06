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

#include <QDateTime>

DualwordPdb::DualwordPdb(int &argc, char **argv) : QApplication(argc, argv), db(nullptr) {
	QCoreApplication::setApplicationName(QString(_DUALWORD));

	#ifdef _VER
		QApplication::setApplicationVersion(_VER);
	#endif

	QApplication::setQuitOnLastWindowClosed(true);
	db = new Db(this);
}

DualwordPdb::~DualwordPdb() {

}

void DualwordPdb::start() {
	w.reset(new MainWindow());
    w->show();
    mainApp->log(QDateTime::currentDateTime().toString());
}

void DualwordPdb::log(const QString& str){
	mainWin->con()->appendPlainText(str);
}
