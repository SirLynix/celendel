description = "Un humain un peu étrange..."
work = "Heros à plein temps"
name = "Jean-Claude"
class = "Paysan"
age = 23
player = ""

attributes = {}
attributes["force"] = 1
attributes["inteligence"] = 5
attributes["charisme"] = -50
attributes["endurance"] = 3

data = {}
data["description"] = "Description"
data["name"] = "Nom"
data["work"] = "Travail"
data["class"] = "Classe"
data["age"] = "Âge"
data["attributes"] = "Attributs"
data["player"] = "Joueur"
data["languages"] = "Langues"

languages = {}
languages["Commun"] = 100

function once(this)
	this:registerAsCharacter("ShadicMoimeme");
end

function onDeath(this)
	
end

function onUpdate(this, ti)
	
end

