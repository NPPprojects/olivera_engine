#include <memory>
#include <list>
#include<vector>
class  Entity;
class  Core;

class Component
{
private:
	std::weak_ptr<Entity> entity;

	void onInitialise();
	void onStart();
	void onTick();
	void onDisplay();

public:
	std::shared_ptr<Entity> getEntity();
	std::shared_ptr<Core> getCore();

	template<typename T>
	std::shared_ptr<T> AddComponent()
	{
		std::shared_ptr<T> t = make_shared<T>();
		components.push_back(t);

		return (t);
	}
	template<typename T, typename A>
	std::shared_ptr<T>AddComponent(A a)
	{
		std::shared_ptr<T> t = make_shared<T>(a);
		components.push_back(t);
		
		return t;
	}
	template<typename T, typename A, typename B>
	std::shared_ptr<T>AddComponent(A a, B b)
	{
		std::shared_ptr<T> t = make_shared<T>(a,b);
		components.push_back(t);

		return t;
	}

	template<typename T, typename A, typename B, typename C>
	std::shared_ptr<T> AddComponent(A a, B b, C c)
	{
		std::shared_ptr<T> t = make_shared<T>(a, b, c);
		components.push_back(t);

		return t;
	}
	


};