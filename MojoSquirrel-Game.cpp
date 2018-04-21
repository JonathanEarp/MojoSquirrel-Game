/*
//Objective:
Move a player bmp with arrow keys.
Collect 3 score bmp's with player bmp.
Keep score using text of amount of score bmp's collected.
Have 3 enemy bmp's move randomly and independant of player.
End game if player hits enemy, if score is 3, or if escape key is hit.

//Requirements:
Non-standard Allegro libraries ("allegro5/allegro.h", "allegro5/allegro_primitives.h", <allegro5/allegro_image.h>, <allegro5/allegro_font.h>, <allegro5/allegro_ttf.h>)
Math.h
data-control.ttf file for text
player.bmp, enemy.bmp, and score.bmp included in folder file for visuals

//Algorithm:
/*
struct gameobject
Init Allegro
Create and init drawobject function linked to bmp
create screen
create gameobject variables
create movement variables
Loop forever
read keyboard
if escape pressed end loop
if right pressed
increment x
if left pressed
decrement x
if up pressed
decrement y
if down pressed
increment y
drawobject function for each object on screen
enemy movement
scoring variables
clear buffer
show buffer on screen
wait
*/
#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h" 
#include <allegro5/allegro_image.h>
#include <math.h>
#include <allegro5/allegro_font.h> 
#include <allegro5/allegro_ttf.h>



//global variable for display
ALLEGRO_DISPLAY* g_display = NULL; //ALLEGRO_DISPLAY is a "user defined type" in Allegro. * shows a pointer
//global variable for font
ALLEGRO_FONT* g_font;
ALLEGRO_FONT* g_font1;

struct GameObject
{
	int x;
	int y;

	ALLEGRO_BITMAP* bmp;
};

struct AnimatedObject
{
	int x;
	int y;
	ALLEGRO_BITMAP* bmp; //current bitmap
	ALLEGRO_BITMAP* frames[48]; //animation frames
	ALLEGRO_BITMAP* idle; //idle bitmap
	int currentFrame; //frame number
};


//initialzie Allegro components
void InitAllegro(int W, int H)
{

	//initialize allegro
	if (!al_init())
	{
		printf("failed to initialize allegro!\n");
	}

	//initialize display screen
	g_display = al_create_display(W, H);
	if (!g_display)
	{
		printf("failed to create display!\n");
		//exit(0);
	}
	else
	{
		printf("ok");
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	//initialize keyboard
	if (!al_install_keyboard())
	{
		printf("failed to install keyboard!\n");
		//exit(0);
	}

	//initialize primitives
	if (!al_init_primitives_addon())
	{
		printf("failed to initialize primitives!\n");
		//exit(0);
	}

	//initialize image addon
	if (!al_init_image_addon())
	{
		printf("failed to initialize image addon!\n");
	}

	al_init_font_addon();
	al_init_ttf_addon();
	g_font = al_load_ttf_font("data-latin.ttf", 24, 0);
	g_font1 = al_load_ttf_font("data-latin.ttf", 40, 0);
	if (!g_font)
	{
		printf("failed to create font!\n");
		al_destroy_display(g_display);
		//exit(0);
	}
	if (!g_font1)
	{
		printf("failed to create font!\n");
		al_destroy_display(g_display);
		//exit(0);
	}
}

//End and clean up Allegro components
void EndAllegro()
{
	al_destroy_display(g_display);
}

//helper function for drawing a pixel
void PutPixel(int x, int y, int r, int g, int b)
{
	al_put_pixel(x, y, al_map_rgb(r, g, b));
}

//helper function for drawing a line
void DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	al_draw_line(x1, y1, x2, y2, al_map_rgb(r, g, b), 1);
}

//helper function to wait for a key
void WaitForKey(int k)
{
	ALLEGRO_KEYBOARD_STATE key_state;
	bool quit = false;
	while (!quit)
	{
		al_get_keyboard_state(&key_state);
		//end program
		if (al_key_down(&key_state, k))
		{
			quit = true;
		}

	}
}

//makng gameobject bitmap
void DrawObject(GameObject obj)
{
	al_draw_bitmap(obj.bmp, obj.x, obj.y, 0);
}

void DrawObject(AnimatedObject obj)
{
	al_draw_bitmap(obj.bmp, obj.x, obj.y, 0);
}


///////////////////////////////////////////////////////////////////////
//main function
///////////////////////////////////////////////////////////////////////

void main()
{
	//initialize
	int sw = 640;
	int sh = 480;
	InitAllegro(sw, sh);

	//keyboard data
	ALLEGRO_KEYBOARD_STATE key_state;

	//movie
	AnimatedObject m1;
	m1.x = m1.y = 0;
	m1.frames[0] = al_load_bitmap("Montage1.bmp");
	m1.frames[1] = al_load_bitmap("Montage2.bmp");
	m1.frames[2] = al_load_bitmap("Montage3.bmp");
	m1.frames[3] = al_load_bitmap("Montage4.bmp");
	m1.frames[4] = al_load_bitmap("Montage5.bmp");
	m1.frames[5] = al_load_bitmap("Montage6.bmp");
	m1.frames[6] = al_load_bitmap("Montage7.bmp");
	m1.frames[7] = al_load_bitmap("Montage8.bmp");
	m1.frames[8] = al_load_bitmap("Montage9.bmp");
	m1.frames[9] = al_load_bitmap("Montage10.bmp");
	m1.frames[10] = al_load_bitmap("Montage11.bmp");
	m1.frames[11] = al_load_bitmap("Montage12.bmp");
	m1.frames[12] = al_load_bitmap("Montage13.bmp");
	m1.frames[13] = al_load_bitmap("Montage14.bmp");
	m1.frames[14] = al_load_bitmap("Montage15.bmp");
	m1.frames[15] = al_load_bitmap("Montage16.bmp");
	m1.frames[16] = al_load_bitmap("Montage17.bmp");
	m1.frames[17] = al_load_bitmap("Montage18.bmp");
	m1.frames[18] = al_load_bitmap("Montage19.bmp");
	m1.frames[19] = al_load_bitmap("Montage20.bmp");
	m1.frames[20] = al_load_bitmap("Montage21.bmp");
	m1.frames[21] = al_load_bitmap("Montage22.bmp");
	m1.frames[22] = al_load_bitmap("Montage23.bmp");
	m1.frames[23] = al_load_bitmap("Montage24.bmp");
	m1.frames[24] = al_load_bitmap("Montage25.bmp");
	m1.frames[25] = al_load_bitmap("Montage26.bmp");
	m1.frames[26] = al_load_bitmap("Montage27.bmp");
	m1.frames[27] = al_load_bitmap("Montage28.bmp");
	m1.frames[28] = al_load_bitmap("Montage29.bmp");
	m1.frames[29] = al_load_bitmap("Montage30.bmp");
	m1.frames[30] = al_load_bitmap("Montage31.bmp");
	m1.frames[31] = al_load_bitmap("Montage32.bmp");
	m1.frames[32] = al_load_bitmap("Montage33.bmp");
	m1.frames[33] = al_load_bitmap("Montage34.bmp");
	m1.frames[34] = al_load_bitmap("Montage35.bmp");
	m1.frames[35] = al_load_bitmap("Montage36.bmp");
	m1.frames[36] = al_load_bitmap("Montage37.bmp");
	m1.frames[37] = al_load_bitmap("Montage38.bmp");
	m1.frames[38] = al_load_bitmap("Montage39.bmp");
	m1.frames[39] = al_load_bitmap("Montage40.bmp");
	m1.frames[40] = al_load_bitmap("Montage41.bmp");
	m1.frames[41] = al_load_bitmap("Montage42.bmp");
	m1.frames[42] = al_load_bitmap("Montage43.bmp");
	m1.frames[43] = al_load_bitmap("Montage44.bmp");
	m1.frames[44] = al_load_bitmap("Montage42.bmp");
	m1.frames[45] = al_load_bitmap("Montage43.bmp");
	m1.frames[46] = al_load_bitmap("Montage44.bmp");
	m1.frames[47] = al_load_bitmap("Montage44.bmp");
	m1.idle = al_load_bitmap("Montage1.bmp");
	m1.currentFrame = 0;
	m1.bmp = m1.idle; //default

	//playerobject
	AnimatedObject p1;
	p1.x = p1.y = 300;
	p1.frames[0] = al_load_bitmap("MojoSquirrel_Front.bmp");
	p1.frames[1] = al_load_bitmap("MojoSquirrel_Front_Walk1.bmp");
	p1.frames[2] = al_load_bitmap("MojoSquirrel_Front.bmp");
	p1.frames[3] = al_load_bitmap("MojoSquirrel_Front_Walk2.bmp");
	p1.frames[4] = al_load_bitmap("MojoSquirrel_Right.bmp");
	p1.frames[5] = al_load_bitmap("MojoSquirrel_Right_Walk1.bmp");
	p1.frames[6] = al_load_bitmap("MojoSquirrel_Right.bmp");
	p1.frames[7] = al_load_bitmap("MojoSquirrel_Right_Walk2.bmp");
	p1.frames[8] = al_load_bitmap("MojoSquirrel_Left.bmp");
	p1.frames[9] = al_load_bitmap("MojoSquirrel_Left_Walk1.bmp");
	p1.frames[10] = al_load_bitmap("MojoSquirrel_Left.bmp");
	p1.frames[11] = al_load_bitmap("MojoSquirrel_Left_Walk2.bmp");
	p1.frames[12] = al_load_bitmap("MojoSquirrel_Back.bmp");
	p1.frames[13] = al_load_bitmap("MojoSquirrel_Back_Walk1.bmp");
	p1.frames[14] = al_load_bitmap("MojoSquirrel_Back.bmp");
	p1.frames[15] = al_load_bitmap("MojoSquirrel_Back_Walk2.bmp");
	p1.idle = al_load_bitmap("MojoSquirrel_Front.bmp");
	p1.currentFrame = 0;
	p1.bmp = p1.idle; //default
	al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));

	//enemyobject
	GameObject e1;
	e1.x = rand() % 600;
	e1.y = rand() % 400;
	e1.bmp = al_load_bitmap("DiscoFrog_Front.bmp");
	al_convert_mask_to_alpha(e1.bmp, al_map_rgb(255, 255, 255));
	GameObject e2;
	e2.x = rand() % 600;
	e2.y = rand() % 400;
	e2.bmp = al_load_bitmap("DeathSkull.bmp");
	al_convert_mask_to_alpha(e2.bmp, al_map_rgb(255, 255, 255));
	GameObject e3;
	e3.x = rand() % 600;
	e3.y = rand() % 400;
	e3.bmp = al_load_bitmap("DeathSkull.bmp");
	al_convert_mask_to_alpha(e3.bmp, al_map_rgb(255, 255, 255));
	//scoreobject
	GameObject s1;
	s1.x = rand() % 600;
	s1.y = rand() % 400;
	s1.bmp = al_load_bitmap("Acorn.bmp");
	al_convert_mask_to_alpha(s1.bmp, al_map_rgb(255, 255, 255));
	GameObject s2;
	s2.x = rand() % 600;
	s2.y = rand() % 400;
	s2.bmp = al_load_bitmap("Acorn.bmp");
	al_convert_mask_to_alpha(s2.bmp, al_map_rgb(255, 255, 255));
	GameObject s3;
	s3.x = rand() % 600;
	s3.y = rand() % 400;
	s3.bmp = al_load_bitmap("Acorn.bmp");
	al_convert_mask_to_alpha(s3.bmp, al_map_rgb(255, 255, 255));

	//score
	int score1 = 0;
	int score2 = 0;
	int score3 = 0;

	//movement ints
	int my1 = 1;
	int mx1 = 1;
	int my2 = 1;
	int mx2 = 1;
	int my3 = 1;
	int mx3 = 1;

	//level
	int map = 1;

	//Menu
	int menu1 = 1;
	int menu2 = 1;

	while (map == 1)
	{
		//keyboard check
		al_get_keyboard_state(&key_state);

		//Skip
		if (al_key_down(&key_state, ALLEGRO_KEY_ENTER))
		{
			map = 2;
		}
		DrawObject(m1);
		m1.currentFrame++;
		m1.bmp = m1.frames[m1.currentFrame];
		if (m1.currentFrame == 48)
		{
			map = 2;
		}
		al_flip_display(); //this copies from secondary buffer (for frames we are working on) to primary buffer (that holds what's showing on screen)
		al_rest(0.15); //delay so we have proper frame rate and not read the keyboard too quickly
	}


	while (map == 2)
	{

		//keyboard check
		al_get_keyboard_state(&key_state);

		//escape exit
		if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE))
			break;
		//Menu Navigation
		if (al_key_down(&key_state, ALLEGRO_KEY_UP))
		{
			if (menu1 >= 2)
				menu1--;
			else
				menu1 = 1;
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_DOWN))
		{
			if (menu1 <= 2)
				menu1++;
			else
				menu1 = 3;
		}

		//Selection
		if (al_key_down(&key_state, ALLEGRO_KEY_ENTER))
		{
			if (menu1 == 1)
				map = 4;
			if (menu1 == 2)
				map = 3;
			if (menu1 == 3)
				break;
		}

		if (menu1 == 1)
		{
			//Background color
			al_clear_to_color(al_map_rgb(25, 25, 25));

			al_draw_textf(g_font1, al_map_rgb(0, 255, 255), 240, 180, 0, "Menu");
			al_draw_textf(g_font, al_map_rgb(255, 255, 255), 240, 240, 0, "Start");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 260, 0, "Map Select");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 280, 0, "Exit");
		}
		if (menu1 == 2)
		{
			//Background color
			al_clear_to_color(al_map_rgb(25, 25, 25));

			al_draw_textf(g_font1, al_map_rgb(0, 255, 255), 240, 180, 0, "Menu");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 240, 0, "Start");
			al_draw_textf(g_font, al_map_rgb(255, 255, 255), 240, 260, 0, "Map Select");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 280, 0, "Exit");
		}
		if (menu1 == 3)
		{
			//Background color
			al_clear_to_color(al_map_rgb(25, 25, 25));

			al_draw_textf(g_font1, al_map_rgb(0, 255, 255), 240, 180, 0, "Menu");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 240, 0, "Start");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 260, 0, "Map Select");
			al_draw_textf(g_font, al_map_rgb(255, 255, 255), 240, 280, 0, "Exit");
		}

		al_flip_display(); //screen
		al_rest(0.10); //framerate
	}


	while (map == 3)
	{

		//keyboard check
		al_get_keyboard_state(&key_state);

		//escape exit
		if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE))
			break;
		//Menu Navigation
		if (al_key_down(&key_state, ALLEGRO_KEY_UP))
		{
			if (menu2 >= 2)
				menu2--;
			else
				menu2 = 1;
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_DOWN))
		{
			if (menu2 <= 3)
				menu2++;
			else
				menu2 = 4;
		}

		//Selection
		if (al_key_down(&key_state, ALLEGRO_KEY_ENTER))
		{
			if (menu2 == 1)
				map = 4;
			if (menu2 == 2)
				map = 5;
			if (menu2 == 3)
				map = 6;
			if (menu2 == 4)
				break; //Wanted this to go back to the previous menu, but I can't figure it out right now, even the "goto" function isnt working correctly
		}

		if (menu2 == 1)
		{
			//Background color
			al_clear_to_color(al_map_rgb(25, 25, 25));

			al_draw_textf(g_font1, al_map_rgb(0, 255, 255), 240, 180, 0, "Menu");
			al_draw_textf(g_font, al_map_rgb(255, 255, 255), 240, 240, 0, "Level 1");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 260, 0, "Level 2");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 280, 0, "Level 3");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 300, 0, "Exit");
		}
		if (menu2 == 2)
		{
			//Background color
			al_clear_to_color(al_map_rgb(25, 25, 25));

			al_draw_textf(g_font1, al_map_rgb(0, 255, 255), 240, 180, 0, "Menu");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 240, 0, "Level 1");
			al_draw_textf(g_font, al_map_rgb(255, 255, 255), 240, 260, 0, "Level 2");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 280, 0, "Level 3");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 300, 0, "Exit");
		}
		if (menu2 == 3)
		{
			//Background color
			al_clear_to_color(al_map_rgb(25, 25, 25));

			al_draw_textf(g_font1, al_map_rgb(0, 255, 255), 240, 180, 0, "Menu");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 240, 0, "Level 1");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 260, 0, "Level 2");
			al_draw_textf(g_font, al_map_rgb(255, 255, 255), 240, 280, 0, "Level 3");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 300, 0, "Exit");
		}
		if (menu2 == 4)
		{
			//Background color
			al_clear_to_color(al_map_rgb(25, 25, 25));

			al_draw_textf(g_font1, al_map_rgb(0, 255, 255), 240, 180, 0, "Menu");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 240, 0, "Level 1");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 260, 0, "Level 2");
			al_draw_textf(g_font, al_map_rgb(255, 0, 0), 240, 280, 0, "Level 3");
			al_draw_textf(g_font, al_map_rgb(255, 255, 255), 240, 300, 0, "Exit");
		}

		al_flip_display(); //screen
		al_rest(0.10); //framerate
	}
	

	while (map == 4)
	{

		//keyboard check
		al_get_keyboard_state(&key_state);

		//escape exit
		if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE))
			break;

		p1.bmp = p1.idle; //idle p1 check
		//movement of player
		if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
		{
			p1.x = p1.x + 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 7)
				p1.currentFrame = 4;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_LEFT))
		{
			p1.x = p1.x - 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 11)
				p1.currentFrame = 8;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_UP))
		{
			p1.y = p1.y - 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 15)
				p1.currentFrame = 12;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_DOWN))
		{
			p1.y = p1.y + 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 3)
				p1.currentFrame = 0;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}

		//Background color
		al_clear_to_color(al_map_rgb(255, 0, 100));

		//playerobject
		DrawObject(p1);
		//scoreobject
		DrawObject(s1);
		DrawObject(s2);
		DrawObject(s3);
		//Enemyobject
		DrawObject(e1);
		DrawObject(e2);
		DrawObject(e3);

		//Enemy movement and hit detection

		//e1 movement
		e1.y = e1.y + my1;
		e1.x = e1.x + mx1;
		if (e1.y <= 0)
		{
			my1 = my1 + 1;
		}
		if (e1.y >= 480)
		{
			my1 = my1 - 1;
		}
		if (e1.x <= 0)
		{
			mx1 = mx1 + 1;
		}
		if (e1.x >= 640)
		{
			mx1 = mx1 - 1;
		}
		//e2 movement
		e2.y = e2.y + my2;
		e2.x = e2.x + mx2;
		if (e2.y <= 0)
		{
			my2 = my2 + 1;
		}
		if (e2.y >= 480)
		{
			my2 = my2 - 1;
		}
		if (e2.x <= 0)
		{
			mx2 = mx2 + 1;
		}
		if (e2.x >= 640)
		{
			mx2 = mx2 - 1;
		}
		//e3 movement
		e3.y = e3.y + my3;
		e3.x = e3.x + mx3;
		if (e3.y <= 0)
		{
			my3 = my3 + 1;
		}
		if (e3.y >= 480)
		{
			my3 = my3 - 1;
		}
		if (e3.x <= 0)
		{
			mx3 = mx3 + 1;
		}
		if (e3.x >= 640)
		{
			mx3 = mx3 - 1;
		}

		//enemy hit detection (hit detection based on the center of a 50x50 object)
		//e1 hit
		if (sqrt(((p1.x + 25) - (e1.x + 25))*((p1.x + 25) - (e1.x + 25)) + ((p1.y + 25) - (e1.y + 25))*((p1.y + 25) - (e1.y + 25))) <= 25)
		{
			//p1.y = p1.x = 1500;
			break;
		}
		//e2 hit
		if (sqrt(((p1.x + 25) - (e2.x + 25))*((p1.x + 25) - (e2.x + 25)) + ((p1.y + 25) - (e2.y + 25))*((p1.y + 25) - (e2.y + 25))) <= 25)
		{
			//p1.y = p1.x = 1500;
			break;
		}
		//e3 hit
		if (sqrt(((p1.x + 25) - (e3.x + 25))*((p1.x + 25) - (e3.x + 25)) + ((p1.y + 25) - (e3.y + 25))*((p1.y + 25) - (e3.y + 25))) <= 25)
		{
			//p1.y = p1.x = 1500;
			break;
		}

		//Scoring statements
		if (sqrt(((p1.x + 25) - (s1.x + 25))*((p1.x + 25) - (s1.x + 25)) + ((p1.y + 25) - (s1.y + 25))*((p1.y + 25) - (s1.y + 25))) <= 25)
		{
			s1.x = s1.y = 1000;
			score1 = score1 + 1;
		}
		if (sqrt(((p1.x + 25) - (s2.x + 25))*((p1.x + 25) - (s2.x + 25)) + ((p1.y + 25) - (s2.y + 25))*((p1.y + 25) - (s2.y + 25))) <= 25)
		{
			s2.x = s2.y = 1000;
			score1 = score1 + 1;
		}
		if (sqrt(((p1.x + 25) - (s3.x + 25))*((p1.x + 25) - (s3.x + 25)) + ((p1.y + 25) - (s3.y + 25))*((p1.y + 25) - (s3.y + 25))) <= 25)
		{
			s3.x = s3.y = 1000;
			score1 = score1 + 1;
		}

		al_draw_textf(g_font, al_map_rgb(255, 255, 255), 0, 0, 0, "score is %d", score1);
		if (score1 == 3)
		{
			map = 5;
		}



		al_flip_display(); //this copies from secondary buffer (for frames we are working on) to primary buffer (that holds what's showing on screen)
		al_rest(0.04); //delay so we have proper frame rate and not read the keyboard too quickly
	}

	//re-initialise gamestate
	s1.x = rand() % 600;
	s1.y = rand() % 400;
	s2.x = rand() % 600;
	s2.y = rand() % 400;
	s3.x = rand() % 600;
	s3.y = rand() % 400;
	my1 = 1;
	mx1 = 1;
	my2 = 1;
	mx2 = 1;
	my3 = 1;
	mx3 = 1;

	while (map == 5)
	{
		//keyboard check
		al_get_keyboard_state(&key_state);

		//escape exit
		if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE))
			break;

		p1.bmp = p1.idle; //idle p1 check
						  //movement of player
		if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
		{
			p1.x = p1.x + 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 7)
				p1.currentFrame = 4;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_LEFT))
		{
			p1.x = p1.x - 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 11)
				p1.currentFrame = 8;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_UP))
		{
			p1.y = p1.y - 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 15)
				p1.currentFrame = 12;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_DOWN))
		{
			p1.y = p1.y + 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 3)
				p1.currentFrame = 0;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}

		//Background color
		al_clear_to_color(al_map_rgb(100, 0, 255));

		//playerobject
		DrawObject(p1);
		//scoreobject
		DrawObject(s1);
		DrawObject(s2);
		DrawObject(s3);
		//Enemyobject
		DrawObject(e1);
		DrawObject(e2);
		DrawObject(e3);

		//Enemy movement and hit detection

		//e1 movement
		e1.y = e1.y + (my1 + 3);
		e1.x = e1.x + (mx1 + 3);
		if (e1.y <= 0)
		{
			my1 = my1 + 3;
		}
		if (e1.y >= 480)
		{
			my1 = my1 - 3;
		}
		if (e1.x <= 0)
		{
			mx1 = mx1 + 3;
		}
		if (e1.x >= 640)
		{
			mx1 = mx1 - 3;
		}
		//e2 movement
		e2.y = e2.y + (my2 + 3);
		e2.x = e2.x + (mx2 + 3);
		if (e2.y <= 0)
		{
			my2 = my2 + 3;
		}
		if (e2.y >= 480)
		{
			my2 = my2 - 3;
		}
		if (e2.x <= 0)
		{
			mx2 = mx2 + 3;
		}
		if (e2.x >= 640)
		{
			mx2 = mx2 - 3;
		}
		//e3 movement
		e3.y = e3.y + (my3 + 3);
		e3.x = e3.x + (mx3 + 3);
		if (e3.y <= 0)
		{
			my3 = my3 + 3;
		}
		if (e3.y >= 480)
		{
			my3 = my3 - 3;
		}
		if (e3.x <= 0)
		{
			mx3 = mx3 + 3;
		}
		if (e3.x >= 640)
		{
			mx3 = mx3 - 3;
		}

		//enemy hit detection (hit detection based on the center of a 50x50 object)
		//e1 hit
		if (sqrt(((p1.x + 25) - (e1.x + 25))*((p1.x + 25) - (e1.x + 25)) + ((p1.y + 25) - (e1.y + 25))*((p1.y + 25) - (e1.y + 25))) <= 25)
		{
			//p1.y = p1.x = 1500;
			break;
		}
		//e2 hit
		if (sqrt(((p1.x + 25) - (e2.x + 25))*((p1.x + 25) - (e2.x + 25)) + ((p1.y + 25) - (e2.y + 25))*((p1.y + 25) - (e2.y + 25))) <= 25)
		{
			//p1.y = p1.x = 1500;
			break;
		}
		//e3 hit
		if (sqrt(((p1.x + 25) - (e3.x + 25))*((p1.x + 25) - (e3.x + 25)) + ((p1.y + 25) - (e3.y + 25))*((p1.y + 25) - (e3.y + 25))) <= 25)
		{
			//p1.y = p1.x = 1500;
			break;
		}

	
		//Scoring statements
		if (sqrt(((p1.x + 25) - (s1.x + 25))*((p1.x + 25) - (s1.x + 25)) + ((p1.y + 25) - (s1.y + 25))*((p1.y + 25) - (s1.y + 25))) <= 25)
		{
			s1.x = s1.y = 1000;
			score2 = score2 + 1;
		}
		if (sqrt(((p1.x + 25) - (s2.x + 25))*((p1.x + 25) - (s2.x + 25)) + ((p1.y + 25) - (s2.y + 25))*((p1.y + 25) - (s2.y + 25))) <= 25)
		{
			s2.x = s2.y = 1000;
			score2 = score2 + 1;
		}
		if (sqrt(((p1.x + 25) - (s3.x + 25))*((p1.x + 25) - (s3.x + 25)) + ((p1.y + 25) - (s3.y + 25))*((p1.y + 25) - (s3.y + 25))) <= 25)
		{
			s3.x = s3.y = 1000;
			score2 = score2 + 1;
		}

		al_draw_textf(g_font, al_map_rgb(255, 255, 255), 0, 0, 0, "score is %d", score2);
		if (score2 == 3)
		{
			map = 6;
		}



		al_flip_display(); //this copies from secondary buffer (for frames we are working on) to primary buffer (that holds what's showing on screen)
		al_rest(0.04); //delay so we have proper frame rate and not read the keyboard too quickly
	}

	//re-initialise gamestate
	s1.x = rand() % 600;
	s1.y = rand() % 400;
	s2.x = rand() % 600;
	s2.y = rand() % 400;
	s3.x = rand() % 600;
	s3.y = rand() % 400;
	my1 = 1;
	mx1 = 1;
	my2 = 1;
	mx2 = 1;
	my3 = 1;
	mx3 = 1;

	while (map == 6)
	{
		//keyboard check
		al_get_keyboard_state(&key_state);

		//escape exit
		if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE))
			break;

		p1.bmp = p1.idle; //idle p1 check
						  //movement of player
		if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
		{
			p1.x = p1.x + 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 7)
				p1.currentFrame = 4;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_LEFT))
		{
			p1.x = p1.x - 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 11)
				p1.currentFrame = 8;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_UP))
		{
			p1.y = p1.y - 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 15)
				p1.currentFrame = 12;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}
		if (al_key_down(&key_state, ALLEGRO_KEY_DOWN))
		{
			p1.y = p1.y + 2;
			p1.currentFrame++;
			if (p1.currentFrame >= 3)
				p1.currentFrame = 0;
			p1.bmp = p1.frames[p1.currentFrame];
			al_convert_mask_to_alpha(p1.bmp, al_map_rgb(255, 255, 255));
		}

		//Background color
		al_clear_to_color(al_map_rgb(25, 25, 25));

		//playerobject
		DrawObject(p1);
		//scoreobject
		DrawObject(s1);
		DrawObject(s2);
		DrawObject(s3);
		//Enemyobject
		DrawObject(e1);
		DrawObject(e2);
		DrawObject(e3);

		//Enemy movement and hit detection

		//e1 movement
		e1.y = e1.y + (my1 + 6);
		e1.x = e1.x + (mx1 + 6);
		if (e1.y <= 0)
		{
			my1 = my1 + 6;
		}
		if (e1.y >= 480)
		{
			my1 = my1 - 6;
		}
		if (e1.x <= 0)
		{
			mx1 = mx1 + 6;
		}
		if (e1.x >= 640)
		{
			mx1 = mx1 - 6;
		}
		//e2 movement
		e2.y = e2.y + (my2 + 6);
		e2.x = e2.x + (mx2 + 6);
		if (e2.y <= 0)
		{
			my2 = my2 + 6;
		}
		if (e2.y >= 480)
		{
			my2 = my2 - 6;
		}
		if (e2.x <= 0)
		{
			mx2 = mx2 + 6;
		}
		if (e2.x >= 640)
		{
			mx2 = mx2 - 6;
		}
		//e3 movement
		e3.y = e3.y + (my3 + 6);
		e3.x = e3.x + (mx3 + 6);
		if (e3.y <= 0)
		{
			my3 = my3 + 6;
		}
		if (e3.y >= 480)
		{
			my3 = my3 - 6;
		}
		if (e3.x <= 0)
		{
			mx3 = mx3 + 6;
		}
		if (e3.x >= 640)
		{
			mx3 = mx3 - 6;
		}

		//enemy hit detection (hit detection based on the center of a 50x50 object)
		//e1 hit
		if (sqrt(((p1.x + 25) - (e1.x + 25))*((p1.x + 25) - (e1.x + 25)) + ((p1.y + 25) - (e1.y + 25))*((p1.y + 25) - (e1.y + 25))) <= 25)
		{
			//p1.y = p1.x = 1500;
			break;
		}
		//e2 hit
		if (sqrt(((p1.x + 25) - (e2.x + 25))*((p1.x + 25) - (e2.x + 25)) + ((p1.y + 25) - (e2.y + 25))*((p1.y + 25) - (e2.y + 25))) <= 25)
		{
			//p1.y = p1.x = 1500;
			break;
		}
		//e3 hit
		if (sqrt(((p1.x + 25) - (e3.x + 25))*((p1.x + 25) - (e3.x + 25)) + ((p1.y + 25) - (e3.y + 25))*((p1.y + 25) - (e3.y + 25))) <= 25)
		{
			//p1.y = p1.x = 1500;
			break;
		}

		//Scoring statements
		if (sqrt(((p1.x + 25) - (s1.x + 25))*((p1.x + 25) - (s1.x + 25)) + ((p1.y + 25) - (s1.y + 25))*((p1.y + 25) - (s1.y + 25))) <= 25)
		{
			s1.x = s1.y = 1000;
			score3 = score3 + 1;
		}
		if (sqrt(((p1.x + 25) - (s2.x + 25))*((p1.x + 25) - (s2.x + 25)) + ((p1.y + 25) - (s2.y + 25))*((p1.y + 25) - (s2.y + 25))) <= 25)
		{
			s2.x = s2.y = 1000;
			score3 = score3 + 1;
		}
		if (sqrt(((p1.x + 25) - (s3.x + 25))*((p1.x + 25) - (s3.x + 25)) + ((p1.y + 25) - (s3.y + 25))*((p1.y + 25) - (s3.y + 25))) <= 25)
		{
			s3.x = s3.y = 1000;
			score3 = score3 + 1;
		}

		al_draw_textf(g_font, al_map_rgb(255, 255, 255), 0, 0, 0, "score is %d", score3);

		if (score3 == 3)
		{
			my1 = -6; // - 6 to stop movement and = 0
			mx1 = -6;
			my2 = -6;
			mx2 = -6;
			my3 = -6;
			mx3 = -6;
			al_draw_textf(g_font, al_map_rgb(255, 255, 255), 280, 240, 0, "You Win!");
			al_draw_textf(g_font, al_map_rgb(255, 255, 255), 240, 280, 0, "Press Esc to Exit");
		}



		al_flip_display(); //this copies from secondary buffer (for frames we are working on) to primary buffer (that holds what's showing on screen)
		al_rest(0.04); //delay so we have proper frame rate and not read the keyboard too quickly
	}
	//clean up
	EndAllegro();
}