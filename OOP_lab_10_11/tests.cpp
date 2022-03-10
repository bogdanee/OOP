#include "tests.h"
#include "Book.h"
#include "validator.h"
#include "repository.h"
#include "service.h"
#include "errors.h"
#include "LabRepository.h"

#include <exception>
#include <assert.h>
#include <iostream>
#include "Cart.h"
#include "UndoAction.h"
#include <map>
#include "FileRepository.h"
#include "FakeRepository.h"


void run_domain_test(){
	Book book{1, "asd", "efg", "xyz", 1900 };
	assert(book.get_id() == 1);
	assert(book.get_title() == "asd");
	assert(book.get_author() == "efg");
	assert(book.get_gen() == "xyz");
	assert(book.get_year() == 1900);
	Book book2{1, "asd", "234", "abc", 1900 };
	Book book3{2, "asde", "efg", "xyz", 1900 };
	assert(book == book);
	assert(book == book2);
	assert((book == book3) == false);
	book3 = book;
	assert(book == book3);
}

void run_validator_test() 
{
	Book book{ 1, "asd", "efg", "xyz", 1900 };
	Book book2{ -1, "asd", "efg", "xyz", 1900 };
	try {
		validate_book(book2);}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "id invalid!");
	}
	
	Book book3{ 1, "", "efg", "xyz", 1900 };
	try {
		validate_book(book3);}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "titlu invalid!");
	}
	Book book4{ 1, "asd", "", "xyz", 1900 };
	try {
		validate_book(book4);}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "autor invalid!");
	}
	Book book5{ 1, "asd", "efg", "", 1900 };
	try {
		validate_book(book5);}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "gen invalid!");
	}

	Book book6{ 1, "asd", "efg", "xyz", 3000 };
	try {
		validate_book(book6);}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "an invalid!");
	}
	
}

void run_repo_test()
{
	Book book{ 1, "asd", "efg", "xyz", 1900 };
	Book book2{ 2, "exy", "Axw", "aksldn", 2000 };
	Book book3{ 1, "asde", "efg", "xyz", 1900 };
	Repository repo;
	assert(repo.size() == 0);
	repo.add_book(book);
	assert(repo.size() == 1);
	try {
		repo.add_book(book);}
	catch (const RepositoryError& repository_exception) {
		assert(repository_exception.get_error_message() == "carte existenta!");
	}
	
	repo.add_book(book2);
	assert(repo.size() == 2);
	
	assert(repo.find_book(book2) == book2);
	
	repo.delete_book(book2);
	assert(repo.size() == 1);
	try {
		repo.delete_book(book2);}
	catch (const RepositoryError& repository_exception) {
		assert(repository_exception.get_error_message() == "carte inexistenta!");
	}

	try {
		repo.find_book(book2);}
	catch (const RepositoryError& repository_exception) {
		assert(repository_exception.get_error_message() == "carte inexistenta!");
	}

	try {
		repo.update_book(book2);}
	catch (const RepositoryError& repository_exception) {
		assert(repository_exception.get_error_message() == "carte inexistenta!");
	}
	repo.update_book(book3);
	assert(repo.get_book(0) == book3);
	
	const std::vector<Book>& all = repo.get_all();
	assert(all.size() == 1);
	assert(all.at(0) == book3);
	
}

void run_filerepo_test()
{
	remove("books_test.txt");
	try {
		FileRepository repo{ "books_test.txt" };}
	catch (const RepositoryError& repository_exception) {
		assert(repository_exception.get_error_message() == "Error open:books_test.txt");
	}
	std::ofstream fout("books_test.txt");
	fout.clear();
	fout.close();
	const Book book{ 1, "asd", "efg", "xyz", 1900 };
	const Book book2{ 2, "exy", "Axw", "aksldn", 2000 };
	const Book book3{ 1, "asde", "efg", "xyz", 1900 };
	FileRepository repo{"books_test.txt"};
	assert(repo.size() == 0);
	repo.add_book(book);
	assert(repo.size() == 1);

	repo.add_book(book2);
	assert(repo.size() == 2);
	repo.delete_book(book2);
	repo.update_book(book3);

	const std::vector<Book>& all = repo.get_all();
	assert(all.size() == 1);
	assert(all.at(0) == book3);
}

void run_service_test()
{
	Repository repo;
	Cart cart{ repo };
	Service service{ repo, cart };
	try {
		service.service_add_book(-1, "a", "b", "c", 2000);}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "id invalid!");
	}
	service.service_add_book(1, "a", "b", "c", 2000);

	try {
		service.service_add_book(1, "a", "b", "c", 2000);}
	catch (const RepositoryError& repository_exception) {
		assert(repository_exception.get_error_message() == "carte existenta!");
	}
	assert(service.size() == 1);

	service.service_add_book(2, "a", "b", "c", 2000);
	assert(service.size() == 2);

	try {
		service.service_find_book(-1);}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "id invalid!");
	}
	Book book{ 1, "a", "b", "c" , 2000 };
	assert(service.service_find_book(1) == book);
	try {
		service.service_find_book(3);}
	catch (const RepositoryError& repository_exception) {
		assert(repository_exception.get_error_message() == "carte inexistenta!");
	}


	const std::vector<Book>& all = service.service_get_all();
	assert(all.size() == 2);

	try {
		service.service_delete_book(-1);}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "id invalid!");
	}
	service.service_delete_book(2);
	try {
		service.service_delete_book(2);}
	catch (const RepositoryError& repository_exception) {
		assert(repository_exception.get_error_message() == "carte inexistenta!");
	}
	assert(service.size() == 1);

	try {
		service.service_update_book(-1, "a", "b", "c", 2000);}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "id invalid!");
	}
	try {
		service.service_add_book(1, "", "b", "c", 2022);}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "titlu invalid!");
	}
	service.service_update_book(1, "A", "B", "C", 2001);
	assert(service.service_find_book(1).get_author() == "B");

	try {
		service.service_update_book(2, "a", "b", "c", 2000);}
	catch (const RepositoryError& repository_exception) {
		assert(repository_exception.get_error_message() == "carte inexistenta!");
	}
	
	service.service_add_book(3, "a", "b", "c", 2000);
	service.service_add_book(4, "A", "B", "c", 2000);
	auto dictionary = service.service_raport_gen();
	assert(dictionary.size() == 2);
}

void run_service_filtre_test()
{
	Book book1{ 1, "ab", "ba", "cd", 200 };
	Book book2{ 2, "bb", "dd", "cc", 201 };
	Book book3{ 3, "bb", "aa", "cd", 200 };
	Repository repo;
	Cart cart{ repo };
	Service const service{ repo, cart };
	repo.add_book(book1);
	repo.add_book(book2);
	repo.add_book(book3);

	std::vector<Book> filtred_list = service.filtre_by_title("bb");
	assert(std::find(filtred_list.begin(), filtred_list.end(), book1) == filtred_list.end());
	assert(std::find(filtred_list.begin(), filtred_list.end(), book2) != filtred_list.end());
	assert(std::find(filtred_list.begin(), filtred_list.end(), book3) != filtred_list.end());

	filtred_list = service.filtre_by_title("ab");
	assert(std::find(filtred_list.begin(), filtred_list.end(), book1) != filtred_list.end());
	assert(std::find(filtred_list.begin(), filtred_list.end(), book2) == filtred_list.end());
	assert(std::find(filtred_list.begin(), filtred_list.end(), book3) == filtred_list.end());

	filtred_list = service.filtre_by_title("a");
	assert(std::find(filtred_list.begin(), filtred_list.end(), book1) == filtred_list.end());
	assert(std::find(filtred_list.begin(), filtred_list.end(), book2) == filtred_list.end());
	assert(std::find(filtred_list.begin(), filtred_list.end(), book3) == filtred_list.end());

	filtred_list = service.filtre_by_year(200);
	assert(std::find(filtred_list.begin(), filtred_list.end(), book1) != filtred_list.end());
	assert(std::find(filtred_list.begin(), filtred_list.end(), book2) == filtred_list.end());
	assert(std::find(filtred_list.begin(), filtred_list.end(), book3) != filtred_list.end());

	filtred_list = service.filtre_by_year(2);
	assert(std::find(filtred_list.begin(), filtred_list.end(), book1) == filtred_list.end());
	assert(std::find(filtred_list.begin(), filtred_list.end(), book2) == filtred_list.end());
	assert(std::find(filtred_list.begin(), filtred_list.end(), book3) == filtred_list.end());
}

void run_service_sort_test()
{
	Book book1{ 1, "ab", "ba", "cd", 200 };
	Book book2{ 2, "bc", "dd", "cc", 201 };
	Book book3{ 3, "bb", "aa", "ca", 200 };

	Repository repo;
	Cart cart{ repo };
	Service const service{ repo, cart };
	repo.add_book(book1);
	repo.add_book(book2);
	repo.add_book(book3);


	std::vector<Book> sorted_list = service.sort_by_title(1);
	std::vector<Book> result_list = { book1, book3, book2 };
	assert(sorted_list == result_list);

	sorted_list = service.sort_by_title(-1);
	result_list = { book2, book3, book1 };
	assert(sorted_list == result_list);

	sorted_list = service.sort_by_author(1);
	result_list = { book3, book1, book2 };
	assert(sorted_list == result_list);

	sorted_list = service.sort_by_author(-1);
	result_list = { book2, book1, book3 };
	assert(sorted_list == result_list);


	sorted_list = service.sort_by_year_and_gen(1);
	result_list = { book3, book1, book2 };
	assert(sorted_list == result_list);

	sorted_list = service.sort_by_year_and_gen(-1);
	result_list = { book2, book1, book3 };
	assert(sorted_list == result_list);

}

void run_cart_test()
{
	Book book1{ 1, "ab", "ba", "cd", 200 };
	Book book2{ 2, "bc", "dd", "cc", 201 };
	Book book3{ 3, "bb", "aa", "ca", 200 };
	

	Repository repo;
	repo.add_book(book1);
	repo.add_book(book2);
	repo.add_book(book3);
	Cart cart{ repo };
	Service service{ repo, cart };
	assert(cart.size() == 0);
	try {
		service.service_add_by_title_cart("");}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "titlu invalid!");
	}
	try {
		service.service_add_by_title_cart("XXX");}
	catch (const RepositoryError& repository_exception) {
		assert(repository_exception.get_error_message() == "carte inexistenta!");
	}
	cart.add_by_title("ab");
	assert(cart.size() == 1);
	try {
		service.service_add_by_title_cart("ab");}
	catch (const RepositoryError& repository_exception) {
		assert(repository_exception.get_error_message() == "carte existenta in cos!");
	}

	try {
		service.service_generate_books_cart(-1);}
	catch (const ValidatorError& validation_exception) {
		assert(validation_exception.get_error_message() == "numar invalid!");
	}

	service.service_generate_books_cart(1);
	assert(cart.size() == 2);
	service.service_generate_books_cart(2);
	assert(cart.size() == 3);
	service.service_generate_books_cart(1);
	assert(cart.size() == 3);
	assert(service.get_cart().get_all().size() == 3);
	service.service_clear_cart();
	assert(cart.size() == 0);
	service.service_generate_books_cart(50);
	assert(cart.size() == 3);

	service.service_clear_cart();
	Book book4{ 4, "ab", "aa", "ca", 200 };
	repo.add_book(book4);
	service.service_add_by_title_cart("ab");
	service.service_add_by_title_cart("ab");
	assert(cart.size() == 2);

	service.service_export_cart();
	service.service_clear_cart();
	service.service_export_cart();
}

void run_undo_test()
{
	Repository repo;
	Cart cart{ repo };
	Service service{ repo, cart };
	try {
		service.undo();
	}
	catch (const ServiceError& service_exception) {
		assert(service_exception.get_error_message() == "nu se poate executa undo!");
	}
	service.service_add_book(1, "ab", "ba", "cd", 200);
	service.service_add_book(2, "bc", "dd", "cc", 201);
	service.service_add_book(3, "bb", "aa", "ca", 200);
	assert(repo.size() == 3);

	service.undo();
	assert(repo.size() == 2);

	service.service_delete_book(2);
	assert(repo.size() == 1);
	service.undo();
	assert(repo.size() == 2);

	service.service_update_book(1, "BB", "AA", "CA", 202);
	assert(repo.size() == 2);
	service.undo();
	assert(repo.size() == 2);

	service.undo();
	service.undo();

	try {
		service.undo();}
	catch (const ServiceError& service_exception) {
		assert(service_exception.get_error_message() == "nu se poate executa undo!");
	}
}

void test__service_add_book__duplicateId__throwsException()
{
	FakeRepository repo_that_always_throws_exception;
	Cart cart{ repo_that_always_throws_exception };
	Service service{ repo_that_always_throws_exception, cart };
	try {
		service.service_add_book(1,"a","b","c",2 );
		assert(false);
	}
	catch (RepositoryError& exception){
		assert(true);
		assert(exception.get_error_message() == "carte existenta!");
	}
}

void run_all_tests(){
	run_domain_test();
	run_validator_test();
	run_repo_test();
	run_filerepo_test();
	run_service_test();
	run_service_filtre_test();
	run_service_sort_test();
	run_cart_test();
	run_undo_test();
	test__service_add_book__duplicateId__throwsException();
}