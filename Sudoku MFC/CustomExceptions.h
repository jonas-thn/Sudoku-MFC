#pragma once

#include <stdexcept>
#include <string>

class SpriteLoadException : public std::exception 
{
private:
    std::string message;
    std::string errorMessage;

public:
    SpriteLoadException(const std::string& msg) : message(msg) 
    {
        errorMessage = "Sprite Load Exception: " + message;
    }

    const char* what() const noexcept override 
    {
		return errorMessage.c_str();
    }
};

class FileStreamException : public std::exception
{
private:
    std::string message;
    std::string errorMessage;

public:
    FileStreamException(const std::string& msg) : message(msg) 
    {
        errorMessage = "File Stream Exception: " + message;
    }

    const char* what() const noexcept override
    {
        return errorMessage.c_str();
    }
};

class MemoryAllocationException : public std::exception
{
private:
    std::string message;
    std::string errorMessage;

public:
    MemoryAllocationException(const std::string& msg) : message(msg) 
    {
        errorMessage = "Memory Allocation Exception: " + message; 
    }

    const char* what() const noexcept override
    {
        return errorMessage.c_str();
    }
};

