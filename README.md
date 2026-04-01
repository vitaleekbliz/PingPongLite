# 🏓 PingPongLite: A Custom C++ 2D Game Engine

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
2. If encountered any asset loading or dll errors - copy $(SolutionDir)/app/{latest version}/ to bin/$(Platform)/

### 🛠️ Linking dependencies

Place build exe file into $(SolutionDir)/app/{latest version} folder and run the program

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
|   |           BallMovementDecorator.cpp
|   |           BallMovementDecorator.h
|   |           
|   +---Board
|   |       Board.cpp
|   |       Board.h
|   |       
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
