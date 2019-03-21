// Written by Delta-47 21/03/2019
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
	char Magic[4];
	uint32_t Version;
	uint32_t ObjectCount;
	uint32_t Padding;
} Header;

typedef struct
{
	float x;
	float z;
	float y;
} float3;

typedef struct
{
	char Name[60];
	uint16_t Padding;
	uint16_t ObjectType;
	float3 Postion;
	float3 Rotation;
	float3 Scale;
	float3 Reserved1;
	float3 Reserved2;
	uint32_t Padding2;
} Object;

void printHeader(Header *header);
void printObject(Object object);

int main(int argc, char *argv[])
{
	FILE *pFileI, *pFileO;
	char filepath[FILENAME_MAX];
	Header header;
	Object *object;

	printf("MapObjects.MOB Extractor V0.0.1\n\n");
	printf("Enter FilePath of the MapObjects.MOB file\n>>");
	scanf("%s%*c", filepath);

	char temp1[BUFSIZ];
		strcpy(temp1,strcat(filepath, "\\MapObjects.MOB"));

	pFileI = fopen(temp1, "r");
	pFileO = fopen("./MapObjects.txt", "w");
	//pFileI = fopen("C:\\LeagueSandbox\\League_Sandbox_Client\\LEVELS\\map1\\Scene\\MapObjects.MOB", "r");
	//pFileO = fopen("C:\\LeagueSandbox\\League_Sandbox_Client\\LEVELS\\map1\\Scene\\MabObjects.txt", "w");

	memset(&header, '\0', sizeof(Header));
	fread(&header, sizeof(Header), 1, pFileI);

	printHeader(&header);

	object = calloc(header.ObjectCount, sizeof(Object));

	fseek(pFileI, sizeof(Header), SEEK_SET);
	// need to add 2 otherwise not everything is exported
	fread(object, sizeof(Object), header.ObjectCount + 2, pFileI);
;
	for (unsigned int i = 0; i < header.ObjectCount; i++)
	{
		fprintf(pFileO, "Name: %s\nObjectType: %u\nPosition:\n\tX: %f\n\tY: %f\n\tZ: %f\nRotation:\n\tX: %f\n\tY: %f\n\tZ: %f\nScale:\n\tX: %f\n\tY: %f\n\tZ: %f\n\n", object[i].Name, object[i].ObjectType,
			object[i].Postion.x, object[i].Postion.y, object[i].Postion.z, object[i].Rotation.x, object[i].Rotation.y, object[i].Rotation.z, object[i].Scale.x, object[i].Scale.y, object[i].Scale.z);
	}
	
	//printf("Fileoffset: 0x%x\n, header.ObjectCount: %d\n", ftell(pFileI), header.ObjectCount);

	fclose(pFileI);
	fclose(pFileO);
	printf("done... Press a key to continue");
	getchar();

	return 0;
}

void printHeader(Header *header)
{
	printf("Header info:\n\tMagic: %s\n\tVersion: %d\n\t#Objects %d\n", header->Magic, header->Version, header->ObjectCount);
}

void printObject(Object object)
{
}
