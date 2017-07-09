local styles = {
	bar = {
		background = {
			layer = 0,
			shape = "rect",
			widthStart = 0,
			widthEnd = 100,
			outlineThickness = -8,
			colours = {
				fill = {
					tag = "backFill",
					default = {255, 0, 0, 255}
				},
				outline = {
					default = {180, 0, 0, 255}
				}
			}
		},
		foreground = {
			layer = 1,
			shape = "rect",
			widthStart = 0,
			widthEnd = 90,
			--widthEnd = "stat",
			outlineThickness = -3,
			colours = {
				fill = {
					tag = "foreFill",
					default = {0, 255, 0, 255}
				},
				outline = {
					default = {0, 180, 0, 255}
				}
			}	
		},
		frame = {
			layer = 2,
			shape = "rect",
			outlineThickness = -5, 
			colours = {
				fill = {
					default = {0, 0, 0, 0}
				},
				outline = {
					tag = "border",
					{255, 255, 255, 255}
				}
			}
		}
	},
	--slots = {
	
	--}
}

return styles