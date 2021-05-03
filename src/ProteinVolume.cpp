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

#include "ProteinVolume.h"
#include "global.h"

#include <BALL/MOLMEC/COMMON/periodicBoundary.h>
#include <BALL/MOLMEC/COMMON/forceField.h>
#include <BALL/MOLMEC/COMMON/support.h>
#include <BALL/STRUCTURE/geometricProperties.h>
#include <BALL/STRUCTURE/geometricTransformations.h>
#include <BALL/SYSTEM/path.h>
#include <BALL/CONCEPT/processor.h>
#include <BALL/FORMAT/HINFile.h>
#include <BALL/MATHS/common.h>
#include <BALL/KERNEL/system.h>
#include <BALL/KERNEL/PTE.h>
#include <BALL/STRUCTURE/numericalSAS.h>
#include <BALL/STRUCTURE/analyticalSES.h>
#include <BALL/STRUCTURE/defaultProcessors.h>
#include <BALL/FORMAT/PDBFile.h>
using namespace BALL;
using namespace std;

ProteinVolume::ProteinVolume() {

}

ProteinVolume::~ProteinVolume() {

}

void ProteinVolume::calculate(const QString& f, Pdb* pdb){

	PDBFile file(f.toStdString());
	if (!file){
//		Log.error() << "cannot open PBD file " << argv[1] << endl;
//		return 2;
	}

	System S;
	file >> S;
	file.close();

	AssignRadiusProcessor rp("radii/PARSE.siz");
	S.apply(rp);
	pdb->setAtoms(S.countAtoms());

	AtomConstIterator it = S.beginAtom();
	for (; +it; ++it) {
		weight += it->getElement().getAtomicWeight();
	}
	pdb->setWeight(weight);
}
