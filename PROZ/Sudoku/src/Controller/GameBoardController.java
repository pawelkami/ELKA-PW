package Controller;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.Color;
import java.awt.Component;
import javax.swing.JPanel;
import javax.swing.JLabel;

import Model.Model;
import View.Field;
import View.GameTimer;
import View.View;

/**
 * Klasa reprezentująca kontroler planszy gry.
 * 
 * @author kamienny
 * 
 */
public class GameBoardController implements MouseListener
{
	/**
	 * Konstruktor domyślny.
	 */
	public GameBoardController(View v)
	{
		view = v;
	}

	/**
	 * Obsługa zdarzeń generowanych przez naciśnięcie myszki.
	 */
	@Override
	public void mousePressed( MouseEvent e )
	{
		Component component = ( (JPanel) e.getSource() ).getComponentAt( e.getPoint() );
		if( component instanceof JLabel )
		{
			JLabel label = (JLabel) component;
			Field field = findField( label );

			if( field == null )
			{
				return;
			}

			int x = field.getFieldX();
			int y = field.getFieldY();

			// lewy przycisk myszy - ustawiamy pole
			if( e.getButton() == MouseEvent.BUTTON1
					&& ( ( Model.getInstance().getNumberGame( x, y ) == 0 ) || field.getField()
							.getForeground().equals( Color.BLUE ) ) )
			{
				int number = Model.getInstance().getSelectedNumber();

				if( number == -1 )
					return;

				Model.getInstance().setNumber( number );
				Model.getInstance().setField( x, y );
				field.setNumber( number, true );

				if( Model.getInstance().checkWin() )
				{
					view.getButtonPanel().setWin(); // ustawiamy komunikat o
														// wygranej
					GameTimer.getInstance().stopTimer();
				}
				else
				{
					view.getButtonPanel().setWinClear(); // czyscimy
																// komunikat o
																// wygranej
				}
			}
			else if( e.getButton() == MouseEvent.BUTTON3
					&& !( field.getField().getForeground().equals( Color.BLACK ) ) ) // prawy
																						// przycisk
																						// myszy
																						// -
																						// zerujemy
																						// pole
			{
				Model.getInstance().setNumber( 0 ); // ustawiamy wybrany numer
				Model.getInstance().setField( x, y ); // ustawiamy pole
				field.setNumber( 0, false ); // wyswietlamy pole
				view.getButtonPanel().setWinClear();
			}
		}

	}

	/**
	 * Metoda szukająca danego pola na podstawie podanego JLabel.
	 * 
	 * @param label
	 *            JLabel należący do pola.
	 * @return Znalezione pole(Field), w przypadku nie znalezienia zwraca null.
	 */

	public Field findField( JLabel label )
	{
		Field[][] fields = view.getGameBoard().getFields();
		for( int x = 0; x < 9; ++x )
		{
			for( int y = 0; y < 9; ++y )
			{
				if( label == fields[y][x].getField() )
					return fields[y][x];
			}
		}

		return null;
	}

	/*
	 * Są bo być muszą ze względu na implementowanie interfejsu MouseListener.
	 */
	public void mouseClicked( MouseEvent e )
	{
	}

	public void mouseEntered( MouseEvent e )
	{
	}

	public void mouseExited( MouseEvent e )
	{
	}

	public void mouseReleased( MouseEvent e )
	{
	}

	private View view;
}
