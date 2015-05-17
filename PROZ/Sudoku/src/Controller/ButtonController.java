package Controller;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import Model.Model;
import View.GameTimer;
import View.View;

/**
 * Klasa przyjmujaca zdarzenia od przyciskow.
 * 
 */
public class ButtonController implements ActionListener
{
	/**
	 * 
	 * @param v
	 *            Widok uzywany w danej rozgrywce.
	 */
	public ButtonController(View v)
	{
		view = v;
	}


	@Override
	public void actionPerformed( ActionEvent e )
	{
		if( e.getActionCommand().equals( "New" ) )
		{
			view.getButtonPanel().setWinClear();
			Model.getInstance().newGame();
			GameTimer.getInstance().resetTimer();
			GameTimer.getInstance().startTimer();
		}
		else if( e.getActionCommand().equals( "Check" ) )
			Model.getInstance().checkGame();
		else if( e.getActionCommand().equals( "Exit" ) )
			System.exit( 0 );
		else
			Model.getInstance().setNumber( Integer.parseInt( e.getActionCommand() ) );

	}

	private View view;
}
