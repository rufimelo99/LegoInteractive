#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "vector3d.h"
#include "matrix4d.h"
#include <glfw/glfw3.h>
#include <map>

using namespace Vectors;
using namespace Matrices;

//struct matrix4D;
//struct vector3D{};

class camera{
    public:
    vector3D m_targetDirection;
    vector3D m_eye;
    vector3D m_center;
    vector3D m_up;
    vector3D m_v;
    vector3D m_u;
    vector3D m_s;
    float m_fovy;
    float m_aspect;
    float m_near;
    float m_far;
    bool m_mouseInFrame;
    float m_prevX;
    float m_prevY;
    float m_yaw;
    float m_pitch;
    float m_mouseSpeed;
    float m_mousePressed;
    float m_left;
    float m_right;
    float m_bottom;
    float m_top;
    bool m_usePerspective;
    int verticalPlane = 0;

    matrix4D m_projectionMatrix;
    matrix4D m_viewMatrix;
    matrix4D m_rotationMatrix;

    /*  we stoped using these variables here and use them in main now... why? including lego.h doesn't work
    //MousePicking
    bool LegoPicked = false;
    bool platform = false;
    */

    //camera();
    camera(const vector3D& eye, const vector3D& up, float fovy, float aspect, float near, float far);

    matrix4D lookAt();
    matrix4D orthographicMatrix();
    matrix4D perspectiveMatrix();
    matrix4D projectionMatrix();

    void ProcessKeyboard(const vector3D& direction, double elapsed_sec);

    void mouseMovement(float x, float y);
    void mouseInput(float x, float y);
    void mouseClick(bool pressed);
    void mouseScroll(float deltaY);
    void changeProjection();
    void updateTargetDirection();
    //routines that calculate the mouse Picking
    vector3D unProject(GLfloat winX, GLfloat winY, vector3D planePoint);
    void  gluUnProjectAdapted(float winX, float winY, float winZ, vector3D* rayDir, vector3D* rayOrigin);
    vector3D intersectPoint(vector3D rayDir, vector3D rayOrigin1, vector3D planePoint);
    void addToVerticalPlane();
    void subToVerticalPlane();
    int getVerticalPlane();

    void setViewMatrix(matrix4D viewMatrix);
    matrix4D getViewMatrix();
    void setRotationMatrix(matrix4D rotationMatrix);
    matrix4D getRotationMatrix();
    void setProjectionMatrix(matrix4D projectionMatrix);
    matrix4D getProjectionMatrix();
};


#endif