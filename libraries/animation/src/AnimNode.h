//
//  AnimNode.h
//
//  Copyright 2015 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_AnimNode_h
#define hifi_AnimNode_h

#include <string>
#include <vector>
#include <memory>
#include <cassert>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "AnimSkeleton.h"
#include "AnimVariant.h"

class QJsonObject;

// Base class for all elements in the animation blend tree.
// It provides the following categories of functions:
//
//   * id getter, id is a string name useful for debugging and searching.
//   * type getter, helpful for determining the derived type of this node.
//   * hierarchy accessors, for adding, removing and iterating over child AnimNodes
//   * skeleton accessors, the skeleton is from the model whose bones we are going to manipulate
//   * evaluate method, perform actual joint manipulations here and return result by reference.

class AnimNode {
public:
    friend class AnimDebugDraw;

    enum Type {
        ClipType = 0,
        BlendLinearType,
        OverlayType,
        NumTypes
    };
    typedef std::shared_ptr<AnimNode> Pointer;

    AnimNode(Type type, const std::string& id) : _type(type), _id(id) {}
    virtual ~AnimNode() {}

    const std::string& getID() const { return _id; }
    Type getType() const { return _type; }

    // hierarchy accessors
    void addChild(Pointer child) { _children.push_back(child); }
    void removeChild(Pointer child) {
        auto iter = std::find(_children.begin(), _children.end(), child);
        if (iter != _children.end()) {
            _children.erase(iter);
        }
    }
    Pointer getChild(int i) const {
        assert(i >= 0 && i < (int)_children.size());
        return _children[i];
    }
    int getChildCount() const { return (int)_children.size(); }

    // pair this AnimNode graph with a skeleton.
    void setSkeleton(const AnimSkeleton::Pointer skeleton) {
        setSkeletonInternal(skeleton);
        for (auto&& child : _children) {
            child->setSkeletonInternal(skeleton);
        }
    }

    AnimSkeleton::ConstPointer getSkeleton() const { return _skeleton; }

    virtual const AnimPoseVec& evaluate(const AnimVariantMap& animVars, float dt) = 0;
    virtual const AnimPoseVec& overlay(const AnimVariantMap& animVars, float dt, const AnimPoseVec& underPoses) {
        return evaluate(animVars, dt);
    }

protected:

    void setCurrentFrame(float frame) {
        setCurrentFrameInternal(frame);
        for (auto&& child : _children) {
            child->setCurrentFrameInternal(frame);
        }
    }

    virtual void setCurrentFrameInternal(float frame) {}
    virtual void setSkeletonInternal(AnimSkeleton::ConstPointer skeleton) {
        _skeleton = skeleton;
    }

    // for AnimDebugDraw rendering
    virtual const AnimPoseVec& getPosesInternal() const = 0;

    Type _type;
    std::string _id;
    std::vector<AnimNode::Pointer> _children;
    AnimSkeleton::ConstPointer _skeleton;

    // no copies
    AnimNode(const AnimNode&) = delete;
    AnimNode& operator=(const AnimNode&) = delete;
};

#endif // hifi_AnimNode_h
