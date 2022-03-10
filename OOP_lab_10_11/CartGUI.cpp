#include "CartGUI.h"
#include <QMessageBox>

CartGUI::CartGUI(Service& srv)
    : service{ srv }
{
    init_GUI();
    load_data(service.get_cart().get_all());
    connect_signals();
}

void CartGUI::init_GUI()
{
    setWindowTitle("Cos de cumparaturi");

    QHBoxLayout* main_layout = new QHBoxLayout{};
    setLayout(main_layout);

    auto left_layout = new QVBoxLayout;

    left_layout->addWidget(cart_list);

    left_layout->addWidget(button_clear);

    main_layout->addLayout(left_layout);

    auto right_layout = new QVBoxLayout;

    auto form_layout = new QFormLayout;
    form_layout->addRow("Id", text_id);
    form_layout->addRow("Titlu", text_title);
    form_layout->addRow("Autor", text_author);
    form_layout->addRow("Gen", text_gen);
    form_layout->addRow("An", text_year);
    form_layout->addRow("Numar generari", text_generate);
    right_layout->addLayout(form_layout);

    right_layout->addWidget(button_generate);
    right_layout->addWidget(button_export);

    main_layout->addLayout(right_layout);
}

void CartGUI::load_data(const std::vector<Book>& books)
{
    cart_list->clear();
    for (const auto& book : books)
    {
        try {
            service.service_find_book(book.get_id());
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(book.get_title()), cart_list);
            item->setData(Qt::UserRole, book.get_id());
        }
        catch (RepositoryError& exception){}
    }
}

void CartGUI::connect_signals()
{   
    service.addObserver(this);
    QObject::connect(cart_list, &QListWidget::itemSelectionChanged, [&]() {
        auto selection = cart_list->selectedItems();
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

    QObject::connect(button_clear, &QPushButton::clicked, [&]() {
        service.service_clear_cart();
        load_data(service.get_cart().get_all());
        });

    QObject::connect(button_export, &QPushButton::clicked, [&]() {
        service.service_export_cart();
        });

    QObject::connect(button_generate, &QPushButton::clicked, [&]() {
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
}

void CartGUI::update()
{
    load_data(service.get_cart().get_all());
}

void CartReadOnlyGUI::update()
{
    repaint();
}
