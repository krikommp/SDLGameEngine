// //
// // Created by kriko on 2021/12/26.
// //

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

        printf("RootComponet Children Size = %lu\n", RootComponent->GetAttachChildren().size());
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