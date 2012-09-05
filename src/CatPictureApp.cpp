/**
 * @file CatPictureApp.cpp
 * This app randomizes the color of the background when it is
 * clicked upon. It will draw a circle that increases in size
 * wherever the mouse currently is, and it will save the circles
 * on a particular background.
 *
 * @author Jake Gregg
 * @date 2012-08-23
 *
 * @note This file is (c) 2012. It is licensed under the
 * CC by 3.0 License, which means you are free to use, share,
 * and remix it as long as you give attribution. Commercial uses
 * are allowed.
 */

/// Include statements

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"
#include "Particle.h"
#include "ParticleController.h"

#define TOTAL_PARTICLES 4800
#define RESOLUTION 10

using namespace ci;
using namespace ci::app;
using namespace std;

/// Define public methods and private variables
class CatPictureApp : public AppBasic {
  public:
    void prepareSettings(Settings *settings);
	void setup();
	void mouseMove( MouseEvent event );	
	void mouseDrag( MouseEvent event );
	void update();
	void draw();
    void keyDown(KeyEvent event);
    
    Channel32f mChannel;
    gl::Texture myTexture_;
    
    ParticleController mParticleController;
    
    bool mDrawParticles_;
    bool mDrawImage_;
    
private:
	Surface mySurface_;
    
	Vec2i mMouseLoc;
};

void CatPictureApp::prepareSettings(Settings *settings) {
    settings->setWindowSize(520, 520);
    settings->setFrameRate(60.0f);
}

/// Sets the initial loop number to 1, initiallizes the random
/// number generator, and initiallizes my random numbers for use
/// in generating the background color.
void CatPictureApp::setup()
{
    mChannel = Channel32f(loadImage(loadResource("assassins_creed_3_logo.jpeg")));
    myTexture_ = mChannel;
    
    mParticleController = ParticleController(RESOLUTION);
    
    mMouseLoc = Vec2i(0, 0);
    
    mDrawParticles_ = true;
    mDrawImage_ = false;

}

/// When the user moves the mouse, it gets the new mouse position
/// and it draws a new circle there. It will start the loop over.
void CatPictureApp::mouseMove( MouseEvent event )
{

	mMouseLoc = event.getPos();
	
}

/// When the user clicks the left click, it will randomize
/// the background color.
void CatPictureApp::mouseDrag( MouseEvent event) {
	
    mouseMove(event);
    
}

/// A continuous loop is running in the background the entire
/// program, and this determines the radius of the drawn circle.
/// if the circle reaches a certain limit, it will stop drawing
/// that particular circle.
void CatPictureApp::update()
{
	
    if (! mChannel) return;
    
	mParticleController.update(mChannel, mMouseLoc);
    
	
}

/// When the draw method is called, it draws a cirlce with the 
/// current parameters.
void CatPictureApp::draw()
{
    gl::clear (Color(0, 0, 0), true);
    
    if (mDrawImage_ ){
        myTexture_.enableAndBind();
        gl::draw(myTexture_, getWindowBounds());
    }
    if (mDrawParticles_) {
        glDisable(GL_TEXTURE_2D);
        mParticleController.draw();
    }
	
}

void CatPictureApp::keyDown(KeyEvent event) {
    if (event.getChar() == '1'){
        mDrawImage_ = !mDrawImage_;
    }
    else if (event.getChar() == '2'){
        mDrawParticles_ = !mDrawParticles_;
    }
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
