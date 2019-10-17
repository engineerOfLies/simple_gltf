#ifndef __SIMPLE_GLTF_GLB_H__
#define __SIMPLE_GLTF_GLB_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    uint32 magic;       /**<equals 0x46546C67. It is ASCII string glTF*/
    uint32 version;     /**<indicates the version of the Binary glTF container format.*/
    uint32 length;      /**<is the total length of the Binary glTF, including Header and all Chunks, in bytes.*/
}GLB_Header;

typedef struct
{
    GLB_Header header;  /**<file header for GLB file*/
    char * buffer;      /**<data blob for the GLB file*/
}GLB_File;

/**
 * @brief load a GLB file from disk
 * @note file must be freed with simple_glb_free
 * @param filepath the file to load
 * @return NULL on error (see logs) or a pointer to a loaded GLB file otherwise
 */
GLB_File *simple_glb_load(char * filepath);

/**
 * @brief free the data from a glbFile
 * @param glbFFile the glb data to free
 */
void simple_glb_free(GLB_File *glbFile);
#define
