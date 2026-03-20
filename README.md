# 🏓 PingPongLite: A Custom C++ 2D Game Engine

⚠️⚠️⚠️**Disclaimer**: *PROJECT IS IN ACTIVE DEVELOPMENT, SOME README PROPS CAN BE OUTDATED*.⚠️⚠️⚠️  


PingPongLite is a high-performance, object-oriented 2D game developed from scratch using C++ and the SDL3 library.
This project serves as a demonstration of clean architecture, real-time physics simulation, and the implementation of common game design patterns.   

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

## Usage 📖 

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

1.Go to x64/Release/ dir  
2.Run program and enjoy

### ⚙️ Debug/Development

1. Clone repositry and open solution in VS
2. If encountered any asset loading or dll errors - copy $(SolutionDir)/app/ to x64/Debug/

### 🛠️ Linking dependencies

Place build exe file into $(SolutionDir)/app folder and run the program

## 📋 Technical Task list

### 🤩 Main Tasks
1. ❗**Demonstrate C++ knowledge**❗. Look inside any code file XD. 7 years of C++ code writing, actually started 11 years ago   
2. ❗**OOP**❗ :  "source\entities\PaddleComponents\." and "source\entities\Paddle{.h, .cpp}"

3. ❗**STL**❗
* containers:
Din't really use much, however I am active leetcode user (1200+ solved problems) https://leetcode.com/u/BiTaJIb41K/  

* Use weak_ptr for weak dependancies:

computer and player referencies :
```cpp
    std::weak_ptr<Object> playerObject;
    std::weak_ptr<Object> computerObject;
```
MainScene
```cpp
	std::unique_ptr<ObjectCreator> factory;
	std::shared_ptr<AudioHandler> audioHandler;
	std::shared_ptr<TextureHandler> textureHandler;
    ...
```

4. ❗**clang-format**❗: using Format on save plugin
5. ❗**external librarires**❗: details in Tech Stack segment
6. ❗**Game architecture**❗
  * Game Loop:  
using temporery solution, cause I have only 1 Scene, however Ready to deploy. Each game object that is on scene also has update and render methods. To get tickRate use SDLHandler Singleton.
```cpp
while (mainScene.isRunning())
	{
		if (!sdlHandler.handleEvents())
		{
			mainScene.close();
		}

		sdlHandler.handleTickRate();

		mainScene.update();
		mainScene.render();
	}
```
7. ❗**Design Patterns**❗ : details in Bonus Task section
8. ❗**Compile code**❗ : tested running on several devices. Check Usage section for more details

### 😱 Bonus Tasks
1. ❌ **Animations** - not yet😔  

2. ✅ **External libraries**:  

    * ✅ *SDL3_mixer* in AudioHandler   
($(ProjectDir)/source/core/).  
    * ✅ *SDL3_ttf* in FontHandler   
($(ProjectDir)/source/core/).  
    * ✅ *SDL3_image* in TextureHandler   
($(ProjectDir)/source/core/)  

3. ✅ **Design Patterns**:  
* *Strategy* :  
  *✅ Computer/Player follow same mechanic
    *($(ProjectDir)/source/core/SDLHandler{.h/.cpp}) 

* *Singleton* :  
  * ✅SDLHandler  
($(ProjectDir)/source/core/SDLHandler{.h/.cpp})  

* *Observer* :  
  * ✅ BallObserver - handles Ball Events : Wall/Paddle hit, Win/Lose goal  
    *($(ProjectDir)/source/interfaces/BallObserver)  
  * ✅ TextureObserver - handles draw requests   
    * ($(ProjectDir)/source/interfaces/TextureObserver)
  * ✅ FontObserver - handles draw requests  
    * ($(ProjectDir)/source/interfaces/FontObserver)

* *Decorator* :  
  * ✅ Ball movement  
  * ✅ Ball collisionComponent  



* *State Machine* :  
❌ BallState - colision detection with state (onTrigger enter Unity analogy). Decides when ball is ready for next collision.  

## Architecture
``` bash
source
|   main.cpp
|   
+---core
|       AudioHandler.cpp
|       AudioHandler.h
|       FontHandler.cpp
|       FontHandler.h
|       SDLHandler.cpp
|       SDLHandler.h
|       TextureHandler.cpp
|       TextureHandler.h
|       
+---entities
|   |   Ball.cpp
|   |   Ball.h
|   |   Board.cpp
|   |   Board.h
|   |   Computer.cpp
|   |   Computer.h
|   |   Object.cpp
|   |   Object.h
|   |   Paddle.cpp
|   |   Paddle.h
|   |   Player.cpp
|   |   Player.h
|   |   ScoreBar.cpp
|   |   ScoreBar.h
|   |   
|   +---BallComponents
|   |       BallCollisionDecorator.cpp
|   |       BallCollisionDecorator.h
|   |       BallMovementDecorator.cpp
|   |       BallMovementDecorator.h
|   |       
|   \---PaddleComponents
|           PaddleComputerStrategy.cpp
|           PaddleComputerStrategy.h
|           PaddlePlayerStrategy.cpp
|           PaddlePlayerStrategy.h
|           PaddleStrategy.cpp
|           PaddleStrategy.h
|           
+---interfaces
|   +---ballObserver
|   |       BallPublisher.cpp
|   |       BallPublisher.h
|   |       BallSubscriber.h
|   |       
|   +---fontObserver
|   |       FontPublisher.cpp
|   |       FontPublisher.h
|   |       FontSubscriber.h
|   |       
|   \---textureObserver
|           TexturePublisher.cpp
|           TexturePublisher.h
|           TextureSubscriber.h
|           
\---scenes
    |   MainScene.cpp
    |   MainScene.h
    |   Scene.cpp
    |   Scene.h
    |   
    \---components
        \---objectFactory
                Creator.cpp
                Creator.h
                objectFactory.cpp
                objectFactory.h
                Product.cpp
                Product.h
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
  * 

**Challenge: Collision Overlap** 
https://youtu.be/brq7M2zOXg4
* Problem: Deterministic Physics Traps  
If the ball didn't exit the paddle's collision volume in a single frame, the physics engine would re-trigger the bounce, causing the ball to jitter or become "glued" inside the paddle.
* **Solution:** 
Implemented a isReadyForCollision flag. This state-gate prevents the physics solver from processing a new hit until the ball has safely exited the current interaction zone

## 🚀 Technical Highlights

## 🎮 Gameplay Features

## 💡 Key Features
