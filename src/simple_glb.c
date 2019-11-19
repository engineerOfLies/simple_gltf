#include <string.h>

#include "simple_logger.h"
#include "simple_json.h"
#include "simple_json_list.h"
#include "simple_json_parse.h"

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

uint32_t simple_glb_get_chunk_length(GLB_Chunk *chunk)
{
    uint32_t size = 0;
    if (!chunk)
    {
        slog("no chunk provided");
        return 0;
    }
    size = (sizeof(uint32_t) * 2)+chunk->chunkLength;
    slog("chunk is size %i",size);
    return size;
}

GLB_Chunk *simple_glb_get_chunk_by_type(GLB_File *glbFile,GLB_ChunkType type)
{
    int i;
    if (!glbFile)return NULL;
    for (i = 0; i < glbFile->chunkCount; i++)
    {
        if (glbFile->chunkList[i].chunkType == type)
        {
            return &glbFile->chunkList[i];
        }
    }
    return NULL;
}

SJson *simple_glb_get_json(GLB_File *glbFile)
{
    SJson *json = NULL;
    GLB_Chunk *chunk = NULL;
    if (!glbFile)
    {
        slog("no glbFile provided");
        return NULL;
    }
    chunk = simple_glb_get_chunk_by_type(glbFile,GLB_CT_JSON);
    if (!chunk)
    {
        slog("no JSON chunk in GLB, bad file");
        return NULL;
    }
    slog("attempting to parse json data from chunk. length %i",chunk->chunkLength);
//    slog("json text loaded:%s\n",chunk->chunkData);
    json = sj_parse_buffer(chunk->chunkData,chunk->chunkLength);
    if (!json)
    {
        slog("json data from glb file failed to parse");
        return NULL;
    }
    return json;
}

void simple_glb_parse(GLB_File *glb)
{
    GLB_Chunk *chunk = NULL;
    uint32_t index = 0;
    uint32_t chunkCount = 0;
    uint32_t chunkIndex = 0;
    if (!glb)return;
    while (index < glb->header.length)
    {
        chunk = (GLB_Chunk *)&glb->buffer[index];
        index += simple_glb_get_chunk_length(chunk);
        chunkCount++;
    }
    slog("chunkCount: %i",chunkCount);
    glb->chunkList = (GLB_Chunk*)malloc(sizeof(GLB_Chunk)*chunkCount);
    if (!glb->chunkList)
    {
        slog("failed to allocate chunk list");
        return;
    }
    memset(glb->chunkList,0,sizeof(GLB_Chunk)*chunkCount);
    index = 0;
    chunkIndex = 0;
    while ((index < glb->header.length)&&(chunkIndex < chunkCount))
    {
        chunk = (GLB_Chunk *)&glb->buffer[index];
        
        glb->chunkList[chunkIndex].chunkLength = chunk->chunkLength - 4;
        glb->chunkList[chunkIndex].chunkType = chunk->chunkType;
        glb->chunkList[chunkIndex].chunkData = (char *)&chunk->chunkData;
        switch (chunk->chunkType)
        {
            case GLB_CT_JSON:
                slog("chunk %i is JSON",chunkIndex);
                
                break;
            case GLB_CT_BIN:
                slog("chunk %i is BINary",chunkIndex);
                break;
            default:
                slog("chunk %i is unknown: 0x%x",chunkIndex,chunk->chunkType);
        }
        chunkIndex++;
        index += simple_glb_get_chunk_length(chunk);
    }
    glb->chunkCount = chunkCount;
    slog("parsed %i chunks out of glb file",chunkCount);
}

GLB_File *simple_glb_load(char * filepath)
{
    GLB_File *glbFile = NULL;
    FILE *file;
    int32_t fileLength = 0;
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
    
    fread(&glbFile->header,sizeof(GLB_Header),1,file);
    
    slog("glb file header:\n-magic: %X\n-version: %i\n-length:%i",glbFile->header.magic,glbFile->header.version,glbFile->header.length);
    fileLength = glbFile->header.length - sizeof(GLB_Header);
    
    if ((fileLength <= 0) || ((glbFile->buffer = malloc(fileLength))==NULL))
    {
        slog("bad glb file length: %i",fileLength);
        fclose(file);
        simple_glb_free(glbFile);
        return NULL;
    }
    memset(glbFile->buffer,0,fileLength);
    
    slog("read %i bytes from glb file",fread(glbFile->buffer,fileLength,1,file)*fileLength);
    
    fclose(file);
    
    simple_glb_parse(glbFile);
    return glbFile;
}

void simple_glb_free(GLB_File *glbFile)
{
    if (!glbFile)
    {
        slog("no glbFile handle provided");
        return;
    }
    if (glbFile->chunkList)
    {
        free(glbFile->chunkList);
        glbFile->chunkList = NULL;
    }
    if (glbFile->buffer)
    {
        free(glbFile->buffer);
        glbFile->buffer = NULL;
    }
    free(glbFile);
}


/*eol@eof*/
