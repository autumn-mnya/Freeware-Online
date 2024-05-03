function ModCS.Game.Init()
	if ModCS.Netplay.Enabled() then
		-- do smth here once at the start of a game "loop"
	end
end

function ModCS.Game.Act()
	if ModCS.Game.GetMode() == 3 and ModCS.Netplay.InServer() then
		if ModCS.Key.Shoot() then
			ModCS.ENet.sendSpecialPacket(1, "This is a test to send packet data across the net.")
		end
	end
end

function ModCS.Tsc.Command.NPJ()
	local event = ModCS.Tsc.GetArgument(1)

	if (ModCS.Netplay.Enabled) then
		ModCS.Tsc.Jump(event)
	end
end

function ModCS.Netplay.ActClient()
	print("We received a packet!")
	if ModCS.Netplay.eventCode() == 20 then
		print("It was type 20!")
	end
	
	if ModCS.Netplay.specialEventCode() == 1 then
		print(ModCS.Netplay.GetSpecialPacketData())
	end
end