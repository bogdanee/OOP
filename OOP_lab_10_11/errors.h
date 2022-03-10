#pragma once
#include <exception>
#include <string>

class Error :public std::exception {

protected:
	std::string error_message;

public:
	Error(const std::string& error_message);
	const std::string& get_error_message() const noexcept;
};

class RepositoryError :public Error {
public:
	RepositoryError(const std::string& error_message) : Error(error_message) {};
};

class ValidatorError :public Error {
public:
	ValidatorError(const std::string& error_message) : Error(error_message) {};
};

class ServiceError :public Error {
public:
	ServiceError(const std::string& error_message) : Error(error_message) {};
};