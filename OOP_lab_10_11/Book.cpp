#include "Book.h"


Book::Book(int id_int, const std::string& title_string, const std::string& author_string, const std::string& gen_string, int year_int) 
	: id{ id_int }, title{ title_string }, author{ author_string }, gen{ gen_string }, year{ year_int }{
}


int Book::get_id() const noexcept{
	return id;
}

std::string Book::get_title() const {
	return title;
}

std::string Book::get_author() const {
	return author;
}

std::string Book::get_gen() const {
	return gen;
}

int Book::get_year() const noexcept {
	return year;
} 

bool Book::operator==(const Book& other_book) const noexcept {
	if (this->id != other_book.id) return false;
	return true;
}
