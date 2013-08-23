QT += quick

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
    States/GameState.cpp \
    AnimatedSprite.cpp \
    States/MenuState.cpp

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
    States/GameState.h \
    AnimatedSprite.h \
    States/MenuState.h \
    MenuEntry.h

QMAKE_CXXFLAGS += -std=gnu++11
