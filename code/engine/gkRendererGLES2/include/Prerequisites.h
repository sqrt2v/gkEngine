﻿//////////////////////////////////////////////////////////////////////////
/*
Copyright (c) 2011-2015 Kaiming Yi
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
	
*/
//////////////////////////////////////////////////////////////////////////



// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "gkPlatform.h"
#include "gk_Math.h"

#ifdef GKRENDERERGLES2_EXPORTS
#define GKRENDERERGLES2API DLL_EXPORT
#else
#define GKRENDERERGLES2API DLL_IMPORT
#endif

// TODO: reference additional headers your program requires here
class gkMeshManager;
class gkShaderManager;
class gkMaterialManager;
class gkTextureManager;
class gkPostProcessManager;
struct ICamera;

#ifdef OS_WIN32

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>

#elif defined( OS_ANDROID )
#include <jni.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>

#elif defined( OS_IOS )

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#endif

// Define GL_NONE for convenience
#define GL_NONE 0

#ifndef GL_BGRA
#   define GL_BGRA  0x80E1
#endif

#if (OGRE_PLATFORM == OGRE_PLATFORM_WIN32)
// an error in all windows gles sdks...
#   undef GL_OES_get_program_binary
#endif

#if (OGRE_PLATFORM == OGRE_PLATFORM_WIN32) && !defined(__MINGW32__) && !defined(OGRE_STATIC_LIB)
#   ifdef OGRE_GLES2PLUGIN_EXPORTS
#       define _OgreGLES2Export __declspec(dllexport)
#   else
#       if defined( __MINGW32__ )
#           define _OgreGLES2Export
#       else
#           define _OgreGLES2Export __declspec(dllimport)
#       endif
#   endif
#elif defined ( OGRE_GCC_VISIBILITY )
#    define _OgreGLES2Export  __attribute__ ((visibility("default")))
#else
#    define _OgreGLES2Export
#endif

#define DEBUG_(text) \
	{\
	fprintf(stderr, "%s:%d: %s\n", __FUNCTION__, __LINE__, text); \
	}

#define ENABLE_GL_CHECK 0
#if ENABLE_GL_CHECK
#define GL_CHECK_ERROR \
	{ \
	int e = glGetError(); \
	if (e != 0) \
		{ \
		const char * errorString = ""; \
		switch(e) \
			{ \
		case GL_INVALID_ENUM:       errorString = "GL_INVALID_ENUM";        break; \
		case GL_INVALID_VALUE:      errorString = "GL_INVALID_VALUE";       break; \
		case GL_INVALID_OPERATION:  errorString = "GL_INVALID_OPERATION";   break; \
		case GL_OUT_OF_MEMORY:      errorString = "GL_OUT_OF_MEMORY";       break; \
		default:                                                            break; \
			} \
			char msgBuf[10000]; \
			sprintf(msgBuf, "OpenGL ES2 error 0x%04X %s in %s at line %i\n", e, errorString, __PRETTY_FUNCTION__, __LINE__); \
			LogManager::getSingleton().logMessage(msgBuf); \
		} \
	}
#else
#define GL_CHECK_ERROR {}
#endif

#if ENABLE_GL_CHECK
#define EGL_CHECK_ERROR \
	{ \
	int e = eglGetError(); \
	if ((e != 0) && (e != EGL_SUCCESS))\
		{ \
		char msgBuf[10000]; \
		sprintf(msgBuf, "EGL error 0x%04X in %s at line %i\n", e, __PRETTY_FUNCTION__, __LINE__); \
		LogManager::getSingleton().logMessage(msgBuf); \
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, msgBuf, __PRETTY_FUNCTION__); \
		} \
	}
#else
#define EGL_CHECK_ERROR {}
#endif






