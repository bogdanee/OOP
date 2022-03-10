#pragma once
#include "repository.h"

class FakeRepository: public Repository
{
private:

public:
	void add_book(const Book& book) override;
};

