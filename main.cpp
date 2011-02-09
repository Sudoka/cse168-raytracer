#include <math.h>
#include <string>

#include "Miro.h"
#include "Scene.h"
#include "Camera.h"
#include "Image.h"
#include "Console.h"

#include "PointLight.h"
#include "Sphere.h"
#include "Plane.h"
#include "TriangleMesh.h"
#include "Triangle.h"
#include "Lambert.h"
#include "Phong.h"
#include "MiroWindow.h"
#include "Texture.h"
#include <FreeImage.h>
using namespace std;

void
makeSpiralScene()
{
    g_camera = new Camera;
    g_scene = new Scene;
    g_image = new Image;

    g_image->resize(512, 512);

    // set up the camera
    g_camera->setBGColor(Vector3(1.0f, 1.0f, 1.0f));
    //g_camera->setEye(Vector3(-5, 2, 3));
    g_camera->setEye(Vector3(0, 0, -5));
    g_camera->setLookAt(Vector3(0, 0, 0));
    g_camera->setUp(Vector3(0, 1, 0));
    g_camera->setFOV(45);

    // create and place a point light source
    PointLight * light = new PointLight;
    light->setPosition(Vector3(-3, 15, -15));
    light->setColor(Vector3(1, 1, 1));
    light->setWattage(1000);
    g_scene->addLight(light);

    // create a spiral of spheres

    const int maxI = 150;
    const float a = 0.15f;
    for (int i = 1; i < maxI; i+=1)
    {
        float t = i/float(maxI);
        float theta = 4*PI*t;
        float r = a*theta;
        float x = r*cos(theta);
        float y = r*sin(theta);
        float z = 2*(2*PI*a - r);
        Material* mat = new Phong(Vector3(1.0f, t, i%2));
        Sphere * sphere = new Sphere;
        sphere->setCenter(Vector3(x,y,z));
        sphere->setRadius(r/10);
        sphere->setMaterial(mat);
        g_scene->addObject(sphere);
    }

    Plane * plane = new Plane();
    plane->setNormal(Vector3(0, 1, 0));
    plane->setOrigin(Vector3(0, -2, 0));
    plane->setMaterial(new Lambert(Vector3(1.0, 0, 0)));
    g_scene->addObject(plane);

    TriangleMesh *mesh = new TriangleMesh();
    mesh->createSingleTriangle();

    mesh->setV1(Vector3(0,0,0));
    mesh->setV2(Vector3(0,3,0));
    mesh->setV3(Vector3(5,5,0));
    mesh->setN1(Vector3(0,0,-1));
    mesh->setN2(Vector3(0.1,0.1,-1).normalize());
    mesh->setN3(Vector3(-0.1,-0.2,-1).normalize());

    Triangle * triangle = new Triangle();
    triangle->setMesh(mesh);
    triangle->setIndex(0);
    triangle->setMaterial(new Lambert(Vector3(0,1,0)));
    g_scene->addObject(triangle);

    // let objects do pre-calculations if needed
    g_scene->preCalc();
}

void
makeSphereScene()
{
    g_camera = new Camera;
    g_scene = new Scene;
    g_image = new Image;

    g_image->resize(512, 512);

    // set up the camera
    g_camera->setBGColor(Vector3(1.0f, 1.0f, 1.0f));
    g_camera->setEye(Vector3(-5, 1, 3));
    g_camera->setLookAt(Vector3(0, 1, 0));
    g_camera->setUp(Vector3(0, 1, 0));
    g_camera->setFOV(45);

    // create and place a point light source
    PointLight * light = new PointLight;
    light->setPosition(Vector3(-3, 15, 10));
    light->setColor(Vector3(1, 1, 1));
    light->setWattage(5000);
    g_scene->addLight(light);

    Material* mat = new Phong(Vector3(1.0f, 0.5f, 0.25f), Vector3(0.1, 0.1, 0.1), Vector3(1, 1, 1), 10);
	mat->SetRefraction(1.0f, 1.5);
    Sphere * sphere = new Sphere;
    sphere->setCenter(Vector3(0,0,0));
    sphere->setRadius(1.5);
    sphere->setMaterial(mat);
    g_scene->addObject(sphere);

    Material* mat2 = new Phong(Vector3(0.25f, 0.5f, 0.75f), Vector3(0.1, 0.1, 0.1), Vector3(1, 1, 1), 20);
	mat2->SetReflection(0.25f);
	Sphere * sphere2 = new Sphere;
    sphere2->setCenter(Vector3(5,0,-1));
    sphere2->setRadius(2);
    sphere2->setMaterial(mat2);
    g_scene->addObject(sphere2);

	Plane * plane = new Plane();
    plane->setNormal(Vector3(0, 1, 0));
    plane->setOrigin(Vector3(0, -3, 0));
    plane->setMaterial(new Lambert(Vector3(0.8, 0.8, 0.8), Vector3(0.1, 0.1, 0.1)));
    g_scene->addObject(plane);

    // let objects do pre-calculations if needed
    g_scene->preCalc();
}

void addModel(const char* filename, Material *mat, Scene* scene, Vector3 position)
{
	TriangleMesh * mesh = new TriangleMesh();
	mesh->load(filename);
    mesh->translate(position);
    for (int i = 0; i < mesh->numTris(); i++)
    {
		Triangle *tri = new Triangle();
		tri->setMesh(mesh);
		tri->setIndex(i);
		tri->setMaterial(mat);
		g_scene->addObject(tri);
    }
}

void makeModelsScene()
{
	LoadedTexture *autumnHDR = new LoadedTexture(string("gfx/autumnforrest.hdr"));
    g_camera = new Camera;
    g_scene = new Scene;
    g_image = new Image;

    //g_image->resize(1024, 1024);
    g_image->resize(512, 512);

    // set up the camera
    float viewAngleXZ = -PI;
    float pitch = -0.2;
    Vector3 dir(std::sin(viewAngleXZ),sin(pitch),std::cos(viewAngleXZ));
    Vector3 eye(0, 3, 0);
    cout << dir << endl;
    g_camera->setBGColor(Vector3(1.0f, 1.0f, 1.0f));
    //g_camera->setEye(Vector3(0, 1, -10));	//0,5,-10
    //g_camera->setLookAt(Vector3(0, 0, 0));	//0,2,0
    g_camera->setEye(eye);
    g_camera->setLookAt(eye+dir);
    //g_camera->setEye(Vector3(-5, 20, 7));
    //g_camera->setLookAt(Vector3(-4, 1, 7));
    g_camera->setUp(Vector3(0, 1, 0));
    g_camera->setFOV(60);

    // create and place a point light source
    PointLight * light = new PointLight;
 /*   light->setPosition(Vector3(3, 10, -3));
    //light->setPosition(Vector3(0, 10, 0));
    light->setColor(Vector3(1, 1, 1));
    light->setWattage(750);
    g_scene->addLight(light);

    light = new PointLight();
    light->setPosition(Vector3(-5, 10, 5));
    light->setColor(Vector3(1, 1, 1));
    light->setWattage(750);*/
    light->setPosition(Vector3(-2, 3, -4));
    light->setColor(Vector3(1, 1, 1));
    light->setWattage(50);
    g_scene->addLight(light);

    light = new PointLight();
    light->setPosition(Vector3(2, 3, -4));
    light->setColor(Vector3(1, 1, 1));
    light->setWattage(80);
    g_scene->addLight(light);
    
    light = new PointLight();
    light->setPosition(Vector3(2, 20, -4));
    light->setColor(Vector3(1, 1, 1));
    light->setWattage(1000);
    g_scene->addLight(light);
    
    light = new PointLight();
    light->setPosition(Vector3(0, 5, -7));
    light->setColor(Vector3(1, 1, 1));
    light->setWattage(50);
    g_scene->addLight(light);

    /*Material* bunnyMat = new Phong(Vector3(0.25f, 0.5f, 0.75f), Vector3(0.1, 0.1, 0.1), Vector3(1, 1, 1), 20, 0.3);
	bunnyMat->SetReflection(0.25f);
	addModel("models/bunny.obj", bunnyMat, g_scene);*/

    Sphere * sphere = new Sphere;
/*    sphere->setCenter(Vector3(0,2,0));
    sphere->setRadius(1.5);
    sphere->setMaterial(new Phong(Vector3(0.25f, 1.f, 0.5f), Vector3(0.1, 0.1, 0.1), Vector3(0.8f), Vector3(0.f), 10, 1.5));
    //sphere->setMaterial(new TexturedPhong(new StoneTexture(512, 5, 5), Vector3(0.1,0.1,0.1), Vector3(1,1,1), 1, 0, 0, 1.5));
    g_scene->addObject(sphere);

    Material* teapotMat = new Phong(Vector3(0.25f, 0.5f, 0.75f), Vector3(0.1, 0.1, 0.1), Vector3(1, 1, 1), 20);
	teapotMat->SetReflection(0.5f);
	teapotMat->SetRefraction(0.5f, 1.5);
	addModel("models/teapot.obj", teapotMat, g_scene);*/
    sphere->setCenter(Vector3(0,1,-7));
    sphere->setRadius(1.5);
    sphere->setMaterial(new Phong(Vector3(1.0f, 0.5f, 0.25f), Vector3(0.1, 0.1, 0.1), Vector3(.3f), Vector3(.7f), 10, 1.5));
    //sphere->setMaterial(new TexturedPhong(new StoneTexture(20), Vector3(0.1,0.1,0.1), Vector3(1,1,1), 5, 0, 0, 1.5));
    //g_scene->addObject(sphere);
    
    sphere = new Sphere;
    sphere->setCenter(Vector3(-2,1,-9));
    sphere->setRadius(1.5);
    //sphere->setMaterial(new Phong(Vector3(1.0f, 0.5f, 0.25f), Vector3(0.1, 0.1, 0.1), Vector3(1, 1, 1), 10, 0.2, 0.8, 1.5));
    sphere->setMaterial(new TexturedPhong(new StoneTexture(20), Vector3(0.1,0.1,0.1), Vector3(0.f), Vector3(0.f), 5, 1.5));
    g_scene->addObject(sphere);

    sphere = new Sphere;
    sphere->setCenter(Vector3(2,1,-9));
    sphere->setRadius(1.5);
    //sphere->setMaterial(new Phong(Vector3(1.0f, 0.5f, 0.25f), Vector3(0.1, 0.1, 0.1), Vector3(1, 1, 1), 10, 0.2, 0.8, 1.5));
    sphere->setMaterial(new TexturedPhong(new StoneTexture(20), Vector3(0.1,0.1,0.1), Vector3(0.f), Vector3(0.f), 5, 1.5));
    g_scene->addObject(sphere);

/*    Material* teapotMat = new Phong(Vector3(.5f, .5f, .5f), Vector3(0.1, 0.1, 0.1), Vector3(0.f), Vector3(0.f), 20);
	teapotMat->SetReflection(0.5f);
	teapotMat->SetRefraction(0.5f, 1.5f);
    addModel("models/teapot.obj", teapotMat, g_scene, Vector3(0,0,-5));*/

	g_scene->setEnvironment(autumnHDR);

	Plane * plane = new Plane();
    plane->setNormal(Vector3(0, 1, 0));
    plane->setOrigin(Vector3(0, -0.5, 0));
    //plane->setMaterial(new Lambert(Vector3(0.8, 0.8, 0.8), Vector3(0.1, 0.1, 0.1), 1));
    
    //plane->setMaterial(new TexturedPhong(new TestTexture3D(), Vector3(0,0,0)));
    //plane->setMaterial(new TexturedPhong(new CellularTexture2D(512, 5, 5), Vector3(0,0,0), Vector3(1), 1, 0));
    plane->setMaterial(new TexturedPhong(new StoneTexture(3), Vector3(0.1,0.1,0.1), Vector3(0.f), Vector3(0.f), 10));
    //plane->setMaterial(new TexturedPhong(new StoneTexture(3), Vector3(0.1,0.1,0.1), Vector3(1,1,1), 5, 0, 0, 1.3));

/*
	Plane * plane2 = new Plane();
    plane2->setNormal(Vector3(0, -1, 0));
    plane2->setOrigin(Vector3(0, 35, 0));
    plane2->setMaterial(new Lambert(Vector3(0.8, 0.8, 0.8), Vector3(0.1, 0.1, 0.1), 0.1f));*/
    g_scene->addObject(plane);
//    g_scene->addObject(plane2);

    // let objects do pre-calculations if needed
    g_scene->preCalc();
}

void
makeBunnyScene()
{
    g_camera = new Camera;
    g_scene = new Scene;
    g_image = new Image;

    g_image->resize(128, 128);
    
    // set up the camera
    g_camera->setBGColor(Vector3(0.0f, 0.0f, 0.2f));
    g_camera->setEye(Vector3(-2, 3, 5));
    g_camera->setLookAt(Vector3(-.5, 1, 0));
    g_camera->setUp(Vector3(0, 1, 0));
    g_camera->setFOV(45);

    // create and place a point light source
    PointLight * light = new PointLight;
    light->setPosition(Vector3(-3, 15, 3));
    light->setColor(Vector3(1, 1, 1));
    light->setWattage(500);
    g_scene->addLight(light);

    Material* mat = new Lambert(Vector3(1.0f));

    TriangleMesh * bunny = new TriangleMesh;
    bunny->load("bunny.obj");
    
    // create all the triangles in the bunny mesh and add to the scene
    for (int i = 0; i < bunny->numTris(); ++i)
    {
        Triangle* t = new Triangle;
        t->setIndex(i);
        t->setMesh(bunny);
        t->setMaterial(mat); 
        g_scene->addObject(t);
    }
    
    // create the floor triangle
    TriangleMesh * floor = new TriangleMesh;
    floor->createSingleTriangle();
    floor->setV1(Vector3(  0, 0,  10));
    floor->setV2(Vector3( 10, 0, -10));
    floor->setV3(Vector3(-10, 0, -10));
    floor->setN1(Vector3(0, 1, 0));
    floor->setN2(Vector3(0, 1, 0));
    floor->setN3(Vector3(0, 1, 0));
    
    Triangle* t = new Triangle;
    t->setIndex(0);
    t->setMesh(floor);
    t->setMaterial(mat); 
    g_scene->addObject(t);
    
    // let objects do pre-calculations if needed
    g_scene->preCalc();
}

int
main(int argc, char*argv[])
{
    //Initialize FreeImage
    FreeImage_Initialise();

    // create a scene
    //makeSpiralScene();
	//makeSphereScene();
	makeModelsScene();
    MiroWindow miro(&argc, argv);
    #ifndef NO_GFX
    miro.mainLoop();
    #else
    g_camera->setRenderer(Camera::RENDER_RAYTRACE);
    g_camera->click(g_scene, g_image);
    g_image->writePPM();
    #endif


	FreeImage_DeInitialise();

    return 0;
}

