local init = function (e)
print("Init function:")
printPhrase(e)
end

local update = function(e, dTime) 
--print("EVERY FRAME SPAM")
end

local interact = function (e)
print("Player has interacted")
printPhrase(e)
end

local inRange = function (e)
print("Player is in range!")
end

local outRange = function (e)
print("Player is out of range!")
end

local functionsTable = {
	init = init,
	update = update,
	interact = interact,
	inRange = inRange,
	outRange = outRange
}

return functionsTable