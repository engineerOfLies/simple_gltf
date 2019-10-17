#include <string.h>
#include "simple_logger.h"
#include "simple_glb.h"

GLB_File *simple_glb_new()
{
    GLB_File *glbFile = NULL;
    glbFile = (GLB_File*)malloc(sizeof(GLB_File));
    if (!glbFile)
    {
        slog("failed to allocate space for GLP FILE");
        return NULL;
    }
    memset(glbFile,0,sizeof(GLB_File));
    return glbFile;
}

GLB_File *simple_glb_load(char * filepath)
{
    GLB_File *glbFile = NULL;
    FILE *file;
    file = fopen(filepath,"rb");
    if (!file)
    {
        slog("failed to open file %s",filepath);
        return NULL;
    }
    glbFile = simple_glb_new();
    if (!glbFile)
    {
        fclose(file);
        return NULL;
    }
    
    fclose(file);
    return glbFile;
}

void simple_glb_free(GLB_File *glbFile)
{
    if (!glbFile)
    {
        slog("no glbFile handle provided");
        return;
    }
    if (glbFile->buffer)
    {
        free(glbFile->buffer);
        glbFile->buffer = NULL;
    }
    free(glbFile);
}


/*eol@eof*/
