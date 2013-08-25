######################################################################
# Automatically generated by qmake (3.0) Sat Aug 24 19:29:17 2013
######################################################################

TEMPLATE = app
TARGET = map-generator
INCLUDEPATH += .

# Input
SOURCES += main.cpp \
	MapLoader.cpp \
	CollisionMapAnalyzer.cpp \
	CollisionMapAnalyzerResult.cpp \
	CollisionMapEntry.cpp \
	LookupResult.cpp \
	Map.cpp

HEADERS += MapLoader.h \
	CollisionMapAnalyzer.h \
	CollisionMapAnalyzerResult.h \
	CollisionMapEntry.h \
	LookupResult.h \
	Map.h \
	QStringEx.h \
	QListEx.h \
    Utilities.h

QMAKE_CXXFLAGS += -std=gnu++11
