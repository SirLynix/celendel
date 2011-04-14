description = "Un humain un peu étrange..."
work = "Heros à plein temps"
name = "Noven"
player = "Gigotdarnaud"
class = "Magicien de combat"
age = 23

attributes = {}
attributes["force"] = 1
attributes["inteligence"] = 5
attributes["charisme"] = -50
attributes["endurance"] = 3

data = {}
data["description"] = "description"
data["name"] = "nom"
data["work"] = "travail"
data["player"] = "joueur"
data["class"] = "classe"
data["age"] = "age"
data["attributes"] = "attributs"


function once(this)
	this:registerAsCharacter();
end

function onDeath(this)
	
end

function onUpdate(this, ti)
	
end

