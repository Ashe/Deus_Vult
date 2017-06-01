local init = function (e)
print("INIT FUNCTION:")
printPhrase(e)
end

local update = function(e, dTime) 
--print("EVERY FRAME SPAM")
end

local interact = function (e)
print("INTERACT FUNCTION")
printPhrase(e)
end

local functionsTable = {
	init = init,
	update = update,
	interact = interact
}

return functionsTable