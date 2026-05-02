#pragma once

#include "Renderable.h"
#include "VAO.h"
#include <vector>

class RenderManager{
public:
    RenderManager();
    virtual ~RenderManager();

    int PushRenderVAO(VAO* vao);
    void Queue(Renderable* renderable);
    void Render();
private:
    std::vector<Renderable*> queue;
    std::vector<VAO*> vaos;
};

extern RenderManager* renderManager;

void ConnectRenderManager(RenderManager* manager);
void SubmitRenderable(Renderable* object);
