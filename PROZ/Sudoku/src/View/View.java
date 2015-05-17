package View;

import java.awt.BorderLayout;
import javax.swing.JFrame;

import Model.Model;

/**
 * 
 */

/**
 * Klasa reprezentująca widok gry Sudoku. Opakowuje klasy ButtonPanel oraz GameBoard.
 *
 */
public class View
{
	
	/**
	 * Konstruktor domyślny widoku, tworzy ButtonPanel oraz GameBoard.
	 */
	public View()
	{
		frame = new JFrame( "Sudoku" );
		frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		frame.getContentPane().setLayout( new BorderLayout() );
		
		buttonpanel = new ButtonPanel();
		gameboard = new GameBoard();
		
		frame.add( buttonpanel.getPanel(), BorderLayout.EAST );
		
		gameboard.setNewGame( Model.getInstance() );
		
		frame.add( gameboard.getBoard() );
		
		frame.setResizable( false );
		frame.pack();
		frame.setLocationRelativeTo( null );
		frame.setVisible( true );
		Model.getInstance().printGame();
	}
	
	/**
	 * Metoda zwracająca prywatny obiekt ButtonPanel
	 * @return ButtonPanel
	 */
	public ButtonPanel getButtonPanel()
	{
		return buttonpanel;
	}
	
	/**
	 * Metoda zwracająca prywatny obiekt GameBoard.
	 * @return GameBoard
	 */
	public GameBoard getGameBoard()
	{
		return gameboard;
	}
	
	private JFrame frame;		// okno programu
	private ButtonPanel buttonpanel;	// panel z przyciskami
	private GameBoard gameboard;	// plansza gry
}
