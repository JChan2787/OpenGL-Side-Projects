#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "OGL.h"

class Graphics
{
public:

	//Class Constructor
	Graphics();

	//Class Destructor
	~Graphics();

	/*
	* Function   : InitializeOGL 
	* Purpose    : Initializes OpenGL and its extensions
	* Parameters : HWND windowInfo
	* Returns    : bool
	*/
	bool InitializeOGL(HWND windowInfo);

	/*
	* Function   : BeginScene 
	* Purpose    : Initializes scene before anything is done
	* Parameters : float red
	               float blue
				   float green
			       float alpha
	* Returns    : n/a
	*/
	void Beginscene(float red, float blue, float green, float alpha);

	/*
	* Function   : EndScene 
	* Purpose    : Ends the scene
	* Parameters : n/a
	* Returns    : n/a
	*/
	void EndScene();

	/*
	* Function   : GetOGLObject 
	* Purpose    : Gets reference to the OGL object
	* Parameters : n/a
	* Returns    : OGL*
	*/
	OGL* GetOGLObject();

	/*
	* Function   : Release 
	* Purpose    : Cleans up any dangling pointers and deallocates memory
	* Parameters : n/a
	* Returns    : n/a
	*/
	void Release();

private:

	OGL* openGLRef;
};

#endif