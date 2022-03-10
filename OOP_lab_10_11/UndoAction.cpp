#include "UndoAction.h"

UndoAdd::UndoAdd(const Book& book, IRepository& repo) : book_added{ book }, repository{ repo }{};

void UndoAdd::do_undo() {
	repository.delete_book(book_added);
}

UndoDelete::UndoDelete(const Book& book, IRepository& repo) : book_deleted{ book }, repository{ repo }{};

void UndoDelete::do_undo() {
	repository.add_book(book_deleted);
}

UndoUpdate::UndoUpdate(const Book& book, IRepository& repo) : book_updated{ book }, repository{ repo }{};

void UndoUpdate::do_undo() {
	repository.update_book(book_updated);
}