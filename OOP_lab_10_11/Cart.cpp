#include "Cart.h"
#include <algorithm>
#include <random> 
#include <chrono>
#include <fstream>

Cart::Cart(IRepository& repository) noexcept : repo{ repository }  {
};

void Cart::clear() noexcept {
	cart_list.erase(cart_list.begin(), cart_list.end());
}

bool Cart::exist(const Book& book) {
	auto iterator_cart = std::find(cart_list.begin(), cart_list.end(), book);
	if (iterator_cart == cart_list.end())
		return false;
	else
		return true;}

void Cart::add_by_title(const std::string& title) {
	auto iterator_list = std::find_if(repo.get_all().begin(), repo.get_all().end(), [&title,this](const Book& book)
		{return (book.get_title() == title) && (this->exist(book) == false); });
	if (iterator_list != repo.get_all().end())
		cart_list.push_back(*iterator_list);
	else {
		auto iterator_cart = std::find_if(cart_list.begin(), cart_list.end(), [&title, this](const Book& book)
			{return (book.get_title() == title); });
		if (iterator_cart == cart_list.end())
			throw RepositoryError("carte inexistenta!");
		else
			throw RepositoryError("carte existenta in cos!");}
}

void Cart::generate_books(int value) {
	if (cart_list.size() == repo.get_all().size()) {
		return;
	}
	if (value+ cart_list.size() >= repo.get_all().size()) {
		cart_list = repo.get_all();
	}
	else {
		std::vector<Book> list = repo.get_all();
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(list.begin(), list.end(),std::default_random_engine(static_cast<unsigned int>(seed)) );
		for (auto book : list) {
			auto iterator_cart = std::find(cart_list.begin(), cart_list.end(), book);
			if (iterator_cart == cart_list.end()) {
				cart_list.push_back(book);
				value--;
			}
			if (value == 0)
				break;}
	}
}

int Cart::size() const noexcept {
	return cart_list.size();
}

std::vector<Book> const& Cart::get_all() const noexcept{
	return cart_list;
}

void Cart::export_cart() 
{
	std::ofstream fout("export.html");
	for (auto book : cart_list)
	{
		fout << "Id:" << std::to_string(book.get_id()) << " ";
		fout << "Titlu:" << book.get_title() << " ";
		fout << "Autor:" << book.get_author() << " ";
		fout << "Gen:" << book.get_gen() << " ";
		fout << "An:" << std::to_string(book.get_year()) << "<br>";
	}
	fout.close();
}