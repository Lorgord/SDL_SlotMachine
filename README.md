# SDL_SlotMachine
Test task:

Implement a model of a slot machine with 5 rotating reels with 3 symbols in a visible field

Add a flashing “Start” button that starts the reels spinning;

Rotation time is 4-5 seconds. The reels must rotate at different speeds and stop sequentially one after another.

At the bottom of the screen, display the current fps of the program in font.

Description:

The slot machine model consists of:
- spinning reels with symbols;
- start button;
- frame counter;

The reels are created in the Game::Init function, and the number of reels can be changed by modifying the reelsAmount variable.

When initializing the reel, an array is filled with coordinates of possible stopping points, based on the size of the image and the number of symbols.

When the start button is pressed, a random number is generated - the speed of the reel's rotation, after which it starts moving.

After that, the reel spins at a fixed speed, regardless of the frame rate.

The FPS limit is set by the targetFrameRate variable in the FPS_Counter.h file.

The visualization of the reel's rotation is achieved by drawing a copy of its texture with an upward or downward offset, depending on the position of the main texture on the screen.

When the timer expires, the Reel::FindClosestStopLocation function returns the closest position for stopping, to which the reel smoothly rotates. The stopping sequence depends on the reel index.

After the last reel stops, the start button becomes operational again.

The project runs on Windows OS using the SDL2 library.
Project author: Egor Voronov.

![изображение](https://github.com/Lorgord/SDL_SlotMachine/assets/33752831/a4290af1-8368-4f63-9c5a-0fa67518717f)

https://github.com/Lorgord/SDL_SlotMachine/assets/33752831/b136f7e3-beeb-43ea-8779-d5b453052825
