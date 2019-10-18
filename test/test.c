#include "simple_glb.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    GLB_File *glb = NULL;
    printf("Loading gltf file %s\n",argv[1]);
    
    if (argv[1])
    {
        glb = simple_glb_load(argv[1]);
        
        simple_glb_free(glb);
    }

    printf("complete\n");

    return 0;
}

