/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extensions.keenanswidget;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.properties.BooleanProperty;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Canvas;
import javax.swing.JFrame;


public class CameraBorder extends Widget{
    private boolean isRed;
    public final BooleanProperty newVal = new BooleanProperty(this, "Is Red", false);
    
    public CameraBorder () {isRed = false;}
    
    @Override
    protected void paintComponent (Graphics graphics) {
        if(!isRed)
            graphics.setColor(Color.BLACK);
        else
            graphics.setColor(Color.RED);
        graphics.fillRect(10, 10, 680, 520);
    }
    /*
    public static void main (String[] args) {
        CameraBorder canvas = new CameraBorder ();
        JFrame frame = new JFrame ();
        frame.setSize (450, 450);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(canvas);
        frame.setVisible(true);
    }
*/
 
    public void setValue(Object o) {
       boolean b = isRed;
       try{b = (Boolean) o;}
       catch(Exception e){}
       isRed = b;
       repaint();
    }

    @Override
    public void init() {
       isRed = false;
       setPreferredSize(new Dimension(50,50));
    }

    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }
   
}
    
