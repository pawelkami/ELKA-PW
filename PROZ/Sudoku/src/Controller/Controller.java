package Controller;
import Model.Model;
import View.View;

/**
 * Klasa reprezentująca kontroler. Opakowuje klasy ButtonController oraz
 * GameBoardController.
 * 
 * @author kamienny
 */
public class Controller
{
	public Controller( View v )
	{
		view = v;
		buttoncontroller = new ButtonController( view );
		gameboardcontroller = new GameBoardController( view );
		view.getButtonPanel().setController( buttoncontroller );
		view.getGameBoard().setController( gameboardcontroller );
		Model.getInstance().addObserver( view.getButtonPanel() );
		Model.getInstance().addObserver( view.getGameBoard() );
	}

	/**
	 * Metoda zwracająca kontroler przycisków.
	 * 
	 * @return ButtonController
	 */
	public ButtonController getButtonController()
	{
		return buttoncontroller;
	}

	
	/**
	 * Metoda zwracająca prywatny obiekt kontrolera planszy gry.
	 * @return	GameBoardController
	 */
	public GameBoardController getGameBoardController()
	{
		return gameboardcontroller;
	}

	private View view; // widok
	private ButtonController buttoncontroller; // kontroler przycisków
	private GameBoardController gameboardcontroller; // kontroler planszy
}
