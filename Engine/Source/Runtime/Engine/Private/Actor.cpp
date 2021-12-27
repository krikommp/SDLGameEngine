#include <GameFramework/Actor.h>
#include <iostream>

Actor::Actor() {}

Actor::~Actor() {}

void Actor::Say()
{
    printf("Actor Say: Hello\n");
}