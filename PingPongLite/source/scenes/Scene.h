#pragma once
class Scene
{
  public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void init() = 0;
	virtual void close() = 0;

	bool isRunning() const;

  protected:
	bool isActive = true;
};
