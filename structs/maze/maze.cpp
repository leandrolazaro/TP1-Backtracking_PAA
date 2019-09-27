#include "maze.hpp"
#include "../stack/stack.hpp"

void mazeInitMaze(maze *_maze, char *fileName){
    
    char path[100]="././inputFiles/";
    FILE *file=NULL;
    char *line=NULL;
    char *temp=(char*)malloc(sizeof(char));
    size_t len = 0;
    ssize_t read;
    int typeCellNum=1;

    strcat(path, fileName);

    file=fopen(path, "r");

    if(file != NULL){
        if((read = getline(&line, &len, file)) != -1) {
            //printf("Retrieved line of length %zu:\n", read);
            //printf("%s", line);

            _maze->sizeY= atoi(strtok(line," "));
            _maze->sizeX= atoi(strtok(NULL, " "));
            _maze->keysNumber=atoi(strtok(NULL, " "));


            (_maze->_cell)=(cell**)malloc((_maze->sizeY)*sizeof(cell*));

            for (int i=0; i < _maze->sizeY; i++){

                (_maze->_cell)[i]=(cell*)malloc((_maze->sizeX)*sizeof(cell)); 

                for (int j = 0; j < _maze->sizeX; j++){ 

                    (*temp)=fgetc(file);

                    if((*temp)=='\n'){
                        (*temp)=fgetc(file);
                    }

                    (_maze->_cell)[i][j].pathUsed=0;

                    typeCellNum=atoi(temp);
                    
                    switch (typeCellNum){
                        case 0:
                            (_maze->_cell)[i][j]._typeCell=student;
                            (_maze->studentCoordinateY)=i;
                            (_maze->studentCoordinateX)=j;
                            break;
                        case 1:
                            (_maze->_cell)[i][j]._typeCell=empty;
                            break;
                        case 2:
                            (_maze->_cell)[i][j]._typeCell=wall;
                            break;
                        case 3:
                            (_maze->_cell)[i][j]._typeCell=door;
                            break;                                
                        case 4:
                            (_maze->_cell)[i][j]._typeCell=key;
                            break;
                        case 5:
                            (_maze->_cell)[i][j]._typeCell=output;
                            break;                                
                        default:
                            (_maze->_cell)[i][j]._typeCell=empty;
                            break;
                    }
                }
            }  

            mazeMallocCellMaze(&(_maze->_cell), _maze->sizeX, _maze->sizeY);
        }   
    }    

}

#ifdef DEBUG

    int mazeMoveStudent(maze *_maze, int backtrackingCoordinateY, int backtrackingCoordinateX, int *sucessCoordinateY, int *sucessCoordinateX, int *movements, int *recursiveCalls, stack ** exitRoute){
        *recursiveCalls+=1;
        if(backtrackingCoordinateY>=0 && backtrackingCoordinateY<_maze->sizeY && backtrackingCoordinateX>=0 && backtrackingCoordinateX<_maze->sizeX){
            if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==output){
                (*sucessCoordinateY)=backtrackingCoordinateY;
                (*sucessCoordinateX)=backtrackingCoordinateX;
                stackStack(exitRoute, backtrackingCoordinateY, backtrackingCoordinateX);

                return 1;
            }else if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell!=wall && !(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX].pathUsed)){
                if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==door){
                    if(_maze->keysNumber<=0){
                        return 0;
                    }
                    _maze->keysNumber-=1;
                }else if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==key){
                    _maze->keysNumber+=1;
                }
                _maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX].pathUsed=1;
                *movements+=1;
                //printf("Avanco: %d, %d\n", backtrackingCoordinateY, backtrackingCoordinateX);
                if(!mazeMoveStudent(_maze, backtrackingCoordinateY, backtrackingCoordinateX-1, sucessCoordinateY, sucessCoordinateX, movements, recursiveCalls, exitRoute)){
                    if(!mazeMoveStudent(_maze, backtrackingCoordinateY-1, backtrackingCoordinateX, sucessCoordinateY, sucessCoordinateX, movements, recursiveCalls, exitRoute)){
                        if(!mazeMoveStudent(_maze, backtrackingCoordinateY, backtrackingCoordinateX+1, sucessCoordinateY, sucessCoordinateX, movements, recursiveCalls, exitRoute)){
                            if(!mazeMoveStudent(_maze, backtrackingCoordinateY+1, backtrackingCoordinateX, sucessCoordinateY, sucessCoordinateX, movements, recursiveCalls, exitRoute)){
                                *movements+=1;
                                if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==door){
                                    _maze->keysNumber+=1;
                                }else if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==key){
                                    _maze->keysNumber-=1;
                                }
                                _maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX].pathUsed=0;
                                //printf("Retorno: %d, %d\n", backtrackingCoordinateY, backtrackingCoordinateX);
                                return 0;
                            }
                        }
                    }
                }

                stackStack(exitRoute, backtrackingCoordinateY, backtrackingCoordinateX);
                return 1;
            }

            
        }

        return 0;
    }

#endif
#ifndef DEBUG

    int mazeMoveStudent(maze *_maze, int backtrackingCoordinateY, int backtrackingCoordinateX, int *sucessCoordinateY, int *sucessCoordinateX, int *movements, stack ** exitRoute){
        if(backtrackingCoordinateY>=0 && backtrackingCoordinateY<_maze->sizeY && backtrackingCoordinateX>=0 && backtrackingCoordinateX<_maze->sizeX){
            if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==output){
                (*sucessCoordinateY)=backtrackingCoordinateY;
                (*sucessCoordinateX)=backtrackingCoordinateX;
                stackStack(exitRoute, backtrackingCoordinateY, backtrackingCoordinateX);

                return 1;
            }else if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell!=wall && !(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX].pathUsed)){
                if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==door){
                    if(_maze->keysNumber<=0){
                        return 0;
                    }
                    _maze->keysNumber-=1;
                }else if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==key){
                    _maze->keysNumber+=1;
                }
                _maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX].pathUsed=1;
                *movements+=1;
                //printf("Avanco: %d, %d\n", backtrackingCoordinateY, backtrackingCoordinateX);
                if(!mazeMoveStudent(_maze, backtrackingCoordinateY, backtrackingCoordinateX-1, sucessCoordinateY, sucessCoordinateX, movements, exitRoute)){
                    if(!mazeMoveStudent(_maze, backtrackingCoordinateY-1, backtrackingCoordinateX, sucessCoordinateY, sucessCoordinateX, movements, exitRoute)){
                        if(!mazeMoveStudent(_maze, backtrackingCoordinateY, backtrackingCoordinateX+1, sucessCoordinateY, sucessCoordinateX, movements, exitRoute)){
                            if(!mazeMoveStudent(_maze, backtrackingCoordinateY+1, backtrackingCoordinateX, sucessCoordinateY, sucessCoordinateX, movements, exitRoute)){
                                *movements+=1;
                                if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==door){
                                    _maze->keysNumber+=1;
                                }else if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==key){
                                    _maze->keysNumber-=1;
                                }
                                _maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX].pathUsed=0;
                                //printf("Retorno: %d, %d\n", backtrackingCoordinateY, backtrackingCoordinateX);
                                return 0;
                            }
                        }
                    }
                }

                stackStack(exitRoute, backtrackingCoordinateY, backtrackingCoordinateX);
                return 1;
            }

            
        }

        return 0;
    }

#endif

void mazeBacktrackingAlghoritmMaze(maze *_maze, stack ** exitRoute){
    int movements=0;
    int sucessCoordinateX=0;
    int sucessCoordinateY=0;
    stackInitStack(exitRoute);
    #ifdef DEBUG
        int recursiveCalls=0;
        if(mazeMoveStudent(_maze, _maze->studentCoordinateY, _maze->studentCoordinateX, &sucessCoordinateY, &sucessCoordinateX, &movements, &recursiveCalls, exitRoute)){
            printf("Movimentos: %d\nCoordenada de chegada: %d, %d\n", movements, sucessCoordinateY, sucessCoordinateX);
            printf("Chamadas recursivas: %d\n", recursiveCalls);
        }else{
            printf("Movimentos: %d\n", movements);
            printf("Chamadas recursivas: %d\n", recursiveCalls);
            printf("Labirinto sem saida");
        }
    #endif
    #ifndef DEBUG
        if(mazeMoveStudent(_maze, _maze->studentCoordinateY, _maze->studentCoordinateX, &sucessCoordinateY, &sucessCoordinateX, &movements, exitRoute)){
            printf("Movimentos: %d\nCoordenada de chegada: %d, %d\n", movements, sucessCoordinateY, sucessCoordinateX);
        }else{
            printf("Movimentos: %d\n", movements);
            printf("Labirinto sem saida");
        }
    #endif
}

void mazeMallocCellMaze(cell ***_cell, int sizeX, int sizeY){
    //(*_cell)=(cell**)malloc(sizeY*sizeof(cell*));
    for (int i=0; i < sizeY; i++){
        //(*_cell)[i]=(cell*)malloc(sizeX*sizeof(cell)); 
        for (int j = 0; j < sizeX; j++){ 
            //(*_cell)[i][j].pathUsed=0;
            printf("%d", (*_cell)[i][j]._typeCell);
        }
        printf("\n");
    } 
}