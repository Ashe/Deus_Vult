--local combatSystem = require("combatSystem")

local showCode = false

local handleInput = function(e, key, isDown)
	if isDown then
		if showCode then
			print("Key pressed: " .. key)
		end
		--combatSystem["combatFunc"](e)

		if key == 0 then
			mc_move(e, false)
		elseif key == 3 then
			mc_move(e, true)
		elseif key == 4 then
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
		if showCode then
			print("Key released: " .. key)
		end

		if key == 0 then
			mc_move(e, true)
		elseif key == 3 then
			mc_move(e, false)
		elseif key == 38 then
			mc_setSpeed(e, 1)

		-- DEBUGGING
		elseif key == 37 then
			showCode = false
		end
		-- END DEBUG
	end
end

local table = {
	handleInput = handleInput
}

return table