#include <exception>
#include <string>

class InsertException : public std::exception {
private:
    std::string message;

public:
    explicit InsertException(const std::string& msg) : message("Insert Exception: " + msg) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};
