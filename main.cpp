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
    int dificult;
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
                printf("3 - Gerar labirinto aleatório\n");
                printf("4 - Mostrar solução utilizando backing track\n");
                printf("5 - Mostrar melhor caminho utilizando pesquisa em largura\n");
                printf("6 - Sair\n");
                if(!scanf("%d", &option)){
                    printf("Error\n");
                    return 0;
                }
                break;
            case 2:
                mazeDeleteMaze(_maze);
                _maze=(maze*)malloc(sizeof(maze));
                printf("Digite o nome do arquivo txt:\n");
                if(!scanf("%s", fileName)){
                    printf("Error\n");
                    return 0;
                }
                
                printf("Montando labirinto...\n");
                mazeInitMaze(_maze, fileName);
                printf("Labirinto montado com sucesso!\n");

                option=-1;

                break;
            case 3:
                mazeDeleteMaze(_maze);
                _maze=(maze*)malloc(sizeof(maze));
                printf("Escolha uma dificuldade:\n");
                printf("0-Fácil:\n");
                printf("1-Médio\n");
                printf("2-Difícil\n");
                if(!scanf("%d", &dificult)){
                    printf("Error\n");
                    return 0;
                }
                printf("Montando labirinto....\n");
                mazeInitRandomMaze(_maze, dificult);
                printf("Labirinto montado com sucesso!\n");

                option=-1;

                break;
            case 4:
                mazeBacktrackingAlghoritmMaze(_maze, &exitRoute);            
                printf("Cooredanas de movimentação até a sáida:\n");
                while (exitRoute!=NULL){
                    stackUnstack(&exitRoute, &x, &y);
                    printf("%d, %d\n", x, y);
                }
                option=-1;
                
                break;
            case 5:
                printf("Cooredanas de movimentação até a sáida:\n");
                mazeWidthSearch(_maze);            
                option=-1;
                
                break;
            case 6:
                printf("Obrigado por usar o Labririnto do ET Bilu. Busquem conhecimento!\n");
                option=0;
                break;
            
            default:
                printf("Digite outra opção ou digite 1 para mostrar o menu novamente\n");
                if(!scanf("%d", &option)){
                    printf("Error\n");
                    return 1;
                }
                break;
        }
    }
    


}   