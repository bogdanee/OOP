#include "FileRepository.h"
#include "errors.h"

FileRepository::FileRepository(std::string file) : filename{ file }, Repository() {
	load_from_file();
};

void FileRepository::load_from_file() {
	std::ifstream file_in(filename);
	if (!file_in.is_open())
		throw RepositoryError("Error open:" + filename);
	std::string line;
	while (std::getline(file_in, line))
	{
		if (!line.empty())
		{
			std::vector<std::string> elements;
			elements.reserve(5);
			std::istringstream stream_line(line);
			std::string curent_element;
			while (std::getline(stream_line, curent_element, ';'))
			{
				elements.push_back(curent_element);
			}
			if (elements.size() == 5)
			{
				Book book{ std::stoi(elements.at(0)),elements.at(1), elements.at(2), elements.at(3), std::stoi(elements.at(4)) };
				Repository::add_book(book);
			}
		}
	}
	file_in.close();
}

void FileRepository::store_to_file() {
	std::ofstream file_out(filename);
	if (!file_out.is_open())
		throw RepositoryError("Error open:" + filename);
	for (const auto& book : get_all())
	{
		file_out << std::to_string(book.get_id()) << ";";
		file_out << book.get_title() << ";";
		file_out << book.get_author() << ";";
		file_out << book.get_gen() << ";";
		file_out << std::to_string(book.get_year()) << ";\n";
	}
	file_out.close();
}

void FileRepository::add_book(const Book& book) {
	Repository::add_book(book);
	store_to_file();
}

Book FileRepository::delete_book(const Book& book) {
	const Book& copy_book = Repository::delete_book(book);
	store_to_file();
	return copy_book;
}

Book FileRepository::update_book(const Book& book) {
	const Book& copy_book = Repository::update_book(book);
	store_to_file();
	return copy_book;
}