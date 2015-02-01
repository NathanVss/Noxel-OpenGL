#pragma once
class Config
{
public:
	Config(void) {
		lighting = false;
	};
	~Config(void) {

	};

	void setLighting(bool _flag) {
		lighting = _flag;
	}
	bool getLighting() {
		return lighting;
	}


private:
	bool lighting;
};

