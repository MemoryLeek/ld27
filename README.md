# Ludum Dare #27

## How to get the game

You can download our submission at http://www.ludumdare.com/compo/ludum-dare-27/?action=preview&uid=7989

It's currently quite buggy and crashes randomly on Windows. We will try to fix this within the next few days
and if it doesn't require too many changes we will update our submission.

We might also do a polished post-LD version, if we do you will be able to find it here.

We also have Jenkins set up for continuous integration at https://ci.kwarf.com/job/ld27/
where you can download binaries for every working commit.

## Compiling the source

This project requires Qt5.1 and SDL 2.0.

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
