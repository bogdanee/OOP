#include "GUI.h"
#include <vector>
#include <string>
#include "Book.h"
#include <QMessageBox>
#include <QLabel>
#include <QDebug>

GUI::GUI(Service& srv)
    : service{srv}
{
    init_GUI();
    load_data(service.service_get_all());
    connect_signals();
}

void GUI::init_GUI()
{
    setWindowTitle("Biblioteca");

    QHBoxLayout* main_layout = new QHBoxLayout{};
    setLayout(main_layout);

    auto left_layout = new QVBoxLayout;

    left_layout->addWidget(list);
    //left_layout->addWidget(table);

    left_layout->addWidget(button_list);

    left_layout->addWidget(new QLabel("Sortare dupa:", this));

    main_layout->addLayout(left_layout);
    
    auto sort_buttons_layout = new QHBoxLayout{};
    sort_buttons_layout->addWidget(button_sort_by_title);
    sort_buttons_layout->addWidget(button_sort_by_author);
    sort_buttons_layout->addWidget(button_sort_by_year_and_gen);
    sort_buttons_layout->addWidget(new QLabel("  ", this));
    left_layout->addLayout(sort_buttons_layout);

    left_layout->addWidget(new QLabel("Filtrare dupa:", this));

    auto filtre_buttons_layout = new QHBoxLayout{};
    filtre_buttons_layout->addWidget(button_filtre_by_title);
    filtre_buttons_layout->addWidget(button_filtre_by_year);
    filtre_buttons_layout->addWidget(new QLabel("  ", this));
    left_layout->addLayout(filtre_buttons_layout);

    auto right_layout = new QVBoxLayout;

    auto form_layout = new QFormLayout;
    form_layout->addRow("Id", text_id);
    form_layout->addRow("Titlu", text_title);
    form_layout->addRow("Autor", text_author);
    form_layout->addRow("Gen", text_gen);
    form_layout->addRow("An", text_year);
    right_layout->addLayout(form_layout);

    auto buttons_layout = new QHBoxLayout{};
    buttons_layout->addWidget(button_add);
    buttons_layout->addWidget(button_delete);
    buttons_layout->addWidget(button_update);
    buttons_layout->addWidget(button_undo);
    buttons_layout->addWidget(button_raport);
    right_layout->addLayout(buttons_layout);

    auto cart_layout = new QVBoxLayout{};

    cart_layout->addWidget(new QLabel("Cos de cumparaturi:"));

    auto cart_layout_up = new QHBoxLayout{};
    
    cart_layout_up->addWidget(button_add_to_cart);
    cart_layout_up->addWidget(button_clear_cart);
    cart_layout_up->addWidget(button_generate_cart);
    cart_layout_up->addWidget(text_generate);
    cart_layout->addLayout(cart_layout_up);

    auto cart_layout_down = new QHBoxLayout{};
    cart_layout_down->addWidget(button_cart);
    cart_layout_down->addWidget(button_cart_readonly);
    cart_layout->addLayout(cart_layout_down);


    right_layout->addLayout(cart_layout);

    main_layout->addLayout(right_layout);
}

void GUI::load_data(const std::vector<Book>& books)
{
    
    list->clear();
    for (const auto& book : books)
    {
        QListWidgetItem* curent_book = new QListWidgetItem(QString::fromStdString(book.get_title()), list);
        curent_book->setData(Qt::UserRole, book.get_id());
    }
    
    table->clear();

    table->setHorizontalHeaderItem(0, new QTableWidgetItem("Titlu"));
    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Autor"));
    table->setHorizontalHeaderItem(2, new QTableWidgetItem("Gen"));
    table->setHorizontalHeaderItem(3, new QTableWidgetItem("An"));
    int number_of_books = 0;
    /*
    table->setRowCount(service.service_get_all().size());
    for (const auto& book : books)
    {
        table->setVerticalHeaderItem(number_of_books, new QTableWidgetItem(QString::number(book.get_id())));
        QTableWidgetItem* curent_book = new QTableWidgetItem(QString::fromStdString(book.get_title()));
        curent_book->setData(Qt::UserRole, book.get_id());
        table->setItem(number_of_books, 0, curent_book);
        table->setItem(number_of_books, 1, new QTableWidgetItem(QString::fromStdString(book.get_author())));
        table->setItem(number_of_books, 2, new QTableWidgetItem(QString::fromStdString(book.get_gen())));
        table->setItem(number_of_books, 3, new QTableWidgetItem(QString::number(book.get_year())));
        number_of_books++;
    }
    */
    
}

void GUI::connect_signals()
{
    QObject::connect(button_add, &QPushButton::clicked, [&]() {
        auto id = text_id->text().toInt();
        auto title = text_title->text().toStdString();
        auto author = text_author->text().toStdString();
        auto gen = text_gen->text().toStdString();
        auto year = text_year->text().toInt();
        try {
            service.service_add_book(id, title, author, gen, year);
            load_data(service.service_get_all());
        }
        catch (RepositoryError& exception) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(exception.get_error_message()));
        }
        catch (ValidatorError& exception) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(exception.get_error_message()));
        }
        });

    QObject::connect(list, &QListWidget::itemSelectionChanged, [&]() {
        auto selection = list->selectedItems();
        if (selection.isEmpty()) {
            text_id->setText("");
            text_title->setText("");
            text_author->setText("");
            text_gen->setText("");
            text_year->setText("");
        }
        else {
            auto selection_item = selection.at(0);
            auto id = selection_item->data(Qt::UserRole).toString();
            auto title = selection_item->text();
            text_id->setText(id);
            text_title->setText(title);
            auto book = service.service_find_book(id.toInt());
            text_author->setText(QString::fromStdString(book.get_author()));
            text_gen->setText(QString::fromStdString(book.get_gen()));
            text_year->setText(QString::number(book.get_year()));
        }
        });


    QObject::connect(button_delete, &QPushButton::clicked, [&]() {
        auto selection = list->selectedItems();
        if (selection.isEmpty()) {
            QMessageBox::information(this, "Warning", "niciun item selectat!");
        }
        else {
            auto selection_item = selection.at(0);
            auto id = selection_item->data(Qt::UserRole).toString();
            service.service_delete_book(id.toInt());
            load_data(service.service_get_all());

        }
        });

    QObject::connect(button_update, &QPushButton::clicked, [&]() {
        auto id = text_id->text().toInt();
        auto title = text_title->text().toStdString();
        auto author = text_author->text().toStdString();
        auto gen = text_gen->text().toStdString();
        auto year = text_year->text().toInt();
        try {
            service.service_update_book(id, title, author, gen, year);
            load_data(service.service_get_all());
        }
        catch (RepositoryError& exception) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(exception.get_error_message()));
        }
        catch (ValidatorError& exception) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(exception.get_error_message()));
        }
        });

    QObject::connect(button_undo, &QPushButton::clicked, [&]() {
        try {
            service.undo();
            load_data(service.service_get_all());
        }
        catch (ServiceError& exception) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(exception.get_error_message()));
        }
        });

    QObject::connect(button_list, &QPushButton::clicked, [&]() {
        load_data(service.service_get_all());
        });

    QObject::connect(button_sort_by_title, &QPushButton::clicked, [&]() {
        load_data(service.sort_by_title(1));
        });


    QObject::connect(button_sort_by_author, &QPushButton::clicked, [&]() {
        load_data(service.sort_by_author(1));
        });

    QObject::connect(button_sort_by_year_and_gen, &QPushButton::clicked, [&]() {
        load_data(service.sort_by_year_and_gen(1));
        });

    QObject::connect(button_filtre_by_title, &QPushButton::clicked, [&]() {
        auto title = text_title->text().toStdString();
        if (title == "") {
            QMessageBox::warning(this, "Warning", "titlu invalid!");
        }
        else {
            const auto& filtred_list = service.filtre_by_title(title);
            if (filtred_list.size() == 0) {
                QMessageBox::warning(this, "Warning", "nu exista elemente de acest tip!");
            }
            else {
                load_data(filtred_list);
            }
        }
        });

    QObject::connect(button_filtre_by_year, &QPushButton::clicked, [&]() {
        auto year_str = text_year->text().toStdString();
        auto year = text_year->text().toInt();
        if (year_str == "") {
            QMessageBox::warning(this, "Warning", "an invalid!");
        }
        else {
            const auto& filtred_list = service.filtre_by_year(year);
            if (filtred_list.size() == 0) {
                QMessageBox::warning(this, "Warning", "nu exista elemente de acest tip!");
            }
            else {
                load_data(filtred_list);
            }
        }
        });

    QObject::connect(button_add_to_cart, &QPushButton::clicked, [&]() {
        auto selection = list->selectedItems();
        if (selection.isEmpty()) {
            QMessageBox::information(this, "Warning", "niciun item selectat!");
        }
        else {
            auto selection_item = selection.at(0);
            auto title = text_title->text().toStdString();
            try {
                service.service_add_by_title_cart(title);
            }
            catch (RepositoryError& exception) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(exception.get_error_message()));
            }
        }
        });

    QObject::connect(button_cart, &QPushButton::clicked, [&]() {
        CartGUI* cart_gui = new CartGUI{ service };
        cart_gui->show();
        });

    QObject::connect(button_cart_readonly, &QPushButton::clicked, [&]() {
        CartReadOnlyGUI* cart_gui = new CartReadOnlyGUI{ service };
        cart_gui->show();
        });

    QObject::connect(button_generate_cart, &QPushButton::clicked, [&]() {
        try {
            auto generate_number_str = text_generate->text().toStdString();
            auto generate_number = text_generate->text().toInt();
            if (generate_number_str == "") {
                QMessageBox::warning(this, "Warning", "numar invalid");
            }
            else {
                service.service_generate_books_cart(generate_number);
                load_data(service.get_cart().get_all());
            }
        }
        catch (ValidatorError& exception) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(exception.get_error_message()));
        }
        });

    QObject::connect(button_clear_cart, &QPushButton::clicked, [&](){
        service.service_clear_cart();
        load_data(service.get_cart().get_all());
        });

    QObject::connect(button_raport, &QPushButton::clicked, [&]() {
        QWidget* raport_window = new QWidget;
        raport_window->setWindowTitle("Raport dupa gen");
        QHBoxLayout* layout = new QHBoxLayout;
        raport_window->setLayout(layout);

        auto books = service.service_raport_gen();
        QTableWidget* table_raport = new QTableWidget{ int(books.size()), 2 };
        table_raport->setHorizontalHeaderItem(0, new QTableWidgetItem("Gen"));
        table_raport->setHorizontalHeaderItem(1, new QTableWidgetItem("Aparitii"));
        int index = 0;
        for (const auto& book : books)
        {
            table_raport->setItem(index, 0, new QTableWidgetItem(QString::fromStdString(book.first)));
            table_raport->setItem(index, 1, new QTableWidgetItem(QString::number(book.second)));
            index++;
        }
        layout->addWidget(table_raport);
        raport_window->show();
        });

}
