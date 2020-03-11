include("version.pri")

TARGET = dualword-pdb
TEMPLATE = app
CONFIG += qt thread console release
QT += opengl

DEPENDPATH += .
INCLUDEPATH += .

HEADERS = \
	MainWindow.h \
	DualwordPdb.h
		
SOURCES = \
	MainWindow.cpp \
	DualwordPdb.cpp \
	main.cpp

FORMS += \
	MainWindow.ui
							
OBJECTS_DIR = .build/obj
MOC_DIR     = .build/moc
RCC_DIR     = .build/rcc
UI_DIR      = .build/ui
