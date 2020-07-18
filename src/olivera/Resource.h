#ifndef OLIVERA_RESOURCE_H
#define OLIVERA_RESOURCE_H

#include <memory>
#include <string>

namespace olivera
{
  /********************************************************
  @brief Base class for all resources.

  *when a resource is loaded a string is attached to it
  so that the resource can be refrenced using it.

  *********************************************************/
	class Resource
	{
	  public:
    /**********************
    @brief Getter for name

    ***********************/
	    std::string getName();

    /**********************
    @brief Setter for name

    ***********************/
	    void setName(std::string _name);
      
     /**********************
     @brief Setter for name

     ***********************/
      std::string getPath();

    /**********************
    @brief Setter for path
      
    ***********************/
      void setPath(std::string _path);

    /*******************************************************
    @brief virtual destructor to be used by derived classes

    ********************************************************/
	  virtual ~Resource() {}


	  private:
    /**************************************************************/

		  std::string name;                     //!<Resource's name tag
      std::string path;                        //!<Path to resource

    /**************************************************************/
	};
}

#endif