#include "UseHeaders/LevelLoader.h"
#include "UseHeaders/globals.h"
#include "nds.h"
#include <malloc.h>

void LoadLevel(std::string file){
    if (nitroFSInit(NULL)) {
		//dirlist("/");
		
		{
			// now, try reading a file to make sure things are working OK.
			FILE* inf = fopen("World.txt","rb");
			if(inf)
			{
                
				int len;

				fseek(inf,0,SEEK_END);
				len = ftell(inf);
				fseek(inf,0,SEEK_SET);

				printf("\nthe following %d bytes message\nfrom file1.txt is\nbrought to you by fread:\n",len);
				
					char *entireFile = (char*)malloc(len+1);
					entireFile[len] = 0;
					if(fread(entireFile,1,len,inf) != len)
						printf("savage error reading the bytes from the file!\n");
					else
						printf("%s\n-done-\n",entireFile);
					free(entireFile);
				

				fclose(inf);
			}
		}

		printf("here is the dirlist once more:\n");
		//dirlist("/");

	} else {
		printf("nitroFSInit failure: terminating\n");
	}
}