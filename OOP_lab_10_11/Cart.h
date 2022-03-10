#pragma once
#include "repository.h"
#include "IRepository.h"
#include <vector>
#include <string>
#include <algorithm>
#include "errors.h"
#include "Observer.h"

class Cart
{
	friend class IRepository;
	
private:
	std::vector<Book> cart_list;
	IRepository& repo;
public:
	Cart(IRepository& repo) noexcept;

	void clear() noexcept;

	bool exist(const Book& book);

	void add_by_title(const std::string& title);

	void generate_books(int value) ;

	int size() const noexcept;

	std::vector<Book> const& get_all() const noexcept;

	void export_cart();
};

