#pragma once

#include <string>

namespace gx{

class Exception{
protected:
  std::string message; 

public:
  Exception(const std::string& message) noexcept : message(message) {}

  inline auto what() const noexcept -> const std::string&{
    return this->message;
  }
};

class FontException :public Exception{ 
public: 
  FontException(const std::string& message) noexcept : Exception("FontException: " + message) {} 
};

class FileException :public Exception{ 
public: 
  FileException(const std::string& message) noexcept : Exception("FileException: " + message) {} 
};

class TextureException :public Exception{ 
public: 
  TextureException(const std::string& message) noexcept : Exception("TextureException: " + message) {} 
};

class ShaderException :public Exception{ 
public: 
  ShaderException(const std::string& message) noexcept : Exception("ShaderException: " + message) {} 
};

class GLException :public Exception{ 
public: 
  GLException(const std::string& message) noexcept : Exception("GLException: " + message) {} 
};

}//namespace gx