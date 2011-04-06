-- the first program in every language
io.write("File \"test.lua\" running, ",_VERSION,"\n")

vari = 0

function onInit(this)
	this:sendMessageToGM("Init");
end

function onDeath(this)
	this:sendMessageToGM("Death");
end

function onUpdate(this, ti)
	--io.write("From the inside ! Elapsed : " .. ti .. "\n");
	this:sendMessageToGM("To the outside ! Int = " .. vari);
	vari = vari+1;
	if vari > 10 then
		vari=0;
	end
end




io.write("File \"test.lua\" ended\n")
