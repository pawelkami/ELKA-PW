package View;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.SwingConstants;

/**
 * Klasa reprezentująca pole gry.
 * 
 */
public class Field
{
	/**
	 * Konstruktor pola planszy.
	 */
	public Field( int xCord, int yCord )
	{
		field = new JLabel( "", SwingConstants.CENTER );
		x = xCord;
		y = yCord;

		field.setMinimumSize( new Dimension( 40, 40 ) );
		field.setPreferredSize( new Dimension( 40, 40 ) );
		field.setMaximumSize( new Dimension( 40, 40 ) );
		field.setBorder( BorderFactory.createLineBorder( Color.BLACK ) );
		field.setFont( new Font( Font.DIALOG, Font.PLAIN, 20 ) );
		field.setOpaque( true );
	}

	/**
	 * Metoda ustawiająca numer na polu planszy.
	 * 
	 * @param number
	 *            numer do wstawienia.
	 * @param ifUser
	 *            czy wstawia użytkownik czy komputer.
	 */
	public void setNumber( int number, boolean ifUser )
	{
		field.setForeground( ifUser ? Color.BLUE : Color.BLACK );
		field.setText( number > 0 ? number + "" : "" );
	}

	/**
	 * Metoda zwracająca współrzędna X.
	 * 
	 * @return Współrzędna X pola.
	 */
	public int getFieldX()
	{
		return x;
	}

	/**
	 * Metoda zwracająca współrzędna Y pola.
	 * 
	 * @return Współrzędna Y pola.
	 */
	public int getFieldY()
	{
		return y;
	}

	public JLabel getField()
	{
		return field;
	}

	/**
	 * x - wspolrzedna X pola na planszy y - wspolrzedna Y pola na planszy
	 */
	private int x;
	private int y;
	private JLabel field;

}
