/*  
 * model.h
 * 
 * This header file defines the structures and functions used in the game model.
 * 
 * Author: Tameem Aboueldahab, Andres Isturiz 
 * Date: 28/02/25  
 */

 #ifndef MODEL_H
 #define MODEL_H
 
 /* Screen Dimensions */
 #define SCREEN_WIDTH  640
 #define SCREEN_HEIGHT 400
 
 /* Object Sizes */
 #define BASKET_Y      360
 #define BASKET_WIDTH  32
 #define BASKET_HEIGHT  8
 #define FRUIT_WIDTH   16
 #define FRUIT_HEIGHT  16
 #define BOMB_WIDTH    16
 #define BOMB_HEIGHT   16
 
 /* Basket Structure */
 typedef struct {
     int x;          /* Horizontal position */
     int velocity;   /* Movement speed */
     int direction;
 } Basket;
 
 /* Fruit Structure */
 typedef struct {
     int x, y;       /* Position */
     int velocity;   /* Falling speed */
     int value;      /* Points awarded for catching */
     int active;
 } Fruit;
 
 /* Bomb Structure */
 typedef struct {
     int x, y;       /* Position */
     int velocity;   /* Falling speed */
     int active;
 } Bomb;
 
 /* Score Structure */
 typedef struct {
     int current_score;
     int high_score;
 } Score;
 
 /* Game State Structure */
 typedef struct {
     Basket basket;
     Fruit fruits[40];  /* Array of falling fruits */
     Bomb bombs[50];     /* Array of falling bombs */
     Score score;
     unsigned long start_time;
     int game_over;
 } GameState;
 
 /* Function Prototypes */
 void initialize_game(GameState *game);
 void move_basket(Basket *basket, int direction);
 void update_fruits(Fruit *fruits, unsigned long start_time);
 void update_bombs(Bomb *bombs, Fruit *fruits, unsigned long start_time);
 int check_collision(Basket *basket, Fruit *fruit);
 int check_bomb_collision(Basket *basket, Bomb *bomb);
 int get_elapsed_seconds(unsigned long start_time);
 int get_random_position(int range);
 int get_random_offset();
 #endif /* MODEL_H */
 