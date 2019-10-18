#ifndef __SIMPLE_GLTF_GLB_H__
#define __SIMPLE_GLTF_GLB_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    uint32_t magic;       /**<equals 0x46546C67. It is ASCII string glTF*/
    uint32_t version;     /**<indicates the version of the Binary glTF container format.*/
    uint32_t length;      /**<is the total length of the Binary glTF, including Header and all Chunks, in bytes.*/
}GLB_Header;

typedef enum
{
    GLB_CT_JSON = 0x4E4F534A,
    GLB_CT_BIN = 0x004E4942
}GLB_ChunkTypes;

typedef struct
{
    uint32_t chunkLength;   /**<is the length of chunkData, in bytes.*/
    uint32_t chunkType;     /**<indicates the type of chunk. one of GLB_ChunkTypes*/
    char    *chunkData;     /**<is a binary payload of chunk*/
}GLB_Chunk;

typedef struct
{
    GLB_Header header;      /**<file header for GLB file*/
    char * buffer;          /**<data blob for the GLB file*/
    GLB_Chunk *chunkList;   /**<list of chunks in the buffer*/
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


#endif
