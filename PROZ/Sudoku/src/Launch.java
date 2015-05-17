import javax.swing.UIManager;

import Controller.Controller;
import Model.Model;
import View.View;

/**
 * Klasa tworząca wszystkie obiekty i łącząca je ze sobą. Zawiera również metodę
 * main().
 * 
 */
public class Launch
{
	/**
	 * Funkcja main uruchamiająca całą grę i tworząca całe MVC.
	 * @param args
	 */
	public static void main( String[] args )
	{
		try
		{
			UIManager.setLookAndFeel( UIManager.getSystemLookAndFeelClassName() );
		}
		catch( Exception ex )
		{
			ex.printStackTrace();
		}

		Model.getInstance();
		new Controller( new View() );
	}
}
