#pragma once
#include "Book.h"
#include <vector>

class IRepository {
public:
	virtual size_t size() const noexcept = 0;

	virtual void add_book(const Book&) = 0;

	virtual Book delete_book(const Book&) = 0;

	virtual const Book& find_book(const Book&) = 0;

	virtual Book update_book(const Book&) = 0;

	virtual std::vector<Book> const& get_all() = 0;

	virtual ~IRepository() = default;

};