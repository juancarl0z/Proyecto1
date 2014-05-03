#include <curses.h>
#include <time.h>
const char ENEMIGO = '@';
const char SIMBOLO_PERSONAJE = 'O';
const char SIMBOLO_PERSONAJE2 = '>';
const char ESPACIO_VACIO = ' ';
const char MURALLA = '#';
const char SIMBOLO_VIDA = '+';
const int MapaDy = 50;
const int MapaDx = 50;

char Mapa[50][50] = {
"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°",
"°############°°°°°°############################°",
"°#           #°°°°°°##                        |°",
"°#           #°°°°°°°##  +     ++             |°",
"°#          ##°°°°°°°##               ++      |°",
"°#          ##°°°°°°°°#                       |°",
"°#          #°°°°°°°°°#                       |°",
"°#  +      ##°°°°°°°°°##             ___      |°",
"°#     ####°°#######°°°°#          _/°°°|_____|°",
"°°#    #°°°°#       #°°°##        /°°°°°°°°°°°°°",
"°°°#    #°°#  ####   #°°°°#      |°°°°°°°°°°°°°°",
"°°°°#    #°°#     #   ###°°##     -|°°°°°/----|°",
"°°°°°#    #°°###   ##   ##°°°#     |°°°°/     |°",
"°###°°#    ##°°#   #°##   ###°#   ##----      |°",
"°#  #°# +    #°#   #°°°#     #°#  #   #  #### |°",
"°#   ##    ##°°#   #°°°°####  #°# # # # #   # |°",
"°#+     ###°°°°#  #°°°°°°°°°#  ## # # #   # # |°",
"°#  ####°°#####  #°°°°°°°°°°°#  # # # ####  # |°",
"°#  #°°°°#   +  #°°°°°°°°°°°°°# #   #      #  |°",
"°#  ######  ####°°°°°°°°°°°°°##  ##########   |°",
"°°#        #°°°°°°°°°°°°°°°°°#+               |°",
"°°°########°°°°°°°°°°°°°°°°°°°#################°",
"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°"
};
void MostrarMapa(){ for (int i=0; i<MapaDy; i++) { printw("%s\n", Mapa[i]); } refresh();}
struct Jugador
{
	int Vida, VidaMaxima, x, y;
	Jugador(int v, int vm) : Vida(v), VidaMaxima(vm), x(-1), y(-1){}
	void Curacion(int hp)
	{
		Vida += hp;
		if (Vida>VidaMaxima) { Vida=VidaMaxima; }
	}

};
bool PosicionValida(int y, int x) { return (x>=0 && x<MapaDx && y>=0 && y<MapaDy); }
bool MoverJugador(Jugador &player, int y, int x)
{
	char ch = Mapa[y][x];
	if      (ch==SIMBOLO_VIDA)                   { player.Curacion(1); }
    else if (ch!=ESPACIO_VACIO)                  { return false; }
	if      (PosicionValida(player.y, player.x)) { Mapa[player.y][player.x] = ESPACIO_VACIO; }

	player.y = y; player.x = x;
	Mapa[player.y][player.x] = SIMBOLO_PERSONAJE;
	return true;
}

void MostrarJugador(Jugador &player)
{
	printw("PlayerHP: %i / %i\n", player.Vida, player.VidaMaxima);
}
void gameLoop()
{
	Jugador player(0, 10);
	MoverJugador(player, 5, 5);

	while (1)
    {
		clear();
		MostrarJugador(player);MostrarMapa();
		refresh();
  printw("Bienvenido a mi juego, si desea salir presione \"q\" o \"Q\",\n si desea jugar presione cualquier otro ");
		int ch = getch();
		  if (ch == 'q' || ch == 'Q') {break;}
		  if      (ch == KEY_UP)   { MoverJugador(player, player.y-1, player.x)  ;}
		  else if (ch == KEY_DOWN) { MoverJugador(player, player.y+1, player.x)  ;}
		  else if (ch == KEY_LEFT) { MoverJugador(player, player.y,   player.x-1);}
          else if (ch == KEY_RIGHT){ MoverJugador(player, player.y,   player.x+1);}
	}
}
int main()
{
	keypad(initscr(),1);
	curs_set(0);
	gameLoop();

 printw("Gracias por jugar :) ");int ch = getch();

    endwin();
	return 0;
}
