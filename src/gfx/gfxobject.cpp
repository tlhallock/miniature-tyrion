#include "gfxobject.h"

#include "model/unit.h"

#include <iostream>
#include "cvconfig.h"
#include <opencv2/highgui.hpp>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "opencv2/core/core.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "main/settings.h"

#include <vector>


#if 0
void load_obj(const char* filename, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements) {
  ifstream in(filename, ios::in);
  if (!in) { cerr << "Cannot open " << filename << endl; exit(1); }

  string line;
  while (getline(in, line)) {
    if (line.substr(0,2) == "v ") {
      istringstream s(line.substr(2));
      glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
      vertices.push_back(v);
    }  else if (line.substr(0,2) == "f ") {
      istringstream s(line.substr(2));
      GLushort a,b,c;
      s >> a; s >> b; s >> c;
      a--; b--; c--;
      elements.push_back(a); elements.push_back(b); elements.push_back(c);
    }
    else if (line[0] == '#') { /* ignoring this line */ }
    else { /* ignoring this line */ }
  }

  normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
  for (int i = 0; i < elements.size(); i+=3) {
    GLushort ia = elements[i];
    GLushort ib = elements[i+1];
    GLushort ic = elements[i+2];
    glm::vec3 normal = glm::normalize(glm::cross(
      glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
      glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
    normals[ia] = normals[ib] = normals[ic] = normal;
  }
}
#endif


namespace aoe
{

GfxObject::GfxObject(const Location& pos, const std::string& object_file, const cv::Mat& img)
{
//    Location l = pos / Settings::get_instance().MODEL_TO_OPENGL_RATIO;
//    Location l = pos;
    Location l = pos / Settings::get_instance().MAP_SIZE;

    cv::Mat_<cv::Vec2f> vertex(1, 4);
    vertex << cv::Vec2f(0, l.x), cv::Vec2f(0, 0), cv::Vec2f(l.y, 0), cv::Vec2f(l.x, l.y);

    cv::Mat_<cv::Vec2f> texCoords(1, 4);
    texCoords << cv::Vec2f(0, 0), cv::Vec2f(0, 1), cv::Vec2f(1, 1), cv::Vec2f(1, 0);

    cv::Mat_<int> indicesm(1, 6);
    indicesm << 0, 1, 2, 2, 3, 0;

    arr.setVertexArray(vertex);
    arr.setTexCoordArray(texCoords);
    indices.copyFrom(indicesm);
    tex.copyFrom(img);
}

GfxObject::~GfxObject()
{

}

void GfxObject::draw()
{
    glEnable(GL_TEXTURE_2D);
    tex.bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glDisable(GL_CULL_FACE);

    cv::ogl::render(arr, indices, cv::ogl::TRIANGLES);
}



GlDrawInstance::GlDrawInstance(Unit* original_, GfxObject* type_) :
    original{original_},
    pos{original_->get_location()},
    type{type_}
{}

GlDrawInstance::~GlDrawInstance() {}


void GlDrawInstance::updatePosition()
{
    pos = (Location{original->get_location()} / Settings::get_instance().MAP_SIZE);
//    pos = (Location{original->get_location()} / Settings::get_instance().MODEL_TO_OPENGL_RATIO);
//    pos = original->get_location();
}

Unit* GlDrawInstance::getOriginal()
{
    return original;
}
void GlDrawInstance::draw()
{
    updatePosition();

    glTranslated(pos.x, pos.y, 0);
    type->draw();
    glTranslated(-pos.x, -pos.y, 0);
}


}


