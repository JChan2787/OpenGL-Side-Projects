//Programmed By: Jay Chan Jr.
//Date		   : 4 JUL 2015
 
#ifndef OGL_H
#define OGL_H

//Pre Processor Directives
#include "glew.h"
#include "wglew.h"

//DEFINES
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092

//typedefs that we need to access the OpenGL 4.0 functionality
typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* attribList);

//Class definition starts here
class OGL
{
public:

	//Class Constructor
	OGL();

	//Class Destructor
	~OGL();

	/*
	* Function   : InitializeExtensions 
	* Purpose    : Initializes OpenGL extensions
	* Parameters : n/a
	* Returns    : n/a
	*/
	void InitializeExtensions();

	/*
	* Function   : InitializeOGL 
	* Purpose    : Initializes OpenGL
	* Parameters : bool vSyncOn
	* Returns    : bool
 	*/
	void InitializeOGL(bool vSyncOn);

	/*
	* Function   : BeginScene 
	* Purpose    : Begin the scene for OpenGL
	* Parameters : float red, 
	*		       float blue, 
	*			   float green, 
	*			   float alpha
	* Returns    : n/a
	*/
	void BeginScene(float red, float blue, float green, float alpha);

	/*
	* Function   : EndScene
	* Purpose    : End the scene for OpenGL
	* Parameters : n/a
	* Returns    : n/a
	*/
	void EndScene();

	/*
	* Function   : GetVideoCardInfo 
	* Purpose    : Gets the name of your GPU
	* Parameters : char* pInfo
	* Returns    : n/a
	*/
	void GetVideoCardInfo(char* pInfo);

	/*
	* Function   : GetHWND
	* Purpose    : Get HWND object
	* Parameters : n/a
	* Returns    : HWND object
	*/
	HWND GetHWND();

	/*
	* Function   : SetHWND
	* Purpose    : Set HWND, mainly setting OpenGL window
	* Parameters : HWND pHWND
	* Returns    : n/a
	*/
	void SetHWND(HWND pHWND);

	/*
	* Function   : Release
	* Purpose    : Release OpenGL, alongside most memory that this
    *	           program allocated.
	* Parameters : n/a
	* Returns    : n/a
	*/
	void Release();

private:

	/*
	* Function   : LoadExtensions
	* Purpose    : Load extensions
	* Parameters : n/a
	* Returns    : n/a
	*/
	void LoadExtensions();

	//Data Members:

	//OpenGL objects
	HDC m_deviceContext; //A device context is a windows data structure containing
						 //information about the drawing attributes of a device
						 //such as a display or a printer. Draw calls are made through
						 //a device context object, which encapsulates Windows APIs	
						 //for drawing lines, shapes, and text. DC's allow device
						 //independent drawing in Windows. Can be used to draw on the
					     //screen, printer, or a metafile.

	HGLRC m_renderingContext; //A rendering context is used in OpenGL as a port in which
							  //all OpenGL instructions pass through. All threads that 
							  //make OpenGL calls must have a current rendering context. 
							  //Rendering contexts link OpenGL to the Windows windowing
							  //systems.
	HWND m_hwnd;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
	
	//Primitives
	char m_videoCardDescription[128];
};

#endif