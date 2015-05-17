package View;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.util.Observable;
import java.util.Observer;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JToggleButton;
import javax.swing.JLabel;

import Controller.ButtonController;
import Model.ActionEnumerate;

/**
 * Klasa reprezentująca widok - panel z przyciskami.
 * 
 */

public class ButtonPanel implements Observer
{

	/**
	 * Tworzenie obiektu reprezentującego panel z przyciskami sterującymi
	 * przebiegiem gry.
	 */
	public ButtonPanel()
	{
		panel = new JPanel( new BorderLayout() );

		JPanel pnlAlign = new JPanel();
		pnlAlign.setLayout( new BoxLayout( pnlAlign, BoxLayout.PAGE_AXIS ) );
		panel.add( pnlAlign, BorderLayout.NORTH );

		JPanel pnlOptions = new JPanel( new FlowLayout( FlowLayout.LEADING ) );
		pnlOptions.setBorder( BorderFactory.createTitledBorder( " Options " ) );
		pnlAlign.add( pnlOptions );

		btnNew = new JButton( "New" );
		btnNew.setMinimumSize( new Dimension( 70, 35 ) );
		btnNew.setPreferredSize( new Dimension( 70, 35 ) );
		btnNew.setMaximumSize( new Dimension( 70, 35 ) );
		btnNew.setFocusable( false );
		pnlOptions.add( btnNew );

		btnCheck = new JButton( "Check" );
		btnCheck.setMinimumSize( new Dimension( 70, 35 ) );
		btnCheck.setPreferredSize( new Dimension( 70, 35 ) );
		btnCheck.setMaximumSize( new Dimension( 70, 35 ) );
		btnCheck.setFocusable( false );
		pnlOptions.add( btnCheck );

		btnExit = new JButton( "Exit" );
		btnExit.setMinimumSize( new Dimension( 70, 35 ) );
		btnExit.setPreferredSize( new Dimension( 70, 35 ) );
		btnExit.setMaximumSize( new Dimension( 70, 35 ) );
		btnExit.setFocusable( false );
		pnlOptions.add( btnExit );

		JPanel pnlNumbers = new JPanel();
		pnlNumbers.setLayout( new GridLayout( 3, 3 ) );
		pnlNumbers.setBorder( BorderFactory.createTitledBorder( " Numbers " ) );
		pnlAlign.add( pnlNumbers );

		bgNumbers = new ButtonGroup();
		tgNumbers = new JToggleButton[9];
		for( int i = 0; i < 9; ++i )
		{
			tgNumbers[i] = new JToggleButton( "" + ( i + 1 ) );
			tgNumbers[i].setMinimumSize( new Dimension( 50, 50 ) );
			tgNumbers[i].setPreferredSize( new Dimension( 50, 50 ) );
			tgNumbers[i].setMaximumSize( new Dimension( 50, 50 ) );
			tgNumbers[i].setFocusable( false );
			bgNumbers.add( tgNumbers[i] );
			pnlNumbers.add( tgNumbers[i] );
		}

		JPanel pnlText = new JPanel();
		pnlAlign.add( pnlText );
		statusText = new JLabel( "             " );
		statusText.setFont( new Font( Font.DIALOG, Font.BOLD, 49 ) );
		statusText.setForeground( Color.RED );
		pnlText.add( statusText );

		pnlAlign.add( GameTimer.getInstance().getTimerLabel() );

	}

	/**
	 * Ustawia komunikat o wygranej
	 */

	public void setWin()
	{
		statusText.setText( "SOLVED" );
	}

	/**
	 * Zeruje komunikat o wygranej.
	 */

	public void setWinClear()
	{
		statusText.setText( "             " );
	}

	/**
	 * Funkcja jest wywoływana kiedy obserwowany obiekt zmieni stan.
	 */
	@Override
	public void update( Observable arg0, Object arg1 )
	{
		switch( (ActionEnumerate) arg1 )
		{
			case NEW_GAME:
			case CHECK:
				bgNumbers.clearSelection();
				break;
		}

	}

	/**
	 * Funkcja ustawiająca kontrolery dla przycisków należących do ButtonPanel.
	 * 
	 * @param bc
	 *            Kontroler przycisków.
	 */

	public void setController( ButtonController bc )
	{
		btnNew.addActionListener( bc );
		btnCheck.addActionListener( bc );
		btnExit.addActionListener( bc );

		for( int i = 0; i < 9; ++i )
		{
			tgNumbers[i].addActionListener( bc );
		}
	}

	/**
	 * Funkcja zwracająca panel należący do obiektu ButtonPanel.
	 * 
	 * @return panel
	 */

	public JPanel getPanel()
	{
		return panel;
	}

	private JPanel panel; // panel na buttony
	private JButton btnNew, btnCheck, btnExit; // buttony odpowiedzialne za nową
												// grę, sprawdzenie stanu gry
	private JLabel statusText; // oraz za wyjście z gry
	private ButtonGroup bgNumbers; // grupa guzików z cyferkami
	private JToggleButton[] tgNumbers; // przyciski z cyferkami

}