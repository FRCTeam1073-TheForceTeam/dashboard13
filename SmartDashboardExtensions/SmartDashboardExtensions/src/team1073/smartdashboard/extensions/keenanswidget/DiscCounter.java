/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extensions.keenanswidget;

import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Canvas;
import javax.swing.JFrame;


/**
 *
 * @author Keenan
 */
public class DiscCounter extends Widget{
    public DiscCounter () {
}
    @Override
    public void paint (Graphics graphics) {
        graphics.setColor (Color.BLACK);
        graphics.drawRect(60,80,330,100);
        graphics.setColor(Color.RED);
        graphics.drawOval(70, 95, 70, 70);
        graphics.setColor(Color.RED);
        graphics.drawOval(150, 95, 70, 70);
        graphics.setColor(Color.RED);
        graphics.drawOval(230, 95, 70, 70);
        graphics.setColor(Color.RED);
        graphics.drawOval(310, 95, 70, 70);
        graphics.setColor(Color.BLACK);
        graphics.drawString("Team 1073 Disc Counter", 160, 50);
        

        
        
        
    }
    
    public static void main (String[] args) {
        DiscCounter canvas = new DiscCounter ();
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
    
