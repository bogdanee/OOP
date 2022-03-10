#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QPainter>
#include "service.h"
#include "Observer.h"

class CartGUI: public QWidget, public Observer
{
	Q_OBJECT

	friend class GUI;
public:
	CartGUI(Service& srv);

private:
	Service& service;

	QListWidget* cart_list = new QListWidget;

	QPushButton* button_clear = new QPushButton{ "&Golire cos" };
	QPushButton* button_export = new QPushButton{ "&Export" };
	QPushButton* button_generate = new QPushButton{ "&Genereaza" };

	QLineEdit* text_id = new QLineEdit;
	QLineEdit* text_title = new QLineEdit;
	QLineEdit* text_author = new QLineEdit;
	QLineEdit* text_gen = new QLineEdit;
	QLineEdit* text_year = new QLineEdit;
	QLineEdit* text_generate = new QLineEdit;

	void init_GUI();
	void load_data(const std::vector<Book>& books);
	void connect_signals();

	void update() override;
};

class CartReadOnlyGUI : public QWidget, public Observer
{
	Q_OBJECT

	friend class GUI;
public:
	CartReadOnlyGUI(Service& srv) : service{ srv } {
		service.addObserver(this);
		setWindowTitle("Desene");
};
private:
	Service& service;

	void paintEvent(QPaintEvent* event) override {
		QPainter painter{ this };
		for (auto book : service.get_cart().get_all())
		{
			painter.drawRect(rand() % 300 + 1, rand() % 300 + 1, rand() % 100 + 10, rand() % 100 + 10);
		}
	}

	void update() override;
};
