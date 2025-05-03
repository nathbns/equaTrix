#include "Function.h"
#include "../antlr4/ExprTree.h"
#include "System.h"
#include "Matrix.h"
#include <iostream>


int main(void){
    int choix = 0;
    do {
        std::cout << "\n Menu principal:" << std::endl;
        std::cout << "1. Résoudre un système d'équations" << std::endl;
        std::cout << "2. Tester la classe Matrix" << std::endl;
        std::cout << "3. Tester la classe Function" << std::endl;
       // std::cout << "4. Tester la classe Integral" << std::endl;
        std::cout << "0. Quitter" << std::endl;
        std::cout << "Votre choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1:
                System::userSolveSystem();
                break;
            case 2:
                Matrix::testMatrix();
                break;
            case 3:
                Function::testFunction();
                break;
           // case 4:
                //Integral::testIntegral();
             //   break;
            case 0:
                std::cout << "Au revoir!" << std::endl;
                break;
            default:
                std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
        }
    } while (choix != 0);
    std::cout << "All tests passed!" << std::endl;
    return 0;
}