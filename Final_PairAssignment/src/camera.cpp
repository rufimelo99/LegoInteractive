#include "camera.h"
#include "math.h"

float speed = 2.0;
float mouseSpeed = 0.005;
#define PI 3.14159265

camera::camera(const vector3D& eye, const vector3D& up, float fovy, float aspect, float near, float far)
    : m_eye(eye), m_up(up), m_fovy(fovy), m_aspect(aspect), m_near(near), m_far(far), 
    m_targetDirection(vector3D(0, 0, -1)), m_mouseInFrame(false), m_mouseSpeed(mouseSpeed), m_mousePressed(false), 
    m_yaw(PI * 1.0f / 2.0f), m_pitch(0.0), m_usePerspective(true), m_left(-2), m_right(2), m_bottom(-2), m_top(2)
{
    updateTargetDirection();
   // m_rotationMatrix = matrix4D::rotationMatrix();
    matrix4D m = perspectiveMatrix();
}

matrix4D camera::lookAt(){
    matrix4D mView(matrix4D::createViewMatrix(m_eye, m_eye + m_targetDirection, m_up));
    m_s = vector3D(mView.values[0][0], mView.values[0][1], mView.values[0][2]);
    m_u = vector3D(mView.values[1][0], mView.values[1][1], mView.values[1][2]);
    m_v = vector3D(-mView.values[2][0], -mView.values[2][1], -mView.values[2][2]);
    return mView;
}

matrix4D camera::perspectiveMatrix(){
    matrix4D mPersp(matrix4D::createPerspectiveMatrix(m_fovy, m_aspect, m_near, m_far));
    setProjectionMatrix(mPersp);
    return mPersp;
}

matrix4D camera::orthographicMatrix(){
    matrix4D mOrtho(matrix4D::createOrthographicMatrix(m_left, m_right, m_bottom, m_top, m_near, m_far));
    setProjectionMatrix(mOrtho);
    return mOrtho;
}

matrix4D camera::projectionMatrix(){
    if(m_usePerspective){
        return perspectiveMatrix();
    }
    else{
        return orthographicMatrix();
    }
}   

void camera::ProcessKeyboard(const vector3D& direction, double elapsed_sec)
{
    float velocity = speed * elapsed_sec;
    if (direction == vector3D(0, 0, 1))
        m_eye += m_v * velocity;
    if (direction == vector3D(0, 0, -1))
        m_eye -= m_v * velocity;
    if (direction == vector3D(-1, 0, 0))
        m_eye -= m_s * velocity;
    if (direction == vector3D(1, 0, 0))
        m_eye += m_s * velocity;
    if (direction == vector3D(0, 1, 0))
        m_eye += m_u * velocity;
    if (direction == vector3D(0, -1, 0))
        m_eye -= m_u * velocity;
}

void camera::mouseClick(bool pressed){
    m_mousePressed = pressed;
}

void camera::mouseMovement(float x, float y)
{   
    if (!m_mouseInFrame)
    {
        m_prevX = x;
        m_prevY = y;
        m_mouseInFrame = true;
    }
    if(m_mousePressed){
        float deltaX = x - m_prevX;
        float deltaY = m_prevY - y;
        m_yaw += (deltaX) * m_mouseSpeed;
        m_pitch += (deltaY) * m_mouseSpeed;
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
        updateTargetDirection();
    }  
    m_prevX = x;
    m_prevY = y;
}

void camera::mouseScroll(float deltaY)
{
    m_fovy -= deltaY;
    if (m_fovy < 1.0f)
        m_fovy = 1.0f;
    if (m_fovy > 89.0f)
        m_fovy = 89.0f; 
}

void camera::changeProjection(){
    if(!m_usePerspective){
        m_eye = vector3D(-0.609405398, -0.603979826, 4);
        m_yaw = 8.0f;
        m_pitch = 3.0f;
        m_fovy = 30.0f;
    }  
    else{
        m_eye = vector3D(2.88432527, -0.271740347, -4.39744806);
        m_yaw = -0.986660301;
        m_pitch = -0.0589259043;
    }
    updateTargetDirection();
    m_usePerspective = !m_usePerspective;
}

void camera::updateTargetDirection(){
    vector3D newTarget;
    newTarget.x = cos(m_yaw) * cos(m_pitch);
    newTarget.y = sin(m_pitch);
    newTarget.z = sin(m_yaw) * cos(m_pitch);
    m_targetDirection = normalize(newTarget);
    m_viewMatrix = lookAt();
}

//Takes the normalized screenCoordinates and transforms them in worldCoords
vector3D camera::unProject(GLfloat winX, GLfloat winY, vector3D planePoint) {
    vector3D rayDir;
    vector3D rayOrigin;
    gluUnProjectAdapted(winX, winY, 1, &rayDir, &rayOrigin);
    //std::cout << "rayDir: " << rayDir << std::endl;
    //std::cout << "rayOrigin: "<<rayOrigin << std::endl;
    vector3D hitPoint = intersectPoint(rayDir, rayOrigin, planePoint);
    //vector3D hitPoint = intersectPoint(vector3D(0.0, -1.0, -1.0), vector3D(0.0, 0.0, 10.0), vector3D(0.0, 0.0, 1.0), vector3D(10.0, 10.0, 5.0));
    //std::cout << "The ray intersects the plane at " << hitPoint << std::endl;
    
    // pickingCheck(hitPoint);

    //ROUND 2 DECIMAL the worldCoords
    float posX = ((int)(hitPoint.getX() * 10 + .5) / 10.0);
    float posY = ((int)(hitPoint.getY() * 10 + .5) / 10.0);
    float posZ = ((int)(hitPoint.getZ() * 10 + .5) / 10.0);
    
    return vector3D(posX, posY, posZ);
}

void  camera::gluUnProjectAdapted(float winX, float winY, float winZ, vector3D* rayDir, vector3D* rayOrigin)
{
    matrix4D view = m_viewMatrix;
    matrix4D proj = m_projectionMatrix;
    matrix4D mul = proj * view;
    matrix4D invVP = matrix4D::inverse(mul);
    //std::cout << invVP << std::endl;
    vector4D screenPos = vector4D(winX, -winY, winZ, 1.0f);
    //std::cout << screenPos << std::endl;
    vector4D worldPos = invVP * screenPos; //actually it works by itself
    worldPos = vector4D::normalize(worldPos);
    rayDir->setX(worldPos.getX());
    rayDir->setY(worldPos.getY());
    rayDir->setZ(worldPos.getZ());
    //std::cout << rayDir << std::endl;
    vector4D centerScreenPos = vector4D(0, 0, 1, 1);
    vector4D centerWorldPos = invVP * centerScreenPos;
    //centerWorldPos = vector4D::normalize(centerWorldPos);
    rayOrigin->setX(-centerWorldPos.getX()); 
    rayOrigin->setY(-centerWorldPos.getY());
    rayOrigin->setZ(-centerWorldPos.getZ());

    return;
}
void camera::addToVerticalPlane() {
    if (verticalPlane >= 10) {
        std::cout << "The max height is 10." << std::endl;
    }
    else {
        verticalPlane += 1;
        std::cout << "You are now in height: " << verticalPlane << "." << std::endl;
    }
}
    
int camera::getVerticalPlane() {
    return verticalPlane;
}
void camera::subToVerticalPlane() {
    if (verticalPlane <= 0) {
        std::cout << "The min height is 0: the floor." << std::endl;
    }
    else {
        verticalPlane -= 1;
        std::cout << "You are now in height: " << verticalPlane << "." << std::endl;
    }
   
}

//plane Point is given by the translation of the ground (qualquer ponto no plano daria, este é o centro do plano especificamente)
vector3D camera::intersectPoint(vector3D rayDir, vector3D rayOrigin1, vector3D planePoint)
{
    vector3D planeNormal = vector3D(0, 1, 0); //atm only checking colisions with the ground

    vector3D rayOrigin = rayOrigin1 * 65; //we have to hardcode this value (the vector direction is normalized meaning we have to give the length)
    //lets try to give a plane Y = 1;
    planePoint.setY(verticalPlane);
    vector3D diff = rayOrigin - planePoint;
    double prod1 = dot(diff, planeNormal);
    double prod2 = dot(rayDir, planeNormal);
    double prod3 = prod1 / prod2;
    return rayOrigin - rayDir * prod3;
}

/*void camera::pickingCheck(vector3D hitPoint) {
    //TODO iterate over all legos in scene and for each do the IFS statements
    float posX = hitPoint.getX();
    float posY = hitPoint.getY();
    float posZ = hitPoint.getZ();
    //LegoSize will come with the iterated lego (we are assuming the rectangles here)
    float LegoSizeX = 2.0f;
    float LegoSizeY = 1.2f;
    float LegoSizeZ = 4.5f;
    
    //Obviously this is also given by the translate of the lego being iterated 
    float LegoPosX = 1.0f* 2.0f- 2.5f/0.15f;
    float LegoPosY = 0.0f;
    float LegoPosZ = 2.0f* 4.5f- 2.7f / 0.15f;
    //vector3D(-2.5, -0.0,-2.7));
   // 18, 7, 9);
    
    platform = true;
    if (posX >= LegoPosX - (LegoSizeX / 2) && posX <= LegoPosX + (LegoSizeX / 2 + 0.1f)) {
        if (posY >= LegoPosY - (LegoSizeY / 2) && posY <= LegoPosY + (LegoSizeY / 2 + 0.1f)) {
            if (posZ >= LegoPosZ - (LegoSizeZ / 2) && posZ <= LegoPosZ + (LegoSizeZ / 2 + 0.1f)) {
                LegoPicked = !LegoPicked;
                if (LegoPicked == true) std::cout << "RED LEGO PICKED: " <<  "true" << std::endl;
                else std::cout << "RED LEGO PICKED: " <<  "false" << std::endl;
                platform = false;
                return;
            }
        }
    }
}*/


void camera::setViewMatrix(matrix4D viewMatrix){
    m_viewMatrix = viewMatrix;

}
matrix4D camera::getViewMatrix(){
    return m_viewMatrix;
}
void camera::setRotationMatrix(matrix4D rotationMatrix) {
    m_rotationMatrix = rotationMatrix;
}
matrix4D camera::getRotationMatrix() {
    return m_rotationMatrix;
}
void camera::setProjectionMatrix(matrix4D projectionMatrix){
    m_projectionMatrix = projectionMatrix;
}
matrix4D camera::getProjectionMatrix(){
    return m_projectionMatrix;
}