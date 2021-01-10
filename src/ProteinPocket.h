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

#ifndef SRC_PROTEINPOCKET_H_
#define SRC_PROTEINPOCKET_H_

#include <QtCore>

class ProteinPocket : public QThread {
	Q_OBJECT

public:
	ProteinPocket(const QString&, QObject *p = 0);
	virtual ~ProteinPocket();

signals:
	void showPocket(const QString&);

protected:
     void run();

private:
     QString name;



};

#endif /* SRC_PROTEINPOCKET_H_ */
