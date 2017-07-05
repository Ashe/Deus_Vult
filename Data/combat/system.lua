local combatButtonPressed = function (e)
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

local functionsTable = {
	combatButtonPressed = combatButtonPressed
}

return functionsTable