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

#ifndef SRC_GLOBAL_H_
#define SRC_GLOBAL_H_

#include "DualwordPdb.h"
#include "MainWindow.h"

class Pdb{
public:
	Pdb() : Pdb("") {};
	Pdb(const QString& str) : pdb(str), pocket(""), atoms(0), weight(0) {};
	virtual ~Pdb() {};
	const QString& getText() const { return pdb; }
	int getAtoms() const { return atoms; }
	void setAtoms(int atoms) {this->atoms = atoms;}
	double getWeight() const { return weight; }
	void setWeight(double weight) {this->weight = weight;}
	const QString& getPdb() const {return pdb;}
	void setPdb(const QString& pdb) {this->pdb = pdb;}
	const QString& getPocket() const {return pocket;}
	void setPocket(const QString& pocket) {this->pocket = pocket;}
	const QString& getName() const {return name;}
	void setName(const QString& name) {this->name = name;}

private:
	QString pdb;
	QString pocket;
	QString name;
	int atoms;
	double weight;
};
Q_DECLARE_METATYPE(Pdb)

#include "Db.h"


#if defined(mainApp)
#undef mainApp
#endif
#define mainApp (DualwordPdb::instance())

#if defined(mainWin)
#undef mainWin
#endif
#define mainWin (mainApp->win())

#if defined(mainDb)
#undef mainDb
#endif
#define mainDb (mainApp->getDb())

#include <stdexcept>
class dualword_exception: public std::runtime_error {
public:
	dualword_exception(const std::string& arg) : runtime_error(arg) {}
};

#endif /* SRC_GLOBAL_H_ */
