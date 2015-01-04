#include <GL/glut.h>
#include <stdlib.h>

#define WIDTH 1000
#define HEIGHT 1000
#define PRZESUNIECIE_W_PIONIE 0.29

extern void epicykle(float* x, float* y, const float* omega,const float* t);

float omega1  = 12.0;
float *x_cord;
float *y_cord;
float *omega;
float *t;

void Display()
{
    // kolor kwadraciku rysujacego
    glColor3f( 1.0, 1.0, 0.0 );


    //rysujemy kwadracik odpowiadajacy pixelowi
    glBegin(GL_POLYGON);

    glVertex3d(*(x_cord)/WIDTH, *(y_cord)/HEIGHT+0.005-PRZESUNIECIE_W_PIONIE, 0.0);
    glVertex3d(*(x_cord)/WIDTH+0.005, *(y_cord)/HEIGHT+0.005-PRZESUNIECIE_W_PIONIE, 0.0);
    glVertex3d(*(x_cord)/WIDTH+0.005, *(y_cord)/HEIGHT-PRZESUNIECIE_W_PIONIE, 0.0);
    glEnd();  
    
    // skierowanie poleceń do wykonania
    glFlush();
    
    // zamiana buforów koloru
    glutSwapBuffers();
}

void Oblicz()
{	
	(*t) += 0.0015;
	
	epicykle(x_cord, y_cord, omega, t);
  
	Display();	
}

void Keyboard( unsigned char key, int x, int y )
{
    // klawisz +
    if( key == '+' ) 
	(*omega)++;
    else
    
    // klawisz -
    if( key == '-')
	(*omega)--;
    else
    if (key == 'c' || key == 'C' )	//czyscimy ekran
    {
	glClearColor( 0.0, 0.0, 0.0, 0.0 );		 

	glClear( GL_COLOR_BUFFER_BIT );
    	Display();
    }
    
    Oblicz();
   
}

void timer_func(int n) 
{
	Oblicz();  //wyznaczamy wspolrzedne
         
	glutTimerFunc(n, timer_func, n); // rekursywne wywolanie timer_func
}
 


// zmiana wielkości okna

void Reshape( int width, int height )
{
    // generowanie sceny 3D
        // kolor tła - zawartość bufora koloru
    glClearColor( 0.0, 0.0, 0.0, 0.0 );		//red - 0, green -0, blue - 0 czyli kolor czarny
    
    // czyszczenie bufora koloru
    glClear( GL_COLOR_BUFFER_BIT );
    Display();
}

// stałe do obsługi menu podręcznego

enum
{
    EXIT // wyjście
};

// obsługa menu podręcznego

void Menu( int value )
{
    switch( value )
    {
        // wyjście
    case EXIT:
        exit( 0 );
    }
}

int main( int argc, char * argv[] )
{
    x_cord = malloc(sizeof(*x_cord));
    y_cord = malloc(sizeof(*y_cord));
    omega = malloc(sizeof(*omega));
    t = malloc(sizeof(*t));
    *t = 0.0;
    *x_cord = 0.0;
    *y_cord = 0.0;
    *omega = 45;

    // inicjalizacja biblioteki GLUT
    glutInit( & argc, argv );
    
    // inicjalizacja bufora ramki
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    
    // rozmiary głównego okna programu
    glutInitWindowSize( WIDTH, HEIGHT );

    
    // utworzenie głównego okna programu
    glutCreateWindow( "Copernicus" );
    
    // kolor tła - zawartość bufora koloru
    glClearColor( 0.0, 0.0, 0.0, 0.0 );		//red - 0, green -0, blue - 0 czyli kolor czarny
    
    // czyszczenie bufora koloru
    glClear( GL_COLOR_BUFFER_BIT );

    // dołączenie funkcji generującej scenę 3D
    glutDisplayFunc( Oblicz );
    
    // dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
    glutReshapeFunc( Reshape );
    
    // utworzenie menu podręcznego
    glutCreateMenu( Menu );
   
    timer_func(1);		//timer na 1ms
   
    // dołączenie funkcji obsługi klawiatury
    glutKeyboardFunc( Keyboard );
    
    // dodatnie pozycji do menu podręcznego    
    glutAddMenuEntry( "Wyjscie", EXIT );
    
    // określenie przycisku myszki obsługującej menu podręczne
    glutAttachMenu( GLUT_RIGHT_BUTTON );

    // wprowadzenie programu do obsługi pętli komunikatów
    glutMainLoop();

    return 0;
}
