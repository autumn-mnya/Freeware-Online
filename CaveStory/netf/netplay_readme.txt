#######################################################
### Kaitlyn's Wip port of CSE2 Online to mod loader ###
#######################################################

#########
# Setup #
#########

-Like any other Cave Story freeware DLL mod loader mod, you need to put the "mods" folder into your freeware directory after
installing the DLL mod loader. The latest release can be found here: https://github.com/Clownacy/Cave-Story-Mod-Loader/releases

-You'll want to copy the SDL2.dll file into your game directory as well -- Next to the game exe.

-Once the netplay folder has been moved into the mods folder and the SDL2.dll file into the game directory, you need to enable
the mod.

-Open "mods.txt" in the mods folder, and add "netplay" to the top of the list (making sure it loads first)

-Open the netplay folder, and change your player name in the settings.ini file.

-Once you're done, open the game and load! It will automatically load into the game with netplay.
It doesn't say if you disconnect, but if you notice that you did, pressing "period" will reconnect to the server incase
of an error like that ever happening.

###########
# Credits #
###########

CuckyDev / Clownacy / GabrielRavier - CSE2, CSE2 Online, and other code used.