#include "scenegraph.h"

/// standardCallback ///

void standardCallback::preDraw(sceneNode* sNode) {
    mesh* mesh = sNode->getMesh();
    ShaderManager* shader = sNode->getShader();
    glBindVertexArray(mesh->mVaoId);
    shader->use();
    shader->setUniformMatrix4fv("ModelMatrix", sNode->getModelMatrix());
    shader->setUniformMatrix4fv("ViewMatrix", sNode->getSceneGraph()->getCamera()->getViewMatrix());
    shader->setUniformMatrix4fv("ProjectionMatrix", sNode->getSceneGraph()->getCamera()->getProjectionMatrix());
}

void standardCallback::postDraw(sceneNode* sNode) {
    mesh* mesh = sNode->getMesh();
    ShaderManager* shader = sNode->getShader();
    shader->unuse();
    glBindVertexArray(0);
}


colorCallback::colorCallback(vector4D& color) {
    mColor = color;
    colorA = vector3D(color.x + 0.2, color.y+ 0.2 , color.z + 0.2); 
    colorD = vector3D(color.x + 0.3, color.y + 0.3, color.z + 0.3); //diffuse
    colorS = vector3D(0.5, 0.5, 0.5); //specular
}

void colorCallback::preDraw(sceneNode* sNode) {
    mesh* mesh = sNode->getMesh();
    ShaderManager* shader = sNode->getShader();
    glBindVertexArray(mesh->mVaoId);
    shader->use();
    shader->setUniformMatrix4fv("ModelMatrix", sNode->getModelMatrix());
    shader->setUniformMatrix4fv("ViewMatrix", sNode->getSceneGraph()->getCamera()->getViewMatrix());
    shader->setUniformMatrix4fv("ProjectionMatrix", sNode->getSceneGraph()->getCamera()->getProjectionMatrix());
  
    vector3D lightPos = vector3D(2.0f, 3.0f, -3.0f);
    shader->setUniformV3("light.position", lightPos);
    shader->setUniformV3("viewPos", vector3D(2.0f, 2.0f, 2.0f));
    shader->setUniformV3("light.ambient", vector3D(0.3f));
    shader->setUniformV3("light.diffuse", vector3D(0.6f));
    shader->setUniformV3("light.specular", vector3D(1.0f));

    shader->setUniformV3("material.ambient", colorA); //colorA
    shader->setUniformV3("material.diffuse", colorD); // colorD
    shader->setUniformV3("material.specular", colorS); // colorS
    shader->setUniformV1("material.shininess", 32.0f);
}

void colorCallback::postDraw(sceneNode* sNode) {
    mesh* mesh = sNode->getMesh();
    ShaderManager* shader = sNode->getShader();
    shader->unuse();
    glBindVertexArray(0);
}

vector4D colorCallback::getColor()
{
    return mColor;
}


/// sceneNode ///

matrix4D sceneNode::getModelMatrix() {
    matrix4D modelMatrix = matrix4D::translationMatrix(mTranslation) * quaternion::toMatrix(mRotation) * matrix4D::scaleMatrix(mScale);
    if (mParent) {
        modelMatrix = mParent->getModelMatrix() * modelMatrix;
    }
    return modelMatrix;
}

sceneNode::sceneNode(sceneNode* parent)
{
    if (parent) {
        mParent = parent;
    }
    setTranslation(vector3D(0.0, 0.0, 0.0));
    setRotation(quaternion(0.0f, vector4D(1, 0, 0, 1)));
    setScale(vector3D(1.0));
}

sceneNode::~sceneNode() {}

sceneNode* sceneNode::createChild() {
    sceneNode* child = new sceneNode(this);
    addChild(child);
    return child;
}

void sceneNode::addChild(sceneNode* child) {
    child->setSceneGraph(this->mSceneGraph);
    this->mChildren.push_back(child);

}

std::vector <sceneNode*> sceneNode::getChildren() {
    return this->mChildren;
}

void sceneNode::setSceneGraph(sceneGraph* sceneGraph) {
    this->mSceneGraph = sceneGraph;
}

void sceneNode::setMesh(mesh* mesh) {
    this->mMesh = mesh;
}

void sceneNode::setMatrix(matrix4D matrix) {
    this->mMatrix = matrix;
}
void sceneNode::setTranslation(vector3D translation) {
    mTranslation = translation;
}
void sceneNode::setScale(vector3D scale) {
    mScale = scale;
}

void sceneNode::setRotation(quaternion rotation) {
    mRotation = rotation;
}

vector3D sceneNode::getTranslation() {
    return mTranslation;
}

vector3D sceneNode::getScale() {
    return mScale;
}

quaternion sceneNode::getRotation() {
    return mRotation;
}

void sceneNode::setShader(ShaderManager* shaderManager) {
    this->mShaderManager = shaderManager;
}

void sceneNode::setCallback(sceneNodeCallback* callback) {
    this->mSceneNodeCallback = callback;
}

sceneGraph* sceneNode::getSceneGraph() {
    return this->mSceneGraph;
}

mesh* sceneNode::getMesh() {
    return this->mMesh;
}

matrix4D sceneNode::getMatrix() {
    return this->mMatrix;
}

ShaderManager* sceneNode::getShader() {
    return this->mShaderManager;
}

sceneNodeCallback* sceneNode::getCallback() {
    return this->mSceneNodeCallback;
}

void sceneNode::draw() {
    if (mMesh) {
        //mShaderManager->use();
        //mShaderManager->setUniformMatrix4fv("ModelMatrix", getModelMatrix());
        //mShaderManager->setUniformMatrix4fv("ViewMatrix", mSceneGraph->getCamera()->getViewMatrix());
        //mShaderManager->setUniformMatrix4fv("ProjectionMatrix", mSceneGraph->getCamera()->getProjectionMatrix());
        mSceneNodeCallback->preDraw(this);
        //mMesh->draw(*mShaderManager);
        mMesh->draw();
        mSceneNodeCallback->postDraw(this);
        //mShaderManager->unuse();
    }
    for (sceneNode* child : mChildren) {
        child->draw();
    }
}

/// SceneGraph ///

sceneGraph::sceneGraph() {
    mRoot = sceneGraph::createChild();
}

sceneGraph::~sceneGraph() {}

camera* sceneGraph::getCamera() {
    return mCamera;
}

void sceneGraph::setCamera(camera* camera) {
    mCamera = camera;
}

sceneNode* sceneGraph::getRoot() {
    return mRoot;
}

sceneNode* sceneGraph::createChild() {
    sceneNode* child = new sceneNode(nullptr);
    //child->setSceneGraph(this);
    return child;
}

void sceneGraph::draw() {
    mRoot->draw();
}