# Multi Asteroids
This repo contains the source code for our extension for the first-year C project as part of the COMP40009 Computing Practical I module at Imperial College London. We implemented the classic arcade game Asteroids entirely in C, with singleplayer, multiplayer co-op, and AI game modes.

![image](https://github.com/justinkeung1018/c-project-extension/assets/94550621/a5ce037f-facd-495d-9783-780280382ed9)
![image](https://github.com/justinkeung1018/c-project-extension/assets/94550621/caa22476-864a-4412-9ae9-2a464005abb7)
![image](https://github.com/justinkeung1018/c-project-extension/assets/94550621/d72d3d94-5238-4f82-b06a-63982073390f)

## Setup
Clone the repo and its submodules:
```
git clone --recurse-submodules https://github.com/justinkeung1018/c-project-extension.git
```
Follow the instructions in the [Raylib repo](https://github.com/raysan5/raylib) to set up the library. Then simply compile the program in the root directory and run the executable:
```
make
./main
```

## Controls
### Singleplayer mode
| Control      | Action        |
|--------------|---------------|
| <kbd>↑</kbd> | Move forward  |
| <kbd>←</kbd> | Rotate left   |
| <kbd>→</kbd> | Rotate right  |
| <kbd>↓</kbd> | Shoot bullets |

### Multiplayer mode
The blue spaceship moves with the same controls as in singleplayer mode. The controls for the red spaceship are the <kbd>W</kbd> <kbd>A</kbd> <kbd>S</kbd> <kbd>D</kbd> equivalents of those of the blue spaceship. Precisely, they are as follows:
| Control      | Action        |
|--------------|---------------|
| <kbd>W</kbd> | Move forward  |
| <kbd>A</kbd> | Rotate left   |
| <kbd>D</kbd> | Rotate right  |
| <kbd>S</kbd> | Shoot bullets |
