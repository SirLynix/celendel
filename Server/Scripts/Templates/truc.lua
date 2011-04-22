vari = 0

function onInit(this)
	this:sendMessageToGM("Init");
end

function onDeath(this)
	this:sendMessageToGM("Death");
end

function onUpdate(this, ti)
	this:sendMessageToGM("To the outside ! Int = " .. vari);
	vari = vari+1;
	if vari > 10 then
		vari=0;
	end
end
