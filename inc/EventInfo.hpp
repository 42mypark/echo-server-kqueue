#if !defined(EventInfo_hpp)
#define EventInfo_hpp

#include <sys/wait.h>

#include <sstream>

class Parser;

class EventInfo {
 private:
  const int         _to_fd;
  int               _from_fd;
  std::stringstream _storage;
  bool              _empty_line;
  pid_t             _pid;

 public:
  EventInfo(int to_fd, int from_fd) : _to_fd(to_fd), _from_fd(from_fd), _empty_line(false) {}
  const int          toFd() const { return _to_fd; }
  pid_t&             pid() { return _pid; }
  int&               fromFd() { return _from_fd; }
  bool&              emptyLine() { return _empty_line; }
  std::stringstream& storage() { return _storage; }
};

#endif  // EventInfo_hpp