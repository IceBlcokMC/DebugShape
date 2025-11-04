#pragma once

#ifndef DEBUG_SHAPE_EXPORT
#define DSAPI __declspec(dllexport)
#else
#define DSAPI __declspec(dllimport)
#endif

#define DSNDAPI [[nodiscard]] DSAPI

#define DS_DISABLE_COPY(CLASS)                                                                                         \
    CLASS(CLASS const&)            = delete;                                                                           \
    CLASS& operator=(CLASS const&) = delete

#define DS_DISABLE_MOVE(CLASS)                                                                                         \
    CLASS(CLASS&&)            = delete;                                                                                \
    CLASS& operator=(CLASS&&) = delete

#define DS_DISABLE_COPY_MOVE(CLASS)                                                                                    \
    DS_DISABLE_COPY(CLASS);                                                                                            \
    DS_DISABLE_MOVE(CLASS)