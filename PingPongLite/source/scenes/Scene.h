#pragma once
class Scene
{
  public:
	virtual ~Scene() = default;
	virtual void run() {};

  protected:
	virtual void update() {};
	virtual void render() {};

	virtual void init() {};
	virtual void close() {};

	bool isRunning() const;

	bool isActive = true;
};
