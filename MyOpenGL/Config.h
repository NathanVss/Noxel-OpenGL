#pragma once
class Config
{
public:
	Config(void) {
		lighting = true;
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

