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

#include "Db.h"

Db::Db(QObject* p) : QObject(p) {


}

Db::~Db() {

}

void Db::back(){
	if(list.size() == 0) return;
	if(--idx<0) idx = 0;
	emit newPdb(list[idx]);
}

void Db::next(){
	if(list.size() == 0) return;
	if(++idx>list.size()-1) idx = list.size()-1;
	emit newPdb(list[idx]);
}

void Db::first(){
	if(list.size() == 0) return;
	idx = 0;
	emit newPdb(list[idx]);
}

void Db::last(){
	if(list.size() == 0) return;
	idx = list.size()-1;
	emit newPdb(list[idx]);
}

void Db::deleteAll(){
	list.clear();
	idx = 0;
//	deleteMol();
}

void Db::save(const QString& str){
	list.append(Pdb(str));
	//list.push_back(m);
	last();
}

void Db::savePdb(Pdb& pdb){
	//list.append(pdb);
	list.push_back(pdb);
	if(list.size() == 1) last();
}



