#pragma once
#include "service.h"
#include <unordered_map>
#include <functional>
#include <iostream>
#include <map>

class UI
{
private:
	Service& service;
	
public:
	
	UI(Service& srv) noexcept;

	void print_menu();

	void print_book(const Book& book);

	void print_books_list(const std::vector<Book>& list);

	void ui_add();

	void ui_delete();

	void ui_update();

	void ui_print();

	void ui_find();

	void ui_filtre();

	void ui_sort();

	void ui_add_to_cart();

	void ui_clear_cart();

	void ui_generate_books_cart();

	void ui_print_cart();

	void ui_raport_gen();

	void ui_export_cart();

	void ui_undo();

	void run();
};

