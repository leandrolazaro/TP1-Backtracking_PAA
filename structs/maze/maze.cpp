#include "maze.hpp"

void initMaze(maze *_maze, char *fileName){
    
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

            mallocCellMaze(&(_maze->_cell), _maze->sizeX, _maze->sizeY);
        }   
    }    

}

int moveStudent(maze *_maze, int backtrackingCoordinateY, int backtrackingCoordinateX, int *sucessCoordinateY, int *sucessCoordinateX, int *movements){
    if(backtrackingCoordinateY>=0 && backtrackingCoordinateY<_maze->sizeY && backtrackingCoordinateX>=0 && backtrackingCoordinateX<_maze->sizeX){
        if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==output){
            (*sucessCoordinateY)=backtrackingCoordinateY;
            (*sucessCoordinateX)=backtrackingCoordinateX;
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
            printf("%d, %d\n", backtrackingCoordinateY, backtrackingCoordinateX);
            if(!moveStudent(_maze, backtrackingCoordinateY, backtrackingCoordinateX-1, sucessCoordinateY, sucessCoordinateX, movements)){
                if(!moveStudent(_maze, backtrackingCoordinateY-1, backtrackingCoordinateX, sucessCoordinateY, sucessCoordinateX, movements)){
                    if(!moveStudent(_maze, backtrackingCoordinateY, backtrackingCoordinateX+1, sucessCoordinateY, sucessCoordinateX, movements)){
                        if(!moveStudent(_maze, backtrackingCoordinateY+1, backtrackingCoordinateX, sucessCoordinateY, sucessCoordinateX, movements)){
                            *movements+=1;
                            if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==door){
                                _maze->keysNumber+=1;
                            }else if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==key){
                                _maze->keysNumber-=1;
                            }
                            _maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX].pathUsed=0;
                            printf("%d, %d\n", backtrackingCoordinateY, backtrackingCoordinateX);
                            return 0;
                        }
                    }
                }
            }

            return 1;
        }

        
    }

    return 0;
}

void backtrackingAlghoritmMaze(maze *_maze){
    int movements=0;
    int sucessCoordinateX=0;
    int sucessCoordinateY=0;
    if(moveStudent(_maze, _maze->studentCoordinateY, _maze->studentCoordinateX, &sucessCoordinateY, &sucessCoordinateX, &movements)){
        printf("Movimentos: %d\nCoordenada de chegada: %d, %d\n", movements, sucessCoordinateY, sucessCoordinateX);
    }else{
        printf("Labirinto sem saida");
    }
}

void mallocCellMaze(cell ***_cell, int sizeX, int sizeY){
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