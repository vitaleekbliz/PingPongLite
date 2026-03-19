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
+---font
|       font.ttf
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
2. ❗**OOP**❗ :  
* *Ball and MainScene* class have the most implemented features. Recommend checking them out, along with their component folder : 
- $(ProjectDir)/source/scenes/MainScene
- $(ProjectDir)/source/scenes/Components
- $(ProjectDir)/source/enities/Ball{.h, .cpp}
- $(ProjectDir)/source/enities/BallComponents  

* *General*  
- Structured class inheritence
MainScene(Child) -> , and MainMenu(Child) -> Scene(Parent)
Entities : Ball, Computer, Player, ScoreBar -> Object(Scene placble objects)

- Prioritizing using private and protected visibility in Classes

* *Implementation*  
Use OOP in pattern designs implementation

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

	std::shared_ptr<Board> board;
	std::shared_ptr<Computer> computer;
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
✅ *SDL3_mixer* in AudioHandler   
($(ProjectDir)/source/core/).  
❌ *SDL3_ttf* in TextureHandler   
($(ProjectDir)/source/core/).  
✅ *SDL3_image* in TextureHandler   
($(ProjectDir)/source/core/)  

3. ✅ **Design Patterns**:  
* *Singleton* :  
✅SDLHandler  
($(ProjectDir)/source/core/SDLHandler{.h/.cpp})  

* *Observer* :  
✅ BallObserver - handles Ball Events : Wall/Paddle hit, Win/Lose goal  
($(ProjectDir)/source/interfaces/BallObserver)  
✅ TextureObserver - handles draw requests (✅ drawTexture, ❌ drawText)  

* *Abstract Factory* :  
- [✅/❌] MainScene is abstract factory - handles creation/linking of game Objects (ones that are placed on Scene)  
($(ProjectDir)/source/scenes/MainScene).  
MainScene is Builder.  

- ❌ ButtonCreator : EUREKE I can create buttons with different texts and background images for main menu using Builder class  
- ❌ TextCreator : component of ScoreBar object  

* *ByteCode*  
✅ TextureHandler for centrilized drawing loaded textures  
✅ AudioHandler for centrilized playing loaded audio files  
✅ MainScene for object creation  

* *Builder* :  
[✅] MainScene is builder  
Ps. Now I am using clean object creation, however hardcoded dependancies setup. I want to make dependencies fucntions for cleaner code and set Position/Size inside Object Creation.  

* *Decorator* :  
✅ Ball movement  
✅ Ball collisionComponent  

* *Strategy* :  
❌ Computer/Player follow mechanic (have code dublicate in both classes)  

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
|   |   Player.cpp
|   |   Player.h
|   |   ScoreBar.cpp
|   |   ScoreBar.h
|   |   
|   \---BallComponents
|           Collision.cpp
|           Collision.h
|           Movement.cpp
|           Movement.h
|           
+---interfaces
|   +---ballObserver
|   |       BallPublisher.cpp
|   |       BallPublisher.h
|   |       BallSubscriber.h
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
* **Issue:** The ball occasionally entered infinite vertical or horizontal loops due to perfect reflection math, leading to "stuck" gameplay states.  
* **Solution:** Implemented **Stochastic Vector Perturbation**. By introducing a controlled `m_maxAngularDeviation` during collision resolution, I ensured the ball maintains high entropy in its trajectory. This prevents infinite loops and introduces a more organic, "pro-feel" to the ball physics.  

## 🚀 Technical Highlights

## 🎮 Gameplay Features


## 💡 Key Features
