#ifndef _GAME_RENDER_ANIMATION_H
#define _GAME_RENDER_ANIMATION_H

#include <vector>

#include <components/nifogre/ogre_nif_loader.hpp>
#include <openengine/ogre/renderer.hpp>
#include "../mwworld/actiontalk.hpp"
#include <components/nif/node.hpp>
#include <openengine/bullet/physic.hpp>




namespace MWRender {

class Animation {
protected:
    Ogre::SceneNode* mInsert;
    OEngine::Render::OgreRenderer &mRend;

    float mTime;
    float mStartTime;
    float mStopTime;
    float mLoopStartTime;
    float mLoopStopTime;

    int mAnimate;
    bool mSkipFrame;

    NifOgre::EntityList mEntityList;
    NifOgre::TextKeyMap mTextKeys;

    bool findGroupTimes(const std::string &groupname, float *starttime, float *stoptime,
                        float *loopstarttime, float *loopstoptime);

public:
    Animation(OEngine::Render::OgreRenderer& _rend);
    virtual ~Animation();

    void playGroup(std::string groupname, int mode, int loops);
    void skipAnim();
    virtual void runAnimation(float timepassed);
};

}
#endif
