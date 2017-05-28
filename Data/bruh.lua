bruh = {
    GraphicsComponent = {
        filename = "img/BlackKnight.png",
		size = {32, 32},
		defaultAnim = "idle",
		animations = {
			idle = {
				frameTime = 70,
				animation = {
					{0, 0},
					{32, 0},
					{64, 0},
					{96, 0},
					{128, 0},
					{160, 0},
					{192, 0},
					{224, 0},
					{256, 0},
					{288, 0}
				}
			},
			walk = {
				frameTime = 70,
				animation = {
					{0, 64},
					{32, 64},
					{64, 64},
					{96, 64},
					{128, 64},
					{160, 64},
					{192, 64},
					{224, 64},
					{256, 64},
					{288, 64}
				}
			}
		}
    },
	TransformComponent = {
		position = {
			500, 300
		},
		flipX = true,
		scale = {
			5, 5
		}, 
		rotation = 0
	},
    NpcComponent = {
        phrase = "Bruh."
    }
}