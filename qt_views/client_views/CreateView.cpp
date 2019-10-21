#include <iostream>
#include <QLineEdit>
#include "CreateView.h"
#include "ui_createView.h"

CreateView::CreateView(ProtocolSocket &ps, QWidget *parent) :
                        QDialog(parent),
                        ps(ps),
                        ui() {
    ui.setupUi(this);
}

void CreateView::on_btnBoxCreate_accepted() {
    std::vector<uint8_t> buffer(4096);
    std::string server_match_answer("ERROR");
    while (server_match_answer.substr(0,5) == "ERROR") {
        std::cout << "Write match name..." << "\n";
        QLineEdit *matchTxtIn = findChild<QLineEdit*>("matchTxtIn");
        std::string match_name = matchTxtIn->text().toStdString();
        std::cout << "EL Match " << match_name << "\n";
        ps.send(match_name);
        ps.receive(buffer);
        server_match_answer.assign(reinterpret_cast<const char *>(buffer.data()), buffer.size());
        buffer.clear(); buffer.resize(4096);
        std::cout << server_match_answer;
  }

    std::string server_username_answer("ERROR");
    while (server_username_answer.substr(0,5) == "ERROR") {
        std::cout << "Write your username..." << "\n";
        QLineEdit *usrTxtIn = findChild<QLineEdit*>("usrTxtIn");
        std::string username = usrTxtIn->text().toStdString();
        std::cout << "EL usuario " << username << "\n";
        ps.send(username);
        ps.receive(buffer);
        server_username_answer.assign(reinterpret_cast<const char *>(buffer.data()), buffer.size());
        buffer.clear(); buffer.resize(4096);
        std::cout << server_username_answer;
    }
    this->close();
}

CreateView::~CreateView() {}
