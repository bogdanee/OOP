#pragma once
#include "repository.h"
#include "IRepository.h"
#include "validator.h"
#include <vector>
#include "Cart.h"
#include <map>
#include "UndoAction.h"
#include "Observer.h"

class Service : public Observable
{
	friend class Cart;
private:
	IRepository& repo;
	Cart& cart;
	std::vector<std::unique_ptr<UndoAction>> undo_actions;
public:

	Service(IRepository& repository, Cart& cart_of_books) noexcept;

	Service(const Service& other_service) = delete;

	size_t size() const noexcept;

	std::vector<Book> const& service_get_all() const;

	void service_add_book(int id, const std::string& title, const std::string& author, const std::string& gen, int year);

	void service_delete_book(int id);

	void service_update_book(int id, const std::string& title, const std::string& author, const std::string& gen, int year);
	
	void undo();

	Book service_find_book(int id) const;

	std::vector<Book> filtre_by_title(const std::string &title) const;

	std::vector<Book> filtre_by_year(int year) const;

	std::vector<Book> sort_by_title(const int& reverse) const;
	
	std::vector<Book> sort_by_author(const int& reverse) const;

	std::vector<Book> sort_by_year_and_gen(const int& reverse) const;

	const Cart& get_cart() const noexcept;

	void service_add_by_title_cart(const std::string& title);

	void service_clear_cart() noexcept;

	void service_generate_books_cart(int value);

	std::map<std::string, int> service_raport_gen() const;

	void service_export_cart();
};

