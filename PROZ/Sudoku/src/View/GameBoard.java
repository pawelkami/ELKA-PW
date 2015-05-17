package View;

import java.awt.Color;
import java.awt.GridLayout;
import java.util.Observable;
import java.util.Observer;
import javax.swing.BorderFactory;
import javax.swing.JPanel;

import Controller.GameBoardController;
import Model.ActionEnumerate;
import Model.Model;

/**
 * Klasa wchodząca w skład widoku gry. Reprezentuje planszę Sudoku.
 * 
 * @author kamienny
 * 
 */
public class GameBoard implements Observer
{
	/**
	 * Konstruktor planszy Sudoku.
	 */
	public GameBoard()
	{
		board = new JPanel( new GridLayout( 3, 3 ) );
		panels = new JPanel[3][3];

		for( int y = 0; y < 3; ++y )
		{
			for( int x = 0; x < 3; ++x )
			{
				panels[y][x] = new JPanel( new GridLayout( 3, 3 ) );
				panels[y][x].setBorder( BorderFactory.createLineBorder( Color.DARK_GRAY ) );
				board.add( panels[y][x] );
			}
		}

		fields = new Field[9][9];
		for( int y = 0; y < 9; ++y )
		{
			for( int x = 0; x < 9; ++x )
			{
				fields[y][x] = new Field( x, y );
				panels[y / 3][x / 3].add( fields[y][x].getField() );
			}
		}
	}


	/**
	 * Metoda aktualizuje plaszę gry.
	 */
	@Override
	public void update( Observable o, Object arg )
	{
		switch( (ActionEnumerate) arg )
		{
			case NEW_GAME:
				setNewGame( (Model) o );
				break;

			case CHECK:
				setGameCheck( (Model) o );
				break;

		}

	}

	/**
	 * Metoda tworzy nową planszę z grą.
	 * 
	 * @param m
	 *            Obiekt modelu gry.
	 */
	public void setNewGame( Model m )
	{
		for( int y = 0; y < 9; ++y )
		{
			for( int x = 0; x < 9; ++x )
			{
				fields[y][x].getField().setBackground( Color.WHITE );
				fields[y][x].setNumber( m.getNumberGame( x, y ), false );
			}
		}
	}

	/**
	 * Maluje planszę na odpowiednie kolory, po naciśnięciu przycisku CHECK.
	 * Zielony kolor oznacza dobry ruch, a czerwone błąd.
	 * 
	 * @param m
	 *            Obiekt modelu gry.
	 */
	private void setGameCheck( Model m )
	{
		for( int y = 0; y < 9; ++y )
		{
			for( int x = 0; x < 9; ++x )
			{
				fields[y][x].getField().setBackground( Color.WHITE );
				if( fields[y][x].getField().getForeground().equals( Color.BLUE ) )
				{
					fields[y][x].getField().setBackground(
							m.getCheck( x, y ) ? Color.GREEN : Color.RED );
				}
			}
		}
	}

	/**
	 * Funkcja zwracająca panel planszy gry.
	 * 
	 * @return plansza gry
	 */

	public JPanel getBoard()
	{
		return board;
	}

	/**
	 * Metoda zwracająca tablicę pól.
	 * @return tablica pól.
	 */
	public Field[][] getFields()
	{
		return fields;
	}

	/**
	 * Ustawia kontrolery dla wszystkich paneli.
	 * 
	 * @param gbc
	 *            Kontroler planszy gry.
	 */
	public void setController( GameBoardController gbc )
	{
		for( int y = 0; y < 3; ++y )
		{
			for( int x = 0; x < 3; ++x )
			{
				panels[y][x].addMouseListener( gbc );
			}
		}
	}

	private Field[][] fields; // tablica pól gry
	private JPanel[][] panels; // panele reprezentujące "duże" kwadraty na
								// planszy (3x3)
	private JPanel board; // plansza gry
}
