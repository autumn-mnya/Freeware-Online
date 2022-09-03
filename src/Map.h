struct CS_MAP_DATA2
{
	unsigned char* data;
	unsigned char atrb[0x102];
	short width;
	short length;
};

CS_MAP_DATA2* gMap = (CS_MAP_DATA2*)0x49E480;