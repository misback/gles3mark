/**
  *  gles3mark v1.0
  *
  *  \date   2014-05-28
  *  \author Tomas Kimer <xkimer00@stud.fit.vutbr.cz>
  */

#include "loadingscreen.h"
#include "shaderprogram.h"
#include "texture.h"
#include "glinclude.h"
#include "quadrenderer.h"

LoadingScreen::LoadingScreen(const AssetManager& assetManager, int width, int height) {
    ShaderProgram screenQuadProgram(assetManager.LoadText("shaders/screenquad-vs.glsl"),
                                    assetManager.LoadText("shaders/screenquad-fs.glsl"));
    screenQuadProgram.AddUniform("tex");

    Texture texture;
    texture.FromKTXdata(assetManager.LoadContents("textures/loading.ktx")); 

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    screenQuadProgram.Use();
    screenQuadProgram.SetUniform("tex", 0);
    texture.Bind();
    
    QuadRenderer quadRenderer;
    quadRenderer.Render(0.0f, 0.0f, 2.0f);
}

LoadingScreen::~LoadingScreen() {

}