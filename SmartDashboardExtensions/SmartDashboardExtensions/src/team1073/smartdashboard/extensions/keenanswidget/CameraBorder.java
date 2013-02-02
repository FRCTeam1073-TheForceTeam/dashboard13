/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extensions.keenanswidget;

import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Canvas;
import java.awt.Color;
import javax.swing.JFrame;


/**
 *
 * @author Keenan
 */
public class CameraBorder extends Widget{
   public CameraBorder (int lag) {
       this.lag = lag;
   }
   private int lag;
   private final int LOW = 20;
   @Override
   public void paint (Graphics graphics) {
   Color color = lag > LOW ? Color.RED : Color.GREEN;
   graphics.setColor(color);
   graphics.drawRect(90,80,250,250);
   }
    
    public static void main (String[] args) {
        CameraBorder canvas = new CameraBorder (1);
        JFrame frame = new JFrame ();
        frame.setSize (450, 450);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(canvas);
        frame.setVisible(true);
    }

    @Override
    public void setValue(Object o) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void init() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void propertyChanged(Property prprt) {
        throw new UnsupportedOperationException("Not supported yet.");
    }
   
}
    
