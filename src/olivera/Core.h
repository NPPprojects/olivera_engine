//#ifndef _CORE_H_
//#define _CORE_H_


#include <memory>
#include <list>

class Entity;


class Core 
{
private:

	std::list<std::shared_ptr<Entity>> entity;

	bool running;
public:
	static std::shared_ptr<Core> initialise();
	void start();
	void stop();

	std::shared_ptr<Entity> addEntity();
};

