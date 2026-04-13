# 🏓 PingPongLite: A Custom C++ 2D Game Engine

Pong clone using custom game engine. 

## 👀 Demo 

Youtube : https://youtu.be/AcxncfVBUCg  

## 📝 Rules 
![Intro scene](./ReadmePictures/Intro.png)

## 🕹️ GamePlay 
![Gameplay](./ReadmePictures/Gameplay.png)

## ℹ️ info

Features I am proud of :  
* Observer make dependencies between objects much more managable.  
* Inheritance and polymorphism  
* Scene loading and cleaning its seperate subsystems like Font/Audio/Texture if needed  
* External collision system
* clean structure, although could unite files into one header for readability 
* edge cases handling:
  * ✔️ Collision triggering multiple times unless ball left boarders (state for ball/paddle collisions)  
  * ✔️ Pushing ball out of bounds on collisions/boundaries checks  
  * ✔️ Ball movement enchansing (changing angles and clamping Y velocity when stuck up/down motion)  
  * ❌ Ball skipps paddle if FPS is too low :
    * **Problem** :(deltaTime * speed) makes ball move too much in one frame.  
    * **Solutions** : 1. move ball multiple times during one frame. 2. Just implement maximum delta time(if game freezes, delta time will be max value despite of freeze duration)

## 🛠️ Tech Stack

Language: C++20  
Graphics/Input: SDL3-3.4.0 (Simple DirectMedia Layer)  
Font Rendering: SDL3_ttf-3.2.2  
Texture Rendering: SDL3_image-3.4.0  
Audio: SDL3_mixer-3.2.0  

## 💻 System Specifications

Platform: Windows 10 / 11 (x64-based PC)  
Architecture: x64 (64-bit)  

## 📖 Usage  

1. Go to Scripts/$(Platform) and generate solution files.

### ⚙️ Debug/Development

Building project should copy assets and dependencies automatically.

### 🛠️ Linking dependencies

Automatic

## Architecture
``` bash
source
|   Game.h
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
|   |           BallMovementDecorator.cpp
|   |           BallMovementDecorator.h
|   |           
|   +---Board
|   |   |   Board.cpp
|   |   |   Board.h
|   |   |   
|   |   \---components
|   +---Collectibles
|   |   |   Collectible.cpp
|   |   |   Collectible.h
|   |   |   
|   |   +---enum
|   |   |       CollectibleType.h
|   |   |       
|   |   \---subclasses
|   |           BlueStar.cpp
|   |           BlueStar.h
|   |           Potion.cpp
|   |           Potion.h
|   |           RedStar.cpp
|   |           RedStar.h
|   |           
|   +---interfaces
|   |   +---BoundaryObserver
|   |   |       BoundaryPublisher.cpp
|   |   |       BoundaryPublisher.h
|   |   |       BoundarySubscriber.h
|   |   |       
|   |   +---ChangeScoreObserver
|   |   |       ChangeScorePublisher.cpp
|   |   |       ChangeScorePublisher.h
|   |   |       ChangeScoreSubscriber.h
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
    |   IntroScene.cpp
    |   IntroScene.h
    |   MainScene.cpp
    |   MainScene.h
    |   Scene.cpp
    |   Scene.h
    |   
    \---components
        +---CollectiblesSpawner
        |       CollectibleSpawner.cpp
        |       CollectibleSpawner.h
        |       
        +---CollisionDetector
        |   |   CollisionDetector.cpp
        |   |   CollisionDetector.h
        |   |   
        |   +---Decorators
        |   |       CollectiblesCollisionDecorator.cpp
        |   |       CollectiblesCollisionDecorator.h
        |   |       CollisionDecorator.cpp
        |   |       CollisionDecorator.h
        |   |       PaddleCollisionDecorator.cpp
        |   |       PaddleCollisionDecorator.h
        |   |       
        |   \---PaddleHItObserver
        |           PaddleHitPublisher.cpp
        |           PaddleHitPublisher.h
        |           PaddleHitSubscriber.h
        |           
        \---interfaces
            +---CollectiblePickedObserver
            |       CollectiblePickedPublisher.cpp
            |       CollectiblePickedPublisher.h
            |       CollectiblePickedSubscriber.h
            |       
            \---CollectibleSpawnObserver
                    CollectibleSpawnedPublisher.cpp
                    CollectibleSpawnedPublisher.h
                    CollectibleSpawnSubscriber.h
```
