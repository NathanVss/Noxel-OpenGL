#pragma once

namespace YuEngine {
class Renderable
{
public:
	Renderable(void);
	virtual ~Renderable(void);
	virtual void render() = 0;
};


}