#include "boundary.h"
#include "computeCellValues.h"

int is_valid(int x, int y, int z, int xlength){
    return (x >= 0) && (x <= xlength + 1) && (y >= 0) && (y <= xlength + 1) && (z >= 0) && (z <= xlength + 1);
}

void treatBoundary(double *collideField, unsigned int* flagField, const double * const wallVelocity, int xlength){
    
    int x, y, z, xinv, yinv, zinv, idx, idxinv, f;
    int Q = 19;
    int xl = xlength + 2;
    int xl2 = (xl)*(xl);
    double density, inner;
    
    // z-faces
    for(z = 0; z <= xlength + 1; z+= (xlength + 1) ){
        for(y = 0; y <= xlength + 1; y++) {
            for(x = 0; x <= xlength + 1; x++) {
                
                idx = z*xl2 + y*(xl) + x;
                
                f = flagField[idx];
                switch (f){
                    
                    case 1: // No Slip
                    for(int i = 0; i < Q; i++) {
                        //Define inverse block
                        xinv = x + LATTICEVELOCITIES[i][0];
                        yinv = y + LATTICEVELOCITIES[i][1];
                        zinv = z + LATTICEVELOCITIES[i][2];
                        
                        if(is_valid(xinv, yinv, zinv, xlength)){ //If the inverse cell is in the boundary or the domain
                            idxinv = zinv*xl2 + yinv*(xl) + xinv; 
                            if (flagField[idxinv]==FLUID){          //If the inverse cell is fluid
                                collideField[Q*idx+i] = collideField[Q*idxinv+18-i];
                            }
                        }
                    }
                    break;
                    
                    case 2: // Moving Wall
                    for(int i = 0; i < Q; i++) {
                        //Define inverse block
                        xinv = x + LATTICEVELOCITIES[i][0];
                        yinv = y + LATTICEVELOCITIES[i][1];
                        zinv = z + LATTICEVELOCITIES[i][2];
                        
                        if(is_valid(xinv, yinv, zinv, xlength)){ //If the inverse cell is in the boundary or the domain
                            idxinv = zinv*xl2 + yinv*(xl) + xinv; 
                            if (flagField[idxinv]==0){          //If the inverse cell is fluid
                                
                                computeDensity(&collideField[Q*idxinv], &density); //Density of the inverse cell
                                inner = LATTICEVELOCITIES[i][0]*wallVelocity[0] + LATTICEVELOCITIES[i][1]*wallVelocity[1] 
                                        + LATTICEVELOCITIES[i][2]*wallVelocity[2]; // dot_product(ci, Uwall)
                                
                                collideField[Q*idx+i] = collideField[Q*idxinv+18-i] + 2.0*LATTICEWEIGHTS[i]*density*inner/C_S/C_S;
                            }
                        }
                    }
                    break;
                    
                }
                
            }
        }
    }
    
    // y-faces
    for(z = 0; z <= xlength + 1; z++ ){
        for(y = 0; y <= xlength + 1; y+= (xlength + 1)) {
            for(x = 0; x <= xlength + 1; x++) {
                
                idx = z*xl2 + y*(xl) + x;
                
                f = flagField[idx];
                switch (f){
                    
                    case 1: // No Slip
                    for(int i = 0; i < Q; i++) {
                        //Define inverse block
                        xinv = x + LATTICEVELOCITIES[i][0];
                        yinv = y + LATTICEVELOCITIES[i][1];
                        zinv = z + LATTICEVELOCITIES[i][2];
                        
                        if(is_valid(xinv, yinv, zinv, xlength)){ //If the inverse cell is in the boundary or the domain
                            idxinv = zinv*xl2 + yinv*(xl) + xinv; 
                            if (flagField[idxinv]==FLUID){          //If the inverse cell is fluid
                                collideField[Q*idx+i] = collideField[Q*idxinv+18-i];
                            }
                        }
                    }
                    break;
                    
                    case 2: // Moving Wall
                    for(int i = 0; i < Q; i++) {
                        //Define inverse block
                        xinv = x + LATTICEVELOCITIES[i][0];
                        yinv = y + LATTICEVELOCITIES[i][1];
                        zinv = z + LATTICEVELOCITIES[i][2];
                        
                        if(is_valid(xinv, yinv, zinv, xlength)){ //If the inverse cell is in the boundary or the domain
                            idxinv = zinv*xl2 + yinv*(xl) + xinv; 
                            if (flagField[idxinv]==FLUID){          //If the inverse cell is fluid
                                
                                computeDensity(&collideField[Q*idxinv], &density); //Density of the inverse cell
                                inner = LATTICEVELOCITIES[i][0]*wallVelocity[0] + LATTICEVELOCITIES[i][1]*wallVelocity[1] 
                                        + LATTICEVELOCITIES[i][2]*wallVelocity[2]; // dot_product(ci, Uwall)
                                
                                collideField[Q*idx+i] = collideField[Q*idxinv+18-i] + 2.0*LATTICEWEIGHTS[i]*density*inner/C_S/C_S;
                            }
                        }
                    }
                    break;
                    
                }
                
            }
        }
    }
    
    // x-faces
    for(z = 0; z <= xlength + 1; z++ ){
        for(y = 0; y <= xlength + 1; y++) {
            for(x = 0; x <= xlength + 1; x+= (xlength + 1)) {
                
                idx = z*xl2 + y*(xl) + x;
                
                f = flagField[idx];
                switch (f){
                    
                    case 1: // No Slip
                    for(int i = 0; i < Q; i++) {
                        //Define inverse block
                        xinv = x + LATTICEVELOCITIES[i][0];
                        yinv = y + LATTICEVELOCITIES[i][1];
                        zinv = z + LATTICEVELOCITIES[i][2];
                        
                        if(is_valid(xinv, yinv, zinv, xlength)){ //If the inverse cell is in the boundary or the domain
                            idxinv = zinv*xl2 + yinv*(xl) + xinv; 
                            if (flagField[idxinv]==FLUID){          //If the inverse cell is fluid
                                collideField[Q*idx+i] = collideField[Q*idxinv+18-i];
                            }
                        }
                    }
                    break;
                    
                    case 2: // Moving Wall
                    for(int i = 0; i < Q; i++) {
                        //Define inverse block
                        xinv = x + LATTICEVELOCITIES[i][0];
                        yinv = y + LATTICEVELOCITIES[i][1];
                        zinv = z + LATTICEVELOCITIES[i][2];
                        
                        if(is_valid(xinv, yinv, zinv, xlength)){ //If the inverse cell is in the boundary or the domain
                            idxinv = zinv*xl2 + yinv*(xl) + xinv; 
                            if (flagField[idxinv]==FLUID){          //If the inverse cell is fluid
                                
                                computeDensity(&collideField[Q*idxinv], &density); //Density of the inverse cell
                                inner = LATTICEVELOCITIES[i][0]*wallVelocity[0] + LATTICEVELOCITIES[i][1]*wallVelocity[1] 
                                        + LATTICEVELOCITIES[i][2]*wallVelocity[2]; // dot_product(ci, Uwall)
                                
                                collideField[Q*idx+i] = collideField[Q*idxinv+18-i] + 2.0*LATTICEWEIGHTS[i]*density*inner/C_S/C_S;
                            }
                        }
                    }
                    break;
                    
                }
                
            }
        }
    }
    
}
