#include "service.h"
#include <algorithm>



Service::Service(IRepository& repository, Cart& cart_of_books) noexcept : repo{ repository }, cart{cart_of_books}, Observable() {
};

size_t Service::size() const noexcept{
	return repo.size();
}

std::vector<Book> const& Service::service_get_all() const {
	return repo.get_all();
}

void Service::service_add_book(int id, const std::string& title, const std::string& author, const std::string& gen, int year) {
	Book book{ id, title, author, gen, year };
	validate_book(book);
	repo.add_book(book);
	undo_actions.push_back(std::make_unique<UndoAdd>(book, repo));
}

void Service::service_delete_book(int id) {
	Book book{ id, "a", "b", "c", 2000 };
	validate_book(book);
	const Book& deleted_book = repo.delete_book(book);
	undo_actions.push_back(std::make_unique<UndoDelete>(deleted_book, repo));
}

void Service::service_update_book(int id, const std::string& title, const std::string& author, const std::string& gen, int year) {
	Book book{ id, title, author, gen, year };
	validate_book(book);
	const Book& updated_book = repo.update_book(book);
	undo_actions.push_back(std::make_unique<UndoUpdate>(updated_book, repo));
}

void Service::undo() {
	if (undo_actions.empty())
		throw ServiceError("nu se poate executa undo!");
	auto action = std::move(undo_actions.back());
	undo_actions.pop_back();
	action->do_undo();
}

Book Service::service_find_book(int id) const {
	Book book{ id, "a", "b", "c", 2000 };
	validate_book(book);
	return repo.find_book(book);
}

std::vector<Book> Service::filtre_by_title(const std::string& title) const
{
	const std::vector<Book>& list = service_get_all();
	std::vector<Book> filtred_list{};
	for (const auto& book : list) {
		if (book.get_title() == title)
			filtred_list.push_back(book);
	}
	return filtred_list;
}

std::vector<Book> Service::filtre_by_year(int year) const
{
	const std::vector<Book> list = service_get_all();
	std::vector<Book> filtred_list{};
	for (const auto& book : list) {
		if (book.get_year() == year)
			filtred_list.push_back(book);
	}
	return filtred_list;
}

std::vector<Book> Service::sort_by_title(const int& reverse) const
{
	std::vector<Book> all = service_get_all();

	std::sort(all.begin(), all.end(), [&reverse](const Book& book1, const Book& book2) 
			{return book1.get_title() < book2.get_title(); });
	if (reverse == -1)
		std::reverse(all.begin(), all.end());
	return all;
}

std::vector<Book> Service::sort_by_author(const int& reverse) const
{
	std::vector<Book> all = service_get_all();
	std::sort(all.begin(), all.end(), [&reverse](const Book& book1, const Book& book2) 
		{return book1.get_author() < book2.get_author(); });
	if (reverse == -1)
		std::reverse(all.begin(), all.end());
	return all;
}

std::vector<Book> Service::sort_by_year_and_gen(const int& reverse) const
{
	std::vector<Book> all = service_get_all();
	std::sort(all.begin(), all.end(), [&reverse](const Book& book1, const Book& book2) {
		if (book1.get_year() == book2.get_year()) {
			return book1.get_gen() < book2.get_gen();
		}
		return book1.get_year() < book2.get_year();
		});
	if (reverse == -1)
		std::reverse(all.begin(), all.end());
	return all;
}

const Cart& Service::get_cart() const noexcept
{
	return cart;
}

void Service::service_add_by_title_cart(const std::string& title){
	Book book{ 1, title, "a", "b", 2000 };
	validate_book(book);
	cart.add_by_title(title);
	notify();
}


void Service::service_clear_cart() noexcept
{
	cart.clear();
	notify();
}

void Service::service_generate_books_cart(int value)
{
	if (value <= 0)
		throw ValidatorError("numar invalid!");
	cart.generate_books(value);
	notify();
}

std::map<std::string, int> Service::service_raport_gen() const {
	const std::vector<Book>& all = service_get_all();
	std::map<std::string, int> frequency_gen;
	for (auto book : all) {
		if (frequency_gen.find(book.get_gen()) == frequency_gen.end())
			frequency_gen.insert(std::pair<std::string, int>(book.get_gen(), 1));
		else
			frequency_gen[book.get_gen()]++;
	}
	return frequency_gen;
}

void Service::service_export_cart()
{
	cart.export_cart();
}