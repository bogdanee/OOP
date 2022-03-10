#include "errors.h"

Error::Error(const std::string& message) :error_message{ message }, std::exception() {
}

const std::string& Error::get_error_message() const noexcept{
	return error_message;
}

