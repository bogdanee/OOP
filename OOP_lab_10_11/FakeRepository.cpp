#include "FakeRepository.h"
#include "errors.h"

void FakeRepository::add_book(const Book& book)
{
	throw RepositoryError("carte existenta!");
}