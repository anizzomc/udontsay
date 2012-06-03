/* crtc6845.c */

#include "drivers/crtc6845.h"
#include "arch/io.h"

/* Driver de video */

/* La idea es que permita escribir a páginas no activas en el momento */

#define VIDEO_ADDRESS 0xB8000
#define VIDEO_COLS 80
#define VIDEO_ROWS 25
#define VIDEO_SIZE VIDEO_COLS*VIDEO_ROWS*2
#define BUFFER_SIZE VIDEO_SIZE/2
#define CANT_PAGES 8

static char *video = (char *) VIDEO_ADDRESS;

static int tabs = TAB_SPACE;

/* La página activa en el momento */
static int activePage = 0;

/* La memoria própia de cada página */
static char videopages[CANT_PAGES][VIDEO_SIZE];

/* Indica el desplazamiento desde el borde izquierdo de la pantall */
static char linepos[CANT_PAGES] = { 0 };

static coord_t cursor[CANT_PAGES] = { { 0, 0 } };

/* Marcador de que lineas deben actualizarse al escribir en
 * el video
 */
static char renderline[VIDEO_ROWS] = { 0 };

/* Flag de que la página fue scrolleada, por lo tanto debe
 * actualizarse completamente
 */
static char scrolled = 0;

static coord_t lightpen = { -1, -1 };

static void pageScroll(int page);
static void rerenderVideo(int page);
static void outCursorCoords(coord_t coord);
static void copyLine(int i);
static int _vispendisabled();
static char inv(char attr);
static void lineScroll(int lines);

void _vdisblepen() {
	if (!_vispendisabled())
		video[lightpen.y * VIDEO_COLS * 2 + lightpen.x * 2 + 1] = WHITE_TXT;
	lightpen.y = lightpen.x = -1;
}

static int _vispendisabled() {
	return lightpen.x == lightpen.y && lightpen.y == -1;
}
void _vsetpen(coord_t coord) {
	if (coord.y < 0 || coord.y > VIDEO_ROWS - 1 || coord.x < 0 || coord.x
			> VIDEO_COLS - 1) { /* Light pen fuera de los límites */
		_vdisblepen();
	} else {
		if (!_vispendisabled())
			video[lightpen.y * VIDEO_COLS * 2 + lightpen.x * 2 + 1] = inv(
					video[lightpen.y * VIDEO_COLS * 2 + lightpen.x * 2 + 1]);
		video[coord.y * VIDEO_COLS * 2 + coord.x * 2 + 1] = inv(video[coord.y
				* VIDEO_COLS * 2 + coord.x * 2 + 1]);
		lightpen.x = coord.x;
		lightpen.y = coord.y;
	}
}

void _vtsetcursor(int page, coord_t coord) {

	if (0 > coord.x || VIDEO_COLS - 1 < coord.x || coord.y < 0 || VIDEO_ROWS
			- 1 < coord.y) { /* Estoy fuera de la pantalla */
		return;
	}

	cursor[page] = coord;

	if (page == activePage) {
		outCursorCoords(coord);
	}
}

static void outCursorCoords(coord_t coord) {
	int res = coord.y * VIDEO_COLS + coord.x;

	_out(0x3D4, 0x0F);
	_out(0x3D5, res & 0xFF);
	_out(0x3D4, 0x0E);
	_out(0x3D5, (res >> 8) & 0xFF);
}
/* Recive un buffer donde va a cambiar el contenido de la pantalla
 * entre las coordenas begin y end con un m�ximo de max caracteres.
 * las lineas las va a terminar con un \n.
 * Retorna la cantidad de caracteres copiados.
 */

int _vcopy(void *buff, coord_t begin, coord_t end, int max) {

	char xstart, xend, ystart, yend, xorg, *bufferOut;
	int i;
	bufferOut = buff;

	(begin.x <= end.x) ? (xstart = begin.x, xend = end.x)
			: (xstart = end.x, xend = begin.x);
	(begin.y <= end.y) ? (ystart = begin.y, yend = end.y)
			: (ystart = end.y, yend = begin.y);

	for (i = 0; ystart <= yend && i < max; ystart++) {
		for (xorg = xstart; xorg <= xend && i < max; xorg++, i++)
			bufferOut[i] = videopages[activePage][ystart * VIDEO_COLS * 2
					+ xorg * 2];
		bufferOut[i++] = '\n';
	}

	return i;
}

coord_t _vgetcusor(int p) {
	return cursor[p];
}

coord_t _vgetpen() {
	return lightpen;
}

int _vcols() {
	return VIDEO_COLS;
}

int _vrows() {
	return VIDEO_ROWS;
}

int _vtabs() {
	return tabs;
}

int _vcurrentpage() {
	return activePage;
}

int _vpagesqty() {
	return CANT_PAGES;
}

/*
 * Realiza un scroll dentro de la página, pero sin impactarlo en la pantalla.
 */
static void pageScroll(int page) {

	int i, j;

	for (i = 1; i < VIDEO_ROWS; i++)
		for (j = 0; j < VIDEO_COLS; j++)
			videopages[page][(i - 1) * VIDEO_COLS * 2 + 2 * j]
					= videopages[page][i * VIDEO_COLS * 2 + 2 * j];
	for (i = 0; i < VIDEO_COLS; i++)
		videopages[page][24 * VIDEO_COLS * 2 + i * 2] = ' ';
	linepos[page] = 0;
	scrolled = 1;
}

void _vscroll(int page) {
	pageScroll(page);
	rerenderVideo(page);
}

coord_t _vgetcursor(int page) {
	return cursor[page];
}

void _vtcflush(int page, void *buff, size_t qty) {

	char *bufferIn = buff;
	coord_t coord = _vgetcursor(page);
	int i, j;

	for (i = 0; i < qty; i++) {

		switch (bufferIn[i]) {
		case '\n':
			coord.x = 0;
			coord.y++;
			break;
		case '\r':
			coord.x = 0;
			break;
		case '\t':
			for (j = 0; j < TAB_SPACE; j++) {
				renderline[coord.y] = 1;
				videopages[page][(coord.y * VIDEO_COLS + coord.x) * 2] = ' ';
				coord.x++;
				if (coord.x >= VIDEO_COLS) {
					coord.x = 0;
					coord.y++;
				}

				if (coord.y >= VIDEO_ROWS) {
					pageScroll(page);
					coord.y = VIDEO_ROWS - 1;
				}

				_vtsetcursor(page, coord);
			}

			break;

		default:
			renderline[coord.y] = 1; //Marco la linea y para actualizarla
			videopages[page][(coord.y * VIDEO_COLS + coord.x) * 2]
					= bufferIn[i];
			coord.x++;
			break;
		}

		if (coord.x >= VIDEO_COLS) {
			coord.x = 0;
			coord.y++;
		}

		if (coord.y >= VIDEO_ROWS) {
			pageScroll(page);
			coord.y = VIDEO_ROWS - 1;
		}

		_vtsetcursor(page, coord);

	}
	rerenderVideo(page);
}

void _vtflush(int page, void *buff, size_t qty) {

	char *buffer = (char *) buff;

	int i;
	int j;
	for (i = 0; i < qty; i++) {
		switch (buffer[i]) {
		case '\n':
			pageScroll(page);
			linepos[activePage] = 0;
			break;
		case '\t':
			for (j = 0; j < tabs; j++) {
				videopages[page][24 * VIDEO_COLS * 2 + 2 * (linepos[page]++)]
						= ' ';
				renderline[24] = 1;
				if (linepos[activePage] >= VIDEO_COLS) {
					pageScroll(page);
					linepos[page] = 0;
				}
			}
			break;
		default:
			renderline[24] = 1;
			videopages[page][24 * VIDEO_COLS * 2 + 2 * (linepos[page]++)]
					= buffer[i];
			break;

		}
		if (linepos[page] >= VIDEO_COLS) {
			pageScroll(page);
			linepos[activePage] = 0;
		}
	}
	rerenderVideo(page);
}

static void rerenderVideo(int page) {
	int i;

	if (page == activePage) {
		if (scrolled) {
			for (i = 0; i < VIDEO_ROWS; i++)
				copyLine(i);
		} else {
			for (i = 0; i < VIDEO_ROWS; i++) {
				if (renderline[i]) {
					copyLine(i);
					renderline[i] = 0;
				}
			}
		}

		if (!_vispendisabled())
			video[lightpen.y * VIDEO_COLS * 2 + lightpen.x * 2 + 1] = inv(
					video[lightpen.y * VIDEO_COLS * 2 + lightpen.x * 2 + 1]); //Coloco el cursor donde estaba
	}

	for (i = 0; i < VIDEO_ROWS; i++)
		renderline[i] = 0;
	scrolled = 0;
}

static void copyLine( i) {
	int j;

	for (j = 0; j < VIDEO_COLS * 2; j++)
		video[i * VIDEO_COLS * 2 + j] = videopages[activePage][i * VIDEO_COLS
				* 2 + j];
}

/* Cambia la página activa, la que va a actualizar el video cada vez que haya
 * una escritura.
 */
void _vsetpage(int p) {

	/* Si la página es inválida, o ya está activa, no hago nada */
	if (!(0 <= p && p < CANT_PAGES) || p == activePage)
		return;

	activePage = p;
	_vtsetcursor(p, _vgetcursor(p));
	_vdisblepen();
	scrolled = 1;
	rerenderVideo(p);
}

void _vinit() {
	int i;

	for (i = 0; i < CANT_PAGES; i++)
		_vresetpage(i);
	return;
}

void _vresetpage(int p) {
	int i;
	for (i = 0; i < VIDEO_SIZE - 1; i += 2) {
		videopages[p][i] = ' ';
		videopages[p][i + 1] = WHITE_TXT;
	}
	linepos[p] = 0;
	scrolled = 1;
	rerenderVideo(p);
	return;
}

void _vreset() {
	scrolled = 1;
	rerenderVideo(activePage);
}

static char inv(char attr) {
	char low;
	char high;
	char bb; //Parpadeo y Brillo


	/* Salva el parpadeo y el brillo */

	bb = attr & 0x88;

	/*Toma la parte alta y la baja del atributo. */

	low = attr & 0x07;

	high = attr & 0x70;

	/* Las intercambia y las vuelve a reeconstruir */

	low = low << 4;
	high = high >> 4;

	return bb | low | high;
}

void _vpaint(coord_t begin, coord_t end) {

	char xstart, xend, ystart, yend;

	char xorg;

	(begin.x <= end.x) ? (xstart = begin.x, xend = end.x)
			: (xstart = end.x, xend = begin.x);
	(begin.y <= end.y) ? (ystart = begin.y, yend = end.y)
			: (ystart = end.y, yend = begin.y);

	for (; ystart <= yend; ystart++)
		for (xorg = xstart; xorg <= xend; xorg++)
			video[ystart * VIDEO_COLS * 2 + xorg * 2 + 1] = inv(video[ystart
					* VIDEO_COLS * 2 + xorg * 2 + 1]);
}

/*
 * scrollea lines líneas para arriba e imprime lo apuntado por line
 * en la última línea. Para usar excelusivamente con uprintf.
 */
void _vuprint(char* line, int lines) {
	lineScroll(lines);
	int i;
	char *ini_pos = (char*) (video + (VIDEO_ROWS - 1) * VIDEO_COLS * 2);

	for(i=0; i<80 && line[i] != '\0'; i++){
		*(ini_pos + i*2)=line[i];
	}
}

/*
 * Realiza un scroll de lines líneas impactando en la pantalla. Uso exclusivo
 * para el panic
 */
static void lineScroll(int lines) {

	int i, j, ini_pos = (VIDEO_ROWS - lines) * VIDEO_COLS * 2;

	for (i = 1; i < lines; i++)
		for (j = 0; j < VIDEO_COLS; j++)
			*(video + ini_pos + (i - 1) * VIDEO_COLS * 2 + 2 * j) = *(video
					+ ini_pos + (i) * VIDEO_COLS * 2 + 2 * j);
	for (i = 0; i < VIDEO_COLS; i++)
		*(video + (VIDEO_ROWS - 1) * VIDEO_COLS * 2 + i * 2) = ' ';
}

