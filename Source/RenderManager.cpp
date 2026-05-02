#include "RenderManager.h"
#include <iostream>



RenderManager::RenderManager(){}
RenderManager::~RenderManager(){
    vaos.clear();
    queue.clear();
}
int RenderManager::PushRenderVAO(VAO* vao){
    vaos.push_back(vao);
    return vaos.size()-1;
}
void RenderManager::Queue(Renderable* renderable){
    queue.push_back(renderable);
}
void RenderManager::Render(){
    if (queue.empty())
        return;

    for(int i=0;i<queue.size();i++) {
        int id = queue[i]->vaoID;
        if(id < vaos.size()){
            switch (queue[i]->renderType){
            case CoreRenderType::triangle:
                queue[i]->Render();
                vaos[id]->Bind();
                vaos[id]->Draw();
            break;
            case CoreRenderType::text:
                queue[i]->Render();
            case CoreRenderType::point:

            break;
            case CoreRenderType::line:

            break;
        }
            //queue[i]->Render();
            //vaos[id]->Bind();
            //vaos[id]->Draw();
        }

        

        
    }
    queue.clear();
}

RenderManager* renderManager;
void ConnectRenderManager(RenderManager* manager){
    renderManager = manager;
}
void SubmitRenderable(Renderable* object){
    renderManager->Queue(object);
}