#pragma once
#include "GraphicsBuildSettings.h"

#ifdef 0

#ifdef DRAW_LIBRARY_DX11
class Texture2DDX11Impl;

typedef Texture2DDX11Impl Texture2D;

#elif DRAW_LIBRARY_OPENGL

class Texture2DOPENGLImpl;

typedef Texture2DDX11Impl Texture2D;

#endif

#endif