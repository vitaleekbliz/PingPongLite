#pragma once
#include "TextureSubscriber.h"
#include <SDL3/SDL.h>
#include <memory>

class TexturePublisher
{ 
	public:
	void addListener(std::weak_ptr<TextureSubscriber> listener);
	 void removeListener();

  private:
	  virtual void requestDraw() = 0;
	  std::weak_ptr<TextureSubscriber> subscriber;
};
