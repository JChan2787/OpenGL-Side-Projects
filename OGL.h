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
	* Returns    : bool
	*/
	bool InitializeExtensions();

	/*
	* Function   : InitializeOGL 
	* Purpose    : Initializes OpenGL
	* Parameters : n/a
	* Returns    : bool
 	*/
	bool InitializeOGL();

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
	* Returns    : bool
	*/
	bool LoadExtensions();

	//Data Members:

	//OpenGL objects
	HDC m_deviceContext;
	HGLRC m_renderingContext;
	HWND m_hwnd;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
	
	//Primitives
	char m_videCardDescription[128];
};

#endif