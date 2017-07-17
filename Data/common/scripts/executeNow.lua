print("Loading the map!")
changeMap("maps/testmap.lua")

print("Creating the player entity with pure lua!")
loadEntity("player/player.lua")

print("Now creating an NPC..")
loadEntity("npcs/bruh/bruh.lua")
loadEntity("npcs/bruh/bruh(sprite).lua")

print("Now creating a training dummy..")
loadEntity("enemies/dummy/dummy.lua")

print("Testing ping")
pingTag("Woo!", "npc")

print("Done!")