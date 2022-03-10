#pragma once
#include "repository.h"
#include <fstream>
#include <sstream>

class FileRepository: public Repository
{
private:
	std::string filename;

	void load_from_file();

	void store_to_file();

public:
	FileRepository(std::string file);

	void add_book(const Book& book) override;

	Book delete_book(const Book& book) override;

	Book update_book(const Book& new_book) override;
};

