#pragma once
class Light
{
public:
	Light(void);
	virtual ~Light(void);

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	void setPosition(float _x, float _y) {
		x = _x;
		y = _y;
	}

protected:
	float x;
	float y;
};

