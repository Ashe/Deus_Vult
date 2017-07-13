local entity = {
    dummy = {
		Tags = {
			"enemy"
		},
        SpriteComponent = {
            filename = "enemies/dummy/Training_dummy.png",
            size = {122, 146}
        },
        TransformComponent = {
            position = {
                250, 300
            },
            scale = {1, 1},
            rotation = 0
        }
    }
}

return entity
