#include "id_mm.h"
#include "id_ca.h"
#include "id_in.h"
#include "id_rf.h"
#include "ck_def.h"
#include "ck_play.h"

#include <stdio.h>
#include <stdlib.h>

//typedef struct ca_huffnode;

void CAL_SetupGrFile();
void CA_CacheGrChunk(int chunk);
void VL_InitScreen();
void VL_SetDefaultPalette();
void VH_DrawBitmap(int x, int y, int chunk);
void VH_DrawMaskedBitmap(int x, int y, int chunk);
void VH_DrawTile16(int x, int y, int tile);
void VH_DrawTile16M(int x, int y, int tile);
void VH_DrawSprite(int x, int y, int chunk);
void VL_Present();

void CAL_SetupMapFile();
void CA_CacheMap(int mapIndex);
void VH_DrawPropString(const char *string,int x, int y, int chunk, int colour);
void VH_DrawPropChar(int x, int y, int chunk, char c, int colour);

int ck_currentMapNumber;

int main(int argc, char **argv)
{
	int ch = atoi(argv[1]);
	MM_Startup();
	CAL_SetupGrFile();
	CAL_SetupMapFile();
	//for (int i = ch; i < ch+(12*18); ++i) CA_CacheGrChunk(i);
	//printf("%s", (char*)(ca_graphChunks[ch]));
//	CA_CacheGrChunk(ch);
	CA_CacheGrChunk(88);
	CA_CacheGrChunk(3);
	CA_CacheGrChunk(ca_gfxInfoE.hdrBitmaps);
	CA_CacheGrChunk(ca_gfxInfoE.hdrMasked);
	CA_CacheGrChunk(ca_gfxInfoE.hdrSprites);

	if (ch <= 100)
	{
		ck_currentMapNumber = ch;

		CA_CacheMap(ch);

		//int mapWidth = CA_MapHeaders[ch]->width;
	}

	VL_InitScreen();
	VL_SetDefaultPalette();
	IN_Startup();

	RF_Startup();
	if (ch <= 100)
	{
		RF_NewMap(ch);
		RF_Reposition(0,0);
	
		CK_SetupObjArray();
		CK_PlayLoop();
	}
	else
		CK_PlayDemo(ch);

	MM_Shutdown();
}