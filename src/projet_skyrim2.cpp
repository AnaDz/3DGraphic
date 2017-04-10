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

  //Position the camera
  viewer.getCamera().setViewMatrix(
    glm::lookAt(
      glm::vec3(0, -8, 8 ),
      glm::vec3(0, 0, 0),
      glm::vec3( 0, 0, 1 ) ) );


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


  bool Matthieu = false;
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

/*  bool Olivier = false;
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

	  //possible de faire tout ça en une seule classe si besoin :) comme ça une texture "globale"
	  int n = 10;
	  for (int x=0; x<10; x++){
		  for (int y=0; y<10; y++){
			  groundR = std::make_shared<GroundRenderable>(flatShader,x,y,n);
			  //parentTransformation=glm::rotate(glm::translate(glm::mat4(1.0), glm::vec3(x,y,0)), (float)3.14/6, glm::vec3(1,0,0));
			  parentTransformation=glm::translate(glm::rotate(glm::mat4(1.0), -(float)3.14/12, glm::vec3(1,0,0)), glm::vec3(x,y,0));
			  groundR->setParentTransform(parentTransformation);
			  localTransformation = glm::mat4(1.0);
			  groundR->setLocalTransform(localTransformation);

			  viewer.addRenderable(groundR);
		  }
	  }
  }*/
  // Run the animation
//  viewer.setAnimationLoop(true, 10);
  viewer.startAnimation();
}
