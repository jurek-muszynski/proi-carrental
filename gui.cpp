// #include <QApplication>
// #include <QTabWidget>
// #include <QWidget>
// #include <QVBoxLayout>
// #include <QLabel>
// #include <QPushButton>
// #include <QListWidget>
// #include <QLineEdit>
// #include <QJsonDocument>
// #include <QJsonArray>
// #include <QJsonObject>
// #include <QFile>
// #include "./src/customer.h"

// int main(int argc, char **argv)
// {
//     QApplication app(argc, argv);

//     QPalette palette = app.palette();
//     palette.setColor(QPalette::Window, Qt::lightGray);
//     app.setPalette(palette);

//     QTabWidget tabWidget;

//     QWidget *carsTab = new QWidget();
//     QVBoxLayout *carsLayout = new QVBoxLayout();
//     carsLayout->addWidget(new QLabel("Cars content goes here..."));
//     carsTab->setLayout(carsLayout);

//     QWidget *customersTab = new QWidget();
//     QVBoxLayout *customersLayout = new QVBoxLayout();

//     QListWidget *customersList = new QListWidget();
//     QFile file("/home/mlewko/proi/24l-proi-lewko-muszynski/build/customers.json");
//     if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
//         QJsonArray customersArray = doc.array();
//         for (int i = 0; i < customersArray.size(); i++) {
//             QJsonObject customerJson = customersArray[i].toObject();
//             QString customerId = customerJson["id"].toString();
//             QString customerName = customerJson["name"].toString();
//             QString customerItem = customerId + ": " + customerName;
//             customersList->addItem(customerItem);
//         }
//         file.close();
//     }

//     QLineEdit *firstNameInput = new QLineEdit();
//     QLineEdit *lastNameInput = new QLineEdit();
//     QPushButton *addCustomerButton = new QPushButton("Add Customer");
//     QPushButton *removeCustomerButton = new QPushButton("Remove Customer");

//     int currentCustomerId = 1;

//     QObject::connect(addCustomerButton, &QPushButton::clicked, [=]() mutable {
//         QString customerName = firstNameInput->text() + " " + lastNameInput->text();
//         QString customerItem = QString::number(currentCustomerId) + ": " + customerName;
//         customersList->addItem(customerItem);

//         // Create a new customer and add it to the JSON file
//         Customer newCustomer(QString::number(currentCustomerId).toStdString(), customerName.toStdString(), "");
//         QJsonObject newCustomerJson;
//         newCustomerJson["id"] = QString::fromStdString(newCustomer.getId());
//         newCustomerJson["name"] = QString::fromStdString(newCustomer.getName());
//         newCustomerJson["contact"] = QString::fromStdString(newCustomer.getContact());

//         QFile file("customers.json");
//         file.open(QIODevice::ReadWrite | QIODevice::Text);
//         QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
//         QJsonArray customersArray = doc.array();
//         customersArray.append(newCustomerJson);
//         doc.setArray(customersArray);
//         file.write(doc.toJson());
//         file.close();

//         currentCustomerId++;
//         firstNameInput->clear();
//         lastNameInput->clear();
//     });

//     QObject::connect(removeCustomerButton, &QPushButton::clicked, [=]() {
//         delete customersList->currentItem();
//     });

//     customersLayout->addWidget(new QLabel("First Name:"));
//     customersLayout->addWidget(firstNameInput);
//     customersLayout->addWidget(new QLabel("Last Name:"));
//     customersLayout->addWidget(lastNameInput);
//     customersLayout->addWidget(addCustomerButton);
//     customersLayout->addWidget(removeCustomerButton);
//     customersLayout->addWidget(customersList);
//     customersTab->setLayout(customersLayout);

//     tabWidget.addTab(carsTab, "Cars");
//     tabWidget.addTab(customersTab, "Customers");

//     tabWidget.resize(800, 600);  // Set the window size to 800x600

//     tabWidget.show();

//     return app.exec();
// }