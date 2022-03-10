#include "LabRepository.h"
#include "errors.h"
#include <algorithm>
#include <iterator>
#include <random>
#include <time.h>

void LabRepository::generate_error() {
	std::random_device random;
	std::default_random_engine engine(random());
	std::uniform_real_distribution<float> distribution(0, 1);
	const float& random_number = distribution(engine);
	if (random_number < probability)
		throw RepositoryError("Exceptie!!");
}

size_t LabRepository::size() const noexcept {
	return new_list.size();
}

void LabRepository::add_book(const Book& book) {
	generate_error();
	for (const auto& book_pair : new_list)
	{
		if (book_pair.second == book)
			throw RepositoryError("carte existenta!");
	}
	new_list.insert(std::pair<int, Book>(book.get_id(), book));
	list.push_back(book);
}

Book LabRepository::delete_book(const Book& book) {
	generate_error();
	for (const auto& book_pair : new_list)
	{
		if (book_pair.second == book)
		{
			auto copy_book = book_pair.second;
			new_list.erase(book.get_id());
			auto  book_to_delete = std::find_if(this->list.begin(), this->list.end(), [&book](const Book& curent_book) noexcept
				{return curent_book == book; });
			list.erase(book_to_delete);
			return copy_book;
		}
	}
	throw RepositoryError("carte inexistenta!");
}

const Book& LabRepository::find_book(const Book& book) {
	generate_error();
	for (const auto& book_pair : new_list)
	{
		if (book_pair.second == book)
			return book_pair.second;
	}
	throw RepositoryError("carte inexistenta!");
}

Book LabRepository::update_book(const Book& new_book) {
	generate_error();
	for (auto book_pair : new_list)
	{
		if (book_pair.second == new_book)
		{
			auto copy_book = book_pair.second;
			new_list.at(book_pair.first) = new_book;
			auto  book_to_update = std::find_if(this->list.begin(), this->list.end(), [&new_book](const Book& curent_book) noexcept
				{return curent_book == new_book; });
			*book_to_update = new_book;
			return copy_book;
		}
	}
	throw RepositoryError("carte inexistenta!");
}

Book const& LabRepository::get_book(int index) const {
	return this->list.at(index);
}

std::vector<Book> const& LabRepository::get_all() {
	generate_error();
	return list;
}