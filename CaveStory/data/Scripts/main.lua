function ModCS.Game.Init()
	if ModCS.Netplay.Enabled() then
		-- do smth here once at the start of a game "loop"
	end
end

function ModCS.Game.Act()
	if ModCS.Netplay.Enabled() then
		-- do smth here every frame
	end
end

function ModCS.Tsc.Command.NPJ()
	local event = ModCS.Tsc.GetArgument(1)

	if (ModCS.Netplay.Enabled) then
		ModCS.Tsc.Jump(event)
	end
end