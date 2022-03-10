#pragma once
#include "Book.h"
#include <vector>
#include "IRepository.h"
#include <map>


class LabRepository: public IRepository
{
private:
	std::map<int, Book> new_list;
	std::vector<Book> list;
	float probability;
	void generate_error();
public:
	LabRepository(const float& prob) : probability{prob} {};

	size_t size() const noexcept override;

	void add_book(const Book & book) override;

	Book delete_book(const Book & book) override;

	const Book& find_book(const Book & book) override;

	Book update_book(const Book & new_book) override;

	Book const& get_book(int index) const;

	std::vector<Book> const& get_all() override;

};

