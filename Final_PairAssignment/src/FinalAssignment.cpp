///////////////////////////////////////////////////////////////////////////////
//TODO grid coincida com o floor
//de preferencia que funcione para tras (so a grid translated)
//merge com o diogo
//pick&check com todos os legos da scene
//call red to drag nao funciona
//need to add grouping to file
//ver se possivel a cena dos vblocos em grupo nao checkarem parents collisions
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "mesh.h"
#include "shader.h"
#include "matrix4d.h"
#include "scenegraph.h"
#include "quaternion.h"
#include "grid.h"
#include "gridUnit.h"
#include "lego.h"
#include "camera.h"
#include <map>

using namespace Matrices;
using namespace Quaternions;

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2
bool TexcoordsLoaded, NormalsLoaded;

GLuint VaoId, ProgramId;
GLint ModelMatrix_UId, ViewMatrix_UId, ProjectionMatrix_UId;
std::map<std::string, sceneGraph*> sGraphMap;
std::map<std::string, ShaderManager*> shaderManagerMap;
std::map<std::string, Lego*> legoMap;

quaternion rotationQuaternion(0.0f, vector4D(1, 0, 0, 1));
quaternion quaternionStart(0.0f, vector4D(1, 0, 0, 1));
bool mouseInFrame = false;
float prevMouseX = 0.0f;
float prevMouseY = 0.0f;
bool leftMousePressed = false;
bool rightMousePressed = false;
float animationDuration = 2.0;
float elapsedAnimation = 0.0;
bool ongoingAnimation = false;
bool animateReverse = true;
vector3D translationStart1(0.0, -3.75, 0.0);
vector3D translationStart2(0.0, -1.25, 0.0);
vector3D translationStart3(-2.5, 2.5, 0.0);
vector3D translationStart4(2.5, 2.5, 0.0);
float moveSpeed = 2.0;


// Grid
Grid legoGrid = Grid(vector3D::vector3D(2/2, 1.2, 4.5/4), 36, 10, 36);
Lego* legoRed, legoYellow, legoBlue;
float translationX = 2.5f;
float translationZ = 2.7f;
float scaleFactor = 0.15f;

//MousePicking
bool LegoPicked = false; //do we have a lego picked?
std::string CurrentLego = ""; //the name of the lego being picked.
std::string LastLegoPicked = ""; //the name of the last lego picked (for Grouping purposes).

//GroupingOperations
bool isWaitingToGroup = false; //tells if we are currently on a grouping operation.

int window_size_x = 640;
int window_size_y = 480;
vector3D currentPoint;
vector3D mouse2D;
vector3D hitPoint;	//unprojected clicked
GLdouble posX = 0, posY = 0.5, posZ = 0; //unproject clicked

///////////////////////////////////////////////// ERROR HANDLING (All versions)

static const std::string errorString(GLenum error)
{
	switch (error) {
	case GL_NO_ERROR:
		return "No error has been recorded.";
	case GL_INVALID_ENUM:
		return "An unacceptable value is specified for an enumerated argument.";
	case GL_INVALID_VALUE:
		return "A numeric argument is out of range.";
	case GL_INVALID_OPERATION:
		return "The specified operation is not allowed in the current state.";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "The framebuffer object is not complete.";
	case GL_OUT_OF_MEMORY:
		return "There is not enough memory left to execute the command.";
	case GL_STACK_UNDERFLOW:
		return "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
	case GL_STACK_OVERFLOW:
		return "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
	default: exit(EXIT_FAILURE);
	}
}

static bool isOpenGLError()
{
	bool isError = false;
	GLenum errCode;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		std::cerr << "OpenGL ERROR [" << errorString(errCode) << "]." << std::endl;
	}
	return isError;
}

static void checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

/////////////////////////////////////////////////////////////////////// SCENE
void saveProject(std::string filename) {
	//TODO clean up the file first
	std::ofstream myfile;
	myfile.open(filename);
	for (auto const& x : legoMap)
	{
		myfile << x.first  // string (key)// string's value
			<< ';'
			<< x.second->getPosition()
			<< ';'
			<< x.second->getMeshPath()
			<< ';'
			<< x.second->getColor()
			<< std::endl;
	}
	myfile.close();

}
vector3D stringToPosition(std::string positionString) {
	positionString = positionString.substr(1, positionString.size() - 2);
	std::vector<int> vect;
	std::stringstream ss(positionString);

	for (int i; ss >> i;) {
		vect.push_back(i);
		if (ss.peek() == ',')
			ss.ignore();
	}
	float posx = (float)vect[0];
	float posy = (float)vect[1];
	float posz = (float)vect[2];

	vector3D position = vector3D(posx, posy, posz);

	return position;
}

vector4D stringToColor(std::string colorString) {

	colorString = colorString.substr(1, colorString.size() - 2);
	std::vector<std::string> stringV;
	std::stringstream  ss(colorString);
	std::string str;
	while (getline(ss, str, ',')) {
		stringV.push_back(str);
	}
	float pos1 = (float)std::atof(stringV[0].c_str());
	float pos2 = (float)std::atof(stringV[1].c_str());
	float pos3 = (float)std::atof(stringV[2].c_str());
	float pos4 = (float)std::atof(stringV[3].c_str());

	vector4D color = vector4D(pos1, pos2, pos3, pos4);

	return color;
}


void loadFilename(std::string filename, ShaderManager* shaderManager, sceneNode* legoContainer) {
	//for now i am not using the meshPath to construct the legos, but ill need it after to construct different legos
	std::ifstream MyReadFile(filename);
	std::string line;

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, line)) {
		std::vector<std::string> v;
		std::stringstream ss(line);
		while (ss.good()) {
			std::string substr;
			getline(ss, substr, ';');
			v.push_back(substr);
		}

		std::string legoName = v[0];
		std::string legoCoord = v[1];
		vector3D pos = stringToPosition(legoCoord);
		std::string legoMesh = v[2];
		std::string legoColor = v[3];
		vector4D color = stringToColor(legoColor);
		Lego* legoooo = new Lego(legoName, &legoGrid, pos, legoMesh, color, shaderManager, legoContainer);
		legoMap[legoName] = legoooo;


	}
	// Close the file
	MyReadFile.close();
}

void calculateRotation(float x, float y) {
	mouse2D = vector3D(x, y, 0);
	sceneGraph* sGraph = sGraphMap["scenegraph"];
	matrix4D rotationMatrix;
	if (!mouseInFrame)
	{
		prevMouseX = x;
		prevMouseY = y;
		mouseInFrame = true;
	}
	if (rightMousePressed) {
		float deltaX = x - prevMouseX;
		float deltaY = prevMouseY - y;
		quaternion yQuat(-deltaX, vector4D(0, 1, 0, 1));
		quaternion xQuat(deltaY, vector4D(1, 0, 0, 1));
		rotationQuaternion = xQuat * yQuat;
		rotationMatrix = quaternion::toMatrix(rotationQuaternion);
	}
	prevMouseX = x;
	prevMouseY = y;
	sGraph->getCamera()->setViewMatrix(rotationMatrix * sGraph->getCamera()->getViewMatrix());
}

void mouseClick(std::string button, bool pressed) {
	if (button == "left") {
		leftMousePressed = pressed;
	}
	else if (button == "right") {
		rightMousePressed = pressed;
	}
}

vector3D gridToWorldCoords(vector3D gridCoords) {
	vector3D translation(-translationX / scaleFactor, 0, -translationZ / scaleFactor);
	gridCoords.setX((int)gridCoords.getX() * legoGrid.sizeUnit.getX());
	gridCoords.setY((int)gridCoords.getY() * legoGrid.sizeUnit.getY());
	gridCoords.setZ((int)gridCoords.getZ() * legoGrid.sizeUnit.getZ());
	vector3D transformation = (gridCoords + translation);
	//ROUND the worldCoords
	float posX = (int)std::round(transformation.getX());
	float posY = (int)std::round(transformation.getY());
	float posZ = (int)std::round(transformation.getZ());
	return vector3D(posX, posY, posZ);
}


vector3D worldToGridCoords(vector3D worldCoords) {
	vector3D translation(translationX / scaleFactor, 0, translationZ / scaleFactor);
	vector3D transformation = (worldCoords + translation);
	transformation.setX((int)transformation.getX() / legoGrid.sizeUnit.getX());
	transformation.setY((int)transformation.getY() / legoGrid.sizeUnit.getY());
	transformation.setZ((int)transformation.getZ() / legoGrid.sizeUnit.getZ());
	//ROUND the grid coords
	float posX = (int)std::round(transformation.getX());
	float posY = (int)std::round(transformation.getY());
	float posZ = (int)std::round(transformation.getZ());

	return vector3D(posX,posY,posZ);
}

void pickingCheck(vector3D hitPoint) {
	float posX = hitPoint.getX();
	float posY = hitPoint.getY();
	float posZ = hitPoint.getZ();

	//LegoSize declaration
	float LegoSizeX;
	float LegoSizeY;
	float LegoSizeZ;

	//Obviously this is also given by the translate of the lego being iterated
	float LegoPosX;
	float LegoPosY;
	float LegoPosZ;
	
	vector3D WorldLegoPosition; //legos are in grid coordinates. this vector stores the lego position in world coords
	for (auto const& x : legoMap)
	{
		//(2 / 2, 1.2, 4.5 / 4)
		float LegoSizeX = x.second->getGridSize().getX() * 1;
		float LegoSizeY = x.second->getGridSize().getY() * 1.2;
		float LegoSizeZ = x.second->getGridSize().getZ() * 4.5/4;

		//Grid  to --> World 
		WorldLegoPosition = gridToWorldCoords(x.second->getPosition());
		LegoPosX = WorldLegoPosition.getX();
		LegoPosY = WorldLegoPosition.getY();
		LegoPosZ = WorldLegoPosition.getZ();

		if (posX >= LegoPosX - (LegoSizeX / 2) && posX <= LegoPosX + (LegoSizeX / 2 + 0.1f)) {
			if (posY >= LegoPosY - (LegoSizeY / 2) && posY <= LegoPosY + (LegoSizeY / 2 + 0.1f)) {
				if (posZ >= LegoPosZ - (LegoSizeZ / 2) && posZ <= LegoPosZ + (LegoSizeZ / 2 + 0.1f)) {
					if (isWaitingToGroup) {
						if (x.first == LastLegoPicked) //selected the same lego (cancelamos a transação)
						{
							std::cout << "Grouping Operation cancelled." << std::endl;
						}
						else { // selected another lego to group
							legoMap[LastLegoPicked]->addInGroup(legoMap[x.first]);
							std::cout << LastLegoPicked << " grouped with " << x.first << "!" << std::endl;
						}
						isWaitingToGroup = false;
					}
					if(LastLegoPicked != "")
						legoMap[LastLegoPicked]->highLight();
					CurrentLego = x.first;
					legoMap[CurrentLego]->highLight();
					LastLegoPicked = x.first;
					LegoPicked = true;
					std::cout << "Novo Lego Selecionado: " << CurrentLego << std::endl;
					return;
				}
			}
		}
	}
}

void legoDeletePointers() {
	for (auto const& x : legoMap)
	{
		x.second->deleteGroupPointer();
	}
}

void legoGroupingOperation(bool ungroup) {
	// The next CurrentLego will be grouped with lastLegoPicked
	isWaitingToGroup = true;
	if (ungroup) {
		legoMap[LastLegoPicked]->removeInGroup();
	}
	else {
		std::cout << "Choose a lego to group with " << LastLegoPicked << std::endl;
	}

}
void drawScene(float elapsed_sec)
{
	if (!leftMousePressed) {
		LegoPicked = false;
		CurrentLego = "";
	}
	sceneGraph* sGraph = sGraphMap["scenegraph"];
	if (leftMousePressed) {
		GLfloat winX, winY;               // Holds Our X, Y and Z Normalized Coordinates
		winX = (float)mouse2D.x / (window_size_x * 0.5f) - 1.0f; // Holds The Mouse X Coordinate
		winY = (float)mouse2D.y / (window_size_y * 0.5f) - 1.0f; // Holds The Mouse Y Coordinate

		//Unproject -> mousePicking
		hitPoint = sGraph->getCamera()->unProject(winX, winY, sGraph->getRoot()->getTranslation());
		//we check if our ray intersects any of the legos in the scene (currently only checking Y = 0 legos)
		if (!LegoPicked) {
			pickingCheck(hitPoint);
		}
	}
	
	if (LegoPicked && CurrentLego != "") {
		legoMap[CurrentLego]->moove(worldToGridCoords(hitPoint));
	}
	
	sGraph->getCamera()->setProjectionMatrix(sGraph->getCamera()->getProjectionMatrix());
	sGraph->getCamera()->setViewMatrix(matrix4D::translationMatrix(0.0, 0.0, -5.0) * sGraph->getCamera()->getViewMatrix());
	sGraph->draw();
	sGraph->getCamera()->setViewMatrix(matrix4D::translationMatrix(0.0, 0.0, 5.0) * sGraph->getCamera()->getViewMatrix());
}

///////////////////////////////////////////////////////////////////// CALLBACKS

void window_close_callback(GLFWwindow* win)
{
}

void window_size_callback(GLFWwindow* win, int winx, int winy)
{
	glViewport(0, 0, winx, winy);
	// Change projection matrices to maintain aspect ratio
}

///////////////////////////////////////////////////////////////////////// SETUP

void glfw_error_callback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void glfw_mouse_callback(GLFWwindow* window, double x, double y)
{
	calculateRotation(x, y);
}

void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		mouseClick("left", true);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		mouseClick("left", false);
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		mouseClick("right", true);
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		mouseClick("right", false);
	}
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		sGraphMap["scenegraph"]->getCamera()->subToVerticalPlane();

		if (CurrentLego != "" && sGraphMap["scenegraph"]->getCamera()->getVerticalPlane() >= 0) {
			legoMap[CurrentLego]->moove(legoMap[CurrentLego]->getPosition() + vector3D::vector3D(0, -1, 0));
		}
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		sGraphMap["scenegraph"]->getCamera()->addToVerticalPlane();

		if (CurrentLego != "" && sGraphMap["scenegraph"]->getCamera()->getVerticalPlane() <= 10) {
			legoMap[CurrentLego]->moove(legoMap[CurrentLego]->getPosition() + vector3D::vector3D(0, 1, 0));
		}
	}
	if (key == GLFW_KEY_P && action == GLFW_RELEASE)
	{
		std::cout << "Saved Scene on nono.txt" << std::endl;
		saveProject("nono.txt");
	}
	if (key == GLFW_KEY_G && action == GLFW_RELEASE)
	{
		legoGroupingOperation(0); //started a grouping operation
	}
	if (key == GLFW_KEY_U && action == GLFW_RELEASE)
	{
		legoGroupingOperation(1); //started a UNgrouping operation
	}
}

GLFWwindow* setupWindow(int winx, int winy, const char* title,
	int is_fullscreen, int is_vsync)
{
	GLFWmonitor* monitor = is_fullscreen ? glfwGetPrimaryMonitor() : 0;
	GLFWwindow* win = glfwCreateWindow(winx, winy, title, monitor, 0);
	if (!win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(is_vsync);
	return win;
}

void setupCallbacks(GLFWwindow* win)
{
	glfwSetWindowCloseCallback(win, window_close_callback);
	glfwSetWindowSizeCallback(win, window_size_callback);
	glfwSetCursorPosCallback(win, glfw_mouse_callback);
	glfwSetMouseButtonCallback(win, glfw_mouse_button_callback);
	glfwSetKeyCallback(win, glfw_key_callback);
}

GLFWwindow* setupGLFW(int gl_major, int gl_minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* win = setupWindow(winx, winy, title, is_fullscreen, is_vsync);
	setupCallbacks(win);

#if _DEBUG
	std::cout << "GLFW " << glfwGetVersionString() << std::endl;
#endif
	return win;
}

void setupGLEW()
{
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
}

void checkOpenGLInfo()
{
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}

void setupOpenGL(int winx, int winy)
{
#if _DEBUG
	checkOpenGLInfo();
#endif
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glViewport(0, 0, winx, winy);
}



GLFWwindow* setup(int major, int minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	GLFWwindow* win =
		setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
	setupGLEW();
	int width, height;
	glfwGetFramebufferSize(win, &width, &height);	//opengl needs pixel coordinates
	setupOpenGL(winx, winy);

	std::string meshPath = "src\\legoBrickOK.obj";
	std::string floorPath = "src\\optimazedFloor.obj";
	mesh* testMesh = new mesh(meshPath);
	mesh* floorMesh = new mesh(floorPath);
	std::string vs = "src\\test_vs.vert";
	std::string fs = "src\\test_fs.frag";
	ShaderManager* shaderManager = new ShaderManager();
	shaderManagerMap["shader"] = shaderManager;
	shaderManager->compileShaders(vs, fs);
	shaderManager->addAtribute("inPosition", VERTICES);
	if (testMesh->mTexCoordsLoaded)
		shaderManager->addAtribute("inTexcoord", TEXCOORDS);
	if (testMesh->mNormalsLoaded)
		shaderManager->addAtribute("inNormal", NORMALS);
	shaderManager->linkShaders();

	checkOpenGLError("Shaders");

	sceneGraph* sGraph = new sceneGraph();
	sGraphMap["scenegraph"] = sGraph;
	camera* cam = new camera(vector3D(0, 0, 0), vector3D(0, 1, 0), 30.0, 640.0f / 480.0f, 0.02, 20.0);
	sGraph->setCamera(cam);
	standardCallback* cb = new standardCallback();
	vector4D floorColor(0, 0.7, 0, 1);

	sceneNode* root = sGraph->getRoot();
	root->setSceneGraph(sGraph);
	root->setCallback(cb);
	root->setShader(shaderManager);
	root->setMesh(nullptr);
	root->setMatrix(matrix4D::scaleMatrix(0.01) * matrix4D::rotationMatrix(vector3D(0, 1, 0), 45.0));
	root->setScale(vector3D(0.5));
	root->setRotation(quaternion(0.0, vector4D(0, 1, 0, 1)));
	root->setTranslation(vector3D(0.0));

	sceneNode* floor = root->createChild();
	floor->setMesh(floorMesh);
	floor->setCallback(new colorCallback(floorColor));
	floor->setShader(shaderManager);
	floor->setScale(vector3D(0.15, 0.05, 0.15)); // for the preety but heavy floor
	//floor->setScale(vector3D(6, 0.05, 6)); //for the light floor
	floor->setTranslation(vector3D(0.0, -0.05, 0.0));
	sceneNode* legoContainer = root->createChild();
	legoContainer->setScale(vector3D(scaleFactor));
	legoContainer->setTranslation(vector3D(-translationX, 0.0,-translationZ));


	//Load From File
	std::cout << "Saved Loaded Scene from nono.txt" << std::endl;
	loadFilename("nono.txt", shaderManager, legoContainer);

	// We grouped some Legos (the brown bench)
	legoMap["legob1"]->addInGroup(legoMap["legob3"]);
	
	return win;
}

////////////////////////////////////////////////////////////////////////// RUN

void processKeyboardInput(GLFWwindow* window, double elapsed_sec)
{
	float velocity = moveSpeed * elapsed_sec;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	sceneGraph* sGraph = sGraphMap["scenegraph"];
	sceneNode* root = sGraph->getRoot();

}

void display(GLFWwindow* win, double elapsed_sec)
{
	drawScene(elapsed_sec);
}

void run(GLFWwindow* win)
{
	double last_time = glfwGetTime();
	while (!glfwWindowShouldClose(win))
	{
		double time = glfwGetTime();
		double elapsed_time = time - last_time;
		last_time = time;
		processKeyboardInput(win, elapsed_time);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display(win, elapsed_time); 
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	//destruct the LegoPointers to groups.
	legoDeletePointers();
	glfwDestroyWindow(win);
	glfwTerminate();
}

////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[])
{
	int gl_major = 4, gl_minor = 1;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		window_size_x, window_size_y, "1-LegoYellow 2-DarkLego Arrows->Movement Mouse to click&drag red", is_fullscreen, is_vsync);
	run(win);
	exit(EXIT_SUCCESS);
}


///////////////////////////////////////////////////////////////////////////////