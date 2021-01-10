include("version.pri")
include("../3rdparty/ligsitecsc/ligsitecsc.pri")

TARGET = dualword-pdb
TEMPLATE = app
CONFIG += qt thread console release
QT += opengl

DEPENDPATH += . ../3rdparty/ligsitecsc
INCLUDEPATH += . ../3rdparty/ligsitecsc

HEADERS += \
	MainWindow.h \
	DualwordPdb.h \
	ProteinPocket.h
		
SOURCES += \
	MainWindow.cpp \
	DualwordPdb.cpp \
	ProteinPocket.cpp \
	main.cpp

FORMS += \
	MainWindow.ui
							
OBJECTS_DIR = .build/obj
MOC_DIR     = .build/moc
RCC_DIR     = .build/rcc
UI_DIR      = .build/ui
