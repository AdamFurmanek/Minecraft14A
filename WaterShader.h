#ifndef WaterShader_h
#define WaterShader_h

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include <Cg/cg.h>
#include <Cg/cgGL.h>

static const char* myProgramName = "waterVertexShader",
* myVertexProgramFileName = "WaterVertexShader.cg",
* myVertexProgramName = "main";

static CGcontext   myCgContext;
static CGprofile   myCgVertexProfile;
static CGprogram   myCgVertexProgram;
static CGparameter height, modelViewMatrix;

class WaterShader
{

    static void checkForCgError(const char* situation)
    {
        CGerror error;
        const char* string = cgGetLastErrorString(&error);

        if (error != CG_NO_ERROR) {
            printf("%s: %s: %s\n",
                myProgramName, situation, string);
            if (error == CG_COMPILER_ERROR) {
                printf("%s\n", cgGetLastListing(myCgContext));
            }
            exit(1);
        }
    }

public:

    WaterShader() {
        myCgContext = cgCreateContext();
        checkForCgError("creating context");
        cgGLSetDebugMode(CG_FALSE);
        cgSetParameterSettingMode(myCgContext, CG_DEFERRED_PARAMETER_SETTING);

        myCgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
        cgGLSetOptimalOptions(myCgVertexProfile);
        checkForCgError("selecting vertex profile");

        myCgVertexProgram =
            cgCreateProgramFromFile(
                myCgContext,              /* Cg runtime context */
                CG_SOURCE,                /* Program in human-readable form */
                myVertexProgramFileName,  /* Name of file containing program */
                myCgVertexProfile,        /* Profile: OpenGL ARB vertex program */
                myVertexProgramName,      /* Entry function name */
                NULL);                    /* No extra compiler options */
        checkForCgError("creating vertex program from file");
        cgGLLoadProgram(myCgVertexProgram);
        checkForCgError("loading vertex program");

        modelViewMatrix = cgGetNamedParameter(myCgVertexProgram, "ModelViewProj");
        checkForCgError("getting ModelViewProj parameter");

        height = cgGetNamedParameter(myCgVertexProgram, "height");
        checkForCgError("getting height parameter");
    }

    void Enable(float height2, char textureIndex) {

        cgGLSetStateMatrixParameter(modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

        cgGLSetParameter1f(height, height2);

        cgGLBindProgram(myCgVertexProgram);
        checkForCgError("binding vertex program");

        cgGLEnableProfile(myCgVertexProfile);
        checkForCgError("enabling vertex profile");


    }

    void Disable() {

        cgGLDisableProfile(myCgVertexProfile);
        checkForCgError("disabling vertex profile");
    }

};

#endif