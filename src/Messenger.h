#ifndef MESSENGER_H
#define MESSENGER_H

#include <tbb/atomic.h>

class SceneNode;

class Messenger
{
private:
    bool& runningFlag;

    tbb::atomic<const SceneNode*> sceneToRender;

public:
    Messenger (bool& r);

    bool& running ();

    inline const SceneNode* getAndSetScene (const SceneNode* sn)
    {
        return sceneToRender.fetch_and_store(sn);
    }

};

#endif // MESSENGER_H
