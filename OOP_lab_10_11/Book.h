#pragma once
#include <string>
#include <iostream>
class Book
{
private:
	int id;
	std::string title;
	std::string author;
	std::string gen;
	int year;
public:
	Book() = default;
	
	Book(int id_int, const std::string& title_string, const std::string& author_string, const std::string& gen_string, int year_int);
	
	/*
	Book(const Book& op) :id{ op.id }, title{ op.title }, author{ op.author }, gen{ op.gen }, year{ op.year }{
		std::cout << "!!!!\n";
	}
	*/
	bool operator==(const Book& other_book) const noexcept;
	
	int get_id() const noexcept;

	std::string get_title() const ;

	std::string get_author() const ;

	std::string get_gen() const ;

	int get_year() const noexcept;

};

