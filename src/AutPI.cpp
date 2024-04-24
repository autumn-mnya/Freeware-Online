// AutPI.cpp

#include <windows.h>
#include <iostream>
#include "AutPI.h"
#include "mod_loader.h"
#include "cave_story.h"
#include "lua/Lua.h"

HMODULE autpiDLL = nullptr;  // Global variable

// Function pointer for dynamically loaded functions
typedef void (*RegisterElementFunc)(void (*)());

// Function to register an element handler
void RegisterElement(std::vector<void (*)()>& handlers, const char* functionName, void (*handler)())
{
    if (autpiDLL != nullptr) {
        RegisterElementFunc registerFunc =
            reinterpret_cast<RegisterElementFunc>(
                GetProcAddress(autpiDLL, functionName));

        if (registerFunc != nullptr) {
            registerFunc(handler);
            handlers.push_back(handler);
        }
        else {
            std::cerr << "Failed to get the function pointer for " << functionName << "\n";
            // You might want to handle the error appropriately.
        }
    }
}

typedef int (*GetCurrentModeF)();

int GetCurrentMode()
{
    // Load GetLuaL function pointer from the DLL
    GetCurrentModeF func = reinterpret_cast<GetCurrentModeF>(
        GetProcAddress(autpiDLL, "GetCurrentMode"));

    if (func == nullptr) {
        std::cerr << "Failed to get the function pointer for GetCurrentMode\n";
        return NULL;
    }

    int num = func();
    return num;
}

void AutPI_AddBoss(BOSSFUNCTION func, char* author, char* name)
{
    typedef void (*AutPI_AddBossFunc)(BOSSFUNCTION, char*, char*);
    AutPI_AddBossFunc addBossFunc = reinterpret_cast<AutPI_AddBossFunc>(
        GetProcAddress(autpiDLL, "AutPI_AddBoss"));

    if (addBossFunc == nullptr) {
        std::cerr << "Failed to get the function pointer for AutPI_AddBoss\n";
        return;
    }

    addBossFunc(func, author, name);
}

void AutPI_AddCaret(CARETFUNCTION func, char* author, char* name)
{
    typedef void (*AutPI_AddCaretFunc)(CARETFUNCTION, char*, char*);
    AutPI_AddCaretFunc addCaretFunc = reinterpret_cast<AutPI_AddCaretFunc>(
        GetProcAddress(autpiDLL, "AutPI_AddCaret"));

    if (addCaretFunc == nullptr) {
        std::cerr << "Failed to get the function pointer for AutPI_AddCaret\n";
        return;
    }

    addCaretFunc(func, author, name);
}

void AutPI_AddEntity(NPCFUNCTION func, char* author, char* name)
{
    typedef void (*AutPI_AddEntityFunc)(NPCFUNCTION, char*, char*);
    AutPI_AddEntityFunc addEntityFunc = reinterpret_cast<AutPI_AddEntityFunc>(
        GetProcAddress(autpiDLL, "AutPI_AddEntity"));

    if (addEntityFunc == nullptr) {
        std::cerr << "Failed to get the function pointer for AutPI_AddEntity\n";
        return;
    }

    addEntityFunc(func, author, name);
}

// Function to load autpi.dll
void LoadAutPiDll()
{
    autpiDLL = LoadLibrary("autpi.dll");
    if (autpiDLL == nullptr) {
        std::cerr << "Failed to load autpi.dll\n";
        // You might want to handle the error appropriately, e.g., throw an exception or return early.
    }
}


std::vector<PreModeElementHandler> premodeElementHandlers;
std::vector<ReleaseElementHandler> releaseElementHandlers;

std::vector<GetTrgElementHandler> gettrgElementHandlers;

std::vector<OpeningBelowFadeElementHandler> Opening_belowfadeElementHandlers;
std::vector<OpeningAboveFadeElementHandler> Opening_abovefadeElementHandlers;
std::vector<OpeningBelowTextBoxElementHandler> Opening_belowtextboxElementHandlers;
std::vector<OpeningAboveTextBoxElementHandler> Opening_abovetextBoxElementHandlers;
std::vector<OpeningEarlyActionElementHandler> Opening_earlyactionElementHandlers;
std::vector<OpeningActionElementHandler> Opening_actionElementHandlers;
std::vector<OpeningInitElementHandler> Opening_initElementHandlers;

std::vector<TitleInitElementHandler> Title_initElementHandlers;
std::vector<TitleActionElementHandler> Title_actionElementHandlers;
std::vector<TitleBelowCounterElementHandler> Title_belowcounterElementHandlers;

std::vector<PlayerHudElementHandler> playerhudElementHandlers;
std::vector<CreditsHudElementHandler> creditshudElementHandlers;
std::vector<BelowFadeElementHandler> belowfadeElementHandlers;
std::vector<AboveFadeElementHandler> abovefadeElementHandlers;
std::vector<BelowTextBoxElementHandler> belowtextboxElementHandlers;
std::vector<AboveTextBoxElementHandler> abovetextboxElementHandlers;
std::vector<BelowPlayerElementHandler> belowplayerElementHandlers;
std::vector<AbovePlayerElementHandler> aboveplayerElementHandlers;
std::vector<EarlyActionElementHandler> earlyactionElementHandlers;
std::vector<ActionElementHandler> actionElementHandlers;
std::vector<CreditsActionElementHandler> creditsactionElementHandlers;
std::vector<InitElementHandler> initElementHandlers;

std::vector<SaveProfilePreWriteElementHandler> saveprofileprewriteElementHandlers;
std::vector<SaveProfilePostWriteElementHandler> saveprofilepostwriteElementHandlers;
std::vector<LoadProfilePreCloseElementHandler> loadprofileprecloseElementHandlers;
std::vector<LoadProfilePostCloseElementHandler> loadprofilepostcloseElementHandlers;
std::vector<InitializeGameInitElementHandler> intializegameElementHandlers;

std::vector<PutFPSElementHandler> putfpsElementHandlers;

std::vector<TextScriptSVPElementHandler> textscriptsvpElementHandlers;

std::vector<TransferStageInitElementHandler> transferstageinitElementHandlers;

std::vector<LuaPreGlobalModCSElementHandler> preglobalmodcsElementHandlers;
std::vector<LuaMetadataElementHandler> luametadataElementHandlers;
std::vector<LuaFuncElementHandler> luafuncElementHandlers;

// Game() API

void RegisterPreModeElement(PreModeElementHandler handler)
{
    RegisterElement(premodeElementHandlers, "RegisterPreModeElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterReleaseElement(ReleaseElementHandler handler)
{
    RegisterElement(releaseElementHandlers, "RegisterReleaseElement", reinterpret_cast<void (*)()>(handler));
}

// GetTrg() API

void RegisterGetTrgElement(GetTrgElementHandler handler)
{
    RegisterElement(gettrgElementHandlers, "RegisterGetTrgElement", reinterpret_cast<void (*)()>(handler));
}

// ModeOpening() API

void RegisterOpeningBelowFadeElement(OpeningBelowFadeElementHandler handler)
{
    RegisterElement(Opening_belowfadeElementHandlers, "RegisterOpeningBelowFadeElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterOpeningAboveFadeElement(OpeningAboveFadeElementHandler handler)
{
    RegisterElement(Opening_abovefadeElementHandlers, "RegisterOpeningAboveFadeElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterOpeningBelowTextBoxElement(OpeningBelowTextBoxElementHandler handler)
{
    RegisterElement(Opening_belowtextboxElementHandlers, "RegisterOpeningBelowTextBoxElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterOpeningAboveTextBoxElement(OpeningAboveTextBoxElementHandler handler)
{
    RegisterElement(Opening_abovetextBoxElementHandlers, "RegisterOpeningAboveTextBoxElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterOpeningEarlyActionElement(OpeningEarlyActionElementHandler handler)
{
    RegisterElement(Opening_earlyactionElementHandlers, "RegisterOpeningEarlyActionElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterOpeningActionElement(OpeningActionElementHandler handler)
{
    RegisterElement(Opening_actionElementHandlers, "RegisterOpeningActionElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterOpeningInitElement(OpeningInitElementHandler handler)
{
    RegisterElement(Opening_initElementHandlers, "RegisterOpeningInitElement", reinterpret_cast<void (*)()>(handler));
}

// ModeTitleAPI

void RegisterTitleInitElement(TitleInitElementHandler handler)
{
    RegisterElement(Title_initElementHandlers, "RegisterTitleInitElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterTitleActionElement(TitleActionElementHandler handler)
{
    RegisterElement(Title_actionElementHandlers, "RegisterTitleActionElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterTitleBelowCounterElement(TitleBelowCounterElementHandler handler)
{
    RegisterElement(Title_belowcounterElementHandlers, "RegisterTitleBelowCounterElement", reinterpret_cast<void (*)()>(handler));
}

// ModeActionAPI

void RegisterPlayerHudElement(PlayerHudElementHandler handler)
{
    RegisterElement(playerhudElementHandlers, "RegisterPlayerHudElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterCreditsHudElement(CreditsHudElementHandler handler)
{
    RegisterElement(creditshudElementHandlers, "RegisterCreditsHudElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterBelowFadeElement(BelowFadeElementHandler handler)
{
    RegisterElement(belowfadeElementHandlers, "RegisterBelowFadeElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterAboveFadeElement(AboveFadeElementHandler handler)
{
    RegisterElement(abovefadeElementHandlers, "RegisterAboveFadeElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterBelowTextBoxElement(BelowTextBoxElementHandler handler)
{
    RegisterElement(belowtextboxElementHandlers, "RegisterBelowTextBoxElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterAboveTextBoxElement(AboveTextBoxElementHandler handler)
{
    RegisterElement(abovetextboxElementHandlers, "RegisterAboveTextBoxElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterBelowPlayerElement(BelowPlayerElementHandler handler)
{
    RegisterElement(belowplayerElementHandlers, "RegisterBelowPlayerElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterAbovePlayerElement(AbovePlayerElementHandler handler)
{
    RegisterElement(aboveplayerElementHandlers, "RegisterAbovePlayerElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterEarlyActionElement(EarlyActionElementHandler handler)
{
    RegisterElement(earlyactionElementHandlers, "RegisterEarlyActionElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterActionElement(ActionElementHandler handler)
{
    RegisterElement(actionElementHandlers, "RegisterActionElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterCreditsActionElement(CreditsActionElementHandler handler)
{
    RegisterElement(creditsactionElementHandlers, "RegisterCreditsActionElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterInitElement(InitElementHandler handler)
{
    RegisterElement(initElementHandlers, "RegisterInitElement", reinterpret_cast<void (*)()>(handler));
}

// Profile API

void RegisterSaveProfilePreWriteElement(SaveProfilePreWriteElementHandler handler)
{
    RegisterElement(saveprofileprewriteElementHandlers, "RegisterSaveProfilePreWriteElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterSaveProfilePostWriteElement(SaveProfilePostWriteElementHandler handler)
{
    RegisterElement(saveprofilepostwriteElementHandlers, "RegisterSaveProfilePostWriteElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterLoadProfilePreCloseElement(LoadProfilePreCloseElementHandler handler)
{
    RegisterElement(loadprofileprecloseElementHandlers, "RegisterLoadProfilePreCloseElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterLoadProfilePostCloseElement(LoadProfilePostCloseElementHandler handler)
{
    RegisterElement(loadprofilepostcloseElementHandlers, "RegisterLoadProfilePostCloseElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterInitializeGameInitElement(InitializeGameInitElementHandler handler)
{
    RegisterElement(intializegameElementHandlers, "RegisterInitializeGameInitElement", reinterpret_cast<void (*)()>(handler));
}

// PutFPS API

void RegisterPutFPSElement(PutFPSElementHandler handler)
{
    RegisterElement(putfpsElementHandlers, "RegisterPutFPSElement", reinterpret_cast<void (*)()>(handler));
}

// TextScript API

void RegisterSVPElement(TextScriptSVPElementHandler handler)
{
    RegisterElement(textscriptsvpElementHandlers, "RegisterSVPElement", reinterpret_cast<void (*)()>(handler));
}

// TransferStage API

void RegisterTransferStageInitElement(TransferStageInitElementHandler handler)
{
    RegisterElement(transferstageinitElementHandlers, "RegisterTransferStageInitElement", reinterpret_cast<void (*)()>(handler));
}

// Lua API
typedef lua_State* (*GetLuaLFunc)();

lua_State* GetLuaL()
{
    // Load GetLuaL function pointer from the DLL
    GetLuaLFunc getLuaLFunc = reinterpret_cast<GetLuaLFunc>(
        GetProcAddress(autpiDLL, "GetLuaL"));

    if (getLuaLFunc == nullptr) {
        std::cerr << "Failed to get the function pointer for GetLuaL\n";
        return nullptr;
    }

    // Call GetLuaL function to retrieve lua_State*
    lua_State* luaL = getLuaLFunc();
    return luaL; // Return the lua_State* obtained from GetLuaL
}

BOOL ReadStructBasic(lua_State* L, const char* name, STRUCT_TABLE* table, void* data, int length)
{
    typedef BOOL (*ReadStructBasicFunc)(lua_State*, const char*, STRUCT_TABLE*, void*, int);

    ReadStructBasicFunc Func = reinterpret_cast<ReadStructBasicFunc>(
        GetProcAddress(autpiDLL, "ReadStructBasic"));

    if (Func == nullptr) {
        std::cerr << "Failed to get the function pointer for ReadStructBasic\n";
        return FALSE;
    }

    Func(L, name, table, data, length);
}

BOOL Write2StructBasic(lua_State* L, const char* name, STRUCT_TABLE* table, void* data, int length)
{
    typedef BOOL(*Write2StructBasicFunc)(lua_State*, const char*, STRUCT_TABLE*, void*, int);

    Write2StructBasicFunc Func = reinterpret_cast<Write2StructBasicFunc>(
        GetProcAddress(autpiDLL, "Write2StructBasic"));

    if (Func == nullptr) {
        std::cerr << "Failed to get the function pointer for Write2StructBasic\n";
        return FALSE;
    }

    Func(L, name, table, data, length);
}

void PushFunctionTable(lua_State* L, const char* name, const FUNCTION_TABLE* table, int length, BOOL pop)
{
    typedef void(*PushFunctionTableFunc)(lua_State*, const char*, const FUNCTION_TABLE*, int, BOOL);

    PushFunctionTableFunc Func = reinterpret_cast<PushFunctionTableFunc>(
        GetProcAddress(autpiDLL, "PushFunctionTable"));

    if (Func == nullptr) {
        std::cerr << "Failed to get the function pointer for PushFunctionTable\n";
        return;
    }

    Func(L, name, table, length, pop);
}

void PushFunctionTableModName(lua_State* L, const char* modname, const char* name, const FUNCTION_TABLE* table, int length, BOOL pop)
{
    typedef void(*PushFunctionTableFunc)(lua_State*, const char*, const char*, const FUNCTION_TABLE*, int, BOOL);

    PushFunctionTableFunc Func = reinterpret_cast<PushFunctionTableFunc>(
        GetProcAddress(autpiDLL, "PushFunctionTableModName"));

    if (Func == nullptr) {
        std::cerr << "Failed to get the function pointer for PushFunctionTableModName\n";
        return;
    }

    Func(L, modname, name, table, length, pop);
}

void PushSimpleMetatables(lua_State* L, const METATABLE_TABLE* table, int length)
{
    typedef void(*PushSimpleMetatablesFunc)(lua_State*, const METATABLE_TABLE*, int);

    PushSimpleMetatablesFunc Func = reinterpret_cast<PushSimpleMetatablesFunc>(
        GetProcAddress(autpiDLL, "PushSimpleMetatables"));

    if (Func == nullptr) {
        std::cerr << "Failed to get the function pointer for PushSimpleMetatables\n";
        return;
    }

    Func(L, table, length);
}

void RegisterLuaPreGlobalModCSElement(LuaPreGlobalModCSElementHandler handler)
{
    RegisterElement(preglobalmodcsElementHandlers, "RegisterLuaPreGlobalModCSElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterLuaMetadataElement(LuaMetadataElementHandler handler)
{
    RegisterElement(luametadataElementHandlers, "RegisterLuaMetadataElement", reinterpret_cast<void (*)()>(handler));
}

void RegisterLuaFuncElement(LuaFuncElementHandler handler)
{
    RegisterElement(luafuncElementHandlers, "RegisterLuaFuncElement", reinterpret_cast<void (*)()>(handler));
}