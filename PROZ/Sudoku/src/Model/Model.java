package Model;

import java.util.Collections;
import java.util.Observable;
import java.util.ArrayList;
import java.util.List;

/**
 * Klasa reprezentuje grę Sudoku. Zawiera metodę generującą rozwiązanie, nową
 * rozgrywkę oraz sprawdzanie poprawności rozwiązania.
 * 
 * 
 */

public class Model extends Observable
{
	/**
	 * Konstruktor, tworzy nową grę.
	 */
	private Model()
	{
		newGame();
		check = new boolean[9][9];
	}

	/**
	 * Singleton
	 * 
	 * @return instancja obiektu
	 */

	public static Model getInstance()
	{
		if( instance == null )
		{
			instance = new Model();
		}
		return instance;
	}

	/**
	 * Funkcja generująca nową grę.
	 */
	public void newGame()
	{
		solution = generateSolution( new int[9][9], 0 );
		game = generateGame( copyGame( solution ) );
		setChanged();
		notifyObservers( ActionEnumerate.NEW_GAME );
	}

	/**
	 * Metoda generująca nowe rozwiązanie gry.
	 * 
	 * @param aGame
	 *            Gra do wypełnienia
	 * @param index
	 *            Indeks, który dodajemy i sprawdzamy. Powinno się zaczynać od
	 *            0.
	 * @return Wypełniona gra. null w przypadku błędu.
	 */

	private int[][] generateSolution( int[][] aGame, int index )
	{
		if( index > 80 )
			return aGame;

		int xCoordinate = index % 9;
		int yCoordinate = index / 9;

		List<Integer> possibleNumbers = new ArrayList<Integer>();

		for( int i = 1; i <= 9; ++i )
		{
			possibleNumbers.add( i );
		}

		Collections.shuffle( possibleNumbers );

		while( possibleNumbers.size() > 0 )
		{
			int number = getPossibleNumber( aGame, xCoordinate, yCoordinate, possibleNumbers );

			if( number == -1 )
				return null;

			aGame[yCoordinate][xCoordinate] = number;

			int[][] result = generateSolution( aGame, index + 1 );

			if( result != null )
				return result;

			aGame[yCoordinate][xCoordinate] = 0;
		}

		return null;
	}

	/**
	 * Metoda zwracająca numer, który należy wstawić w dane pole rozwiązania
	 * gry.
	 * 
	 * @param aGame
	 *            Plansza gry do wypełnienia.
	 * @param x
	 *            Współrzędna x miejsca pod którą zamierzamy wstawić nową
	 *            liczbę.
	 * @param y
	 *            Współrzędna y miejsca pod które zamierzamy wstawić nową
	 *            liczbę.
	 * @param possibleNumbers
	 *            Lista możliwych liczb do wstawienia w dane pole.
	 * @return Zwraca znaleziony numer, który należy wstawić do gry. W przypadku
	 *         błędu zwraca -1.
	 */
	private int getPossibleNumber( int[][] aGame, int x, int y, List<Integer> possibleNumbers )
	{
		while( possibleNumbers.size() > 0 )
		{
			int number = possibleNumbers.remove( 0 );
			if( checkX( aGame, x, number ) && checkY( aGame, y, number )
					&& checkSquare( aGame, x, y, number ) )
			{
				return number;
			}
		}

		return -1;
	}

	/**
	 * Metoda sprawdza czy dany numer został już wstawiony w danej kolumnie.
	 * 
	 * @param aGame
	 *            Plansza gry do wypełnienia.
	 * @param x
	 *            Współrzędna kolumny, którą badamy.
	 * @param number
	 *            Numer, który sprawdzamy.
	 * @return Zwraca true jeśli możemy wstawić, false w przeciwnym wypadku.
	 */

	private boolean checkX( int[][] aGame, int x, int number )
	{
		for( int i = 0; i < 9; ++i )
		{
			if( aGame[i][x] == number )
				return false;
		}
		return true;
	}

	/**
	 * Metoda sprawdza czy dany numer został już wstawiony w danym rzędzie.
	 * 
	 * @param aGame
	 *            Plansza gry do wypełnienia.
	 * @param y
	 *            Współrzędna rzędu.
	 * @param number
	 *            Numer, który sprawdzamy.
	 * @returnimport nl.elridge.sudoku.controller.SudokuController; import
	 *               nl.elridge.sudoku.model.Game; import
	 *               nl.elridge.sudoku.model.UpdateAction; Zwraca true jeśli
	 *               możemy wstawić, false w przeciwnym wypadku.
	 */

	private boolean checkY( int[][] aGame, int y, int number )
	{
		for( int i = 0; i < 9; ++i )
		{
			if( aGame[y][i] == number )
				return false;
		}
		return true;
	}

	/**
	 * Metoda sprawdza czy dany numer został już wstawiony w danym bloku.
	 * 
	 * @param aGame
	 *            Plansza gry do wypełnienia.
	 * @param x
	 *            Współrzędna kolumny.
	 * @param y
	 *            Współrzędna rzędu.
	 * @param number
	 *            Numer, który sprawdzamy.
	 * @return Zwraca true jeśli możemy wstawić, false w przeciwnym wypadku.
	 */

	private boolean checkSquare( int[][] aGame, int x, int y, int number )
	{
		int xBlock = x < 3 ? 0 : x < 6 ? 3 : 6;
		int yBlock = y < 3 ? 0 : y < 6 ? 3 : 6;

		for( int i = xBlock; i < xBlock + 3; i++ )
		{
			for( int j = yBlock; j < yBlock + 3; j++ )
			{
				if( aGame[j][i] == number )
					return false;
			}
		}

		return true;
	}

	/**
	 * Metoda sprawdza dane wejściociowe wraz z rozwiązaniem gry i ustawia
	 * tablicę check[][] oraz powiadamia obserwatorów o zmianie co powoduje
	 * zmiane kolorów pól. 
	 */
	public void checkGame()
	{
		setCheck();
		setChanged();
		notifyObservers( ActionEnumerate.CHECK );
	}

	/**
	 * Ustawia tablicę check[][]
	 */

	public void setCheck()
	{
		for( int i = 0; i < 9; i++ )
		{
			for( int j = 0; j < 9; j++ )
			{
				check[i][j] = ( game[i][j] == solution[i][j] );
			}
		}
	}

	/**
	 * Metoda generuje nową grę na podstawie podanego jej rozwiązania.
	 * 
	 * @param aGame
	 *            Gra, która zostanie wygenerowana, należy podać jako parametr
	 *            rozwiązanie(solution).
	 * @return Zwraca wygenerowaną grę.
	 */

	private int[][] generateGame( int[][] aGame )
	{
		List<Integer> indexes = new ArrayList<Integer>();

		for( int i = 0; i < 81; i++ )
			indexes.add( i );

		Collections.shuffle( indexes );
		while( indexes.size() > 0 )
		{
			int index = indexes.remove( 0 );

			int xCoordinate = index % 9;
			int yCoordinate = index / 9;

			int tmp = aGame[yCoordinate][xCoordinate];
			aGame[yCoordinate][xCoordinate] = 0;

			if( !isCorrectGame( aGame ) )
				aGame[yCoordinate][xCoordinate] = tmp;
		}

		return aGame;
	}

	/**
	 * Sprawdza czy podana gra jest poprawna.
	 * 
	 * @param aGame
	 *            Gra do sprawdzenia.
	 * @return True, jeśli gra jest poprawna, false w przeciwnym wypadku.
	 */
	private boolean isCorrectGame( int[][] aGame )
	{
		return isCorrectGame( aGame, 0, new int[] { 0 } );
	}

	/**
	 * Sprawdza czy podana gra jest poprawna. Należy używać drugiej metody
	 * isCorrectGame. Może być tylko jedno rozwiązanie.
	 * 
	 * @param aGame
	 *            Gra, którą sprawdzamy.
	 * @param index
	 *            Index, który w danej chwili sprawdzamy.
	 * @param howManySolutions
	 *            Liczba znalezionych rozwiązań. int[] zamiast int żeby wywołać
	 *            przez referencję.
	 * @return True, jeśli gra jest poprawna, false w przeciwnym przypadku.
	 */
	private boolean isCorrectGame( int[][] aGame, int index, int[] howManySolutions )
	{
		if( index > 80 )
			return ++howManySolutions[0] == 1;

		int xCoordinate = index % 9;
		int yCoordinate = index / 9;

		if( aGame[yCoordinate][xCoordinate] == 0 )
		{
			List<Integer> possibleNumbers = new ArrayList<Integer>();

			for( int i = 1; i <= 9; i++ )
			{
				possibleNumbers.add( i );
			}

			while( possibleNumbers.size() > 0 )
			{
				int number = getPossibleNumber( aGame, xCoordinate, yCoordinate, possibleNumbers );
				if( number == -1 )
					break;

				aGame[yCoordinate][xCoordinate] = number;

				if( !isCorrectGame( aGame, index + 1, howManySolutions ) )
				{
					aGame[yCoordinate][xCoordinate] = 0;
					return false;
				}

				aGame[yCoordinate][xCoordinate] = 0;
			}
		}
		else
		{
			if( !isCorrectGame( aGame, index + 1, howManySolutions ) )
				return false;
		}

		return true;
	}

	/**
	 * Funkcja sprawdzająca czy dany numer może być kandydatem w danym polu gry.
	 * 
	 * @param number
	 *            Sprawdzany numer
	 * @param index
	 *            Indeks pod którym ma być dany numer.
	 * @return True jeśli numer poprawny, false w przeciwnym wypadku.
	 */

	public boolean isNumberCandidate( int number, int index )
	{
		int x = index % 9;
		int y = index / 9;

		return ( game[y][x] == 0 ) && checkX( game, x, number ) && checkY( game, y, number )
				&& checkSquare( game, x, y, number );
	}

	/**
	 * Metoda kopiująca rozwiązanie do gry.
	 * 
	 * @param aGame
	 *            Tablica, którą chcemy skopiować.
	 * @return Zwraca tablicę, do której skopiowaliśmy.
	 */

	private int[][] copyGame( int[][] aGame )
	{
		int[][] result = new int[9][9];
		for( int i = 0; i < 9; i++ )
		{
			for( int j = 0; j < 9; j++ )
			{
				result[i][j] = aGame[i][j];
			}
		}
		return result;
	}

	/**
	 * Metoda ustawiająca ostatni wybrany numer.
	 * 
	 * @param number
	 *            Liczba, która została wybrana przez użytkownika.
	 */
	public void setNumber( int number )
	{
		selectedNumber = number;
	}

	/**
	 * Metoda ustawiająca tablicę gry na wybrany numer.
	 * 
	 * @param x
	 *            współrzędna x.
	 * @param y
	 *            współrzędna y.
	 */
	public void setField( int x, int y )
	{
		game[y][x] = selectedNumber;
	}

	/**
	 * Metoda zwracająca ostatni wybrany numer przez użytkownika.
	 * 
	 * @return Numer wybrany przez użytkownika.
	 */
	public int getSelectedNumber()
	{
		return selectedNumber;
	}

	/**
	 * Metoda zwracająca numer stojący pod tymi współrzędnymi w grze.
	 * 
	 * @param x
	 *            wspolrzedna x
	 * @param y
	 *            wspolrzedna y
	 * @return numer stojacy w tablicy game pod tymi wspolrzednymi
	 */
	public int getNumberGame( int x, int y )
	{
		return game[y][x];
	}

	/**
	 * Zwraca czy pole jest poprawne czy nie.
	 * 
	 * @param x
	 *            Współrzędna x.
	 * @param y
	 *            Współrzędna y.
	 * @return czy pole jest poprawne.
	 */
	public boolean getCheck( int x, int y )
	{
		return check[y][x];
	}

	/**
	 * Sprawdzamy całą grę pod kątem wygranej.
	 * 
	 * @return jeśli gracz wygrał to true, w przeciwnym wypadku false.
	 */
	public boolean checkWin()
	{
		setCheck();

		for( int x = 0; x < 9; ++x )
		{
			for( int y = 0; y < 9; ++y )
			{
				if( !check[y][x] )
					return false;
			}
		}
		return true;
	}

	public void printGame()
	{
		for( int i = 0; i < 9; i++ )
		{
			for( int j = 0; j < 9; j++ )
			{
				System.out.print( solution[i][j] );
			}
			System.out.println();
		}
	}

	public void printGame1()
	{
		for( int i = 0; i < 9; i++ )
		{
			for( int j = 0; j < 9; j++ )
			{
				System.out.print( game[i][j] );
			}
			System.out.println();
		}
	}

	private static Model instance;
	private int[][] solution;
	private int[][] game;
	private boolean[][] check;
	private int selectedNumber;
}
