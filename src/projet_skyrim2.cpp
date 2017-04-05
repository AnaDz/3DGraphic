#include <cmath>

#include "../include/ShaderProgram.hpp"
#include "../include/Viewer.hpp"

/* PRACTICAL_03 : RENDERABLES */
#include "../include/FrameRenderable.hpp"
#include "../teachers/CubeRenderable.hpp"
#include "../teachers/IndexedCubeRenderable.hpp"
#include "../teachers/CylinderRenderable.hpp"
#include "../teachers/MeshRenderable.hpp"

/* PRACTICAL_04 : LIGHTNING */
#include "../include/lighting/DirectionalLightRenderable.hpp"
#include "../include/lighting/PointLightRenderable.hpp"
#include "../include/lighting/SpotLightRenderable.hpp"
#include "../include/lighting/LightedCubeRenderable.hpp"
#include "../include/lighting/LightedCylinderRenderable.hpp"
#include "../include/lighting/LightedMeshRenderable.hpp"

/* PRACTICAL_05 : TEXTURING */
#include "../include/texturing/TexturedPlaneRenderable.hpp"
#include "../include/texturing/TexturedCubeRenderable.hpp"
#include "../include/texturing/MultiTexturedCubeRenderable.hpp"
#include "../include/texturing/MipMapCubeRenderable.hpp"
#include "../include/texturing/TexturedMeshRenderable.hpp"

/* PRACTICAL_06 : KEYFRAMES */
#include "../include/keyframes/KeyframedCylinderRenderable.hpp"
#include "../include/keyframes/GeometricTransformation.hpp"

/* PRACTICAL_07 : DYNAMICS */
#include "../include/dynamics/DynamicSystem.hpp"
#include "../include/dynamics/DampingForceField.hpp"
#include "../include/dynamics/ConstantForceField.hpp"
#include "../include/dynamics/SpringForceField.hpp"
#include "../include/dynamics/EulerExplicitSolver.hpp"

#include "../include/dynamics_rendering/DynamicSystemRenderable.hpp"
#include "../include/dynamics_rendering/ParticleRenderable.hpp"
#include "../include/dynamics_rendering/ParticleListRenderable.hpp"
#include "../include/dynamics_rendering/ConstantForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/SpringForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/SpringListRenderable.hpp"
#include "../include/dynamics_rendering/ControlledForceFieldRenderable.hpp"
#include "../include/dynamics_rendering/QuadRenderable.hpp"

/* INCLUDES SUPPLEMNTAIRES NON PRESENTS DANS LES PRACTICALS */
#include "../teachers/Geometries.hpp"

/* NOS PROPRES CLASSES A INCLUDE ICI */
#include "../include/students/BasicCubicTreeRenderable.hpp"
#include "../include/students/BasicCylindTreeRenderable.hpp"
#include "../include/students/GroundRenderable.hpp"
#include "../include/students/SnowballRenderable.hpp"
void initialize_project_skyrim_2(Viewer& viewer) {

  // Shaders
  ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>(
      "../shaders/flatVertex.glsl", "../shaders/flatFragment.glsl");
  ShaderProgramPtr phongShader = std::make_shared<ShaderProgram>(
      "../shaders/phongVertex.glsl", "../shaders/phongFragment.glsl");
  viewer.addShaderProgram(flatShader);
  viewer.addShaderProgram(phongShader);

  // Two texture shaders: simple and multi-texturing
  ShaderProgramPtr texShader = std::make_shared<ShaderProgram>(
    "../shaders/textureVertex.glsl", "../shaders/textureFragment.glsl");
  viewer.addShaderProgram(texShader);
  ShaderProgramPtr multiTexShader = std::make_shared<ShaderProgram>(
    "../shaders/multiTextureVertex.glsl", "../shaders/multiTextureFragment.glsl");
  viewer.addShaderProgram(multiTexShader);

  // Frame
  FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
  viewer.addRenderable(frame);

  //Position the camera
  viewer.getCamera().setViewMatrix(
    glm::lookAt(
      glm::vec3(0, -8, 8 ),
      glm::vec3(0, 0, 0),
      glm::vec3( 0, 0, 1 ) ) );

  //Initialize a dynamic system (Solver, Time step, Restitution coefficient)
  DynamicSystemPtr system = std::make_shared<DynamicSystem>();
  EulerExplicitSolverPtr solver = std::make_shared<EulerExplicitSolver>();
  system->setSolver(solver);
  system->setDt(0.01);

  //Create a renderable associated to the dynamic system
  //This renderable is responsible for calling DynamicSystem::computeSimulationStep()in the animate() function
  //It also handles some of the key/mouse events
  DynamicSystemRenderablePtr systemRenderable = std::make_shared<DynamicSystemRenderable>(system);
  viewer.addRenderable(systemRenderable);
  system->setCollisionsDetection(true);





  glm::mat4 parentTransformation(1.0), localTransformation(1.0);
  std::string filename;

  //Define a directional light for the whole scene
  glm::vec3 d_direction = glm::normalize(glm::vec3(0.0,0.0,-1.0));
  glm::vec3 d_ambient(1.0,1.0,1.0), d_diffuse(1.0,1.0,0.8), d_specular(1.0,1.0,1.0);
  DirectionalLightPtr directionalLight = std::make_shared<DirectionalLight>(d_direction, d_ambient, d_diffuse, d_specular);
  //Add a renderable to display the light and control it via mouse/key event
  glm::vec3 lightPosition(0.0,0.0,5.0);
  DirectionalLightRenderablePtr directionalLightRenderable = std::make_shared<DirectionalLightRenderable>(flatShader, directionalLight, lightPosition);
  localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5,0.5,0.5));
  directionalLightRenderable->setLocalTransform(localTransformation);
  viewer.setDirectionalLight(directionalLight);
  viewer.addRenderable(directionalLightRenderable);


  MaterialPtr pearl = Material::Pearl();

  filename = "../textures/bark.jpg";
  std::shared_ptr<BasicCubicTreeRenderable> tree = std::make_shared<BasicCubicTreeRenderable>(texShader,filename);
  tree->setParentTransform(glm::mat4(1.0));
  tree->setMaterial(pearl);

  std::shared_ptr<BasicCylindTreeRenderable> treeC = std::make_shared<BasicCylindTreeRenderable>(flatShader);
  treeC->setParentTransform(glm::translate(glm::mat4(1.0),glm::vec3(3,0,0)));


  HierarchicalRenderable::addChild(tree,treeC);
  viewer.addRenderable(tree);

  bool Olivier = true;
  if (Olivier){
	  ShaderProgramPtr flatShader= std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl",
			  "../shaders/flatFragment.glsl");
	  viewer.addShaderProgram(flatShader);

	  ShaderProgramPtr phongShader= std::make_shared<ShaderProgram>("../shaders/phongVertex.glsl",
			  "../shaders/phongFragment.glsl");
	  viewer.addShaderProgram(phongShader);


	  // add a 3D frame to the viewer
	  viewer.addRenderable(std::make_shared<FrameRenderable>(flatShader));


	  glm::mat4 parentTransformation, localTransformation;
	  GroundRenderablePtr groundR ;
	  int nx = 10;
	  int ny = 10;
	  int n = 10; //nb de points par dalle
	  float angle = (float)3.14/12;

	  //cf memo : plan invisible. il n'est même pas tracé. Normalement ça fonctionne
	  glm::vec3 p1(0.0, 0.0, 0.0);
	  glm::vec3 p2(nx, 0.0, 0.0);
	  glm::vec3 p3(nx, ny, 0 );
	  glm::vec3 p4(0, ny, 0);
	  PlanePtr plane = std::make_shared<Plane>(p1, p2, p3);
	  system->addPlaneObstacle(plane);

	  //Create a plane renderable to display the obstacle
//	  PlaneRenderablePtr planeRenderable = std::make_shared<QuadRenderable>(flatShader, p1,p2,p3,p4, glm::vec4(0,0,0,0));
//	  parentTransformation=glm::rotate(glm::mat4(1.0), -angle, glm::vec3(1,0,0));
//	  planeRenderable->setParentTransform(parentTransformation);
//	  HierarchicalRenderable::addChild( systemRenderable, planeRenderable );


	  //possible de faire tout ça en une seule classe si besoin :) comme ça une texture "globale"
	  //voire à faire dans le but d'en faire un plane renderable. Ou alors mettre un plan transparent au même niveau

	  for (int x=0; x<nx; x++){
		  for (int y=0; y<ny; y++){
			  groundR = std::make_shared<GroundRenderable>(flatShader,x,y,n, &viewer);
			  //parentTransformation=glm::rotate(glm::translate(glm::mat4(1.0), glm::vec3(x,y,0)), (float)3.14/6, glm::vec3(1,0,0));
			  parentTransformation=glm::translate(glm::rotate(glm::mat4(1.0), -angle, glm::vec3(1,0,0)), glm::vec3(x,y,0));
			  groundR->setParentTransform(parentTransformation);
			  localTransformation = glm::mat4(1.0);
			  groundR->setLocalTransform(localTransformation);
			  viewer.addRenderable(groundR);
		  }
	  }




	  glm::vec3 px,pv;
	  float pm, pr;
	  px = glm::vec3(0.0, 0.0, 0.0);
	  pv = glm::vec3(0.0, 1.0, 0.0);
	  pr = 0.5;
	  pm = 1.0;
	  ParticlePtr particle = std::make_shared<Particle>(px, pv, pm, pr);
	  system->addParticle(particle);

	  //std::shared_ptr<SnowballRenderable> sb = std::make_shared<SnowballRenderable>(phongShader,  pearl, &viewer, particle);

	  //  viewer.addRenderable(sb);

	  SnowballRenderablePtr sb = std::make_shared<SnowballRenderable>(phongShader, pearl, &viewer, particle);
	  parentTransformation=glm::translate(glm::mat4(1.0), glm::vec3(5,1,0));
	  sb->setParentTransform(parentTransformation);
	  (sb)->setMaterial(pearl);
	  HierarchicalRenderable::addChild(systemRenderable, sb);

	  ConstantForceFieldPtr gravityForceField = std::make_shared<ConstantForceField>(system->getParticles(), glm::vec3{0,0,-10} );
	  system->addForceField(gravityForceField);
	  //viewer.getCamera().setPosition(glm::vec3(5,-2,2));
  }
  // Run the animation

//  viewer.setAnimationLoop(true, 6.0);
  viewer.startAnimation();

}
