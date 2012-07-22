vari = 0;
description = "Je suis un objet pointu !"
name = "Cure-dent Durandil"

data = {}
data[description] = "description"
data[name] = "name"

function onInit(this)
	this:sendMessageToGM("Init");
end

function onDeath(this)
	this:sendMessageToGM("Death");
end

function onUpdate(this, ti)
	if vari < 10 then
		this:sendMessageToGM("To the outside ! Int = " .. vari);
		vari = vari+1;
	end
end

