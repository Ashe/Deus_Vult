player = {
	ControllerComponent = {},
    GraphicsComponent = {
        filename = "img/BlackKnight.png",
		size = {32, 32},
		defaultAnim = "walk",
		frameTime = 80,
		animations = {
			walk = {
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
    },
	PositionComponent = {
		100, 100
	},
    NpcComponent = {
        phrase = "I'm a knight! GRR!"
    }
}
