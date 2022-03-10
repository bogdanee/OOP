#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QTableWidget>
#include "ui_GUI.h"
#include "service.h"
#include "CartGUI.h"

class GUI : public QWidget
{
    Q_OBJECT

    friend class CartGUI;

public:
    GUI(Service& srv);

private:
    Service& service;

    QListWidget* list = new QListWidget;
    QTableWidget* table = new QTableWidget{0,4};

    QPushButton* button_add = new QPushButton{ "&Adauga" };
    QPushButton* button_delete = new QPushButton{ "&Sterge" };
    QPushButton* button_update = new QPushButton{ "&Modifica" };
    QPushButton* button_undo = new QPushButton{ "&Undo" };
    QPushButton* button_raport = new QPushButton{ "&Raport" };
    QPushButton* button_list = new QPushButton{ "&List" };
    QPushButton* button_sort_by_title = new QPushButton{ "&Titlu" };
    QPushButton* button_sort_by_author = new QPushButton{ "&Autor" };
    QPushButton* button_sort_by_year_and_gen = new QPushButton{ "&An si gen" };
    QPushButton* button_filtre_by_title = new QPushButton{ "&Titlu" };
    QPushButton* button_filtre_by_year = new QPushButton{ "&An" };
    QPushButton* button_add_to_cart = new QPushButton{ "&Adauga in cos" };
    QPushButton* button_generate_cart = new QPushButton{ "&Genereaza cos" };
    QPushButton* button_clear_cart = new QPushButton{ "&Goleste cos" };
    QPushButton* button_cart = new QPushButton{ "&Deschide cos" };
    QPushButton* button_cart_readonly = new QPushButton{ "&Deschide cos(read only)" };
    
    QLineEdit* text_id = new QLineEdit;
    QLineEdit* text_title = new QLineEdit;
    QLineEdit* text_author = new QLineEdit;
    QLineEdit* text_gen = new QLineEdit;
    QLineEdit* text_year = new QLineEdit;
    QLineEdit* text_generate = new QLineEdit;

    void init_GUI();
    void load_data(const std::vector<Book>& books);
    void connect_signals();
    
    

};
