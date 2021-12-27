// //
// // Created by kriko on 2021/12/26.
// //

// #include <SDL.h>
// #include <iostream>

// bool Init();

// bool LoadMedia();

// void SDLEvents();

// void Close();

// SDL_Window *gWindowPtr = nullptr;
// SDL_Surface *gScreenSurfacePtr = nullptr;
// SDL_Surface *gHelloWorldPtr = nullptr;

// bool Init()
// {
//     bool bSuccess = true;
//     if (SDL_Init(SDL_INIT_VIDEO) < 0)
//     {
//         printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//         bSuccess = false;
//     }
//     else
//     {
//         gWindowPtr = SDL_CreateWindow(
//             "SDL Tutorial",
//             SDL_WINDOWPOS_UNDEFINED,
//             SDL_WINDOWPOS_UNDEFINED,
//             640, 480,
//             SDL_WINDOW_SHOWN);
//         if (gWindowPtr == nullptr)
//         {
//             printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
//             bSuccess = false;
//         }
//         else
//         {
//             gScreenSurfacePtr = SDL_GetWindowSurface(gWindowPtr);
//         }
//         return bSuccess;
//     }
// }

// bool LoadMedia()
// {
//     bool bSuccess = true;

//     gHelloWorldPtr = SDL_LoadBMP("F:/CppProjects/SDLGameEngine/UnitTest/Resources/hello_world.bmp");
//     if (gHelloWorldPtr == nullptr)
//     {
//         printf("Unable to load image! SDL_Error: %s\n", SDL_GetError());
//         bSuccess = false;
//     }

//     return bSuccess;
// }

// void SDLEvents()
// {
//     // 在 Mac 中必须处理事件，否则窗口不会显示出来
//     while (true)
//     {
//         SDL_Event event;
//         if (SDL_PollEvent(&event))
//         {
//             if (SDL_QUIT == event.type)
//             {
//                 printf("SDL Quit\n");
//                 break;
//             }
//         }
//     }
// }

// void Close()
// {
//     SDL_FreeSurface(gHelloWorldPtr);
//     gHelloWorldPtr = nullptr;

//     SDL_DestroyWindow(gWindowPtr);
//     gWindowPtr = nullptr;

//     SDL_Quit();
// }

// int main(int argc, char **args)
// {
//     if (!Init())
//     {
//         printf("Fail to initialize!\n");
//     }
//     else
//     {
//         if (!LoadMedia())
//         {
//             printf("Failed to Load Media!\n");
//         }
//         else
//         {
//             SDL_BlitSurface(gHelloWorldPtr, nullptr, gScreenSurfacePtr, nullptr);
//             SDL_UpdateWindowSurface(gWindowPtr);
//             SDL_Delay(2000);
//         }
//     }

//     SDLEvents();

//     Close();

//     return 0;
// }

// #include <gtest/gtest.h>

// TEST(HelloTest, BasicAssertions)
// {
//     EXPECT_STRNE("hello", "world");
//     EXPECT_EQ(7 * 6, 42);
// }

#include <iostream>

#include <GameFramework/Actor.h>
#include <Components/SceneComponent.h>
class MyActor : public Actor
{
public:
    MyActor();
    ~MyActor();

public:
    virtual void Tick(float DeltaSeconds) override;
};

MyActor::MyActor()
{
    RootComponent = std::make_shared<SceneCompoent>();
    auto TestSceneComponent = std::make_shared<SceneCompoent>();
    TestSceneComponent->AttachToComponent(RootComponent);
}

MyActor::~MyActor()
{
}

void MyActor::Tick(float DeltaSeconds)
{
    if (RootComponent != nullptr)
    {
        auto Transform = RootComponent->GetTransform();
        std::cout << Transform.ToString() << std::endl;

        printf("RootComponet Children Size = %d\n", RootComponent->GetAttachChildren().size());
    }
    else
    {
        printf("RootComponent is nullptr!\n");
    }
}

int main(int argc, char **args)
{
    MyActor actor;
    actor.Tick(0.5f);
    return 0;
}