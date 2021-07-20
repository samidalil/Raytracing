#pragma once 

class IRenderContext {


public:
	virtual void init() = 0;
	virtual void preRender() = 0;
	virtual void render() = 0;
	virtual void postRender() = 0;
	virtual void terminate() = 0;
};

