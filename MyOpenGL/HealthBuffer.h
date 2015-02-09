#pragma once
class HealthBuffer
{
public:
	HealthBuffer(int _health, int _maxHealth) : health(_health), maxHealth(_maxHealth) {

	}
	~HealthBuffer(void) {

	}
	int getHealth() {
		return health;
	}
	int getMaxHealth() {
		return maxHealth;
	}
	void hit(int value) {
		health -= value;
	}
	void setHealth(int value) {
		health = value;
	}


private:
	
	int health;
	int maxHealth;
};

