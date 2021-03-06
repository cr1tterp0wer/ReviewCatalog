#include<iostream>
#include<vector>
#include "Game.h"
#include "Cell.h"

using namespace std;

class GameOfLife : public Game{

   private:
     const int CELL_SIZE = 5;
     SDL_Rect rect;
     vector<Cell> cells;
     int pop;
     int x = 0;
     int y = 0;
     int live_count = 0;
     int row_width;
     int row_height;

     void update(){

       live_count = 0;
       vector<Cell> tmp = cells;
       
       for( int i = 0; i < pop; i++){
         
         x = i % (row_width) ;
         y = i / (row_width) ;

         //right
         if(  ( x + 1 ) < (row_width) ){
           live_count += cells.at( i + 1 ).getIsAlive() ? 1 : 0;
         }
         //left
         if(  ( x - 1 ) >= 0 ){
           live_count += cells.at( i - 1 ).getIsAlive() ? 1 : 0;
         }
         //top
         if( ( y - 1 ) >= 0 ){
           live_count += cells.at( i - (row_width) ).
             getIsAlive() ? 1 : 0;
         }
         //bottom
         if( ( y + 1 ) < row_height ){
           live_count += cells.at( i + (row_width) ).
             getIsAlive() ? 1 : 0;
         }
         //top-right
         if( ( x + 1 ) < (row_width)  &&  ( y - 1 ) >= 0 ){
           live_count += cells.at( i - (row_width) + 1 ).getIsAlive() ? 1 : 0;
         }
         //top-left
         if( ( x - 1 ) >= 0  &&  ( y - 1 ) >= 0 ){
           live_count += cells.at( i - (row_width) - 1 ).getIsAlive() ? 1 : 0;
         }
         //bottom-right
         if( ( x + 1 ) < (row_width)  &&  ( y + 1 ) < row_height ){
           live_count += cells.at( i + (row_width) + 1 ).getIsAlive() ? 1 : 0;
         }
         //bottom-left
         if( ( x - 1 ) >= 0 && ( y + 1 ) < ( window_height / CELL_SIZE ) ){
           live_count += cells.at( i + (row_width) - 1 ).getIsAlive() ? 1 : 0;
         }

         //1. Spawns + Survival
         if( live_count == 3 ){
           tmp.at( i ).spawn();
         }
         //2. Death by lonliness + overcrowding
         else if( live_count <= 1 || live_count >= 4 ){
           tmp.at( i ).despawn();
         }
         
         live_count = 0;
       }
       cells = tmp;
     };

     void render(){
       
        // Change color to black
        SDL_SetRenderDrawColor( renderer, 31, 31, 54, 0 );
        // Clear the window 
        SDL_RenderClear( renderer );

        // Change color to green + draw rect
        SDL_SetRenderDrawColor( renderer, 240, 240, 101, 255 );

        //RENDER CELLS
        for ( int i = 0; i < pop; i++ ){
          rect.x = cells.at( i ).getX() * CELL_SIZE;
          rect.y = cells.at( i ).getY() * CELL_SIZE;
          if( cells.at( i ).getIsAlive() )
            SDL_RenderFillRect( renderer, &rect );
        }

        // Render the changes above
        SDL_RenderPresent( renderer );
     };
    
     void initCells(){

       int x = 0;
       int y = 0;

       cells.push_back( Cell( x, y ) );
       for( int i = 1; i <= pop; i++ ){
         x = i % (row_width) ;
         y = i / (row_width) ;

         cells.push_back( Cell( x, y ) );
       }

     };
   public:
     GameOfLife( int w=800, int h=800 ) : Game( w, h ){

       pop = ( w / CELL_SIZE ) * ( h / CELL_SIZE );
       rect.w = CELL_SIZE;
       rect.h = CELL_SIZE;
       row_width  = ( window_width / CELL_SIZE ); 
       row_height = ( window_height / CELL_SIZE ); 

       initCells();
     }

     GameOfLife( char* t=(char *)"Game", 
                 int w=680, 
                 int h=480 ) : Game( t, w, h ){

       pop = ( w / CELL_SIZE ) * ( h / CELL_SIZE );
       rect.w = CELL_SIZE;
       rect.h = CELL_SIZE;
       row_width  = ( window_width / CELL_SIZE );
       row_height = ( window_height / CELL_SIZE ); 

       initCells();
     };
};
