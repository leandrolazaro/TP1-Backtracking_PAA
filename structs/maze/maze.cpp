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

            mazeShowMaze(&(_maze->_cell), _maze->sizeX, _maze->sizeY);
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

                if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==door){
                    _maze->keysNumber+=1;
                }else if(_maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX]._typeCell==key){
                    _maze->keysNumber-=1;
                }
                _maze->_cell[backtrackingCoordinateY][backtrackingCoordinateX].pathUsed=0;

                stackStack(exitRoute, backtrackingCoordinateX, backtrackingCoordinateY);
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
            printf("Labirinto sem saida\n");
        }
    #endif
    #ifndef DEBUG
        if(mazeMoveStudent(_maze, _maze->studentCoordinateY, _maze->studentCoordinateX, &sucessCoordinateY, &sucessCoordinateX, &movements, exitRoute)){
            printf("Movimentos: %d\nCoordenada de chegada: %d, %d\n", movements, sucessCoordinateY, sucessCoordinateX);
        }else{
            printf("Movimentos: %d\n", movements);
            printf("Labirinto sem saida\n");
        }
    #endif
}

void mazeShowMaze(cell ***_cell, int sizeX, int sizeY){
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

void mazeDeleteMaze(maze *_maze){
    if(_maze!=NULL){
        for (int i=0; i < _maze->sizeY; i++){
            delete(_maze->_cell[i]); 
        } 
        delete(_maze->_cell);
        delete(_maze);
    }
}

void mazeInitRandomMaze(maze *_maze, int dificult){
    int sizeY;
    int sizeX;
    int wallQuantity;
    int limiteDoorPerWallQuantity;
    int amountkeysOnFloor;
    int keysQuantity;
    int probabilidadeDePorta=5;
    srand(time(0));

    //Facil
    if(dificult==0){
        sizeY=(rand() % (10 - 5 + 1)) + 5;
        sizeX=(rand() % (10 - 5 + 1)) + 5;
        wallQuantity=(rand() % (5 - 0 + 1)) + 0;
        keysQuantity=(rand() % (5 - 0 + 1)) + 0;
        limiteDoorPerWallQuantity=(rand() % (5 - 0 + 1)) + 0;
        amountkeysOnFloor=(rand() % (10 - 0 + 1)) + 0;
    //Medio
    }else if(dificult==1){
        sizeY=(rand() % (20 - 10 + 1)) + 10;
        sizeX=(rand() % (20 - 10 + 1)) + 10;
        wallQuantity=(rand() % (20 - 10 + 1)) + 10;
        keysQuantity=(rand() % (20 - 0 + 1)) + 0;
        limiteDoorPerWallQuantity=(rand() % (2 - 0 + 1)) + 0;
        amountkeysOnFloor=(rand() % (5 - 0 + 1)) + 0;
    //Difícil
    }else{
        sizeY=(rand() % (30 - 20 + 1)) + 20;
        sizeX=(rand() % (300 -20 + 1)) + 20;
        wallQuantity=(rand() % (15 - 10 + 1)) + 10;
        keysQuantity=(rand() % (15 - 0 + 1)) + 0;
        limiteDoorPerWallQuantity=(rand() % (2 - 0 + 1)) + 0;
        amountkeysOnFloor=(rand() % (2 - 0 + 1)) + 0;
    }

    _maze->sizeY=sizeY;
    _maze->sizeX=sizeX;
    _maze->keysNumber=keysQuantity;
    (_maze->_cell)=(cell**)malloc((_maze->sizeY)*sizeof(cell*));

    //Alocação do labirinto na memória
    for (int i=0; i < _maze->sizeY; i++){

        (_maze->_cell)[i]=(cell*)malloc((_maze->sizeX)*sizeof(cell)); 

        for (int j = 0; j < _maze->sizeX; j++){
            if(i==0){ 
                _maze->_cell[i][j]._typeCell=output;
            }else{
                _maze->_cell[i][j]._typeCell=empty;
            }
            _maze->_cell[i][j].pathUsed=0;
        }
    }

    int positionY;
    int positionX;
    int wallOrientation;
    int wallSize;
    int doorQuantity;

    //Define aleatoriamente a posição do estudade
    do{
        positionX=(rand() % ((sizeX-1) - 0 + 1)) + 0;
    }while(_maze->_cell[sizeY-1][positionX]._typeCell!=empty);

    _maze->studentCoordinateY=sizeY-1;
    _maze->studentCoordinateX=positionX;
    _maze->_cell[sizeY-1][positionX]._typeCell=student;

    //Coloca paredes em locais aleatórios
    for(int i=0; i<wallQuantity; i++){
        doorQuantity=0;
        //Encontra uma posição central para a parede
        do{
            positionY=(rand() % ((sizeY-1) - 0 + 1)) + 0;
            positionX=(rand() % ((sizeX-1) - 0 + 1)) + 0;  
        }while(_maze->_cell[positionY][positionX]._typeCell!=empty || positionY==0);
        wallOrientation=(rand() % (1 - 0 + 1)) + 0;

        //Parede na horizontal
        if(wallOrientation){
            wallSize=(rand() % ((sizeY/2) - 0 + 1)) + 0;
            for(int y=0; y<wallSize && positionY-y>=0; y++){
                if(_maze->_cell[positionY-y][positionX]._typeCell==empty){
                    if(doorQuantity<limiteDoorPerWallQuantity){
                        if(((rand() % (probabilidadeDePorta - 0 + 1)) + 0)==0){
                            _maze->_cell[positionY-y][positionX]._typeCell=door;
                        }else{
                            _maze->_cell[positionY-y][positionX]._typeCell=wall;
                        }
                    }else{
                        _maze->_cell[positionY-y][positionX]._typeCell=wall;
                    }
                }
            }
            for(int y=0; y<wallSize && positionY+y<sizeY; y++){
                if(_maze->_cell[positionY+y][positionX]._typeCell==empty){
                    if(doorQuantity<limiteDoorPerWallQuantity){
                        if(((rand() % (probabilidadeDePorta - 0 + 1)) + 0)==0){
                            _maze->_cell[positionY+y][positionX]._typeCell=door;
                        }else{
                            _maze->_cell[positionY+y][positionX]._typeCell=wall;
                        }
                    }else{
                        _maze->_cell[positionY+y][positionX]._typeCell=wall;
                    }
                }
            }
        //Parede na vertical
        }else{
            wallSize=(rand() % ((sizeX/2) - 0 + 1)) + 0;
            for(int x=0; x<wallSize && positionX-x>=1; x++){
                if(_maze->_cell[positionY][positionX-x]._typeCell==empty){
                    if(doorQuantity<limiteDoorPerWallQuantity){
                        if(((rand() % (probabilidadeDePorta - 0 + 1)) + 0)==0){
                            _maze->_cell[positionY][positionX-x]._typeCell=door;
                        }else{
                            _maze->_cell[positionY][positionX-x]._typeCell=wall;
                        }
                    }else{
                        _maze->_cell[positionY][positionX-x]._typeCell=wall;
                    }
                }
            }
            for(int x=0; x<wallSize && positionX+x<sizeX; x++){
                if(_maze->_cell[positionY][positionX+x]._typeCell==empty){
                    if(doorQuantity<limiteDoorPerWallQuantity){
                        if(((rand() % (probabilidadeDePorta - 0 + 1)) + 0)==0){
                            _maze->_cell[positionY][positionX+x]._typeCell=door;
                        }else{
                            _maze->_cell[positionY][positionX+x]._typeCell=wall;
                        }
                    }else{
                        _maze->_cell[positionY][positionX+x]._typeCell=wall;
                    }
                }
            }
        }
    }

    //Coloca chaves em locais aleatórios
    for(int i=0; i<amountkeysOnFloor; i++){
        do{
            positionY=(rand() % ((sizeY-1) - 0 + 1)) + 0;
            positionX=(rand() % ((sizeX-1) - 0 + 1)) + 0;
        }while(_maze->_cell[positionY][positionX]._typeCell!=empty || positionY==0);

        _maze->_cell[positionY][positionX]._typeCell=key;
    }

    mazeShowMaze(&(_maze->_cell), _maze->sizeX, _maze->sizeY);

}

void mazeWidthSearch(maze* _maze){
    row *_row=NULL;
    rowInitRow(&(_row), _maze->studentCoordinateY, _maze->studentCoordinateX, _maze->keysNumber);
    _row=mazeWidthSearchAlghoritm(_maze, _row);
    if(_row==NULL){
        printf("Labirinto sem saída\n");
    }
    rowShowAllPreviousNode(_row);
    //rowDeleteRow(_row);
}
row* mazeWidthSearchAlghoritm(maze* _maze, row* _row){
    row *tempRow;
    cell *tempCell;
    int count=0;
    while(_row!=NULL && count<9999999999){
        if(_row->X-1>=0){
            tempRow=rowSearchNode(_row, _row->Y, _row->X-1);
            if(tempRow==NULL){
                tempCell=&(_maze->_cell[_row->Y][_row->X-1]);
                if(tempCell->_typeCell==empty){
                    rowInsertNode(_row, _row->Y, _row->X-1, _row->keysQuantity);
                }else if(tempCell->_typeCell==door){
                    if(_row->keysQuantity>0){
                        rowInsertNode(_row, _row->Y, _row->X-1, _row->keysQuantity-1);
                    }
                }else if(tempCell->_typeCell==key){
                    rowInsertNode(_row, _row->Y, _row->X-1, _row->keysQuantity+1);
                }else if(tempCell->_typeCell==output){
                    rowInsertNode(_row, _row->Y, _row->X-1, _row->keysQuantity);
                    return rowSearchLastNode(_row);
                }
            }
        }
        if(_row->Y-1>=0){
            tempRow=rowSearchNode(_row, _row->Y-1, _row->X);
            if(tempRow==NULL){
                tempCell=&(_maze->_cell[_row->Y-1][_row->X]);
                if(tempCell->_typeCell==empty){
                    rowInsertNode(_row, _row->Y-1, _row->X, _row->keysQuantity);
                }else if(tempCell->_typeCell==door){
                    if(_row->keysQuantity>0){
                        rowInsertNode(_row, _row->Y-1, _row->X, _row->keysQuantity-1);
                    }
                }else if(tempCell->_typeCell==key){
                    rowInsertNode(_row, _row->Y-1, _row->X, _row->keysQuantity+1);
                }else if(tempCell->_typeCell==output){
                    rowInsertNode(_row, _row->Y-1, _row->X, _row->keysQuantity);
                    return rowSearchLastNode(_row);
                }
            }
        }
        if(_row->X+1<_maze->sizeX){
            tempRow=rowSearchNode(_row, _row->Y, _row->X+1);
            if(tempRow==NULL){
                tempCell=&(_maze->_cell[_row->Y][_row->X+1]);
                if(tempCell->_typeCell==empty){
                    rowInsertNode(_row, _row->Y, _row->X+1, _row->keysQuantity);
                }else if(tempCell->_typeCell==door){
                    if(_row->keysQuantity>0){
                        rowInsertNode(_row, _row->Y, _row->X+1, _row->keysQuantity-1);
                    }
                }else if(tempCell->_typeCell==key){
                    rowInsertNode(_row, _row->Y, _row->X+1, _row->keysQuantity+1);
                }else if(tempCell->_typeCell==output){
                    rowInsertNode(_row, _row->Y, _row->X+1, _row->keysQuantity);
                    return rowSearchLastNode(_row);
                }
            }
        }
        if(_row->Y+1<_maze->sizeY){
            tempRow=rowSearchNode(_row, _row->Y+1, _row->X);
            if(tempRow==NULL){
                tempCell=&(_maze->_cell[_row->Y+1][_row->X]);
                if(tempCell->_typeCell==empty){
                    rowInsertNode(_row, _row->Y+1, _row->X, _row->keysQuantity);
                }else if(tempCell->_typeCell==door){
                    if(_row->keysQuantity>0){
                        rowInsertNode(_row, _row->Y+1, _row->X, _row->keysQuantity-1);
                    }
                }else if(tempCell->_typeCell==key){
                    rowInsertNode(_row, _row->Y+1, _row->X, _row->keysQuantity+1);
                }else if(tempCell->_typeCell==output){
                    rowInsertNode(_row, _row->Y+1, _row->X, _row->keysQuantity);
                    return rowSearchLastNode(_row);
                }
            }
        }
        _row=_row->next;
        count++;
    }
    return NULL;
}