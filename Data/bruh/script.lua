local convNo = 0

local convos = {
	[0] = "Hello there!",
	[1] = "How is it going?",
	[2] = "Why are you still here?",
	[3] = "Quit that!",
	[4] = "Beat it, chump."
}

local init = function (e)
	print("Init function: Nothing")
end

--local update = function(e, dTime) 
	--print("EVERY FRAME SPAM")
--end

local interact = function (e)
	-- The prompt will be shown due to bruh.lua allowing it
	if convNo < 5 then
		setMessage(e, convos[convNo])
	end

	enableIntPrompt(e, false)
	if convNo < 4 then
		convNo = convNo + 1
		enableIntPrompt(e, true)
	end
end

local inRange = function (e)
	print("Player is in range: Reset Conversations")
	if convNo < 4 then
		convNo = 0
		sayMessage(e, "Pssst! Over here!")
		enableIntPrompt(e, true)
	elseif convNo == 4 then
		sayMessage(e, "Fuck off.")
		convNo = 5
	else
		sayMessage(e, "Eh, I'm sorry.")
		convNo = 0
		enableIntPrompt(e, true)
	end
end

local outRange = function (e)
	print("Player is out of range: End conversation")
	setShowMessage(e, false)
end

local functionsTable = {
	init = init,
	update = update,
	interact = interact,
	inRange = inRange,
	outRange = outRange
}

return functionsTable