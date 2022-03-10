#include "validator.h"
#include "errors.h"

void validate_book(const Book& book) {
	if (book.get_id() < 0)
		throw ValidatorError{ "id invalid!" };
	if (size(book.get_title()) == 0) 
		throw ValidatorError{ "titlu invalid!" };
	if (size(book.get_author()) == 0)  
		throw ValidatorError{ "autor invalid!" };
	if (size(book.get_gen()) == 0) 
		throw ValidatorError{ "gen invalid!" };
	if (book.get_year() >=2022 || book.get_year() <= -3000) 
		throw ValidatorError{ "an invalid!" };
}