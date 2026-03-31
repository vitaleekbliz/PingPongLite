# 🏓 PingPongLite: A Custom C++ 2D Game Engine


⚠️⚠️⚠️**Disclaimer**: *PROJECT IS IN ACTIVE DEVELOPMENT, SOME README PROPS CAN BE OUTDATED*.⚠️⚠️⚠️  
  * **Trello**: https://trello.com/b/YYHZVy0R/pingpong  
  * **Currently working on** :
    * [50%]centralized collision system
    * Collectibles
    * Animations
  * **Upcoming systems**:
    * MainMenu

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

### 🚀 Launch

1.Go to app/{version}/  
2.Run program and enjoy

### ⚙️ Debug/Development

1. Clone repositry and open solution in VS
2. If encountered any asset loading or dll errors - copy $(SolutionDir)/app/{latest version}/ to x64/Debug/

### 🛠️ Linking dependencies

Place build exe file into $(SolutionDir)/app/{latest version} folder and run the program

## 😱 Technical Highlights
1. ✅ **Animations**  

2. ✅ **External libraries**:  

    * ✅ *SDL3_mixer* in AudioHandler   
    * ✅ *SDL3_ttf* in FontHandler   
    * ✅ *SDL3_image* in TextureHandler   

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
  * And others

* *Decorator* :  
  * [✅] ScoreDecorator  
  * [✅] TimeDecorator  
    * ($(ProjectDir)source\entities\ScoreBar{.h, .cpp}  
    * ($(ProjectDir)source\entities\ScoreComponents\..)  
  * [✅] Ball movement  
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
    * Implemented a isReadyForCollision flag. This state-gate prevents the physics solver from processing a new hit until the ball has safely exited the current interaction zone  
    * Also pushing ball out of bounds of paddle for editional safety

## 🎮 Gameplay Features
