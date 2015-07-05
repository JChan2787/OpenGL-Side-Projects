//Programmed By: Jay Chan Jr.
//Date         : 4 JUL 2015

//Pre Processor Directives
#include "OGL.h"
#include <iostream>

OGL::OGL()
{
	m_deviceContext = 0;
	m_renderingContext = 0;
}

OGL::~OGL()
{

}

//Function defintion for InitializeOGL
void OGL::InitializeOGL(bool vSyncOn)
{
	//Declaring local variables
	int pixelFormat;
	int result;
	int attributesList[5];
	int glVersion[2];
	char* vendorString;
	char* rendererChar;
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	HGLRC tempOpenGLContext;

	//Initialize local variables
	result = 0;
	glVersion[0] = -1;
	glVersion[1] = 1;

	//Debugging stuff
	std::cout << "Initializing OpenGL..." << std::endl;

	//Getting device
	//----------------------------------------------------------------------------
	//GetDC is a function that retrieves a handle to a device context (DC) for the 
	//client area of a specified window or for the entire screen. You can use the
	//returned handle in subsequent GDI functions to draw in the DC. The device
	//context is an opaque data structure, whose values are used internally by GDI.
	//Source -- https://msdn.microsoft.com/en-us/library/windows/desktop/dd144871(v=vs.85).aspx
	m_deviceContext = GetDC(m_hwnd);
	
	//Make sure it's not null
	if(!m_deviceContext)
	{
		//Throw an exception if it is.
		throw std::runtime_error("Unable to Get Device Context -- OGL.cpp");
	}

	//Query for a pixel format that will get attributes we want.
	//----------------------------------------------------------------------------
	//ChoosePixelFormat is a function that attempts to match an appropriate pixel
	//format supported by a device context to a given pixel format specification.
	//Source -- https://msdn.microsoft.com/en-us/library/windows/desktop/dd318284(v=vs.85).aspx
	pixelFormat = ChoosePixelFormat(m_deviceContext, &pixelFormatDescriptor);

	//Make a check if pixel formats match.
	if(pixelFormat == 0)
	{
		//Thrown exception
		throw std::out_of_range("Pixel format doers not match current device context -- OGL.cpp");
	}

	//If the video card can handle desired pixel format
	//----------------------------------------------------------------------------
	//SetPixelFormat is a function that sets the pixel format of the specified
	//device context to the format speficied by the iPixelFormat index.
	//Source -- https://msdn.microsoft.com/en-us/library/windows/desktop/dd369049(v=vs.85).aspx
	result = SetPixelFormat(m_deviceContext, pixelFormat, &pixelFormatDescriptor);

	//Checks if the above is true
	if(result != 1)
	{
		throw std::out_of_range("Pixel format out of range -- OGL.cpp");
	}

	//Make temporary context that will initialize OpenGL wrangler
	//----------------------------------------------------------------------------
	//wglCreateContext is a function that creates a new OpenGL rendering
	//context, which is suitable for drawing on the device referenced by 
	//hdc (in this case it's 'deviceContext'). The rendering context has
	//the same pixel format as the device context. 
	//Source -- https://msdn.microsoft.com/en-us/library/windows/desktop/dd374379(v=vs.85).aspx
	tempOpenGLContext = wglCreateContext(m_deviceContext);

	//Set temporary rendering context as the current rendering context
	//for this window.
	//----------------------------------------------------------------------------
	//wglMakeCurrent is a function that makes a specified OpenGL rendering context 
	//the calling thread's current rendering context. All subsequent OpenGL calls 
	//made by the thread are drawn on the device identified by HDC. Can also make
	//it to change the calling thread's current rendering context so it's no longer
	//current.
	//Source -- https://msdn.microsoft.com/en-us/library/windows/desktop/dd374387(v=vs.85).aspx	
	wglMakeCurrent(m_deviceContext, tempOpenGLContext);

	//Checks if glewInit() returns GLEW_OK. If it did, then the initialization
	//has succeeded.
	if(glewInit() != GLEW_OK)
	{
		throw std::runtime_error("glewInit failed() -- OGL.cpp");
	}

	//Set OpenGL 4.0
	attributesList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributesList[1] = 4;
	attributesList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributesList[3] = 0;
	attributesList[4] = 0;

	//Creating OpenGL 4.0 rendering context.
	m_renderingContext = wglCreateContextAttribsARB(m_deviceContext, 0, attributesList);

	if(m_renderingContext != NULL)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempOpenGLContext);

		//Set the rendering context to OpenGL 4.0
		if(wglMakeCurrent(m_deviceContext, m_renderingContext) != 1)
		{
			throw std::out_of_range("Rendering context does not exist -- OGL.cpp");
		}
	}

	//Getting name of graphics card
	vendorString = (char*)glGetString(GL_VENDOR);
	rendererChar = (char*)glGetString(GL_RENDERER);

	//Store graphics card information
	strcpy_s(m_videoCardDescription, vendorString);
	strcat_s(m_videoCardDescription, "-");
	strcat_s(m_videoCardDescription, rendererChar);

	//Getting vSync Mode
	//wglSwapIntervalEXT is a function that specifies minimum number of frames befor each
	//buffer swap. Used for virtual synchronization, if the value '1' is passed as its
	//argument.
	if(vSyncOn)
	{
		result = wglSwapIntervalEXT(1);
	}
	else
	{
		result = wglSwapIntervalEXT(0);
	}

	//Checking if vSync is set correctly
	if(result != 1)
	{
		throw std::out_of_range("wglSwapIntervalEXT() failed -- OGL.cpp");
	}

	//Getting which version of OpenGL currently being used - 4.0 or 2.1
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[2]);

	//Printing information to console
	std::cout << "Initializing OpenGL successful!" << std::endl;
	std::cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << std::endl;
	std::cout << "GPU  Information: " << m_videoCardDescription << std::endl;
}

//Function definition for InitializeExtensions
void OGL::InitializeExtensions()
{
	//Declaring local variables
	HDC deviceContext;
	PIXELFORMATDESCRIPTOR pixelFormat;
	HGLRC renderContext;
	int error; 

	//Initializing local variables
	error = 0;

	//Getting the device content for this window
	deviceContext = GetDC(m_hwnd);

	//Make a check if deviceConext is not null
	if(!deviceContext)
	{
		//Throw an exception if it is.
		throw std::runtime_error("Unable to Get Device Context -- OGL.cpp");
	}

	//Set temporary default pixel format
	error = SetPixelFormat(deviceContext, 1, &pixelFormat);

	//Make a check if SetPixelFormat spit out the right value
	if(error != 1)
	{
		//Throw an exception if it is.
		throw std::out_of_range("Pixel Format out of range -- OGL.cpp");
	}

	//Creating a temporary rendering context --
	renderContext = wglCreateContext(deviceContext);

	//Check if the renderContext is not null.
	if(!renderContext)
	{
		//Throw an exception if it is.
		throw std::runtime_error("Unable to create rendering context -- OGL.cpp");
	}

	//Set temporary rendering context as the current rendering context
	//for this window.
	error = wglMakeCurrent(deviceContext, renderContext);

	//Check if the current rendering context is not null
	if(error != 1)
	{
		//Throw exception.
		throw std::out_of_range("Rendering context does not exist -- OGL.cpp");
	}

	//Deallocating memory
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(renderContext);
	renderContext = NULL;
	ReleaseDC(m_hwnd, deviceContext);
	deviceContext = 0;
}

//Function definition for LoadExtensions
void OGL::LoadExtensions()
{
	//Getting the address of our current rendering context.
	//----------------------------------------------------------------------------
	//wglGetProcAddress is a function that returns the address of an OpenGL extension function
	//for use with the current OpenGL rendering context. 
	//Source -- https://msdn.microsoft.com/en-us/library/windows/desktop/dd374386(v=vs.85).aspx
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	//Check if this is not null.
	if(!wglCreateContextAttribsARB)
	{
		//Throw an exception
		throw std::runtime_error("Address of OpenGL extension not valid -- OGL.cpp");
	}
}

//Function definition for BeginScene
void OGL::BeginScene(float red, float blue, float green, float alpha)
{
	//Clean the color buffers first, or else we might get garbage values.
	//----------------------------------------------------------------------------
	//glClearColor is a function in OpenGL that specifies the rgb & alpha values
	//used by glClear to clear the color buffers. Values specified by this function
	//are clamped to the range [0, 1].
	//Source -- https://www.opengl.org/sdk/docs/man/
	glClearColor(red, blue, green, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//Function definition for EndScene
void OGL::EndScene()
{
	//Empties all buffers in OpenGL.
	glFlush();

	//Exchange front and back buffers of the device context,
	//if there is any.
	//----------------------------------------------------------------------------
	//SwapBuffers is a function that exchanges the front and end buffers if the 
	//current pixel format for the window referenced by the specified device
	//context includes a back buffer.
	//Source -- https://msdn.microsoft.com/en-us/library/windows/desktop/dd369060(v=vs.85).aspx
	SwapBuffers(m_deviceContext);

	//Call this function to block any further instructions until
	//all the gl instructions are finished.
	glFinish();
}

//Function definition for Release
void OGL::Release()
{
	//First check if the current rendering context is not null already
	if(m_renderingContext)
	{
		//Make the current rendering context null
		wglMakeCurrent(NULL, NULL);
		
		//Delete the current rendering context in our class
		wglDeleteContext(m_renderingContext);

		//Set it to zero just to be super sure
		m_renderingContext = 0;
	}

	//Checks if the device context is not null
	if(m_deviceContext)
	{
		//Releases the device device context, so other 
		//applications can now use it.
		ReleaseDC(m_hwnd, m_deviceContext);
		m_deviceContext = 0;
	}
}