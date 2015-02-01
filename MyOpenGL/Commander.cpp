#include "Commander.h"
#include "Container.h"
#include "World.h"
#include "GameConsole.h"
#include "Player.h"
#include "Config.h"

#include <YuEngine\Camera2D.h>

#include <regex>

Commander::Commander(void)
{
}


Commander::~Commander(void)
{
}

void Commander::checkCommand(std::string cmd) {

	if(cmd == "/g") {
		myContainer->getWorld()->resetBlocks();
		myContainer->getWorld()->generate();
		myContainer->getGameConsole()->newEntry("Generating World ...");
	}
	if(cmd == "/camscale reset") {
		myContainer->getCamera()->setScale(1);
		myContainer->getGameConsole()->newEntry("Cam Scale : 1 ...");

	}
	if(cmd == "/fly") {
		myContainer->getGameConsole()->newEntry("BIRDS BE LIKE");
		myContainer->getPlayer()->setFly(true);
	}
	if(cmd == "/walk") {
		myContainer->getGameConsole()->newEntry("FROGS BE LIKE");
		myContainer->getPlayer()->setFly(false);
	}
	if(cmd == "/lighting off") {
		myContainer->getGameConsole()->newEntry("Lighting off");
		myContainer->getConfig()->setLighting(false);
	}
	if(cmd == "/lighting on") {
		myContainer->getGameConsole()->newEntry("And there was guit.. light.");
		myContainer->getConfig()->setLighting(true);
	}

	std::smatch match;
	std::regex teleportRegex("/teleport ([0-9]{1,}) ([0-9]{1,})");
	std::regex speedRegex("/speed ([0-9]{1,})");
	std::regex cameraScaleRegex("/camscale ([0-9.]{1,})");
	if(std::regex_search(cmd, match, teleportRegex)) {
		std::string sx = match[1];
		std::string sy = match[2];
		int x = stoi(sx);
		int y = stoi(sy);

		myContainer->getGameConsole()->newEntry(std::string("Teleporting [") + std::to_string(x) + std::string(";") + std::to_string(y) + std::string("] ..."));

		myContainer->getPlayer()->teleport(x, y);
	}
	if(std::regex_search(cmd, match, speedRegex)) {
		std::string sspeed = match[1];
		int speed = stoi(sspeed);

		myContainer->getGameConsole()->newEntry(std::string("Player speed : ") + std::to_string(speed));

		myContainer->getPlayer()->setSpeedX(speed);
	}
	if(std::regex_match(cmd, match, cameraScaleRegex)) {
		std::string sscale = match[1];
		float scale = stof(sscale);
		myContainer->getGameConsole()->newEntry(std::string("Camera Scale : ") + std::to_string(scale));
		myContainer->getCamera()->setScale(scale);

	}
	



}
