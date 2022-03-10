#pragma once

#include "Book.h"
#include <vector>
#include "IRepository.h"

class Repository : public IRepository
{
protected:
	std::vector<Book> list;
public:
	Repository() = default;

	size_t size() const noexcept override;

	void add_book(const Book& book) override;

	Book delete_book(const Book& book) override;

	const Book& find_book(const Book& book) override;

	Book update_book(const Book& new_book) override;

	Book const&  get_book(int index) const;
	
	std::vector<Book> const& get_all() noexcept override;
};