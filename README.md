# Flappy Bird

Flappy Bird clone made in C++ with [raylib](https://www.raylib.com) for the subject *Desarrollo de Videojuegos I* (Image Campus, 2026).

Fly between the pipes without touching them or falling to the ground. Every pipe you pass gives you one point.
You can play alone or against a friend on the same keyboard.

## Controls

| Action | Player 1 | Player 2 |
| --- | --- | --- |
| Jump | `SPACE` | `UP ARROW` |
| Pause / resume | `P` or `ESC` | `P` or `ESC` |
| Navigate menus | Mouse (left click) | Mouse (left click) |

The orange arrow at the top left corner goes back to the main menu.

## Game modes

- **1 Player**: get as many points as you can. Your best score of the session is shown on the game over screen.
- **2 Players**: both birds play at the same time. The player with more points wins; if there is a tie, the one who survived longer wins.

## Features

- 3-layer parallax background
- Countdown before each match
- Pause screen
- Score, best score and winner screen
- 2 music tracks (menu and gameplay) and 7 sound effects

## Building

1. Clone the repository.
2. Open `Flappy Bird.slnx` with Visual Studio (toolset v145).
3. Build in `Debug` or `Release` for `x64`.

The executable is generated in `bin/x64/<Configuration>/` and the `res` folder is copied next to it automatically after each build.

## Credits

- **Mercedes Ramirez Diaz**: original author ([original repository](https://github.com/Mer1203/Flappy-Bird))
- **Valentin Reyes Cuadra**: fork (2 players mode, score, pause, audio, version 1.0)
- Music and sound effects synthesized by code (script in `res_raw/audio`)
- Made with raylib 6.2
