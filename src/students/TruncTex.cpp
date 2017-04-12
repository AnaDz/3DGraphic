#include "../../include/students/TruncTex.hpp"
#include "../../include/gl_helper.hpp"
#include "../../include/log.hpp"
#include "../../include/Utils.hpp"
#include <math.h>

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <SFML/Graphics/Image.hpp>
#include <iostream>

TruncTex::TruncTex(ShaderProgramPtr shaderProgram,
                    const std::string& textureFilename,
                    const MaterialPtr& material) :
  HierarchicalRenderable(shaderProgram), Materiable(material),
  m_pBuffer(0), m_cBuffer(0), m_nBuffer(0), m_tBuffer(0), m_texId(0)
{
  int prec = 10;
  float pi = atan(1) * 4;
  float step = 2*pi/prec;
  for(int i = 0; i<prec; i++) {
    m_positions.push_back(glm::vec3(0,0,0));
    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0));

    m_texCoords.push_back(glm::vec2(0.0,1.0));
    m_texCoords.push_back(glm::vec2(1.0,0.0));
    m_texCoords.push_back(glm::vec2(1.0,1.0));

    m_normals.push_back(glm::vec3(0.0,0.0,-1.0));
    m_normals.push_back(glm::vec3(0.0,0.0,-1.0));
    m_normals.push_back(glm::vec3(0.0,0.0,-1.0));

    m_positions.push_back(glm::vec3(0,0,2));
    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,2));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,2));

    m_texCoords.push_back(glm::vec2(0.0,1.0));
    m_texCoords.push_back(glm::vec2(1.0,0.0));
    m_texCoords.push_back(glm::vec2(1.0,1.0));

    m_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_normals.push_back(glm::vec3(0.0,0.0,1.0));

    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,2));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,2));
    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0));

    m_normals.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0.0));
    m_normals.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0.0));
    m_normals.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0.0));

    m_texCoords.push_back(glm::vec2((double) i/prec,0.0));
    m_texCoords.push_back(glm::vec2((double) (i+1)/prec,1.0));
    m_texCoords.push_back(glm::vec2((double) i/prec,1.0));

    m_positions.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0));
    m_positions.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,2));

    m_normals.push_back(glm::vec3(cos(i*step)*0.5,sin(i*step)*0.5,0.0));
    m_normals.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0.0));
    m_normals.push_back(glm::vec3(cos((i+1)*step)*0.5,sin((i+1)*step)*0.5,0.0));

    m_texCoords.push_back(glm::vec2((double) i/prec,0.0));
    m_texCoords.push_back(glm::vec2((double) (i+1)/prec,0.0));
    m_texCoords.push_back(glm::vec2((double) (i+1)/prec,1.0));
  }

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

  glcheck(glGenBuffers(1, &m_tBuffer)); //textures
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

TruncTex::~TruncTex()
{
  glcheck(glDeleteBuffers(1, &m_pBuffer));
  glcheck(glDeleteBuffers(1, &m_cBuffer));
  glcheck(glDeleteBuffers(1, &m_nBuffer));
  glcheck(glDeleteBuffers(1, &m_tBuffer));
  glcheck(glDeleteBuffers(1, &m_texId));
}

void TruncTex::do_draw()
{
  //Location
  int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
  int colorLocation = m_shaderProgram->getAttributeLocation("vColor");
  int normalLocation = m_shaderProgram->getAttributeLocation("vNormal");
  int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
  int texSamplerLocation = m_shaderProgram->getUniformLocation("texSampler");
  int texCoordLocation = m_shaderProgram->getAttributeLocation("vTexCoord");
  int nitLocation = m_shaderProgram->getUniformLocation("NIT");

  //Send material as uniform to GPU
  Material::sendToGPU(m_shaderProgram, m_material);

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

void TruncTex::do_animate(float time)
{
}

void TruncTex::supprimer()
{
  glcheck(glDeleteBuffers(1, &m_pBuffer));
  glcheck(glDeleteBuffers(1, &m_cBuffer));
  glcheck(glDeleteBuffers(1, &m_nBuffer));
  glcheck(glDeleteBuffers(1, &m_tBuffer));
  std::vector<HierarchicalRenderablePtr> enfants = getChildren();
  for (int i = 0; i < enfants.size(); i++) {
    enfants[i]->supprimer();
  }
}
