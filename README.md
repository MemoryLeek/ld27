# Ludum Dare #27

This is the repo we will use during Ludum Dare 27.
You'll be able to see our progress and all changes here in real time during the event.

## How to get the game

As usual we will provide binaries for Linux, OS X and Windows when the compo is over,
but you are always welcome to build the source yourself.

We also have Jenkins set up for continuous integration at https://ci.kwarf.com/job/ld27/
where you can download binaries for every working commit.

## Compiling the source

This project requires Qt5.1.

### Linux

Run the following:

    qmake -config release
    make

The executable is placed in bin/ and that is also the required working directory when
running the game.

### Windows

Assuming you have Qt5.1 installed with mingw-32.

    qmake -config release
    mingw32-make

The .exe is placed in bin/ and that is also the required working directory when
running the game.
