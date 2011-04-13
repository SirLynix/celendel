description = "Un garde nain grognon"
work = "Garde"
name = "Orik Grimson"

data = {}
data["description"] = "description"
data["name"] = "name"
data["work"] = "work"


function once(this)
	this:registerAsCharacter();
	this:sendMessageToGM("Init");
end

function onDeath(this)
	
end

function onUpdate(this, ti)
	
end

