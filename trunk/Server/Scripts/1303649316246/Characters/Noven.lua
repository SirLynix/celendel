description = "Un humain un peu étrange..."
work = "Heros à plein temps"
name = "Noven"
class = "Magicien de combat"
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
data["inventory"] = "Inventaire"

languages = {}
languages["Draconien"] = 100
languages["Commun"] = 97

inventory = {}
inventory["novenAxe"] = "Primary Weapon"
inventory["novenCristal"] = "Neck"
inventory["elficRope"] = "Backpack"

function once(this)
	this:registerAsCharacter("Gigotdarnaud");
end

function onDeath(this)
	
end

function onUpdate(this, ti)
	
end

