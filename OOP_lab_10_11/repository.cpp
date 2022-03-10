#include "repository.h"
#include "errors.h"
#include <algorithm>
#include <iterator>

size_t Repository::size() const noexcept {
	return list.size();
}

void Repository::add_book(const Book& book) {
	const auto  book_to_add = std::find_if(this->list.begin(), this->list.end(), [&book](const Book& curent_book) noexcept 
		{return curent_book == book; });
	if (book_to_add != this->list.end())
		throw RepositoryError("carte existenta!");
	else
		list.push_back(book);
}

Book Repository::delete_book(const Book& book) {
	auto  book_to_delete = std::find_if(this->list.begin(), this->list.end(), [&book](const Book& curent_book) noexcept 
		{return curent_book == book; });
	if (book_to_delete == this->list.end())
		throw RepositoryError("carte inexistenta!");
	else
	{	
		Book copy_book = *book_to_delete;
		list.erase(book_to_delete);
		return copy_book;}}

const Book& Repository::find_book(const Book& book) {
	auto  book_to_find = std::find_if(this->list.begin(), this->list.end(), [&book](const Book& curent_book) noexcept 
		{return curent_book == book; });
	if (book_to_find == this->list.end())
		throw RepositoryError("carte inexistenta!");
	else
		return *book_to_find;}

Book Repository::update_book(const Book& new_book) {
	auto  book_to_update = std::find_if(this->list.begin(), this->list.end(), [&new_book](const Book& curent_book) noexcept 
		{return curent_book == new_book; });
	if (book_to_update == this->list.end())
		throw RepositoryError("carte inexistenta!");
	else
	{	
		Book copy_book = *book_to_update;
		*book_to_update = new_book;
		return copy_book;}}
	

Book const& Repository::get_book(int index) const {
	return this->list.at(index);
}

std::vector<Book> const& Repository::get_all() noexcept {
	return this->list;
}