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
#include "../include/students/Tree.hpp"
#include "../include/students/BonhommeDeNeige.hpp"
#include "../include/students/GroundRenderable.hpp"
#include "../include/students/ParticleExplosion.hpp"
#include "../include/students/SnowballRenderable.hpp"
#include "../include/students/Explosion.hpp"
void initialize_project_skyrim_2(Viewer& viewer) {

  /*******************************************************************************
   * INITIALISATION *
   ******************************************************************************/

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


  glm::mat4 parentTransformation(1.0), localTransformation(1.0);
  std::string filename;
  std::string filename2;
  //Define a directional light for the whole scene
  glm::vec3 d_direction = glm::normalize(glm::vec3(0.0,0.0,-1.0));
  glm::vec3 d_ambient(1.0,1.0,1.0), d_diffuse(1.0,1.0,0.8), d_specular(1.0,1.0,1.0);
  glm::vec3 ghostWhite(248.0/255, 248.0/255, 248.0/255);
  DirectionalLightPtr directionalLight = std::make_shared<DirectionalLight>(d_direction, ghostWhite, ghostWhite, ghostWhite);
  //Add a renderable to display the light and control it via mouse/key event
  glm::vec3 lightPosition(0,0.0,7.0);
  DirectionalLightRenderablePtr directionalLightRenderable = std::make_shared<DirectionalLightRenderable>(flatShader, directionalLight, lightPosition);
  localTransformation = glm::scale(glm::mat4(1.0), glm::vec3(0.5,0.5,0.5));
  directionalLightRenderable->setLocalTransform(localTransformation);
  viewer.setDirectionalLight(directionalLight);
  viewer.addRenderable(directionalLightRenderable);


  /*******************************************************************************
   * FIN INITIALISATION *
   ******************************************************************************/

  filename = "../textures/bark.jpg";
  filename2 = "../textures/needle.jpg";

  bool Ana = true;
  if(Ana){

    // Temporary variables to use to define transformation
    glm::mat4 rotationM(1.0), rot1(1.0), rot2(1.0);
    glm::mat4 scaleM(1.0);
    glm::mat4 translationM(1.0);

    glm::vec3 p1(-50.0, -50.0, 0.0);
    glm::vec3 p2(50.0, -50.0, 0.0);
    glm::vec3 p3(50.0, 50.0, 0.0);
    glm::vec3 p4(-50.0, 50.0, 0.0);
    PlanePtr plane = std::make_shared<Plane>(p1, p2, p3);
    system->addPlaneObstacle(plane);



    //Create a plane renderable to display the obstacle
    PlaneRenderablePtr planeRenderable = std::make_shared<QuadRenderable>(flatShader, p1,p2,p3,p4);
    HierarchicalRenderable::addChild( systemRenderable, planeRenderable );

    TreePtr tree = std::make_shared<Tree>(texShader, filename, filename2);
    tree->setParentTransform(glm::mat4(1.0));


    glm::vec3 px,pv;
    float pm, pr;
    px = glm::vec3(0,0,0.5);
    pv = glm::vec3(0,0,0);
    pr = 0.5;
    pm = 1.0;
    ParticlePtr particle = std::make_shared<Particle>(px, pv, pm, pr);
    particle->setSpecialAnimation(true);
    particle->setLink(tree);
    system->addParticle(particle);


    HierarchicalRenderable::addChild(tree, tree->tronc);
    //tree->setFalling(true);
    viewer.addRenderable(tree);
//    Explosion(system, systemRenderable, phongShader);

      /*  TexturedMeshRenderablePtr mesh =
            std::make_shared<TexturedMeshRenderable>(
                texShader, "../meshes/Maison.obj", "../textures/Cottage Texture.jpg");
        scaleM = glm::scale(glm::mat4(1.0), glm::vec3(0.2,0.2,0.2));
        mesh->setParentTransform(scaleM);
         mesh->setMaterial(Material::Maison());

        viewer.addRenderable(mesh);*/


         pv = glm::vec3(0.0, 0.0, 0.0);
       pm = 1.0, pr = 1.0;
        px = glm::vec3(10.0,0.0,0.0);
        ParticlePtr mobile = std::make_shared<Particle>( px, pv, pm, pr);
        system->addParticle( mobile );
        ParticleRenderablePtr mobileRenderable = std::make_shared<ParticleRenderable>(flatShader, mobile);
        HierarchicalRenderable::addChild(systemRenderable, mobileRenderable);
        //Initialize a force field that apply only to the mobile particle
        glm::vec3 nullForce(0.0, 0.0, 0.0);
        std::vector<ParticlePtr> vParticle;
        vParticle.push_back(mobile);
        ConstantForceFieldPtr force = std::make_shared<ConstantForceField>(vParticle, nullForce);
        system->addForceField(force);
        ControlledForceFieldRenderablePtr forceRenderable = std::make_shared<ControlledForceFieldRenderable>(flatShader, force);
        HierarchicalRenderable::addChild(systemRenderable, forceRenderable);

        //Add a damping force field to the mobile.
        DampingForceFieldPtr dampingForceField = std::make_shared<DampingForceField>(vParticle, 0.9);
        system->addForceField(dampingForceField);

        //Activate collision and set the restitution coefficient to 1.0
        system->setCollisionsDetection(true);
        system->setRestitution(1.0f);
  }


  bool Matthieu = true;
  if (Matthieu) {

    // Define a directional light for the whole scene
    glm::vec3 lightDirection = glm::normalize(glm::vec3(0.0, -1.0, -1.0));
    glm::vec3 ghostWhite(248.0/255, 248.0/255, 1.0);
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

    /* Création d'un bonhomme de neige */
    BonhommeDeNeigePtr bonhomme = std::make_shared<BonhommeDeNeige>(phongShader, texShader);
    bonhomme->setParentTransform(glm::mat4(1.0));
    HierarchicalRenderable::addChild(bonhomme, bonhomme->base);
    bonhomme->generateAnimation();
    viewer.addRenderable(bonhomme);
  }

bool Olivier = true;
  if (Olivier){
    MaterialPtr pearl = Material::Pearl();
 	  ShaderProgramPtr flatShader= std::make_shared<ShaderProgram>("../shaders/flatVertex.glsl",
 			  "../shaders/flatFragment.glsl");
 	  viewer.addShaderProgram(flatShader);

 	  ShaderProgramPtr phongShader= std::make_shared<ShaderProgram>("../shaders/phongVertex.glsl",
 			  "../shaders/phongFragment.glsl");
 	  viewer.addShaderProgram(phongShader);


 	  // add a 3D frame to the viewer
 	  viewer.addRenderable(std::make_shared<FrameRenderable>(flatShader));



 	  glm::vec3 lightDirection = glm::normalize(glm::vec3(0.0, -1.0, -1.0));
 	  glm::vec3 ghostWhite(248.0/255, 248.0/255, 248.0/255);
 	  DirectionalLightPtr directionalLight = std::make_shared<DirectionalLight>(lightDirection, ghostWhite, ghostWhite, ghostWhite);
 	  viewer.setDirectionalLight(directionalLight);

 	  glm::mat4 parentTransformation, localTransformation;
 	  GroundRenderablePtr groundR ;
 	  int nx = 6;
 	  int ny = 100;
 	  int n = 10; //nb de points par dalle
 	  float angle = -(float)3.14/12;

 	  //cf memo : plan invisible. il n'est même pas tracé. Normalement ça fonctionne
 	  glm::vec3 p1(0.0, 0.0, 0.0);
 	  glm::vec3 p2(nx, 0.0, 0.0);
 	  glm::vec3 p3(nx, ny*cos(angle), ny*sin(angle) );
 	  glm::vec3 p4(0, ny*cos(angle), ny*sin(angle));
 	  PlanePtr plane = std::make_shared<Plane>(p1, p2, p3);
 	  system->addPlaneObstacle(plane);

    glm::vec3 p5(0.0, 0.0, 0.0);
 	  glm::vec3 p6(0, 1, 0.0);
 	  glm::vec3 p7(0,0,1 );
 	  PlanePtr plane2 = std::make_shared<Plane>(p5, p6, p7);
 	  system->addPlaneObstacle(plane2);

    glm::vec3 p8(6, 0.0, 0.0);
 	  glm::vec3 p9(6, 1, 0.0);
 	  glm::vec3 p10( 6,1,1);
 	  PlanePtr plane3 = std::make_shared<Plane>(p8, p9, p10);
 	  system->addPlaneObstacle(plane3);

    system->setRestitution(0.0f);
 	  //Create a plane renderable to display the obstacle
 //PlaneRenderablePtr planeRenderable = std::make_shared<QuadRenderable>(flatShader, p1,p2,p3,p4, glm::vec4(0,0,1,1));
 	 // parentTransformation=glm::rotate(glm::mat4(1.0), -angle, glm::vec3(1,0,0));
 	 // planeRenderable->setParentTransform(parentTransformation);
 	 // HierarchicalRenderable::addChild( systemRenderable, planeRenderable );





 	  glm::vec3 px,pv;
 	  float pm, pr;
 	  px = glm::vec3(3, 1,0 );
 	  pv = glm::vec3(0.0, 1.0, 0.0);
 	  pr = 0.5;
 	  pm = 10;
 	  ParticlePtr particle = std::make_shared<Particle>(px, pv, pm, pr);
	  system->addParticle(particle);

 	  SnowballRenderablePtr sb = std::make_shared<SnowballRenderable>(phongShader, &viewer, particle);
 	  parentTransformation=glm::translate(glm::mat4(1.0), glm::vec3(3,1,0));
 	  sb->setParentTransform(parentTransformation);
 	  HierarchicalRenderable::addChild(systemRenderable, sb);

 	  ConstantForceFieldPtr gravityForceField = std::make_shared<ConstantForceField>(system->getParticles(), glm::vec3{0,0,-10} );
 	  system->addForceField(gravityForceField);

 //	  glm::vec3 nullForce(0.0, 0.0, 0.0);
 //	  ConstantForceFieldPtr force = std::make_shared<ConstantForceField>(system->getParticles(), nullForce);
 //	  system->addForceField(force);
 //
 //	  ControlledForceFieldRenderablePtr forceRenderable = std::make_shared<ControlledForceFieldRenderable>(flatShader, force);
 //	  ControlledForceFieldStatus(glm::vec3(0,1,0));
 //	  HierarchicalRenderable::addChild(systemRenderable, forceRenderable);


     viewer.getCamera().setViewMatrix(
 	      glm::lookAt(
 	        glm::vec3(5, -2, 2),
 	        glm::vec3(5, 0, 0),
 	        glm::vec3(0, 1, 0)));
 	    //viewer.getCamera().setPosition(glm::vec3(5,-2,2));


  }

  // Run the animation
  //viewer.setAnimationLoop(true, 1000);
  viewer.startAnimation();
}
