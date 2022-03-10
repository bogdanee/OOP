#include "GUI.h"
#include <QtWidgets/QApplication>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "tests.h"
#include <iostream>
#include "repository.h"
#include "service.h"
#include "ui.h"
#include "FileRepository.h"
#include "LabRepository.h"


int main(int argc, char* argv[])
{
    
    run_all_tests();
    std::string filename{ "books.txt" };
    FileRepository repo{ filename };
    //LabRepository repo{0.5};
    Cart cart{ repo };
    Service service{ repo, cart };
    
    
    QApplication a(argc, argv);
    GUI gui{service};
    gui.show();
    return a.exec();
    /*
    _CrtDumpMemoryLeaks();
    return 0;
    */
}
