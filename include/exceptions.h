#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class ClosedWindowException : public std::exception {
  private:
    const char message[23] = "Window closed by user!";
  public:
    ClosedWindowException() {};
    const char* what() {
        return message;
    }  
};

#endif