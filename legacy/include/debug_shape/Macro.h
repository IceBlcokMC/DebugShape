#pragma once

#ifndef DEBUG_SHAPE_EXPORT
#define DSAPI __declspec(dllexport)
#else
#define DSAPI __declspec(dllimport)
#endif

#define DSNDAPI [[nodiscard]] DSAPI