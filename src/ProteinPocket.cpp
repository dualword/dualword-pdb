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

#include "ProteinPocket.h"

#include "lcs.h"

ProteinPocket::ProteinPocket(const QString& name, QObject *p) : QThread(p) {
	this->name = name;

}

ProteinPocket::~ProteinPocket() {

}

void ProteinPocket::run() {
	try{
		lcs o;
		o.runLigsite(name.toStdString());
		emit showPocket(o.buf);
	} catch (...) {

	}
}
