#include <memory>
#include <list>
#include<vector>
class Component;
class  Core;

class Entity
{
private:
	std::list<std::shared_ptr<Component>> components;
	std::weak_ptr<Core> core;
	
	void tick();
	void display();

public:
	std::shared_ptr<Core> getCore();
	

};


//#endif