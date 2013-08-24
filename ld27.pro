QT += quick

TARGET = ld27
DESTDIR = bin

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

SOURCES += \
    main.cpp \
    Window.cpp \
    Engine.cpp \
    States/LogoState.cpp \
    States/DummyState.cpp \
    Key.cpp \
    Direction.cpp \
    KeyDirectionMapping.cpp \
    Scene.cpp \
    IDrawable.cpp \
    Sprite.cpp \
    SpriteBundle.cpp \
    States/GameState.cpp \
    States/MenuState.cpp \
    LocalImageProvider.cpp \
    Actor.cpp \
    Player.cpp \
    SpriteLoader.cpp \
	VisionConeDrawable.cpp \
	Bot.cpp \
    States/MainMenuState.cpp \
    States/SettingsMenuState.cpp \
    MapLoader.cpp \
	Map.cpp

OTHER_FILES += \
    Window.qml \
    States/LogoState.qml \
    States/DummyState.qml \
    States/MenuState.qml

HEADERS += \
    Window.h \
	Engine.h \
	QStringEx.h \
    States/LogoState.h \
	States/DummyState.h \
    State.h \
    QTimerEx.h \
	Container.h \
	VisualObject.h \
	Key.h \
	Direction.h \
	KeyDirectionMapping.h \
    Scene.h \
	IDrawable.h \
	QListEx.h \
    Sprite.h \
    SpriteBundle.h \
    States/GameState.h \
    States/MenuState.h \
    MenuEntry.h \
    LocalImageProvider.h \
    Actor.h \
    Player.h \
    SpriteLoader.h \
	VisionConeDrawable.h \
	Bot.h \
    States/MainMenuState.h \
    States/SettingsMenuState.h \
    MapLoader.h \
    Map.h \
    MapLoader.h

QMAKE_CXXFLAGS += -std=gnu++11

RESOURCES += \
    Resources.qrc
