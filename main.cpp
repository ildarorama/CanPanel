#include "mainwindow.h"
#include <QApplication>


#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>




int main(int argc, char *argv[])
{





    int port=0;
    boost::property_tree::ptree pt;
      try {
          boost::property_tree::read_json("/source.json", pt);
          port=pt.get<int>("web_server_port");
    }catch(boost::property_tree::json_parser_error e) {
        std::cout << "Error" << e.what() << e.message();
        return -1;
    }
    std::cout << "Web server port: " << port;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
