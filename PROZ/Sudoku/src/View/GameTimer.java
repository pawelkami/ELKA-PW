package View;
import javax.swing.JLabel;
import java.util.Timer;
import java.util.TimerTask;
import java.awt.*;

/**
 * Klasa reprezentująca zegar odliczający czas gry.
 * 
 */
public class GameTimer
{

	/**
	 * Konstruktor domyślny. Ustawia timerLabel, wyświetlający czas na "0:00"
	 * oraz tworzy Timer i go uruchamia.
	 */
	private GameTimer()
	{
		timerLabel = new JLabel( "0:00" );
		timerLabel.setFont( new Font( Font.DIALOG, Font.BOLD, 43 ) );
		timerLabel.setForeground( Color.BLACK );
		flag = true;
		timer = new Timer();
		resetTimer();
		makeTimer();

	}

	/**
	 * Uruchamia zegar i rozpoczyna odliczanie czasu.
	 */
	private void makeTimer()
	{
		timer.scheduleAtFixedRate( new TimerTask()
		{
			public void run()
			{
				if( flag ) // flaga odpowiedzialna za to czy timer ma stać w
							// miejscu czy odliczać czas.
				{
					timerLabel.setText( getTime() );
					++interval;
				}
			}
		}, 1000, 1000 );
	}

	/**
	 * Ustawia flagę na true(zegar rusza).
	 */
	public void startTimer()
	{
		flag = true;
	}

	/**
	 * Metoda zwracająca pole, na którym jest wyświetlany zegar.
	 * 
	 * @return timerLabel, który wyświetla zegar.
	 */
	public JLabel getTimerLabel()
	{
		return timerLabel;
	}

	/**
	 * Ustawia flagę na false(zatrzymuje zegar).
	 */
	public void stopTimer()
	{
		flag = false;
	}

	/**
	 * Zerowanie zegaru.
	 */
	public void resetTimer()
	{
		interval = 0;
	}

	/**
	 * Metoda formatująca upłynięty czas na String w formacie "m:ss".
	 * 
	 * @return sformatowany tekst "m:ss".
	 */
	private final String getTime()
	{
		int minutes = interval / 60;
		int seconds = interval % 60;

		return ( seconds > 9 ? minutes + ":" + seconds : minutes + ":0" + seconds );
	}

	/**
	 * Singleton.
	 * 
	 * @return zwraca instancję obiektu.
	 */
	public static GameTimer getInstance()
	{
		if( instance == null )
		{
			instance = new GameTimer();
		}

		return instance;
	}

	private boolean flag; // true - zegar idzie do przodu, false - stoi
	private static JLabel timerLabel; // pole wyświetlające czas
	static int interval; // ile czasu upłynęło
	private static Timer timer; // Timer
	private static GameTimer instance; // instancja obiektu
}
