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

#ifndef SRC_DB_H_
#define SRC_DB_H_

#include "global.h"

class Pdb;

class Db : public QObject {
Q_OBJECT

public:
	Db(QObject *p = 0);
	virtual ~Db();

signals:
	void newPdb(const Pdb&);

public slots:
	void back();
	void next();
	void first();
	void last();
	int size() {return list.size();};
	void deleteAll();
	void save(const QString&);
	void savePdb(Pdb&);
	Pdb* pdb() {return &list[idx];};

private:
	int idx;
	QList<Pdb> list;

};

#endif /* SRC_DB_H_ */
