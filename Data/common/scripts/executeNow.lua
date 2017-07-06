print("Loading the map!")
changeMap("maps/testmap.lua")

print("Creating the an entity with pure lua!")
loadEntity("player/player.lua")

print("Now creating an NPC.")
loadEntity("npcs/bruh/bruh.lua")

print("Testing ping")
pingTag("Woo!", "npc")

print("Done!")