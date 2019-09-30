#include <stdio.h>
#include <stdlib.h>
#include "structs/cell/cell.hpp"
#include "structs/maze/maze.hpp"
#include "structs/stack/stack.hpp"

int main(){

    #ifdef DEBUG
        printf("x-x-x-x-x-x-x DEBUG MODE x-x-x-x-x-x-x\n");
    #endif

    maze * _maze=NULL;
    stack * exitRoute=NULL;
    int x, y;
    char fileName[100]="maze.txt";
    //mazeInitMaze(_maze, fileName);
    int option=1;

    while (option){
        switch (option){
            case 1:
                printf("Labirinto do ET Bilu\n");
                printf("1 - Mostrar este Menu\n");
                printf("2 - Carregar arquivo do labrinto\n");
                printf("3 - Mostra solução\n");
                printf("4 - Sair\n");
                scanf("%d", &option);
                break;
            case 2:
                mazeDeleteMaze(_maze);
                _maze=(maze*)malloc(sizeof(maze));
                printf("Digite o nome do arquivo txt:\n");
                scanf("%s", fileName);
                printf("Montando labirinto...\n");
                mazeInitMaze(_maze, fileName);
                printf("Labirinto montado com sucesso!\n");

                option=-1;

                break;
            case 3:
                mazeBacktrackingAlghoritmMaze(_maze, &exitRoute);            
                printf("Cooredanas de movimentação até a sáida:\n");
                while (exitRoute!=NULL){
                    stackUnstack(&exitRoute, &x, &y);
                    printf("%d, %d\n", x, y);
                }
                option=-1;
                
                break;
            case 4:
                printf("Obrigado por usar o Labririnto do ET Bilu. Busquem conhecimento!\n");
                option=0;
                break;
            
            default:
                printf("Digite outra opção ou digite 1 para mostrar o menu novamente\n");
                scanf("%d", &option);
                break;
        }
    }
    


}   