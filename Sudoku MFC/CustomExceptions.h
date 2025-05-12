#pragma once

#include <stdexcept>
#include <string>

class SpriteLoadException : public std::exception 
{
private:
    std::string message;

public:
    SpriteLoadException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override 
    {
		std::string errorMessage = "Sprite Load Exception: " + message;
		return errorMessage.c_str();
    }
};

class FileStreamException : public std::exception
{
private:
    std::string message;

public:
    FileStreamException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override
    {
        std::string errorMessage = "File Stream Exception: " + message;
        return errorMessage.c_str();
    }
};

class MemoryAllocationException : public std::exception
{
private:
    std::string message;

public:
    MemoryAllocationException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override
    {
        std::string errorMessage = "Memory Allocation Exception: " + message;
        return errorMessage.c_str();
    }
};

