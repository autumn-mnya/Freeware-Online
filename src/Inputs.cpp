#include "Inputs.h"
#include "cave_story.h"

long gKeyPlayerList = KEY_TAB;
long gKeyChat = KEY_T;

char gTypedText[MAX_TYPE];

void CustomInputHandler()
{
	if (GetKeyState(VK_TAB) & 0x8000)
		gKey |= KEY_TAB;
	else
		gKey &= ~KEY_TAB;

	if (GetKeyState('T') & 0x8000)
		gKey |= KEY_T;
	else
		gKey &= ~KEY_T;
}

void ChatInput()
{
	if (strlen(gTypedText) != MAX_TYPE)
	{
		if (GetKeyState('A') & 0x8000)
			strcat(gTypedText, "a");
	}
}