local entity = {
    bruh = {
		Tags = {
			"npc"
		},
        SpineComponent = {
            dataIsJSON = false,
            atlas = "common/spine/goblins/export/goblins.atlas",
            data = "common/spine/goblins/export/goblins.skel",
            defaultAnim = "idle",
            timeScale = 1,
            defaultMix = 0.2,
            animations = {
                walk = {
                    animString = "walk"
                }
            },
			skin = "goblin"
        },
        TransformComponent = {
            position = {
                1300, 100
            },
            flipX = true,
            scale = {
                0.8, 0.8
            },
            rotation = 0
        },
        SensoryComponent = {
            range = 150
        },
        InteractionComponent = {
            showPrompt = true
        },
        NpcComponent = {
            facePlayer = true
        },
        OutlineComponent = {
            thickness = 8,
            colour = {255, 0, 0, 200},
            distanceStrong = 150,
            distanceWeak = 350
        },
        ScriptComponent = {
            script = "npcs/bruh/script.lua"
        }
    }
}

return entity
