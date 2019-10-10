#ifndef __SIMPLE_GLTF_H__
#define __SIMPLE_GLTF_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    uint32 magic;       /**<equals 0x46546C67. It is ASCII string glTF*/
    uint32 version;     /**<indicates the version of the Binary glTF container format.*/
    uint32 length;      /**<is the total length of the Binary glTF, including Header and all Chunks, in bytes.*/
}GLTF_Header;

#endif
