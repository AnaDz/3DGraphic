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
#include "../include/students/BonhommeDeNeige.hpp"

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

  // Dynamic System (Solver, Time step, Restitution coefficient)
  DynamicSystemPtr system = std::make_shared<DynamicSystem>();
  EulerExplicitSolverPtr solver = std::make_shared<EulerExplicitSolver>();
  system->setSolver(solver);
  system->setDt(0.01);

  // Renderable associated to the dynamic system (computeSimulationStep() in animate() and key/mouse events)
  DynamicSystemRenderablePtr systemRenderable = std::make_shared<DynamicSystemRenderable>(system);
  viewer.addRenderable(systemRenderable);

  //Position the camera
  /*viewer.getCamera().setViewMatrix(
    glm::lookAt(
      glm::vec3(0, 0, 8),
      glm::vec3(0, 0, 0),
      glm::vec3(1, 0, 1)));*/

  /*std::shared_ptr<BasicCubicTreeRenderable> tree = std::make_shared<BasicCubicTreeRenderable>(flatShader);
  tree->setParentTransform(glm::mat4(1.0));

  std::shared_ptr<BasicCylindTreeRenderable> treeC = std::make_shared<BasicCylindTreeRenderable>(flatShader);
  treeC->setParentTransform(glm::translate(glm::mat4(1.0),glm::vec3(3,0,0)));


  HierarchicalRenderable::addChild(tree,treeC);
  viewer.addRenderable(tree);*/

  /* Création d'un bonhomme de neige */
  BonhommeDeNeigePtr bonhomme = std::make_shared<BonhommeDeNeige>(phongShader);
  viewer.addRenderable(bonhomme->base);
  bonhomme->setParentTransform(glm::mat4(1.0));

  // Define a directional light for the whole scene
  glm::vec3 lightDirection = glm::normalize(glm::vec3(0.0, -1.0, -1.0));
  glm::vec3 ghostWhite(248.0/255, 248.0/255, 248.0/255);
  DirectionalLightPtr directionalLight =
      std::make_shared<DirectionalLight>(lightDirection, ghostWhite, ghostWhite, ghostWhite);
  viewer.setDirectionalLight(directionalLight);
  // Add a renderable to display the light and control it via mouse/key event
  glm::vec3 lightPosition(0.0, 5.0, 8.0);
  DirectionalLightRenderablePtr directionalLightRenderable
      = std::make_shared<DirectionalLightRenderable>(flatShader, directionalLight, lightPosition);
  glm::mat4 localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5, 0.5, 0.5));
  directionalLightRenderable->setLocalTransform(localTransformation);
  viewer.addRenderable(directionalLightRenderable);

  // Run the animation
  /*viewer.setAnimationLoop(true, 6.0);
  viewer.startAnimation();*/
}
