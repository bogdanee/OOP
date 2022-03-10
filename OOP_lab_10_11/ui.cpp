#include "errors.h"
#include "ui.h"

UI::UI(Service& srv) noexcept : service{ srv } {
};

void UI::print_menu() {
	std::cout << "Comenzi:\n";
	std::cout << "'add'           - adauga carti\n";
	std::cout << "'delete'        - sterge carti\n";
	std::cout << "'update'        - modifica carti\n";
	std::cout << "'print'         - printeaza carti\n";
	std::cout << "'add_to_cart'   - adauga carti in cos\n";
	std::cout << "'clear_cart'    - goleste cosul\n";
	std::cout << "'generate_cart' - genereaza carti in cos\n";
	std::cout << "'print_cart'    - printeaza cosul de carti\n";
	std::cout << "'raport_gen'    - raportul pentru genuri\n";
	std::cout << "'exit'          - iesirea din aplicatie\n";

}

void UI::print_book(const Book &book)
{
	std::cout << "Id:" << std::to_string(book.get_id()) << " ";
	std::cout << "Titlu:" << book.get_title() << " ";
	std::cout << "Autor:" << book.get_author() << " ";
	std::cout << "Gen:" << book.get_gen() << " ";
	std::cout << "An:" << std::to_string(book.get_year()) << "\n";
}

void UI::print_books_list(const std::vector<Book>& list) {
	if (list.size() == 0) {
		std::cout << "nu exista carti in lista!\n";
	}
	else {
		for (const auto& element : list) {
			print_book(element);
		}
	}
}

void UI::ui_add() {
	int id;
	std::string title;
	std::string author;
	std::string gen;
	int year;
	std::cout << "Id:"; std::cin >> id;
	std::cin.ignore(256, '\n');


	std::cout << "Titlu:"; getline(std::cin, title);
	std::cout << "Autor:"; getline(std::cin, author);
	std::cout << "Gen:"; getline(std::cin, gen);
	std::cout << "An:"; std::cin >> year;
	std::cin.ignore(256, '\n');

	service.service_add_book(id, title, author, gen, year);
}

void UI::ui_delete() {
	int id;

	std::cout << "Id:"; std::cin >> id;
	std::cin.ignore(256, '\n');

	service.service_delete_book(id);
}

void UI::ui_update() {
	int id;
	std::string title;
	std::string author;
	std::string gen;
	int year;
	std::cout << "Id:"; std::cin >> id;
	std::cin.ignore(256, '\n');

	std::cout << "Titlu:"; getline(std::cin, title);
	std::cout << "Autor:"; getline(std::cin, author);
	std::cout << "Gen:"; getline(std::cin, gen);
	std::cout << "An:"; std::cin >> year;
	std::cin.ignore(256, '\n');

	service.service_update_book(id, title, author, gen, year);
}

void UI::ui_print() {
	print_books_list(service.service_get_all());
}

void UI::ui_find() {
	int id;
	std::cout << "Id:"; std::cin >> id;
	std::cin.ignore(256, '\n');
	print_book(service.service_find_book(id));
}

void UI::ui_filtre() {
	std::string filtre;
	std::cout << "Filtre posibile: 'titlu', 'an'\n";
	std::cout << "Filtru:"; getline(std::cin, filtre);
	if (filtre != "titlu" && filtre != "an") {
		std::cout << "filtru invalid!\n";		
	}
	if (filtre == "titlu") {
		std::string title;
		std::cout << "Titlu:"; getline(std::cin, title);
		std::vector<Book> filtre_list = service.filtre_by_title(title);
		print_books_list(filtre_list);
	}
	if (filtre == "an") {
		int year;
		std::cout << "An:"; std::cin >> year;
		std::cin.ignore(256, '\n');
		std::vector<Book> filtre_list = service.filtre_by_year(year);
		print_books_list(filtre_list);
	}
}

void UI::ui_sort() {
	std::string sort;
	std::cout << "Sortari posibile: 'titlu', 'autor', 'an+gen'\n";
	std::cout << "Sortare:"; getline(std::cin, sort);
	if (sort != "titlu" && sort != "an+gen" && sort != "autor") {
		std::cout << "sortare invalida!\n";
	}
	else{

		int reverse{ 1 };
		std::cout << "Crescator - '1' / descrescator '-1':"; std::cin>> reverse;
		std::cin.ignore(256, '\n');
		if (reverse != 1 && reverse != -1) std::cout << "ordine invalida!\n";
		else {
			if (sort == "titlu") {
				std::vector<Book> sorted_list = service.sort_by_title(reverse);
				print_books_list(sorted_list);
			}
			if (sort == "autor") {
				std::vector<Book> sorted_list = service.sort_by_author(reverse);
				print_books_list(sorted_list);
			}
			if (sort == "an+gen") {
				std::vector<Book> sorted_list = service.sort_by_year_and_gen(reverse);
				print_books_list(sorted_list);
			}
		}
	}
}

void UI::ui_add_to_cart()
{
	std::string title;
	std::cout << "Titlu:"; getline(std::cin, title);
	service.service_add_by_title_cart(title);
	std::cout << "Numarul de carti in cos:" << service.get_cart().size()<<"\n";
}

void UI::ui_clear_cart()
{
	service.service_clear_cart();
	std::cout << "Numarul de carti in cos:" << service.get_cart().size() << "\n";
}

void UI::ui_generate_books_cart()
{
	int numar;
	std::cout << "Numar:"; std::cin >> numar;
	std::cin.ignore(256, '\n');
	service.service_generate_books_cart(numar);
	std::cout << "Numarul de carti in cos:" << service.get_cart().size() << "\n";
}

void UI::ui_print_cart()
{
	const auto& list = service.get_cart().get_all();
	print_books_list(list);
}

void UI::ui_raport_gen()
{
	const std::map<std::string, int> raport = service.service_raport_gen();
	for (auto gen : raport)
		std::cout << "Gen:"<<gen.first << " Aparitii:" << gen.second <<"\n";
}


void UI::ui_export_cart()
{
	service.service_export_cart();
}

void UI::ui_undo()
{
	service.undo();
}


void UI::run() {
	std::string comand;
	std::cout << ">>>"; getline(std::cin, comand);
	//std::unordered_map <std::string, std::function<void()>> comands;
	//comands["add"] = ui_add;
	
	while (true)
	{
		try {
			if (comand == "exit") {
				std::cout << "Sanatate, numa' bine!";
				break;
			}
			else if (comand == "help") {
				print_menu();
			}
			else if (comand == "add") {
				ui_add();
			}
			else if (comand == "delete") {
				ui_delete();
			}
			else if (comand == "update") {
				ui_update();
			}
			else if (comand == "find") {
				ui_find();
			}
			else if (comand == "filtre") {
				ui_filtre();
			}
			else if (comand == "sort") {
				ui_sort();
			}
			else if (comand == "print") {
				ui_print();
			}
			else if (comand == "add_to_cart") {
				ui_add_to_cart();
			}
			else if (comand == "clear_cart") {
				ui_clear_cart();
			}
			else if (comand == "generate_cart") {
				ui_generate_books_cart();
			}
			else if (comand == "print_cart") {
				ui_print_cart();
			}
			else if (comand == "raport_gen") {
				ui_raport_gen();
			}
			else if (comand == "export") {
				ui_export_cart();
			}
			else if (comand == "undo") {
				ui_undo();
			}
			else
				std::cout << "comnda invalida!\n";
			std::cout << ">>>"; getline(std::cin, comand);
		}
		catch (const ValidatorError& validator_exception) {
			std::cout << validator_exception.get_error_message() << "\n";
			std::cout << ">>>"; getline(std::cin, comand);
		}
		catch (const RepositoryError& repository_exception) {
			std::cout << repository_exception.get_error_message() << "\n";
			std::cout << ">>>"; getline(std::cin, comand);
		}
		catch (const ServiceError& service_exception) {
			std::cout << service_exception.get_error_message() << "\n";
			std::cout << ">>>"; getline(std::cin, comand);
		}
		
	}
}