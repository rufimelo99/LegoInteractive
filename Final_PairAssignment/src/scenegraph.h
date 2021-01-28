#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__

#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "quaternion.h"
#include <vector>

using namespace Matrices;
using namespace Quaternions;

class sceneNodeCallback;
class sceneNode;
class sceneGraph;

class sceneNodeCallback {
public:
    virtual void preDraw(sceneNode* sNode) = 0;
    virtual void postDraw(sceneNode* sNode) = 0;
};

class standardCallback : public sceneNodeCallback {
    void preDraw(sceneNode* sNode);
    void postDraw(sceneNode* sNode);
};


class colorCallback : public sceneNodeCallback {
    vector4D mColor;
    vector3D colorA;
    vector3D colorD;
    vector3D colorS;

public:
    colorCallback(vector4D& color);
    void preDraw(sceneNode* sNode);
    void postDraw(sceneNode* sNode);
    vector4D getColor();
};

class sceneNode {
private:
    sceneNode* mParent = nullptr;
    sceneGraph* mSceneGraph = nullptr;
    std::vector<sceneNode*> mChildren;
    mesh* mMesh = nullptr;
    matrix4D mMatrix;
    vector3D mTranslation;
    vector3D mScale;
    quaternion mRotation;
    ShaderManager* mShaderManager = nullptr;
    sceneNodeCallback* mSceneNodeCallback = nullptr;

public:
    sceneNode(sceneNode* parent);
    ~sceneNode();
    sceneNode* createChild();
    void addChild(sceneNode* child);

    matrix4D getModelMatrix();
    matrix3D getNormalMatrix();         //TODO: --> transpose inverse of getModelMatrix
    std::vector <sceneNode*> getChildren();
    void setSceneGraph(sceneGraph* sceneGraph);
    void setMesh(mesh* mesh);
    void setMatrix(matrix4D matrix);
    void setTranslation(vector3D translation);
    void setScale(vector3D scale);
    void setRotation(quaternion rotation);
    vector3D getTranslation();
    vector3D getScale();
    quaternion getRotation();
    void setShader(ShaderManager* shaderManager);
    void setCallback(sceneNodeCallback* callback);
    sceneGraph* getSceneGraph();
    mesh* getMesh();
    matrix4D getMatrix();
    ShaderManager* getShader();
    sceneNodeCallback* getCallback();
    //TODO: Texture?
    void draw();

};

class sceneGraph {
private:
    camera* mCamera;
    sceneNode* mRoot;
public:
    sceneGraph();
    ~sceneGraph();
    camera* getCamera();
    void setCamera(camera* camera);
    sceneNode* getRoot();
    sceneNode* createChild();
    void draw();

};
#endif