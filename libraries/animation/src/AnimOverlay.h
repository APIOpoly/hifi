//
//  AnimOverlay.h
//
//  Copyright 2015 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_AnimOverlay_h
#define hifi_AnimOverlay_h

#include "AnimNode.h"

// Overlay the AnimPoses from one AnimNode on top of another AnimNode.
// child[0] is overlayed on top of child[1].  The boneset is used
// to control blending on a per-bone bases.
// alpha gives the ability to fade in and fade out overlays.
// alpha of 0, will have no overlay, final pose will be 100% from child[1].
// alpha of 1, will be a full overlay.

class AnimOverlay : public AnimNode {
public:
    friend class AnimDebugDraw;

    enum BoneSet {
        FullBodyBoneSet = 0,
        UpperBodyBoneSet,
        LowerBodyBoneSet,
        RightArmBoneSet,
        LeftArmBoneSet,
        AboveTheHeadBoneSet,
        BelowTheHeadBoneSet,
        HeadOnlyBoneSet,
        SpineOnlyBoneSet,
        EmptyBoneSet,
        NumBoneSets,
    };

    AnimOverlay(const std::string& id, BoneSet boneSet, float alpha);
    virtual ~AnimOverlay() override;

    virtual const AnimPoseVec& evaluate(const AnimVariantMap& animVars, float dt) override;

 protected:
    void buildBoneSet(BoneSet boneSet);

    void setBoneSetVar(const std::string& boneSetVar) { _boneSetVar = boneSetVar; }
    void setAlphaVar(const std::string& alphaVar) { _alphaVar = alphaVar; }

    // for AnimDebugDraw rendering
    virtual const AnimPoseVec& getPosesInternal() const override;
    virtual void setSkeletonInternal(AnimSkeleton::ConstPointer skeleton) override;

    AnimPoseVec _poses;
    BoneSet _boneSet;
    float _alpha;
    std::vector<float> _boneSetVec;

    std::string _boneSetVar;
    std::string _alphaVar;

    void buildFullBodyBoneSet();
    void buildUpperBodyBoneSet();
    void buildLowerBodyBoneSet();
    void buildRightArmBoneSet();
    void buildLeftArmBoneSet();
    void buildAboveTheHeadBoneSet();
    void buildBelowTheHeadBoneSet();
    void buildHeadOnlyBoneSet();
    void buildSpineOnlyBoneSet();
    void buildEmptyBoneSet();

    // no copies
    AnimOverlay(const AnimOverlay&) = delete;
    AnimOverlay& operator=(const AnimOverlay&) = delete;
};

#endif // hifi_AnimOverlay_h
