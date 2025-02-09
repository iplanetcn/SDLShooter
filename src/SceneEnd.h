#ifndef SCENE_END_H
#define SCENE_END_H

#include "Scene.h"

class SceneEnd : public Scene{
    virtual void init();
    virtual void update(float deltaTime);
    virtual void render();
    virtual void clean();
    virtual void handleEvent(SDL_Event* event);
};


#endif // SCENE_END_H