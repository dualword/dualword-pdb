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
#ifndef SRC_LOADERPDB_H_
#define SRC_LOADERPDB_H_

#include <QtGui>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class LoaderPDB : public QInputDialog {
	Q_OBJECT

public:
	LoaderPDB(QWidget * p = 0, Qt::WindowFlags f = 0 );
	virtual ~LoaderPDB();
	virtual void done (int);

public slots:
	void downloadFinished(QNetworkReply*);

private:
	QNetworkAccessManager mgr ;

};

#endif /* SRC_LOADERPDB_H_ */
