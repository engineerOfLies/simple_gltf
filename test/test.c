#include <stdio.h>

#include "simple_json.h"
#include "simple_glb.h"

int main(int argc, char *argv[])
{
    SJson *json;
    SJson *obj,*temp;
    SJson *array,*primitives,*prim,*attr;
    int i,n,count,mesh,pcount,p;
    GLB_File *glb = NULL;
    printf("** test begin ***\n");
    printf("Loading gltf file %s\n",argv[1]);
    
    if (argv[1])
    {
        glb = simple_glb_load(argv[1]);
        json = simple_glb_get_json(glb);
        
        simple_glb_free(glb);
        
        printf("parsed json from GLB:\n");
        
//        sj_echo(json);
        sj_object_echo_keys(json);
        
        array = sj_object_get_value(json,"accessors");
        if (array)
        {
            count = sj_array_get_count(array);
            printf("\nparsed %i accessors\n",count);
            for (n = 0; n < MIN(count,3);n++)
            {
                obj = sj_array_get_nth(array,n);
                if (n == 0)sj_object_echo_keys(obj);

                sj_get_integer_value(sj_object_get_value(obj,"bufferView"),&i);
                printf("bufferView: %i\n",i);
                sj_get_integer_value(sj_object_get_value(obj,"count"),&i);
                printf("count: %i\n",i);
                printf("type: %s\n",sj_get_string_value(sj_object_get_value(obj,"type")));
                sj_get_integer_value(sj_object_get_value(obj,"componentType"),&i);
                printf("componentType: %i\n\n",i);
            }
        }
        array = sj_object_get_value(json,"nodes");
        if (array)
        {
            count = sj_array_get_count(array);
            printf("\nparsed %i nodes\n",count);
            for (n = 0; n < count;n++)
            {
                obj = sj_array_get_nth(array,n);
                printf("name: %s\n",sj_get_string_value(sj_object_get_value(obj,"name")));
                sj_object_echo_keys(obj);
                temp = sj_object_get_value(obj,"mesh");
                if (temp)
                {
                    sj_get_integer_value(temp,&mesh);
                    printf("mesh: %i\n",mesh);
                }
                printf("\n");
            }
        }
        array = sj_object_get_value(json,"meshes");
        if (array)
        {
            count = sj_array_get_count(array);
            printf("\nparsed %i meshes\n",count);
            for (n = 0; n < count;n++)
            {
                obj = sj_array_get_nth(array,n);
                printf("name: %s\n",sj_get_string_value(sj_object_get_value(obj,"name")));
                sj_object_echo_keys(obj);
                
                primitives = sj_object_get_value(obj,"primitives");
                pcount = sj_array_get_count(primitives);
                for (p = 0; p < pcount;p++)
                {
                    prim = sj_array_get_nth(primitives,p);
                    if (!prim)continue;
                    printf("*primitives:\n");
                    sj_object_echo_keys(prim);
                    temp = sj_object_get_value(prim,"indices");
                    if (temp)
                    {
                        sj_get_integer_value(temp,&mesh);
                        printf("accessor for indices: %i\n",mesh);
                    }
                    printf("**attributes:\n");
                    attr = sj_object_get_value(prim,"attributes");
                    sj_object_echo_keys(attr);
                    
                }
                printf("\n");
            }
        }
        sj_free(json);
    }

    printf("**test complete***\n");

    return 0;
}

