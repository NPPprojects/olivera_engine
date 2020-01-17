#ifndef OLIVERA_RESOURCE_H
#define OLIVERA_RESOURCE_H

#include <memory>
#include <string>

namespace olivera
{
  /**
 *\ Base class for all Resources
 */
	class Resource
	{
	public:
  /**
  *\ Getter for a Resource's name
  */
	std::string getName();

  /**
  *\ Setter for a Resource's name
  */
	void setName(std::string _name);
  /**
  *\ virtual destructor
  */
	virtual ~Resource() {}


	private:
		std::string name;///<Resource's name tag
	};
}

#endif