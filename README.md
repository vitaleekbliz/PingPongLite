# 🏓 PingPongLite: A Custom C++ 2D Game Engine


**DEVELPMENT PAUSED FOR TECH REVIEW**  
⚠️⚠️⚠️**Disclaimer**: *PROJECT IS IN ACTIVE DEVELOPMENT, SOME README PROPS CAN BE OUTDATED*.⚠️⚠️⚠️  
  * **Trello**: https://trello.com/b/YYHZVy0R/pingpong  
  * **Currently working on** :
    * Adding abstract factory to MainScene
    * centralized collision system
    * [50%]correcting Ball decorators
  * **Ready Features** :
    * Effect system
    * Paddle strategy switch
    * Score switch 
    * Ball movement decorator (under upgrading)
  * **Upcoming systems**:
    * MainMenu
    * Buffs system
    * Collectibles
    * Input handling 

## 🛠️ Tech Stack

Language: C++20  
Graphics/Input: SDL3-3.4.0 (Simple DirectMedia Layer)  
Font Rendering: SDL3_ttf-3.2.2  
Texture Rendering: SDL3_image-3.4.0  
Audio: SDL3_mixer-3.2.0  

## 💻 System Specifications

Platform: Windows 10 / 11 (x64-based PC)  
Architecture: x64 (64-bit)  
Visual Studio: 2026  
MSVC Version: 1950  
Compiler: C/C++ Optimizing Compiler Version 19.50.35727  

## 📖 Usage  

1. Dynamic library depencies. They should be included in app directory.:
  - SDL3.dll
  - SDL3_image.dll
  - SDL3_mixer.dll
  - SDL3_ttf.dll  
2. Assets:  
```bash
assets
+---arts
|       Ball.png
|       BallMotion.png
|       Board.png
|       Computer.png
|       Player.png
|       ScoreBar.png
|       
+---effects
|       blue_end.png
|       blue_loop.png
|       blue_start.png
|       red_end.png
|       red_loop.png
|       red_start.png
|       
+---fonts
|       calibri.ttf
|       
\---sounds
        hit.mp3
        lose.mp3
        music.mp3
        win.mp3
```


### 🚀 Launch

1.Go to app/  
2.Run program and enjoy

### ⚙️ Debug/Development

1. Clone repositry and open solution in VS
2. If encountered any asset loading or dll errors - copy $(SolutionDir)/app/ to x64/Debug/

### 🛠️ Linking dependencies

Place build exe file into $(SolutionDir)/app folder and run the program

## 📋 Technical Task list

### 🤩 Main Tasks
1. ❗**Demonstrate C++ knowledge**❗. Look inside any code file XD. 7 years of C++ code writing, actually started 11 years ago   
2. ❗**OOP**❗ :  
    * "source\entities\PaddleComponents\." and "source\entities\Paddle{.h, .cpp}"  
    * "source\entities\ScoreComponents\." and "source\entities\ScoreBar{.h, .cpp}"  

3. ❗**STL**❗
* containers:
Din't really use much, however I am active leetcode user (1200+ solved problems) https://leetcode.com/u/BiTaJIb41K/  

4. ❗**clang-format**❗: using Format on save plugin
5. ❗**external librarires**❗: details in Tech Stack segment
6. ❗**Game architecture**❗
  * Game Loop:  
using temporery solution, cause I have only 1 Scene, however Ready to deploy. Each game object that is on scene also has update and render methods. To get tickRate use SDLHandler Singleton.
```cpp
while (mainScene.isRunning())
{
	sdlHandler.handleTickRate();

	if (!sdlHandler.handleEvents())
	{
		mainScene.close();
	}

	mainScene.update();

	mainScene.render();
}
```
7. ❗**Design Patterns**❗ : details in Bonus Task section
8. ❗**Compile code**❗ : tested running on several devices. Check Usage section for more details

### 😱 Bonus Tasks
1. ✅ **Animations**  

2. ✅ **External libraries**:  

    * ✅ *SDL3_mixer* in AudioHandler   
    * ✅ *SDL3_ttf* in FontHandler   
    * ✅ *SDL3_image* in TextureHandler   
($(ProjectDir)/source/core/)  

3. ✅ **Design Patterns**:  
* *Abstract Factory* :  
    * ❌ MainScene is a mess right now after testing stuff, need to clean up using factory  

* *Strategy* :  
    * ✅ Computer/Player follow same mechanic  
($(ProjectDir)source\entities\Paddle{.h, .cpp}  
($(ProjectDir)source\entities\PaddleComponents\..)  

* *Singleton* :  
  * ✅SDLHandler  
($(ProjectDir)/source/core/SDLHandler{.h/.cpp})  
  * ✅TextureHandler  
  * ✅AudioHandler  
  * ✅TextHandler  
  * ✅EffectHandler  
($(ProjectDir)/source/core/subsystems/)  

* *Observer* :  
  * ✅ BoundaryObserver - handles Ball Events : Wall/Paddle hit, Win/Lose goal  
    * ($(ProjectDir)/source/entites/interfaces/BoundaryObserver)  
  * ✅ StrategyObserver  
    * ($(ProjectDir)/source/entites/interfaces/StrategyObserver/)

* *Decorator* :  
  * [✅] ScoreDecorator  
  * [✅] TimeDecorator  
    * ($(ProjectDir)source\entities\ScoreBar{.h, .cpp}  
    * ($(ProjectDir)source\entities\ScoreComponents\..)  
  * [✅/❌] Ball movement  
  * [✅/❌] Ball collision  
    * ($(ProjectDir)source\entities\Ball{.h, .cpp}  
    * ($(ProjectDir)source\entities\BallComponents\..)  

* *State Machine* :  
    * ✅EffectComponent  
($(ProjectDir)/source/components/effects/)  

## Architecture
``` bash
source
|   main.cpp
|   
+---components
|   \---effects
|           EffectComponent.cpp
|           EffectComponent.h
|           
+---core
|   |   SDLHandler.cpp
|   |   SDLHandler.h
|   |   
|   \---subsystems
|           AudioHandler.cpp
|           AudioHandler.h
|           EffectHandler.cpp
|           EffectHandler.h
|           FontHandler.cpp
|           FontHandler.h
|           TextureHandler.cpp
|           TextureHandler.h
|           
+---entities
|   |   Object.cpp
|   |   Object.h
|   |   
|   +---Ball
|   |   |   Ball.cpp
|   |   |   Ball.h
|   |   |   
|   |   \---components
|   |           BallCollisionDecorator.cpp
|   |           BallCollisionDecorator.h
|   |           BallMovementDecorator.cpp
|   |           BallMovementDecorator.h
|   |           
|   +---Board
|   |   |   Board.cpp
|   |   |   Board.h
|   |   |   
|   |   \---components
|   +---interfaces
|   |   +---BoundaryObserver
|   |   |       BoundaryPublisher.cpp
|   |   |       BoundaryPublisher.h
|   |   |       BoundarySubscriber.h
|   |   |       
|   |   \---StrategyObserver
|   |           StrategyPublisher.cpp
|   |           StrategyPublisher.h
|   |           StrategySubscriber.h
|   |           
|   +---Paddle
|   |   |   Paddle.cpp
|   |   |   Paddle.h
|   |   |   
|   |   \---components
|   |       \---PaddleStrategy
|   |               PaddleComputerStrategy.cpp
|   |               PaddleComputerStrategy.h
|   |               PaddlePlayerStrategy.cpp
|   |               PaddlePlayerStrategy.h
|   |               PaddleStrategy.cpp
|   |               PaddleStrategy.h
|   |               
|   \---Score
|       |   ScoreBar.cpp
|       |   ScoreBar.h
|       |   
|       \---components
|               ScoreDecorator.cpp
|               ScoreDecorator.h
|               TimeDecorator.cpp
|               TimeDecorator.h
|               
\---scenes
        MainScene.cpp
        MainScene.h
        Scene.cpp
        Scene.h
```


## 🏆 Challenges

### 🧩 Key Challenges & Solutions

**Challenge: Eliminating Deterministic Physics Traps**  
https://youtu.be/fDKUqmMbjVc
* Problem: Deterministic Physics Traps  
The ball would occasionally enter infinite horizontal or vertical loops due to perfect reflection math, stalling gameplay.
* **Solution:** 
  * Vertically : clamping velocity Y axes
  * Horizontally : pushing ball away from paddle center

**Challenge: Collision Overlap**  
https://youtu.be/brq7M2zOXg4
* Problem: Deterministic Physics Traps  
If the ball didn't exit the paddle's collision volume in a single frame, the physics engine would re-trigger the bounce, causing the ball to jitter or become "glued" inside the paddle.
* **Solution:** 
Implemented a isReadyForCollision flag. This state-gate prevents the physics solver from processing a new hit until the ball has safely exited the current interaction zone

## 🚀 Technical Highlights

## 🎮 Gameplay Features

## 💡 Key Features
