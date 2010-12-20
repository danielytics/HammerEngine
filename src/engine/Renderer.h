#ifndef RENDERER_H
#define RENDERER_H

/*
int main () {

    MemoryPool<Scene> scenePool;

    // Add things to render
    Scene* scene = scenePool.request();
    scene->image = player->image->texture();
    scene->position = viewport->transform(player->position());
    scene->colour.set(1.0, 1.0, 1.0);
    for (Tile* tile in viewport->getVisibleTiles())
    {
        Scene* node = scenePool.request();
        node->image = tile->image->texture();
        node->position = viewport->transform(tile->position());
        node->colour->set(1.0, 1.0, 1.0);
    }

    renderQueue->put(scene);

    // ---------------------------

    Scene* scene = renderQueue.get();

    // Render scene
    Renderer renderer();
    renderer.render(scene);

    // Free render state resources
    scene->releaseAll(scenePool);

}
*/

class Renderer
{
public:
    Renderer();
};

#endif // RENDERER_H
