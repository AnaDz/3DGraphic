#include "./../../include/dynamics_rendering/ParticleRenderable.hpp"
#include "./../../include/gl_helper.hpp"
#include "./../../include/log.hpp"
#include "./../../include/Utils.hpp"
#include "../../teachers/Geometries.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <SFML/Graphics/Image.hpp>
#include <iostream>

ParticleRenderable::~ParticleRenderable()
{
    glcheck(glDeleteBuffers(1, &m_pBuffer));
    glcheck(glDeleteBuffers(1, &m_cBuffer));
    glcheck(glDeleteBuffers(1, &m_nBuffer));
}

ParticleRenderable::ParticleRenderable(ShaderProgramPtr shaderProgram,
                                        ParticlePtr particle,
                                        const MaterialPtr& material,
                                        const std::string& textureFilename) :
    HierarchicalRenderable(shaderProgram), Materiable(material), m_particle(particle),
    m_pBuffer(0), m_cBuffer(0), m_nBuffer(0), m_tBuffer(0), m_texId(0)
{
  // Création de la sphère
  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  const unsigned int strips = 20;
  const unsigned int slices = 20;
  teachers::getUnitSphere(positions, normals, strips, slices);
  m_positions.insert(m_positions.end(), positions.begin(), positions.end());
  m_normals.insert(m_normals.end(), normals.begin(), normals.end());

  //Create buffers
  glGenBuffers(1, &m_pBuffer); //vertices
  glGenBuffers(1, &m_cBuffer); //colors
  glGenBuffers(1, &m_nBuffer); //normals

  //Activate buffer and send data to the graphics card
  glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
  glcheck(glBufferData(GL_ARRAY_BUFFER, m_positions.size()*sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW));
  glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
  glcheck(glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(glm::vec4), m_colors.data(), GL_STATIC_DRAW));
  glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
  glcheck(glBufferData(GL_ARRAY_BUFFER, m_normals.size()*sizeof(glm::vec3), m_normals.data(), GL_STATIC_DRAW));

  // Pareil pour les textures, s'il y en a
  if (textureFilename != "") {
    // Buffer de textures avec le UV mapping
    for(int i = 0; i<slices; i++) {
      for (int j = 0; j<strips; j++) {
        double theta = i*(2.0*M_PI/(double)slices);
        double phi = j*(M_PI/(double)strips);
        double next_theta = (i+1)*(2.0*M_PI/(double)slices);
        double next_phi = (j+1)*(M_PI/(double)strips);
        double x;
        double y;
        double z;
        x = cos(theta)*sin(phi);
        y = sin(theta)*sin(phi);
        z = cos(phi);
        m_texCoords.push_back(glm::vec2(0.5+atan2(z,x)/(2*M_PI),0.5-asin(y)/M_PI));
        x = cos(next_theta)*sin(phi);
        y = sin(next_theta)*sin(phi);
        m_texCoords.push_back(glm::vec2(0.5+atan2(z,x)/(2*M_PI),0.5-asin(y)/M_PI));
        x = cos(next_theta)*sin(next_phi);
        y = sin(next_theta)*sin(next_phi);
        z = cos(next_phi);
        m_texCoords.push_back(glm::vec2(0.5+atan2(z,x)/(2*M_PI),0.5-asin(y)/M_PI));
        x = cos(theta)*sin(phi);
        y = sin(theta)*sin(phi);
        z = cos(phi);
        m_texCoords.push_back(glm::vec2(0.5+atan2(z,x)/(2*M_PI),0.5-asin(y)/M_PI));
        x = cos(next_theta)*sin(next_phi);
        y = sin(next_theta)*sin(next_phi);
        z = cos(next_phi);
        m_texCoords.push_back(glm::vec2(0.5+atan2(z,x)/(2*M_PI),0.5-asin(y)/M_PI));
        x = cos(theta)*sin(next_phi);
        y = sin(theta)*sin(next_phi);
        m_texCoords.push_back(glm::vec2(0.5+atan2(z,x)/(2*M_PI),0.5-asin(y)/M_PI));
      }
    }

    glGenBuffers(1, &m_tBuffer);
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_tBuffer));
    glcheck(glBufferData(GL_ARRAY_BUFFER, m_texCoords.size()*sizeof(glm::vec2), m_texCoords.data(), GL_STATIC_DRAW));

    //Handle the texture image itself
    sf::Image image;
    image.loadFromFile(textureFilename);
    image.flipVertically();
    glcheck(glGenTextures(1, &m_texId));
    glcheck(glBindTexture(GL_TEXTURE_2D, m_texId));
    glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glcheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    glcheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F,
        image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
        (const GLvoid*)image.getPixelsPtr()));
    glcheck(glBindTexture(GL_TEXTURE_2D, 0));
  }
}

void ParticleRenderable::do_draw()
{
  //Update the parent and local transform matrix to position the geometric data according to the particle's data.
  const float& pRadius = m_particle->getRadius();
  const glm::vec3& pPosition = m_particle->getPosition();
  glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(pRadius));
  glm::mat4 translate = glm::translate(glm::mat4(1.0), glm::vec3(pPosition));
  setParentTransform(translate*scale);

  //Location
  int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
  int colorLocation = m_shaderProgram->getAttributeLocation("vColor");
  int normalLocation = m_shaderProgram->getAttributeLocation("vNormal");
  int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
  int texSamplerLocation = m_shaderProgram->getUniformLocation("texSampler");
  int texCoordLocation = m_shaderProgram->getAttributeLocation("vTexCoord");
  int nitLocation = m_shaderProgram->getUniformLocation("NIT");

  //Send material to GPU as uniform
  Material::sendToGPU(m_shaderProgram, getMaterial());

  //Send data to GPU
  if(modelLocation != ShaderProgram::null_location)
  {
      glcheck(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getModelMatrix())));
  }

  //NIT matrix
  if (nitLocation != ShaderProgram::null_location) {
      glcheck(glUniformMatrix3fv(nitLocation, 1, GL_FALSE,
          glm::value_ptr(glm::transpose(glm::inverse(glm::mat3(getModelMatrix()))))));
  }

  if(positionLocation != ShaderProgram::null_location)
  {
      //Activate location
      glcheck(glEnableVertexAttribArray(positionLocation));
      //Bind buffer
      glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
      //Specify internal format
      glcheck(glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
  }

  if(colorLocation != ShaderProgram::null_location)
  {
      glcheck(glEnableVertexAttribArray(colorLocation));
      glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
      glcheck(glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0));
  }

  if(normalLocation != ShaderProgram::null_location)
  {
      glcheck(glEnableVertexAttribArray(normalLocation));
      glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
      glcheck(glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
  }

  // Texture and texture coordinates
  if (texCoordLocation != ShaderProgram::null_location) {
      // Bind texture on texture unit 0
      glcheck(glActiveTexture(GL_TEXTURE0));
      glcheck(glBindTexture(GL_TEXTURE_2D, m_texId));

      // Tells the sampler to use the texture unit 0
      glcheck(glUniform1i(texSamplerLocation, 0));

      // Send texture coordinates attributes
      glcheck(glEnableVertexAttribArray(texCoordLocation));
      glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_tBuffer));
      glcheck(glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)0));
  }


  //Draw triangles elements
  glcheck(glDrawArrays(GL_TRIANGLES,0, m_positions.size()));

  if(positionLocation != ShaderProgram::null_location)
  {
      glcheck(glDisableVertexAttribArray(positionLocation));
  }
  if(colorLocation != ShaderProgram::null_location)
  {
      glcheck(glDisableVertexAttribArray(colorLocation));
  }
  if(normalLocation != ShaderProgram::null_location)
  {
      glcheck(glDisableVertexAttribArray(normalLocation));
  }
  if (nitLocation != ShaderProgram::null_location) {
      glcheck(glDisableVertexAttribArray(nitLocation));
  }
  if (texCoordLocation != ShaderProgram::null_location) {
      glcheck(glDisableVertexAttribArray(texCoordLocation));
      glcheck(glBindTexture(GL_TEXTURE_2D, 0));   // unbind the texture!
  }
}

void ParticleRenderable::do_animate(float time)
{}
