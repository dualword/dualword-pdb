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

#ifndef DUALWORDPDB_H_
#define DUALWORDPDB_H_

#define _DUALWORD "Dualword-pdb"

#include <QApplication>
#include <QScopedPointer>

class MainWindow;
class Db;

class DualwordPdb : public QApplication {
    Q_OBJECT

public:
	DualwordPdb(int &argc, char **argv);
	virtual ~DualwordPdb();
	static DualwordPdb *instance() {return (static_cast<DualwordPdb *>(QCoreApplication::instance()));};
	Db* getDb() {return db;};
	MainWindow* win() {return w.data();};

public slots:
	void start();
	void log(const QString&);

private:
	QScopedPointer<MainWindow> w;
	Db* db;

};


#endif /* DUALWORDPDB_H_ */
