#pragma once
#include "Book.h"
#include "repository.h"
class UndoAction{
public:
	virtual void do_undo()=0;
	virtual ~UndoAction() {};
};


class UndoAdd : public UndoAction {
private:
	Book book_added;
	IRepository& repository;

public:
	UndoAdd(const Book& book, IRepository& repo);
	void do_undo() override;
};

class UndoDelete : public UndoAction {
private:
	Book book_deleted;
	IRepository& repository;

public:
	UndoDelete(const Book& book, IRepository& repo);
	void do_undo() override;
};

class UndoUpdate : public UndoAction {
private:
	Book book_updated;
	IRepository& repository;

public:
	UndoUpdate(const Book& book, IRepository& repo);
	void do_undo() override;
};