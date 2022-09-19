#pragma once

#include "cave_story.h"

#define MAX_TYPE 0x20

extern long gKeyPlayerList;
extern long gKeyChat;

extern char gTypedText[MAX_TYPE];

void CustomInputHandler();
void ChatInput();