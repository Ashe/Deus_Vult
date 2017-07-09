local validStats = {
	health = {
		defaultValue = 100,
		display = {
			style = "bar",
			anchor = "topLeft",
			colours = {
				backFill = {255, 0, 0, 255},
				foreFill = {0, 255, 0, 255},
				border = {0, 0, 0, 255}
			}
		}
	},
	actionPoints = {
		defaultValue = 100,
		display = {
			style = "slots",
			anchor = "topLeft",
			colours = {
				activeFill = {255, 255, 255, 255},
				inactiveFill = {0, 0, 0, 0},
				posessBorder = {255, 255, 255, 255},
				maxAmountBorder = {255, 255, 255, 100}
			}
		}
	}
}

local combatFunc = function (e)
	if cc_isInCombat(e) == false then
		print("Activate Combat!")
		mc_setLockMovement(e, true)
		mc_moveToMidpoint(e)
		cc_setInCombat(e, true)
	else
		print("Combat Deactivated.")
		mc_setLockMovement(e, false)
		cc_setInCombat(e, false)
	end
end

local combatTable = {
	validStats = validStats,
	combatFunc = combatFunc
}

return combatTable