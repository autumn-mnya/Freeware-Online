function ModCS.Game.Init()
	if ModCS.Netplay.Enabled() then
		-- do smth here once at the start of a game "loop"
	end
end

function ModCS.Game.Act()
	if ModCS.Game.GetMode() == 3 and ModCS.Netplay.InServer() then
		-- Change weapon ID when press shift
		if ModCS.Key.Shift() then
			if ModCS.Arms.GetCurrent().id >= 13 then
				ModCS.Arms.GetCurrent().id = 1
			else
				ModCS.Arms.GetCurrent().id = ModCS.Arms.GetCurrent().id + 1
			end
		end
	
		-- Send packet ID of our current weapon
		if ModCS.Key.Shoot() then
			ModCS.ENet.sendPacketID(20 + ModCS.Arms.GetCurrent().id)
		end
	end
end

function ModCS.Game.Draw()
	ModCS.PutText(ModCS.Netplay.GetSpecialPacketData(), 0, 0)
end

function ModCS.Tsc.Command.NPJ()
	local event = ModCS.Tsc.GetArgument(1)

	if (ModCS.Netplay.Enabled) then
		ModCS.Tsc.Jump(event)
	end
end

function ModCS.Netplay.ActClient()
	-- Hell, printing the weapon ID of the weapon we're holding
	if ModCS.Netplay.eventCode() == 20 then
		print("ModCS Weapon 0")
	elseif ModCS.Netplay.eventCode() == 21 then
		print("ModCS Weapon Snake")
	elseif ModCS.Netplay.eventCode() == 22 then
		print("ModCS Weapon Polar Star")
	elseif ModCS.Netplay.eventCode() == 23 then
		print("ModCS Weapon Fireball")
	elseif ModCS.Netplay.eventCode() == 24 then
		print("ModCS Weapon Machine Gun")
	elseif ModCS.Netplay.eventCode() == 25 then
		print("ModCS Weapon Missile Launcher")
	elseif ModCS.Netplay.eventCode() == 26 then
		print("ModCS Weapon 6")
	elseif ModCS.Netplay.eventCode() == 27 then
		print("ModCS Weapon Bubbler")
	elseif ModCS.Netplay.eventCode() == 28 then
		print("ModCS Weapon 8")
	elseif ModCS.Netplay.eventCode() == 29 then
		print("ModCS Weapon Blade")
	elseif ModCS.Netplay.eventCode() == 30 then
		print("ModCS Weapon Super Missile Launcher")
	elseif ModCS.Netplay.eventCode() == 31 then
		print("ModCS Weapon 11")
	elseif ModCS.Netplay.eventCode() == 32 then
		print("ModCS Weapon Nemesis")
	elseif ModCS.Netplay.eventCode() == 33 then
		print("ModCS Weapon Spur")
	end
	
	if ModCS.Netplay.specialEventCode() == 1 then
		print(ModCS.Netplay.GetSpecialPacketData())
	end
end