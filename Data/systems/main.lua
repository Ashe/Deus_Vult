local combatSystem = require("Data.systems.combatSystem")

local showCode = false
local playerInCombatMode = false

local handleInput = function(e, key, isDown)
	if isDown then
		if showCode then
			print("Key pressed: " .. key)
		end

		if key == 0 then
			mc_move(e, false)
		elseif key == 3 then
			mc_move(e, true)
		end


		if key == 57 then
			playerInCombatMode = combatSystem["toggleCombat"](e)
		elseif playerInCombatMode == false then
			if key == 4 then
				ic_interact(e)
			elseif key == 38 then
				mc_setSpeed(e, 2)

			 -- DEBUGGING
			elseif key == 37 then
				showCode = true
				print("Key pressed: " .. key)
			end
			-- END DEBUG
		else
			combatSystem["handleInput"](e, key, isDown)
		end
	else
		if showCode then
			print("Key released: " .. key)
		end

		if key == 0 then
			mc_move(e, true)
		elseif key == 3 then
			mc_move(e, false)
		end

		if playerInCombatMode == false then
			if key == 38 then
				mc_setSpeed(e, 1)

			-- DEBUGGING
			elseif key == 37 then
				showCode = false
			end
			-- END DEBUG
		else
			combatSystem["handleInput"](e, key, isDown)
		end
	end
end

local mainTable = {
	handleInput = handleInput
}

return mainTable