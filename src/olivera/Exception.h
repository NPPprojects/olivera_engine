#include <exception>
#include <string>

namespace olivera
{

class Exception : public std::exception
{
public:
  Exception(const std::string& message);
  virtual ~Exception() throw();
  virtual const char* what() const throw();

private:
  std::string message;

};

void pollForError();

}
